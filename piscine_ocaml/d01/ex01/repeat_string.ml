let repeat_string ?str:(st="x") nbr =
	let rec loop str nbr =
		if (nbr < 0) then
			"Error"
		else if (nbr == 0) then
			""
		else if (nbr == 1) then
			str ^ st
		else
			loop (str ^ st) (nbr - 1)
	in
	loop "" nbr

let () = print_endline (repeat_string(-1));
	print_endline (repeat_string(0)) ;
	print_endline (repeat_string(1)) ;
	print_endline (repeat_string(2)) ;
	print_endline (repeat_string(42)) ;
	print_endline (repeat_string ~str: "Toto" 1);
	print_endline (repeat_string ~str: "a" 5);
	print_endline (repeat_string ~str: "what" 3)