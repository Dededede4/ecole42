let fibonacci n =
	if (n < 0) then (-1) else 
	let rec subfibo n a b =
		if (n == 0) then a else
		if (n == 1) then b else
		subfibo (n - 1) b (a + b)
	in subfibo n 0 1

let () = print_int (fibonacci 6); print_char '\n' ;
		print_int (fibonacci 3); print_char '\n' ;
		print_int (fibonacci 1); print_char '\n' ;
		print_int (fibonacci 0); print_char '\n' ;
		print_int (fibonacci (-1)); print_char '\n'
