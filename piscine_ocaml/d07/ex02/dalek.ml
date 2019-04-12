class dalek  =
	object
		
		val mutable hp = 100
		val name:string = "Dalek" ^ 
			(String.make 1 (String.get "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" (Random.int 61))) ^
			(String.make 1 (String.get "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" (Random.int 61))) ^
			(String.make 1 (String.get "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" (Random.int 61)))
		val mutable shield = true
		method talk () =  
			match (Random.int 3) with
			  0 -> print_endline "Explain! Explain!"
			| 1 -> print_endline "Exterminate! Exterminate!"
			| 2 -> print_endline "I obey!"
			| 3 -> print_endline "You are the Doctor! You are the enemy of the Daleks!"
			| _ -> ()
		method die = print_endline "Emergency Temporal Shift!"
		method to_string = (name ^ " have " ^ string_of_int (hp) ^ " hp shield :" ^ (if shield then "OK" else "KO"))
		method exterminate (people:People.people) = begin people#die ; if shield then shield <- false else shield <- true end 
		initializer print_endline "An initializer which indicate that the object has been created"
	end 

