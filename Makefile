OUTDIR=boot
KERNEL=src/kernel/
GRUB_CFG=grub.cfg

all: clean prepare build

prepare:
	@mkdir -p $(OUTDIR)

build:
	@make -C $(KERNEL)
	@mkdir -p $(OUTDIR)/grub
	@cp $(GRUB_CFG) $(OUTDIR)/grub
	@grub-mkrescue  /usr/lib/grub/i386-pc -o $(OUTDIR)/os.iso ./

clean:
	rm -rf $(OUTDIR)
	@make -C $(KERNEL) clean

run:
	@qemu-system-x86_64 -cdrom $(OUTDIR)/os.iso 
