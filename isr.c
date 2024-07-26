#include "isr.h"
#include "idt.h"
#include "io.h"
#include <stdint.h>

// Array of ISR handlers
isr_t interrupt_handlers[256];

// External declarations for ISRs and IRQs
extern void isr0();
extern void isr1();
extern void irq0();
extern void irq1();

// ISR Handler
void isr_handler(registers_t regs) {
    monitor_write("Interrupt: ");
    monitor_write_hex(regs.int_no);
    monitor_write("\n");
}

void irq_handler(registers_t regs) {
    if (regs.int_no == 32) {
        timer_handler(regs);
    } else if (regs.int_no == 33) {
        keyboard_handler(regs);
    }
}

// Timer and Keyboard Handlers
void timer_handler(registers_t regs) {
    monitor_write("Timer interrupt triggered!\n");
}

void keyboard_handler(registers_t regs) {
    monitor_write("Keyboard interrupt triggered!\n");
}

// Install ISRs
void isr_install() {
    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    //idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
}

// Install IRQs
void irq_install() {
    idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);  // IRQ0 - Timer
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);  // IRQ1 - Keyboard
}
