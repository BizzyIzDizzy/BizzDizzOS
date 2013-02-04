/*
 * isr.c
 *
 *  Created on: Feb 3, 2013
 *      Author: uros
 */

#include <common.h>
#include <isr.h>
#include <monitor.h>

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
   monitor_write("recieved interrupt: ");
   monitor_write_hex(regs.int_no);
   monitor_put('\n');
}
