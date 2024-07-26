# Cross-compiler tools
CC=i686-elf-gcc
AS=i686-elf-as
LD=i686-elf-ld

# Kernel source files
KERNEL_SRC=kernel.c
KERNEL_OBJ=$(KERNEL_SRC:.c=.o)
IDT_SRC=idt.c idt_asm.s
IDT_OBJ= idt.o idt_asm.o
ISR_SRC=isr.c isr_asm.s monitor.c gdt_asm.s gdt.c irq_asm.s pic.c
ISR_OBJ= isr.o isr_asm.o monitor.o gdt_asm.o gdt.o irq_asm.o pic.o

# Assembly source files
ASM_SRC=boot.s
ASM_OBJ=$(ASM_SRC:.s=.o)

# Linker script
LINKER_SCRIPT=linker.ld

# Output file
KERNEL_BIN=myos.bin

# Build the kernel
# Build the kernel
all: iso 
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir
	echo "done"
iso: $(KERNEL_BIN)

$(KERNEL_BIN): $(ASM_OBJ) $(KERNEL_OBJ) $(IDT_OBJ) $(ISR_OBJ)
	$(LD) -T $(LINKER_SCRIPT) -o $@ $(ASM_OBJ) $(KERNEL_OBJ) $(IDT_OBJ) $(ISR_OBJ)

%.o: %.c
	$(CC) -ffreestanding -c $< -o $@

%.o: %.s
	$(AS) $< -o $@

clean:
	rm -f *.o kernel.bin

run: all
	qemu-system-i386 -kernel $(KERNEL_BIN)

.PHONY: all clean run
