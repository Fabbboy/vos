# we build the kernel here
TARGET_CC = i686-linux-gnu-gcc
TARGET_ASM = nasm
TARGET_LD = ld

OUTKERNEL=../../boot/kernel.bin	
OUTDIR=../../boot

TARGET_ASMFLAGS = -f elf32
TARGET_CFLAGS = -m32 -nostdlib -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -c -DTARGET_X86
TARGET_LDFLAGS = -m elf_i386 -T linker.ld
OBJ_DIR=../obj

SOURCES_C=$(shell find ./ -type f -name '*.c')
SOURCES_ASM=$(shell find ./ -type f -name '*.asm')
OBJECTS_C=$(SOURCES_C:%.c=$(OBJ_DIR)/%.o)
OBJECTS_ASM=$(SOURCES_ASM:%.asm=$(OBJ_DIR)/%.o)
.PHONY: all clean prepare 

all: prepare build

## We build the kernel to object files to OBJ_DIR and then link it together using the linker script to ../dist/kernel.bin we dont use grub-mkrescue here
build: $(OBJECTS_ASM) $(OBJECTS_C)
	@$(TARGET_LD) $(TARGET_LDFLAGS) -o $(OUTKERNEL) $(OBJECTS_ASM) $(OBJECTS_C)
	@echo "Kernel built"

## We compile the C files to object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(TARGET_CC) $(TARGET_CFLAGS) $< -o $@
	@echo "Compiled "$<" successfully!"

## We compile the assembly files to object files
$(OBJ_DIR)/%.o: %.asm
	@mkdir -p $(@D)
	@$(TARGET_ASM) $(TARGET_ASMFLAGS) $< -o $@
	@echo "Assembled "$<" successfully!"

## We create the output directory
prepare:
	@mkdir -p $(OUTDIR)
	@mkdir -p $(OBJ_DIR)

## We clean the output directory and the object files
clean:
	@rm -rf $(OUTDIR)
	@rm -rf $(OBJ_DIR)
	@echo "Cleanup complete!"
