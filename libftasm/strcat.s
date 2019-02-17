extern _ft_strlen


section .text
	global _ft_strcat

; Premier argument : rdi -> char *restrict s1
; Deuxième argument : rsi -> const char *restrict s2

_ft_strcat:
	push rbp
	mov rbp, rsp

	push rdi
	push rsi
	call _ft_strlen ; return rax
	pop rsi
	pop rdi

	mov rbx, rax
	mov rax, 0 ; i = 0
start :
	cmp byte[rsi + rax], 0
	je end
	mov r8, rdi
	add r8, rax
	add r8, rbx
	mov r10, rsi
	add r10, rax
	mov r9, [r10]
	mov [r8], r9
	add rax, $1
	jmp start
end:
	mov    rax,rdi 
    pop rbp
	ret

