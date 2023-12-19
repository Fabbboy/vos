#pragma once
#include <stdbool.h>
#include <stdint.h>
#define GDT_CODE_SEGMENT 0x08
#define GDT_DATA_SEGMENT 0x10

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
  uintptr_t base; // The address of the first gdt_entry_t struct.
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

void init_gdt();
void __attribute__((cdecl))
gdt_load(gdt_descriptor_t *gdt_descriptor, uint16_t code_segment,
         uint16_t data_segment);

extern gdt_entry_t g_GDT[];
extern gdt_descriptor_t g_GDTDescriptor;
bool verify_gdt();