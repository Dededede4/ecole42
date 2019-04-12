let rec loop func str pos = 
	if (pos >= 0) then begin
		if func (String.get str pos) == false then false
		else loop func str (pos - 1)
	end else true
	

let ft_string_all func str =
	let start = String.length(str) - 1 in
		loop func str start



let is_digit a = if a >= '0' && a <= '9' then true else false

let () = if ft_string_all is_digit "0123456789" then print_endline "true" else print_endline "false" ;
if ft_string_all is_digit "0123E56789" then print_endline "true" else print_endline "false"
