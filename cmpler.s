section .text
	global err
	global _start
	%define sys_call int 0x80
	global p_reg
err:
	mov ecx, msg
	mov edx, len
	mov eax, 4
	mov ebx, 1
	sys_call

	mov eax, 1
	mov ebx, 1
	sys_call
p_reg:

	mov ecx, p_msg_1
	sys_call

	mov eax, 1
	sys_call
section .data ; storing all compiler messages
	msg db "Compilation Error",0xa
	len equ $ - msg
_start:

	mov ecx, p_msg_1
	mov edx, 12
	mov eax, 4
	mov ebx, 1
	sys_call

	mov eax, 1
	mov ebx, 0
	sys_call

section .rodata

	; P REGISTER
	p_msg_1 db 'hi',0xa,'hi',0xa,'hi',0xa,'',0xa,'',0xa,'',0xa,''