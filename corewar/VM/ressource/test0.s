.name "testeur"
.comment "il test il test le testeur, le testuer du bois joli"

la couleur est du au champion du process a sa creation

op_encodages
rrr 0b101010 ou 0b010101 ?
ddd 0b101010
iii 0b111111

  


first:						cycles	jump	opcode?
1	live	%10				10		+5			non
2	ld		%12, r5			5					oui
3	st		r5, r3			5					oui
4	add		r5, r3, r4		?					oui
5	sub		r5, r3, r4							oui		;
6	and		%15, 45, r5							oui		;
7	or		%15, 45, r5							oui		;
8	xor		%15, 45, r5							oui		;
9	zjmp	%:second				+3			non		;
10	ldi		56, %78, r5							oui		;
11	sti		r5, r4, %56							oui		;
12	fork	%78						+3			non		;
13	lld		%26, r5								oui		;
14	lldi	%63, r4, r5									;
15	lfork	%47						+3			non		;
16	aff		r5											;


second:
	live	%10
	ld		%12, r5
	st		r2, r3
	add		r2, r3, r4
	sub		r2, r3, r4
	and		%15, 45, r5
	or		%15, 45, r5
	xor		%15, 45, r5
	zjmp	%:first
	ldi		56, %78, r5
	sti		r5, r4, %56
	fork	%78
	lld		%26, r3
	lldi	%63, r4, r5
	lfork	%47
	aff		r2
