.globl idt_flush
idt_flush:
    lidt 4(%esp)
    sti
    ret
