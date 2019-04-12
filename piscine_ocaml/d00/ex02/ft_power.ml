let rec ft_power number power =
	if (power == 0) then 1 else number * ft_power number (power - 1)


let () =
	print_int(ft_power 2 4) ; print_char('\n');
	print_int(ft_power 3 0) ; print_char('\n');
	print_int(ft_power 0 5) ; print_char('\n')

