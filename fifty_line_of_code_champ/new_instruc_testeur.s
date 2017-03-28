.name "testeur"
.comment "pour le plaisir d'essayer"

	live	%45
	ld		20, r2
	st		r2, -100
	add		r1, r2, r3
	sub		r2, r3, r4
	and		r4, r3, r5
	or		r2, r5, r6
	xor		r2, r2, r7
	zjmp	%8
	live	%5
	ldi		r1, r6, r8
	sti		r8, -100, %-100
	fork	%100
	lld		%2000, r9
	lldi	r1, %2000, r10
	lfork	%2000
	aff		r5
	mul		r1, r6, r11
	div		r1, r6, r12
	not		r5, r13
	asl		r5, r14
	asr		r5, r14
	rol		r5, r15
	ror		r5, r16, r10
	mov		r1, r9
