let a = [|"C'est l'histoire du ptit dej, vous la connaissez ? Non ? Pas de bol.";
"C'est l'histoire d'une blague vaseuse. Mets tes bottes"; 
"C'est l'histoire d'un pingouin qui respire par les fesses.Un jour il s’assoit et il meurt.";
"C'est quoi une chauve souris avec une perruque ? Une souris.";
 "Que dit un escargot quand il croise une limace ?Oh, un naturiste."|]

let () = Random.self_init ();
	print_endline (Array.get a (Random.int 5))