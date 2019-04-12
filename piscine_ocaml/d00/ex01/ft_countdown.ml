let rec ft_countdown number =
	if number <= 0 then
		begin
			print_int(0);
			print_char('\n')
		end
	else
		begin
			print_int(number);
			print_char('\n');
			ft_countdown(number - 1)
		end

let () =
	ft_countdown(12)

