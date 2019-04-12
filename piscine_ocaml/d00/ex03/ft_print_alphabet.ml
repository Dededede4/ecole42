let ft_print_alphabet () =
	let ascii_of_0 = int_of_char 'a' in
	let ascii_of_9 = int_of_char 'z' in
	let rec loop ascii_of_current_digit =
		if ascii_of_current_digit <= ascii_of_9 then
		let char_of_current_digit = char_of_int ascii_of_current_digit in
		print_char char_of_current_digit;
		loop (ascii_of_current_digit + 1)
	in
	loop ascii_of_0;
	print_char '\n'

let () = ft_print_alphabet ()