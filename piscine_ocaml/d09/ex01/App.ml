module App =
	struct
		type project = (string * string * int)

		let zero : project = ("", "", 0)

		let combine (project1:project) (project2:project) : project =
			match (project1, project2) with
				((a1, b1, c1), (a2, b2, c2)) -> 
				let moy = ((c1 + c2) / 2) in
					if (moy >= 80) then
						((a1 ^ a2), "succeed", moy)
					else
						((a1 ^ a2), "failed", moy)

		let fail (project:project) : project =
			match (project) with (a1, b1, c1) ->
				(a1, "failed", 0)

		let success (project:project) : project =
			match (project) with (a1, b1, c1) ->
				(a1, "succeed", 80)
	end