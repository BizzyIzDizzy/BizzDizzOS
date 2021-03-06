global gdt_flush		; allows the C code to call gdt_flush()
gdt_flush:
	mov eax, [esp+4]	; get the pointer to the GDT, passed as a parameter
	lgdt [eax]			; load the new GDT pointer

	mov ax, 0x10		; 0x10 is the offset in the GDT to our data segment
	mov ds, ax			; load all data segment selectors
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush		; 0x08 is the offset to our code segment: Far jump!
.flush:
	ret

global idt_flush		; allows the C code to call idt_flush()
idt_flush:
	mov eax, [esp+4]	; get the pointer to the idt, passed as a parameter
	lidt [eax]			; load the IDT pointer
	ret
