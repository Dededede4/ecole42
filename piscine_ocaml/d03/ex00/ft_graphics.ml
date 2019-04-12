type 'a tree = Nil | Node of 'a * 'a tree * 'a tree

let draw_square x y size =
	Graphics.moveto (x - (size / 2)) (y - (size / 2)) ;
	Graphics.lineto (x + size / 2) (y - (size / 2));
	Graphics.lineto (x + size / 2) (y + size / 2);
	Graphics.lineto (x - (size / 2)) (y + size / 2);
	Graphics.lineto (x - (size / 2)) (y - (size / 2)) 

let draw_tree_node node =
	draw_square 100 100 100 ;
	Graphics.moveto 60 100 ;
	match node with
		| Nil -> Graphics.draw_string " Nil"
		| Node (texte, _, _) -> Graphics.draw_string texte;
	Graphics.moveto 150 100;
	Graphics.lineto 250 300 ;
	Graphics.draw_string " Nil" ;
	draw_square 300 300 100 ;
	Graphics.moveto 150 100 ;
	Graphics.lineto 250 100 ;
	Graphics.draw_string " Nil" ;
	draw_square 300 100 100 

let () =
	Graphics.open_graph(" 600x600");
	draw_tree_node (Node ("Pouet lol", Nil, Nil));
	ignore(Graphics.read_key ())
