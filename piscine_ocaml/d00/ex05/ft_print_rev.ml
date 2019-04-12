let rec loop str pos = 
	if (pos >= 0) then begin
		print_char (String.get str pos); 
		loop str (pos - 1)
	end
	

let ft_print_rev str =
	let start = String.length(str) - 1 in
		loop str start;
	print_char '\n'


let () = ft_print_rev "Hello world !"
