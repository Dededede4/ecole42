section .text
	global _ft_strlenMAFONCTIONAMOI

; Premier argument : rdi -> str *s

_ft_strlenMAFONCTIONAMOI:
	push rbp
	mov rbp, rsp

	xor rax, rax  ; i = 0
	xor rcx, rcx
	not rcx
	repne scasb ; Il d
	not rcx
	dec rcx
	mov rax, rcx

	pop rbp
	ret
