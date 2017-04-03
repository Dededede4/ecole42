#!/usr/bin/php
<?php
if ($argc != 2)
	exit();

if ($argv[1] == "mais pourquoi cette demo ?")
	echo "Tout simplement pour qu'en feuilletant le sujet\non ne s'apercoive pas de la nature de l'exo\n";
if ($argv[1] == "mais pourquoi cette chanson ?")
	echo "Parce que Kwame a des enfants\n";
if ($argv[1] == "vraiment ?")
{
	$nbr = file_get_contents('tmp');
	if ($nbr == NULL)
		$nbr = 0;
	$nbr++;
	if ($nbr == 1)
		echo "Nan c'est parce que c'est le premier avril\n";
	if ($nbr == 2)
		echo "Oui il a vraiment des enfants\n";
	file_put_contents('tmp', "$nbr");
}


