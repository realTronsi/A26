section .text
	global _start
	%define sys_call int 0x80

_start:
	mov eax, 1
	mov ebx, 0
	sys_call