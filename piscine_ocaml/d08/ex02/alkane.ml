class virtual alkane n =
	object
		inherit Molecule.molecule "name" [new Atom.carbon ~_howmany:n () ; new Atom.hydrogen ~_howmany:(2 * (n + 1)) ()]
	
		method getName () = match n with
		| 1 -> "methane"
		| 2 -> "ethane"
		| 3 -> "propane"
		| 4 -> "butane"
		| 5 -> "pentane"
		| 6 -> "hexane"
		| 7 -> "heptane"
		| 8 -> "octane"
		| 9 -> "nonane"
		| 10 -> "decane"
		| 11 -> "undecane"
		| 12 -> "dodecane"
		| _ -> "c tro dur" 
	end

class methane =
	object
		inherit alkane 1
	end

class ethane =
	object
		inherit alkane 2
	end

class propane =
	object
		inherit alkane 3
	end
