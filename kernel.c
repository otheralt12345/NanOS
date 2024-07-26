#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "idt.h"
#include "isr.h"
#include "monitor.h"
#include "gdt.h"
#include "pic.h"
#include "io.h"
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) {
    // Initialize terminal interface
    monitor_initialize();

    // Initialize GDT, IDT, ISRs, and IRQs
    monitor_write("Initializing System.\n");
    monitor_write("Starting ADAM Proc\n");
    monitor_write("Loading global descriptor table.\n");
    gdt_init();

    monitor_write("Installing our interrupts\n");
    isr_install();
    irq_install();
    monitor_write("Loading interrupt descriptor table.\n");
    idt_init();
    monitor_write("Starting PIC.\n");
    pic_init();
    monitor_write("done\n\n");

    // Initialize PIT (Programmable Interval Timer) for timer interrupts
    uint32_t divisor = 1193180 / 1000; // PIT operates at 1.19318 MHz

    // Send the command byte to PIT
    outb(0x43, 0x36); // Channel 0, LSB followed by MSB, mode 2, binary mode

    // Send the frequency divisor to PIT
    outb(0x40, (uint8_t)(divisor & 0xFF)); // LSB
    outb(0x40, (uint8_t)((divisor >> 8) & 0xFF)); // MSB

    // Unmask IRQs
    outb(0x21, inb(0x21) & ~(1 << 0)); // Unmask IRQ0 (Timer)
    outb(0x21, inb(0x21) & ~(1 << 1)); // Unmask IRQ1 (Keyboard)


    monitor_write("Enabling interrupts.\n");
    //asm volatile("sti");
    monitor_write("Interrupts enabled.\n");
    while (true) {}
    /*
    uint32_t divisor = 1193180 / 1000; // PIT operates at 1.19318 MHz

    // Send the command byte
    outb(0x43, 0x36); // Channel 0, LSB followed by MSB, mode 2, binary mode

    // Send the frequency divisor
    outb(0x40, (uint8_t)(divisor & 0xFF)); // LSB
    outb(0x40, (uint8_t)((divisor >> 8) & 0xFF)); // MSB

    // Unmask IRQ0 (Timer) and IRQ1 (Keyboard)
    outb(0x21, inb(0x21) & ~(1 << 0)); // Unmask IRQ0
    outb(0x21, inb(0x21) & ~(1 << 1)); // Unmask IRQ1

    // Enable interrupts
    asm volatile("sti");

    // Output to indicate initialization is complete
    monitor_write("Hello, kernel World!\n");*/
    while (1) {}
}