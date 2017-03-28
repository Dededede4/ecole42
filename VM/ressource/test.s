.name "testeur"
.comment "il test il test le testeur, le testuer du bois joli"

first:
	live	%-1
	fork	%54
	live	%-1
	lld		%11, r5
	lldi	%2, r4, r5
	lfork	%4
	live	%-1
	aff		r2
	live	%-1
	ld		%1, r5
	st		r2, r5
	add		r2, r5, r4
	live	%-1
	sub		r2, r5, r4
	and		%15, 45, r5
	or		%15, 45, r5
	live	%-1
	xor		%15, 45, r5
	zjmp	%:second
	ldi		56, %78, r5
	sti		r5, r4, %56
	fork	%78
	live	%-1
	lld		%26, r5
	live	%-1
	lldi	%63, r4, r5
	lfork	%47
	aff		r5
	live	%-1


second:
live	%-1
fork	%54
live	%-1
lld		%11, r5
lldi	%2, r4, r5
lfork	%4
live	%-1
aff		r2
live	%-1
ld		%1, r5
st		r2, r5
add		r2, r5, r4
live	%-1
sub		r2, r5, r4
and		%15, 45, r5
or		%15, 45, r5
live	%-1
xor		%15, 45, r5
zjmp	%:second
ldi		56, %78, r5
sti		r5, r4, %56
fork	%78
live	%-1
lld		%26, r5
live	%-1
lldi	%63, r4, r5
lfork	%47
aff		r5
live	%-1
live	%-1
fork	%54
live	%-1
lld		%11, r5
lldi	%2, r4, r5
lfork	%4
live	%-1
aff		r2
live	%-1
ld		%1, r5
st		r2, r5
add		r2, r5, r4
live	%-1
sub		r2, r5, r4
and		%15, 45, r5
or		%15, 45, r5
live	%-1
xor		%15, 45, r5
zjmp	%:second
ldi		56, %78, r5
sti		r5, r4, %56
fork	%78
live	%-1
lld		%26, r5
live	%-1
lldi	%63, r4, r5
lfork	%47
aff		r5
live	%-1
