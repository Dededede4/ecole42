class virtual alkane_combustion n =
	object
		inherit Reaction.reaction start result
		
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
