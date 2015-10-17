/*
 * isr.h
 *
 *  Created on: Feb 3, 2013
 *      Author: uros
 */

#ifndef ISR_H_
#define ISR_H_
#include "common.h"

typedef struct registers
{
   u32int ds;                  // Data segment selector
   u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   u32int int_no, err_code;    // Interrupt number and error code (if applicable)
   u32int eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;


#endif /* ISR_H_ */
