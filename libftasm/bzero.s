section .text
	global _ft_bzero

; Premier argument : rdi -> void *s
; Deuxième argument : rsi -> size_t n

_ft_bzero:
	push rbp
	mov rbp, rsp

	mov rax, $0
start :
	cmp rsi, rax
	je end
	mov byte[rdi + rax], $0
	add rax, $1
	jmp start

end:
	pop rbp
	ret
