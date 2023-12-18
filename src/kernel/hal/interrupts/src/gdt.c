#include "../gdt.h"
#include <stdint.h>

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

gdt_descriptor_t g_GDTDescriptor = {
    sizeof(g_GDT) - 1, // Limit
    (intptr_t)g_GDT,   // Base
};

void init_gdt() {
  gdt_load(&g_GDTDescriptor, GDT_CODE_SEGMENT, GDT_DATA_SEGMENT);
}