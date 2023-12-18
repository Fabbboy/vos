#include "../gdt.h"

typedef struct {
  uint16_t limit_low;  // The lower 16 bits of the limit.
  uint16_t base_low;   // The lower 16 bits of the base.
  uint8_t base_middle; // The next 8 bits of the base.
  uint8_t
      access; // Access flags, determine what ring this segment can be used in.
  uint8_t granularity; // Granularity of the segment.
  uint8_t base_high;   // The last 8 bits of the base.
} __attribute__((packed)) gdt_entry_t;

typedef struct {
  uint16_t limit; // The upper 16 bits of all selector limits.
  void *base;     // The address of the first gdt_entry_t struct.
} __attribute__((packed)) gdt_descriptor_t;

typedef enum {
  GDT_ACCESS_CODE_READABLE = 0x02,
  GDT_ACCESS_DATA_WRITABLE = 0x02,

  GDT_ACCESS_CODE_CONFORMING = 0x04,
  GDT_ACCESS_DATA_DIRECTION_NORMAL = 0x00,
  GDT_ACCESS_DATA_DIRECTION_DOWN = 0x04,

  GDT_ACCESS_DATA_SEGMENT = 0x10,
  GDT_ACCESS_CODE_SEGMENT = 0x18,

  GDT_ACCESS_DESCRIPTOR_TSS = 0x00,

  GDT_ACCESS_RING_0 = 0x00,
  GDT_ACCESS_RING_1 = 0x20,
  GDT_ACCESS_RING_2 = 0x40,
  GDT_ACCESS_RING_3 = 0x60,

  GDT_ACCESS_PRESENT = 0x80,

} gdt_access_flags_t;

typedef enum {
  GDT_FLAG_64_BIT = 0x20,
  GDT_FLAG_32_BIT = 0x40,
  GDT_FLAG_16_BIT = 0x00,

  GDT_FLAG_GRANULARITY_1B = 0x00,
  GDT_FLAG_GRANULARITY_4KB = 0x80,
} gdt_flags;

#define GDT_LIMIT_LOW(limit) ((limit)&0xFFFF)
#define GDT_BASE_LOW(base) ((base)&0xFFFF)
#define GDT_BASE_MIDDLE(base) (((base) >> 16) & 0xFF)
#define GDT_BASE_HIGH(base) (((base) >> 24) & 0xFF)
#define GDT_FLAGS_LIMIT_HIGH(flags, limit)                                     \
  (((flags)&0xF0) | (((limit) >> 16) & 0x0F))

#define GDT_ENTRY(base, limit, access, flags)                                  \
  {                                                                            \
    GDT_LIMIT_LOW(limit), GDT_BASE_LOW(base), GDT_BASE_MIDDLE(base), access,   \
        GDT_FLAGS_LIMIT_HIGH(flags, limit), GDT_BASE_HIGH(base)                \
  }

gdt_entry_t g_GDT[] = {
    // NULL
    GDT_ENTRY(0, 0, 0, 0),

    // Kernel Code
    GDT_ENTRY(0, 0xFFFFF,
              GDT_ACCESS_CODE_READABLE | GDT_ACCESS_CODE_SEGMENT |
                  GDT_ACCESS_PRESENT | GDT_ACCESS_RING_0,
              GDT_FLAG_32_BIT | GDT_FLAG_GRANULARITY_4KB),

    // Kernel Data
    GDT_ENTRY(0, 0xFFFFF,
              GDT_ACCESS_DATA_WRITABLE | GDT_ACCESS_DATA_SEGMENT |
                  GDT_ACCESS_PRESENT | GDT_ACCESS_RING_0,
              GDT_FLAG_32_BIT | GDT_FLAG_GRANULARITY_4KB),
};

gdt_descriptor_t g_GDTDescriptor = {sizeof(g_GDT) - 1, g_GDT};

void __attribute__((cdecl)) gdt_load(gdt_descriptor_t *gdt_descriptor, uint16_t code_selector, uint16_t data_selector);