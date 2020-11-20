section .text
	global err
	global _start
	%define sys_call int 0x80
	global glb_reg
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
glb_reg:
	mov eax, 1
	mov ebx, 0
	sys_call
p_reg:

	mov ecx, p_msg_1
	sys_call

	mov ecx, p_msg_2
	sys_call

	mov ecx, p_msg_3
	sys_call

	mov ecx, p_msg_4
	sys_call

	mov eax, 1
	sys_call
section .data ; storing all compiler messages
	msg db "Compilation Error",0xa
	len equ $ - msg
_start:

	mov ecx, p_msg_1
	mov edx, 2
	mov eax, 4
	mov ebx, 1
	sys_call

	mov ecx, p_msg_2
	mov edx, 3
	mov eax, 4
	mov ebx, 1
	sys_call

	mov ecx, p_msg_3
	mov edx, 22
	mov eax, 4
	mov ebx, 1
	sys_call

	mov ecx, p_msg_4
	mov edx, 2
	mov eax, 4
	mov ebx, 1
	sys_call

	mov ecx, p_msg_1
	mov edx, 2
	mov eax, 4
	mov ebx, 1
	sys_call

	mov ecx, p_msg_2
	mov edx, 3
	mov eax, 4
	mov ebx, 1
	sys_call

	mov ecx, p_msg_3
	mov edx, 22
	mov eax, 4
	mov ebx, 1
	sys_call

	mov ecx, p_msg_4
	mov edx, 2
	mov eax, 4
	mov ebx, 1
	sys_call

	mov eax, 1
	mov ebx, 0
	sys_call

section .rodata

	; P REGISTER
	p_msg_1 db "Yo"
	p_msg_2 db "Bro"
	p_msg_3 db "IT WORKS NOW YEEEHAWWW"
	p_msg_4 db "13"