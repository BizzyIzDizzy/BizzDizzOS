#ifndef	VARARGS_H
#define VARARGS_H
// used in kprintf to convert the stack space to a character stream for further processing
#define args_list char *

// rounds the argument size to calculate how many 4-byte it occupies in stakc
#define _arg_stack_size(type) \
(((sizeof(type)-1)/sizeof(int)+1)*sizeof(int))

// arguments are after format string, or on the top of fmt in stack,
// this macro gets the starting address of those arguments
#define args_start(ap, fmt) do { \
	ap = (char *)((unsigned int)&fmt + _arg_stack_size(&fmt)); \
}while(0)

// deosnt do anything at the moment
#define args_end(ap)

// gets the adress of next argument
#define args_next(ap, type) (((type *)(ap+=_arg_stack_size(type)))[-1])

#endif//VARARGS_H
