let rec right valA valB valC = 
	if valC <= 9 then begin
		print_int(valA);
		print_int(valB);
		print_int(valC);
		print_char('\n');
		right valA valB (valC + 1)
	end

let rec middle valA valB = 
	if valB <= 8 then begin
		right (valA) (valB + 1) (valB + 2);
		middle  (valA) (valB + 1)
	end

let rec left valA =
	if valA <= 7 then begin
		middle valA (valA);
		left(valA + 1)
	end

let ft_print_comb () =
	left 0

let () =
	ft_print_comb ()
