// monitor.h -- Defines the interface for monitor

#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

// write a single character out to the screen
void monitor_put(char c);

// clear the sceen to all black
void monitor_clear();

// output a null-terminated ASCII string to the monitor
void monitor_write(char *c);

// write an unsigned 32 bit integer in binary
void monitor_write_bin(u32int n);

// write an unsigned 32 bit integer in hexadecimal
void monitor_write_hex(u32int n);

// write an unsigned 32 bit integer in decimal
void monitor_write_dec(u32int n);

#endif	// MONITOR_H

