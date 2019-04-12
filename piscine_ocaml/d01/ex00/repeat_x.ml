let repeat_x nbr =
	let rec loop str nbr =
		if (nbr < 0) then
			"Error"
		else if (nbr == 0) then
			""
		else if (nbr == 1) then
			str ^ "x"
		else
			loop (str ^ "x") (nbr - 1)
	in
	loop "" nbr

let () = print_endline (repeat_x(-1));
	print_endline (repeat_x(0)) ;
	print_endline (repeat_x(1)) ;
	print_endline (repeat_x(2)) ;
	print_endline (repeat_x(42))