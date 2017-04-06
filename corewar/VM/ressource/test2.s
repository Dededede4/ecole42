.name "testeur"
.comment "il test, il test, le testeur, le testeur du bois joli"

l2:		sti r1,%:first,%1
		and r1,%-1,r1
		ld	%-1, r3
		ld	%0, r4
		fork %:l3
		sti r4,%:first,%20
 
l3:		lldi %:first,%0,r2
		sti r2,%:first,%56
		and r1,%-1,r1
first:
	live	%1
	zjmp	%:first
