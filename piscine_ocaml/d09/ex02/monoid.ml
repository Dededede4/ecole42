module type MONOID =
	sig
		type element
		val zero1 : element
		val zero2 : element
		val mul : element -> element -> element
		val add : element -> element -> element
		val div : element -> element -> element
		val sub : element -> element -> element
end

module Calc =
	functor (M:MONOID) -> struct

	let add x y = M.add x y
	let sub x y = M.sub x y
	let mul x y = M.mul x y
	let div x y = M.div x y

	let rec power x = function
		| 0 -> M.zero1
		| 1 -> x
		| n when (n mod 2 = 0) ->let a = power x (n/2) in M.mul a a
		| n -> let a = power x (n/2) in M.mul x (M.mul a a)

	let rec fact x = 
		if x <= M.zero2 then x
		else M.mul x (fact (M.sub x M.zero2))
		

	end

module INT =
	struct
		type element = int
		let zero1 = 0
		let zero2 = 1
		let mul = ( * )
		let add = ( + )
		let div = ( / )
		let sub = ( - )
	end

module FLOAT =
	struct
		type element = float
		let zero1 = 0.0
		let zero2 = 1.0
		let mul = ( *. )
		let add = ( +. )
		let div = ( /. )
		let sub = ( -. )
	end

module Calc_int = Calc(INT)
module Calc_float = Calc(FLOAT)

let () =
	print_endline (string_of_int (Calc_int.power 3 3));
	print_endline (string_of_float (Calc_float.power 3.0 3));
	print_endline (string_of_int (Calc_int.mul (Calc_int.add 20 1) 2));
	print_endline (string_of_float (Calc_float.mul (Calc_float.add 20.0 1.0) 2.0));
	print_endline (string_of_int (Calc_int.div (Calc_int.sub 20 1) 2));
	print_endline (string_of_float (Calc_float.div (Calc_float.sub 20.0 1.0) 2.0));
	print_endline (string_of_int (Calc_int.fact 10 )); 
	print_endline (string_of_float (Calc_float.fact 10.0 ))