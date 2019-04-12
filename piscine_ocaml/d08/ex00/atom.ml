class virtual atom name symbol atomic_number =
object (self)
	val _name:string = name
	val _symbol:string = symbol
	val _atomic_number:int = atomic_number
	val _howmany:int = 0
	method getName () = _name
	method getSymbol () = _symbol
	method getAtomicNumber () = _atomic_number
	method equals (atom2:atom) = (atom2#getAtomicNumber ()) = atomic_number
	method to_string () = (self#getName ()) ^ " " ^ (self#getSymbol ()) ^ " " ^ (string_of_int (self#getAtomicNumber ()))
end

class hydrogen =
object
	inherit atom "Hydrogen" "H" 1
end

class carbon =
object
	inherit atom "Carbon" "C" 6
end 

class oxygen =
object
	inherit atom "Oxyen" "O" 8
end

class molybdenum =
object
	inherit atom "Molybdenum" "Mo" 42
end

class technetium =
object
	inherit atom "Technetium" "Tc" 43
end

class ruthenium =
object
	inherit atom "Ruthenium" "Ru" 44
end

class rhodium =
object
	inherit atom "Rhodium" "Rh" 45
end