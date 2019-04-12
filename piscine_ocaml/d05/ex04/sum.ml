let sum a b = a +. b

let () =
	print_float (sum 42.0 42.0) ; print_endline "" ;
	print_float (sum 42.0 (-42.0)) ; print_endline "" ;
	print_float (sum 42.42 42.42) ; print_endline "" ;
	print_float (sum (-42.42) 42.42) ; print_endline "" ;
	print_float (sum (-42.42) (-42.42)) ; print_endline "" ;
	print_float (sum 0.0 0.0) ; print_endline ""