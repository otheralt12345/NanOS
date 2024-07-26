#ifndef ISR_H
#define ISR_H

#include <stdint.h>

// Registers structure
typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, reserved, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed)) registers_t;

// Function pointer type for ISR handlers
typedef void (*isr_t)(registers_t);

// Array of ISR handlers
extern isr_t interrupt_handlers[256];

// Function prototypes
void isr_install();
void irq_install();

#endif
