section .text
	global _ft_toupper

_ft_toupper:
	push rbp
	mov rbp, rsp


	mov rax, rdi ; on retoune l argument

	cmp rdi, 'a' ; < 'a'
	jl end

	cmp rdi, 'z' ; > 'z'
	jg end

	sub rax, 32 ; + 32

end:
	leave
	ret