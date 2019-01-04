section .text
	global _ft_memset

; Premier argument : rdi -> void *dst
; Deuxième argument : rsi -> void *src
; Troisième argument : rdx -> size_t len

_ft_memset:
	push rbp
	mov rbp, rsp


	mov    rax,rsi 
	;mov    rdi,offset arr 
	mov    rcx,rdx         ;array size 
	rep movsb

	pop rbp
	ret
