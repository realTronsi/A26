section .text
	global err
	global _start
	%define sys_call int 0x80

	global p_reg ebx, 1
	int 0x80

	mov eax, 1
	mov ebx, 1
	int 0x80

section .data
	msg db "Compilation Error",0xa
	len equ $ - msg
