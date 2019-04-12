let eu_dist a b =
	let total = ref 0.0 in
	for i = 0 to (Array.length a) - 1 do
	  total := !total +. ((a.(i) -. b.(i)) ** 2.0) 
	done ;
	sqrt !total

let () =
	print_float (eu_dist [| 1.2 ; 1.3|] [| 4.2 ; 4.3|])