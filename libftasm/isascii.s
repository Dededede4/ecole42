section .text
	global _ft_isascii

_ft_isascii:
	push rbp
	mov rbp, rsp

	cmp rdi, 0 ; < 0
	jl FALSE

	cmp rdi, 127 ; > 127
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