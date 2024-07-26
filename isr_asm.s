.global isr0
.type isr0, @function
isr0:
    pusha
    call isr_handler
    popa
    iret

// IRQ0
.global irq0
.type irq0, @function
irq0:
    pusha
    movb $0x20, %al
    outb %al, $0x20
    movb $0x20, %al
    outb %al, $0xA0
    popa
    iret