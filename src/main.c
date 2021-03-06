#include "monitor.h"

int main(/*struct multiboot *mboot_ptr*/){
	// Initialise all the ISRs and segmentation
	init_descriptor_tables();
	// Initialise the screen (by clearing it)
	monitor_clear();
	// Write out a sample string
	monitor_write("\nHello, world!\n");

	asm volatile("int $0x3");
	asm volatile("int $0x4");

	return 0;
}
