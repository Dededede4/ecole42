let print_proj (proj:App.App.project) =
	match (proj) with
				(a1, b1, c1) -> print_endline ("(" ^ a1 ^ ", " ^ b1 ^ ", " ^ (string_of_int c1) ^ ")")

let () =
	let a = ("mprevot", "failed", 42) in 
	let b = ("mprevot42", "succeed", 84) in 
	let c = App.App.zero in
	print_proj a;
	print_proj b;
	print_proj c;
	print_proj (App.App.combine a b);
	print_proj (App.App.success (App.App.combine a b));
	print_proj (App.App.fail (App.App.combine a b))