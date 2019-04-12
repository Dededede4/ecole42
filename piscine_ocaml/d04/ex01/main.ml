let rec loop l =
	match l with
		e::rest -> begin 
			print_endline ("Is it " ^ Value.toString e) ;
			print_endline ("Verbose " ^Value.toStringVerbose e) ;
			(*print_endline (Value.toString (Value.previous e));*)
			print_endline ("After ? " ^ Value.toString (Value.next e));
			print_endline ("-----") ;
			loop rest
		end
		| [] -> print_endline "end"

let () = loop Value.all
