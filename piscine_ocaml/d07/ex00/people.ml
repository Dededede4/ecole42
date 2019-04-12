class people name =
	object
		val name:string = name
		val mutable hp = 100
		method talk =  print_endline ("I'm " ^ name ^ "! Do you know the Doctor?")
		method die = print_endline "Aaaarghh!"
		method to_string = name ^ " have " ^ string_of_int (hp) ^ " hp"
		initializer print_endline "An initializer which indicate that the object has been created"
	end 

