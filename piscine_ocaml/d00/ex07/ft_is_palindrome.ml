let rec loop str first last = 
	if (first < last) then begin
		if (String.get str first != String.get str last) then
			false
		else
			loop str (first + 1) (last - 1)
	end else true

	

let ft_print_rev str =
	loop str 0 (String.length(str) - 1)


let () = if ft_print_rev "radar" then print_endline "true" else print_endline "false"
; if ft_print_rev "madam" then print_endline "true" else print_endline "false"
; if ft_print_rev "car" then print_endline "true" else print_endline "false"
; if ft_print_rev "zaz" then print_endline "true" else print_endline "false"
; if ft_print_rev "azz" then print_endline "true" else print_endline "false"
; if ft_print_rev "a" then print_endline "true" else print_endline "false"
; if ft_print_rev "aa" then print_endline "true" else print_endline "false"
; if ft_print_rev "aaa" then print_endline "true" else print_endline "false"
; if ft_print_rev "aaaa" then print_endline "true" else print_endline "false"
; if ft_print_rev "aaaaa" then print_endline "true" else print_endline "false"
; if ft_print_rev "aaaab" then print_endline "true" else print_endline "false"
