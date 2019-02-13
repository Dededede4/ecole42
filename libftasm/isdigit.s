section .text
	global _ft_isdigit

_ft_isdigit:
	push rbp
	mov rbp, rsp

	cmp rdi, '0' ; < '0'
	jl FALSE

	cmp rdi, '9' ; > '9'
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