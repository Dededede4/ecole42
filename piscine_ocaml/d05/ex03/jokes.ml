let file_to_list filename = 
	let ic = open_in filename in
	let tab =  ref [] in
	try
		begin while true do
				tab := [input_line ic] @ !tab
		done ; 
		!tab end
	with
	| _ -> !tab

let list_to_array lst = Array.of_list lst

let get_random_jocke filename =
	let l = (file_to_list filename) in
	let len = (List.length l) in
	let arr = (list_to_array l) in
	Array.get arr (Random.int (len))

let () = Random.self_init () ; try print_endline (get_random_jocke ((Sys.argv.(1)))) with _ -> ()
	