type 'a tree = Nil | Node of 'a * 'a tree * 'a tree

let rec size node =
	match node with
		| Nil -> 0	
		| Node (texte, l, r) -> 1 + (size l) + (size r)

let rec height node =
	match node with
		| Nil -> 0	
		| Node (texte, l, r) -> 1 + (max (height l) (height r))

let draw_square x y size =
	Graphics.moveto (x - (size / 2)) (y - (size / 2)) ;
	Graphics.lineto (x + size / 2) (y - (size / 2));
	Graphics.lineto (x + size / 2) (y + size / 2);
	Graphics.lineto (x - (size / 2)) (y + size / 2);
	Graphics.lineto (x - (size / 2)) (y - (size / 2)) 

let rec draw_tree_node node startx starty =
	draw_square (startx) (starty) 100 ;
	Graphics.moveto (startx - 40) starty ;
	match node with
		| Nil -> Graphics.draw_string " Nil" ;
		| Node (texte, a, b) -> begin
						Graphics.draw_string texte;
						Graphics.moveto (startx + 50) (starty);
						Graphics.lineto (startx + 100) (starty + (120 * ((height node))))  ;
						draw_tree_node a (startx + 150) (starty + (120 * ((height node)))) ;
						Graphics.moveto (startx + 50) (starty) ;
						Graphics.lineto (startx + 100) starty ;
						draw_tree_node b (startx + 150) starty 
						end




let draw_tree node =
	draw_tree_node node 100 100


let () =
	Graphics.open_graph(" 1200x1200");
    let a = Node("aaa", Nil, Nil) in
    let b = Node("bbb", Nil, a) in
    let c = Node("ccc", a, b) in
    let d = Node("ddd", c, a) in
    let e = Node("eee", d, c) in
    draw_tree e ;
    ignore(Graphics.read_key ()) 