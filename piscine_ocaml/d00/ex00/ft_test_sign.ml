let ft_test_sign number =
	if number >= 0 then print_endline "positive" else print_endline("negative")

let () =
	ft_test_sign(-1) ;
	ft_test_sign(0) ;
	ft_test_sign(1)
