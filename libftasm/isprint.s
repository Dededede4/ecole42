section .text
	global _ft_isprint

_ft_isprint:
	push rbp
	mov rbp, rsp

	cmp rdi, 32 ; < 32
	jl FALSE

	cmp rdi, 126 ; > 126
	jg FALSE

	jmp TRUE

TRUE:
	mov rax, 1 ; true
	jmp end

FALSE:
	mov rax, 0 ; false

end:
	leave
	ret