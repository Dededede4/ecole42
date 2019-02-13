section .text
	global _ft_isalpha

_ft_isalpha:
	push rbp
	mov rbp, rsp

	cmp rdi, 'Z' ; > 'Z' 
	jg lower

upper :
	cmp rdi, 'A' ; < 'A'
	jl FALSE

	cmp rdi, 'Z' ; > 'Z'
	jg FALSE

	jmp TRUE

lower :
	cmp rdi, 'a' ; < 'a'
	jl FALSE

	cmp rdi, 'z' ; > 'z'
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