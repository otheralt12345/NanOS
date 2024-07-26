#ifndef MONITOR_H
#define MONITOR_H

#include <stdint.h>
#include <stddef.h>

// Function prototypes for monitor output
void monitor_write(const char* str);
void monitor_write_hex(uint32_t n);
void monitor_write_dec(uint32_t n);
void monitor_write_newline(void);
size_t strlen(const char* str) ;
// Function prototype for snprintf
int snprintf(char* buffer, size_t size, const char* format, ...);

#endif // MONITOR_H
