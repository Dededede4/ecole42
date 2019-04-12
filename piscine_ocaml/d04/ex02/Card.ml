module Color =
	struct
		type t = Spade | Heart | Diamond | Club

		let all = [Spade ; Heart ; Diamond ; Club ;] 

		let toString t =
			match t with
			Spade -> "S"
			| Heart -> "H"
			| Diamond -> "D"
			| Club -> "C"

		let toStringVerbose t =
			match t with
			Spade -> "Spade"
			| Heart -> "Heart"
			| Diamond -> "Diamond"
			| Club -> "Club"
	end

module Value =
	struct
		type t = T2 | T3 | T4 | T5 | T6 | T7 | T8 | T9 | T10 | Jack | Queen | King | As

		let all = [T2 ; T3 ; T4 ; T5 ; T6 ; T7 ; T8 ; T9 ; T10 ; Jack ; Queen ; King ; As]

		let toInt t =
			match t with
		T2 -> 1 | T3 -> 2 | T4 -> 3 | T5 -> 4 | T6 -> 5 | T7 -> 6 | T8 -> 7 | T9 -> 8 | T10 -> 9 | Jack -> 10 | Queen -> 11 | King -> 12 | As -> 13


		let toString t =
			match t with
		T2 -> "1" | T3 -> "2" | T4 -> "3" | T5 -> "4" | T6 -> "5" | T7 -> "6" | T8 -> "7" | T9 -> "8" | T10 -> "9" | Jack -> "J" | Queen -> "Q" | King -> "K" | As -> "A"


		let toStringVerbose t =
			match t with
		T2 -> "1" | T3 -> "2" | T4 -> "3" | T5 -> "4" | T6 -> "5" | T7 -> "6" | T8 -> "7" | T9 -> "8" | T10 -> "9" | Jack -> "Jack" | Queen -> "Queen" | King -> "King" | As -> "As"


		let next t =
			match t with
				T2 -> T3
				| T3 -> T4
				| T4 -> T5
				| T5 -> T6
				| T6 -> T7
				| T7 -> T8
				| T8 -> T9
				| T9 -> T10
				| T10 -> Jack
				| Jack -> Queen
				| Queen -> King
				| King -> As
				| As -> invalid_arg "Bordel de merde"

		let previous t =
			match t with
				T2 -> invalid_arg "Borrdell"
				| T3 -> T2
				| T4 -> T3
				| T5 -> T4
				| T6 -> T5
				| T7 -> T6
				| T8 -> T7
				| T9 -> T8
				| T10 -> T9
				| Jack -> T10
				| Queen -> Jack
				| King -> Queen
				| As -> King
	end

type t = (Value.t * Color.t)

(*val newCard : Value.t -> Color.t -> t*)

let newCard value color = (value, color)

let allSpades = [(Value.T2, Color.Spade) ;
(Value.T3, Color.Spade) ;
(Value.T4, Color.Spade) ;
(Value.T5, Color.Spade) ;
(Value.T6, Color.Spade) ;
(Value.T7, Color.Spade) ;
(Value.T8, Color.Spade) ;
(Value.T9, Color.Spade) ;
(Value.T10, Color.Spade) ;
(Value.Jack, Color.Spade) ;
(Value.Queen, Color.Spade) ;
(Value.King, Color.Spade) ;
(Value.As, Color.Spade)]

let allHearts = [(Value.T2, Color.Heart) ;
(Value.T3, Color.Heart) ;
(Value.T4, Color.Heart) ;
(Value.T5, Color.Heart) ;
(Value.T6, Color.Heart) ;
(Value.T7, Color.Heart) ;
(Value.T8, Color.Heart) ;
(Value.T9, Color.Heart) ;
(Value.T10, Color.Heart) ;
(Value.Jack, Color.Heart) ;
(Value.Queen, Color.Heart) ;
(Value.King, Color.Heart) ;
(Value.As, Color.Heart)]

let allDiamonds = [(Value.T2, Color.Diamond) ;
(Value.T3, Color.Diamond) ;
(Value.T4, Color.Diamond) ;
(Value.T5, Color.Diamond) ;
(Value.T6, Color.Diamond) ;
(Value.T7, Color.Diamond) ;
(Value.T8, Color.Diamond) ;
(Value.T9, Color.Diamond) ;
(Value.T10, Color.Diamond) ;
(Value.Jack, Color.Diamond) ;
(Value.Queen, Color.Diamond) ;
(Value.King, Color.Diamond) ;
(Value.As, Color.Diamond)]

let allClubs = [(Value.T2, Color.Club) ;
(Value.T3, Color.Club) ;
(Value.T4, Color.Club) ;
(Value.T5, Color.Club) ;
(Value.T6, Color.Club) ;
(Value.T7, Color.Club) ;
(Value.T8, Color.Club) ;
(Value.T9, Color.Club) ;
(Value.T10, Color.Club) ;
(Value.Jack, Color.Club) ;
(Value.Queen, Color.Club) ;
(Value.King, Color.Club) ;
(Value.As, Color.Club)]

let all = allSpades @ allHearts @ allDiamonds @ allClubs

let getValue value = match value with (v, color) -> v
let getColor value = match value with (v, color) -> color
let toString value = (Value.toString (getValue value)) ^ (Color.toString (getColor value))
let toStringVerbose value = "Card (" ^ (Value.toStringVerbose (getValue value)) ^ ", " ^ (Color.toStringVerbose (getColor value)) ^ ")"
let compare card1 card2 = (Value.toInt (getValue card1)) - (Value.toInt (getValue card2))
let max card1 card2 = if compare card1 card2 >= 0 then card1 else card2
let min card1 card2 = if compare card1 card2 <= 0 then card1 else card2
let best l =
	match l with 
		[] -> invalid_arg("putain")
		| l -> List.fold_left max (List.hd l) l
let isOf card color = Color.toString (getColor card) = Color.toString (color)
let isSpade card = isOf card Color.Spade
let isHeart card = isOf card Color.Heart
let isDiamond card = isOf card Color.Diamond
let isClub card = isOf card Color.Club