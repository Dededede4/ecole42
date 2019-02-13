extern _ft_isdigit, _ft_isalpha

section .text
	global _ft_isalnum

_ft_isalnum:
	push rbp
	mov rbp, rsp

	call _ft_isalpha

	cmp rax, 1 ; ialpha(str) == true 
	je TRUE

	call _ft_isdigit

	cmp rax, 1 ; isdigit(str) == true 
	je TRUE	

	jmp FALSE


TRUE:
	mov rax, 1 ; true
	jmp end

FALSE:
	mov rax, 0 ; false

end:
	leave
	ret