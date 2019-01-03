section .text
	global _ft_strlenMAFONCTIONAMOI

; Premier argument : rdi -> str *s

_ft_strlenMAFONCTIONAMOI:
	push rbp
	mov rbp, rsp

	mov rax, $0 ; i = 0
start :
	cmp byte[rdi + rax], $0
	je end
	add rax, $1
	jmp start

end:
	mov eax, rax
	pop rbp
	ret
