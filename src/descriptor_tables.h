/*
 * descriptor_tables.h
 *
 *  Created on: Feb 3, 2013
 *      Author: uros
 */

#ifndef DESCRIPTOR_TABLES_H_
#define DESCRIPTOR_TABLES_H_
#include "common.h"
// This structure contains the value of one GDT entry.
// We use the attribute packed to tell GCC not to change
// any of the alignment in the structure
struct gdt_entry_struct{
	u16int limit_low;		// the lower 16 bits of the limit
	u16int base_low;		// the lower 16 bits of the base
	u8int  base_middle;		// the next 8 bits of the base
	u8int  access;			// access flags, determine what ring this segment can be used in
	u8int  granularity;
	u8int  base_high;		// the last 8 bits of the base
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct{
	u16int limit;			// the upper 16 bits of all selector limits
	u32int base;			// the address of the first gdt_entry_t struct
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;

// a struct describing an interrupt gate
struct idt_entry_struct{
	u16int base_lo;			// the lower 16 bits of the address to jump to when this interrupt fires
	u16int sel;				// kernel segment selector
	u8int  always0;			// this must always be zero
	u8int  flags;			// more flags
	u16int base_hi;			// the upper 16 bits of the address to jump to
}__attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

// a struct describing a pointer to an array of interrupt handlers
// this is in a format suitable for giving to lidt
struct idt_ptr_struct{
	u16int limit;
	u32int base;			// the address of the first element in our idt_entry_t array
}__attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

// these extern directives let us access the addresses of our ASM ISR handlers
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void init_descriptor_tables();

#endif /* DESCRIPTOR_TABLES_H_ */
