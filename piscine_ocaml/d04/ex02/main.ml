let newDeck () = Card.all

let rec toStringList deck = 
	match deck with
	| v::rest -> (Card.toString v) ^ "\n" ^ (toStringList rest)
	| _ -> Printf.sprintf "\n"

let rec toStringListVerbose deck = 
	match deck with
	| v::rest -> (Card.toStringVerbose v) ^ "\n" ^ (toStringListVerbose rest)
	| _ -> Printf.sprintf "\n"

let () =  print_endline (toStringList (newDeck ()));
		  print_endline (toStringListVerbose (newDeck ()))