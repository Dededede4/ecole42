
let () =
	let int1:Watchtower.Watchtower.hour = 6 in 
	let int2:Watchtower.Watchtower.hour = 7 in 
	let sum:Watchtower.Watchtower.hour = Watchtower.Watchtower.add int1 int2 in
	print_int (sum) ; print_endline "" ;

	let int1:Watchtower.Watchtower.hour = 1 in 
	let int2:Watchtower.Watchtower.hour = 2 in 
	let sum:Watchtower.Watchtower.hour = Watchtower.Watchtower.sub int1 int2 in
	print_int (sum) ; print_endline ""