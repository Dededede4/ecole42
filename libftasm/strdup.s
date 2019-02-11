extern _malloc, _ft_strlen, _ft_memcpy

section .text
	global _ft_strdup

global _main

; Premier argument : rdi -> str *s

_ft_strdup:
	push rbp
	mov rbp, rsp

	push rdi

	call _ft_strlen

	mov  rdi, rax

	push rdi
	push rdi
	push rdi


    call _malloc

    mov rdi, rax ; (memcpy) Premier argument : rdi -> void *dst

	pop rdx ; (memcpy) Troisième argument : rdx -> size_t len
	pop rdx
	pop rdx
	pop rsi	; Deuxième argument : rsi -> void *src
	
	cmp rax, 0
	jz end

	call _ft_memcpy

end :
    pop rbp
	ret