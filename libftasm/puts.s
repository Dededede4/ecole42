%define MACH_SYSCALL(nb)	0x2000000 | nb
%define STDOUT				1
%define WRITE				4

extern _ft_strlen

section .text
	global _ft_puts

_ft_puts:
	push rbp
	mov rbp, rsp

	push rdi
	call _ft_strlen ; return rax
	pop rdi

	mov rdx, rax
	mov rsi, rdi
	mov rdi, STDOUT

	mov rax, MACH_SYSCALL(WRITE)
	syscall 

	leave
	ret