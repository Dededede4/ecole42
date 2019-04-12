module Watchtower =
	struct
		type hour = int
		let zero : hour = 0

		let add (a:hour) (b:hour) : hour = 1 + (((a + b - 1)) mod (12))
		let sub (a:hour) (b:hour) : hour = 12 + (((a - b - 12)) mod (12))
end