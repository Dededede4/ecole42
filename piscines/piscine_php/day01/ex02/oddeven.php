#!/usr/bin/php
<?php
while (true)
{
	echo 'Entrez un nombre: ';
	if (!$str = fgets(STDIN))
		break;
	$str = rtrim($str);
	if (!ctype_digit($str))
	{
		echo '\''.$str.'\' n\'est pas un chiffre'."\n";
		continue;
	}
	$nbr = intval($str);
	echo 'Le chiffre '.$nbr.' est '.(($str % 2) ? 'Impair' : 'Pair')."\n";
}
echo "\n";
