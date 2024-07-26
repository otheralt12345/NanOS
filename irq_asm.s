.section .text
// IRQ1
.global irq1
.type irq1, @function
irq1:
    pusha
    movb $0x20, %al
    outb %al, $0x20
    popa
    iret
