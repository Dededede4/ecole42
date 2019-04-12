class virtual atom howmany name symbol atomic_number =
object (self)
	val _name:string = name
	val _symbol:string = symbol
	val _atomic_number:int = atomic_number
	val _howmany:int = howmany
	method getName () = _name
	method getSymbol () = _symbol
	method getAtomicNumber () = _atomic_number
	method getHowmany () = _howmany
	method equals (atom2:atom) = (atom2#getAtomicNumber ()) = atomic_number
	method to_string () = (self#getName ()) ^ " " ^ (self#getSymbol ()) ^ " " ^ (string_of_int (self#getAtomicNumber ()))
end

class hydrogen ?_howmany:(_howmany=1) () =
object
	inherit atom _howmany "Hydrogen" "H" 1
end

class carbon ?_howmany:(_howmany=1) () =
object
	inherit atom _howmany "Carbon" "C" 6
end 

class oxygen ?_howmany:(_howmany=1) () =
object
	inherit atom _howmany "Oxyen" "O" 8
end

class molybdenum ?_howmany:(_howmany=1) () =
object
	inherit atom _howmany "Molybdenum" "Mo" 42
end

class technetium ?_howmany:(_howmany=1) () =
object
	inherit atom _howmany "Technetium" "Tc" 43
end

class ruthenium ?_howmany:(_howmany=1) () =
object
	inherit atom _howmany "Ruthenium" "Ru" 44
end

class rhodium ?(_howmany=1) () =
object
	inherit atom _howmany "Rhodium" "Rh" 45
end