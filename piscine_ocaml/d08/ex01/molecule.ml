class virtual molecule name formula =
object (self)
	val _name:string = name
	val _formula:(Atom.atom list) = formula

	method getFormulaString () =  self#formula2string (self#sortformula _formula) 

	method sortformula_algo (a:Atom.atom) (b:Atom.atom) = String.compare (a#getSymbol ()) (b#getSymbol ())    
	method sortformula lst =  List.sort (self#sortformula_algo) (lst)

	method formula2string lst =
		match lst with
		| atom::rest -> (atom#getSymbol ()) ^ 
			begin if (atom#getHowmany ()) > 1 then (string_of_int (atom#getHowmany ())) else "" end
			^ (self#formula2string rest)
		| [] -> ""

	method getName () = _name
	method equals (atom2:molecule) = if ((atom2#to_string ()) = self#to_string ()) then true else false
	method to_string () = (self#getFormulaString ())
end

class water =
object
	inherit molecule "water" [new Atom.oxygen ~_howmany:1 () ; new Atom.hydrogen ~_howmany:2 ()]
end


class carbon_dioxyde =
object
	inherit molecule "carbon dioxyde" [new Atom.carbon ~_howmany:1 () ; new Atom.oxygen ~_howmany:2 ()]
end

class dihydrogen =
object
	inherit molecule "dihydrogen" [new Atom.hydrogen ~_howmany:2 ()]
end

class dioxygen =
object
	inherit molecule "dioxygen" [new Atom.oxygen ~_howmany:2 ()]
end

class sucrose =
object
	inherit molecule "sucrose" [new Atom.carbon ~_howmany:12 () ; new Atom.hydrogen ~_howmany:22 () ; new Atom.oxygen ~_howmany:11 ()]
end
class glucose =
object
	inherit molecule "glucose" [new Atom.carbon ~_howmany:6 () ; new Atom.hydrogen ~_howmany:12 () ; new Atom.oxygen ~_howmany:6 ()]
end