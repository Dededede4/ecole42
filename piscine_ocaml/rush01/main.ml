class stats a b c d =
object (s)
	val mutable health = a
	val mutable energy = b
	val mutable hygiene = c
	val mutable happiness = d
	val mutable last_time:float = (Unix.time ())

	method eat () = health <- health + 25; energy <- energy - 10; hygiene <- hygiene - 20; happiness <- happiness + 5
	method thunder () = health <- health - 20 ; energy <- energy + 25; happiness <- happiness - 20
	method bath () = health <- health - 20 ; energy <- energy - 10; hygiene <- hygiene + 25; happiness <- happiness + 5
	method kill () =  health <- health - 20 ; energy <- energy - 10; happiness <- happiness + 20

	method isAlive () = if ((s#getHealth ()) <= 0 || energy <= 0 || hygiene <= 0 || happiness <= 0) then false else true

	method getHealth () = health - (int_of_float ((Unix.time ()) -. last_time))
	method getEnergy () = energy 
	method getHygiene () = hygiene
	method getHappiness () = happiness

	method getLastTime () = last_time 
end

let draw_square x y size =
	Graphics.moveto (x - (size / 2)) (y - (size / 2)) ;
	Graphics.lineto (x + size / 2) (y - (size / 2));
	Graphics.lineto (x + size / 2) (y + size / 2);
	Graphics.lineto (x - (size / 2)) (y + size / 2);
	Graphics.lineto (x - (size / 2)) (y - (size / 2))

let have_click_here (e:Graphics.status) x y size =
	if (e.button) then begin
		let left = (x - (size / 2)) in
		let top = (y - (size / 2)) in
		let bottom = (y + size / 2) in
		let right = (x + size / 2) in
		(*Printf.printf "%d %d %d %d -> %d %d\n" left top right bottom  e.mouse_x e.mouse_y;*)
		if (e.mouse_x >= left &&
			e.mouse_x <= right &&
			e.mouse_y >= top &&
			e.mouse_y <= bottom) then true else false
	end else false

let draw_bonhomme () =
	draw_square 200 300 20;
    draw_square 300 300 20;
    draw_square 250 250 20;
    draw_square 250 250 150;
    draw_square 210 200 20;
    draw_square 230 200 20;
    draw_square 250 200 20;
    draw_square 270 200 20;
    draw_square 290 200 20

let draw_menu () =
	draw_square 100 100 60 ;
	Graphics.moveto 80 90 ;
	Graphics.draw_string "EAT";

	draw_square 200 100 60 ;
	Graphics.moveto 180 90 ;
	Graphics.draw_string "THUNDER" ;

	draw_square 300 100 60 ;
	Graphics.moveto 280 90 ;
	Graphics.draw_string "BATH" ;

	draw_square 400 100 60 ;
	Graphics.moveto 380 90 ;
	Graphics.draw_string "KILL" ;

	draw_square 468 468 60 ;
	Graphics.moveto 450 460 ;
	Graphics.draw_string "SAVE"

let draw_stats (numbers) =
	Graphics.moveto 80 400 ;
	Graphics.draw_string ("HEALT : " ^ string_of_int (numbers#getHealth ()));
	Graphics.moveto 180 400 ;
	Graphics.draw_string ("ENERGY : " ^ string_of_int (numbers#getEnergy ()));
	Graphics.moveto 280 400 ;
	Graphics.draw_string ("HYGIENE : " ^ string_of_int (numbers#getHygiene ()));
	Graphics.moveto 380 400 ;
	Graphics.draw_string ("HAPPY : " ^ string_of_int (numbers#getHappiness ()))

let save file string =
	try
		let channel = open_out file in
		output_string channel string;
		close_out channel
	with | _ -> ()

let read filename = 
	let lines = ref [] in
	try
		let fd = open_in filename in
		while true; do
		lines := input_line fd :: !lines
		done; !lines
	with | _ -> !lines

let save_objet numbers = 
	save "save.itama" (
		string_of_int (numbers#getHealth ()) ^ "\n" ^
		string_of_int (numbers#getEnergy ()) ^ "\n" ^
		string_of_int (numbers#getHygiene ()) ^ "\n" ^
		string_of_int (numbers#getHappiness ()) ^ "\n" ^
		""
		)

let get_objet () =
	try
		let lines = read "save.itama" in
		match lines with
		| [d; c; b; a] -> new stats (int_of_string a) (int_of_string b) (int_of_string c) (int_of_string d)
		| _ -> new stats 100 100 100 100
	with | _ -> new stats 100 100 100 100



let rec loop (numbers) =
	Graphics.clear_graph ();
	draw_bonhomme ();
    draw_stats (numbers);
    draw_menu ();

  let e = Graphics.wait_next_event [Button_down] in
  let mouse_description = Printf.sprintf "Mouse position: %d,%d" e.mouse_x e.mouse_y in
  let key_description = if e.keypressed then Printf.sprintf "Key %c was pressed" e.key else "" in 

  if have_click_here e 200 100 60 then numbers#thunder ();
  if have_click_here e 300 100 60 then numbers#bath ();
  if have_click_here e 400 100 60 then numbers#kill ();
  if have_click_here e 100 100 60 then numbers#eat ();

  if have_click_here e 468 468 60 then save_objet numbers;

  Graphics.moveto 0 100; Graphics.draw_string key_description;
  Graphics.moveto 0 0; Graphics.draw_string mouse_description;


  if (numbers#isAlive ()) then loop (numbers) else begin
	  	let rec game_over () = Graphics.clear_graph ();
		  	Graphics.moveto 220 250 ;
		  	Graphics.draw_string "Game over x_x" ;
		  	Unix.sleep 10;
		  	game_over ()
  	 	in game_over ()
  end


let () =
	let numbers = get_objet () in
    Graphics.open_graph(" 500x500");
    try
		loop (numbers)
		with
  	| _ -> ()
    (*Graphics.close_graph ()*)