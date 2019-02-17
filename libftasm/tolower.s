section .text
	global _ft_tolower

_ft_tolower:
	push rbp
	mov rbp, rsp


	mov rax, rdi ; on retoune l argument

	cmp rdi, 'A' ; < 'A'
	jl end

	cmp rdi, 'Z' ; > 'Z'
	jg end

	add rax, 32 ; + 32

end:
	leave
	ret