let () =
	let a = new Atom.hydrogen in print_endline (a#to_string ()) ;
	let a = new Atom.carbon in print_endline (a#to_string ()) ;
	let a = new Atom.oxygen in print_endline (a#to_string ()) ;
	let a = new Atom.molybdenum in print_endline (a#to_string ()) ;
	let a = new Atom.technetium in print_endline (a#to_string ()) ;
	let a = new Atom.ruthenium in print_endline (a#to_string ()) ;
	let a = new Atom.rhodium in print_endline (a#to_string ()) ;

	let a = new Atom.rhodium in
	let b = new Atom.rhodium in
	let c = new Atom.molybdenum in
	print_string "rhodium == rhodium ?? " ;
	begin
	if (a#equals b) then
		print_endline "uiii"
	else
		print_endline "naaa"
	end ;
	print_string "rhodium == molybdenum ?? " ;
	begin
	if (a#equals c) then
		print_endline "uiii"
	else
		print_endline "naaa"
	end