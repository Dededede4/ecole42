let rec testShort l =
	match l with
		e::rest -> begin print_endline (Color.toString e) ; testShort rest end
		| [] -> print_endline "end"

let rec testVerbose l =
	match l with
		e::rest -> begin print_endline (Color.toStringVerbose e) ; testVerbose rest end
		| [] -> print_endline "end"

let () = testShort Color.all ; testVerbose Color.all
