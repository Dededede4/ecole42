%define MACH_SYSCALL(nb)	0x2000000 | nb
%define STDOUT				1
%define WRITE				4
%define READ				3
%define BUFF				8192

section .text
	global _ft_cat

_ft_cat:
	push rbp
	mov rbp, rsp

	
	sub rbp, BUFF
	mov r8, rbp

loop:
	mov rsi, r8 ; char*
	mov rdx, BUFF
	;mov rdi, rdi ; Le FD

	mov rax, MACH_SYSCALL(READ)
	syscall
	jc end
	cmp rax, 0
	je end

	mov rdx, rax ; la taille retournée par read pour write 
	mov rdi, STDOUT

	mov rsi, rsi ; la str

	mov rax, MACH_SYSCALL(WRITE)
	syscall
	jc end

	jmp loop
end :
	pop rbp
	leave
	ret