#include "idt.h"

extern void idt_flush(uint32_t);

struct idt_entry idt[256];
struct idt_ptr idt_p __attribute__((aligned(16)));  // Ensure proper alignment

extern void irq0();  // Declare the IRQ0 handler
extern void irq1();  // Declare the IRQ1 handler

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_init(void) {
    idt_p.limit = (sizeof(struct idt_entry) * 256) - 1;
    idt_p.base = (uint32_t)&idt;

    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0); // Set default gate
    }

    idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E); // Timer
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E); // Keyboard

    asm volatile("lidt %0" :: "m"(idt_p));
}
