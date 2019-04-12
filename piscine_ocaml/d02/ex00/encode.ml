let encode listacaca =
    let rec loop listacaca len acc = match listacaca with
        | a::b::rest ->
            if a = b then loop ([b] @ rest) (len + 1) acc
            else loop ([b] @ rest) 0 (acc @ [((len + 1), a)])
        | a::b -> acc @ [((len + 1), a)]
        | [] -> acc
    in loop listacaca 0 []

let print_list_int listacaca =
    let rec loop listacaca = match listacaca with
        | (a, b) :: rest ->  Printf.printf "%d %d\n" a b ; loop(rest)
        | [] -> []
    in loop listacaca

let print_list_string listacaca =
    let rec loop listacaca = match listacaca with
        | (a, b) :: rest ->  Printf.printf "%d %s\n" a b ; loop(rest)
        | [] -> []
    in loop listacaca

let () =
    ignore (print_list_int (encode [42;42;42;42;42;42;12;12;12;12;0;0;0;0;0;1;0]))
    ;
     ignore (print_list_string (encode ["42";"42";"42";"42";"42";"42";"12";"12";"12";"12";"0";"0";"0";"0";"0";"1";"0"]))
     ; ()

