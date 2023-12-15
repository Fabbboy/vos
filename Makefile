OUTDIR=dist
KERNEL=src/kernel/
GRUB_CFG=grub.cfg

all: clean prepare build

prepare:
	@mkdir -p $(OUTDIR)

build:
	@make -C $(KERNEL)
	@grub-mkrescue -o $(OUTDIR)/os.iso

clean:
	@rm -rf $(OUTDIR)
	@make -C $(KERNEL) clean

run:
	@qemu-system-i386 -cdrom $(OUTDIR)/os.iso -m 512M
