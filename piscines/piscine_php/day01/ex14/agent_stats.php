#!/usr/bin/php
<?php

function moyenne()
{
	$som = 0;
	$i = 0;
	while (true)
	{
		if (!$line = fgets(STDIN))
			break;
		explode(':', $line);
		$som += $line[1];
		$i++;
	}
	echo $som / $i."\n";
}

function ecart_moulinette()
{

}


function moyenne_user()
{

}

if ($argc != 2)
	exit();
$argv[0]();