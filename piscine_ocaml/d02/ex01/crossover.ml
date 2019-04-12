let rec in_list l v = match l with
	| a::b when a = v -> true
	| a::b when a != v -> in_list b v
	| [] -> false
	| _::_ -> false

let rec crossover lst1 lst2 =
	match lst1 with
	| a::rest when in_list lst2 a -> [a] @ crossover rest lst2
	| a::rest -> crossover rest lst2
	| [] -> []

let print_list_int listacaca =
    ignore(let rec loop listacaca = match listacaca with
        | a::rest ->  Printf.printf "%d\n" a ; loop(rest)
        | [] -> []
    in loop listacaca)

let () =
     print_list_int (crossover [42;433;120;0;1;2] [42;433;12;0;1])
    ;
    print_list_int (crossover [42;433;120;0;1;2] [])