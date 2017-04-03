#!/usr/bin/php
<?php
function getAlfa($unsorted)
{
	$arr = array(); 
	foreach ($unsorted as $value) {
		if (ctype_alpha($value))
			$arr[] = $value;
	}
	return $arr;
}

function getNbr($unsorted)
{
	$arr = array();
	foreach ($unsorted as $value) {
		if (ctype_digit($value))
			$arr[] = $value;
	}
	return $arr;
}

function getRest($unsorted)
{
	$arr = array();
	foreach ($unsorted as $value) {
		if (!ctype_digit($value) && !ctype_alpha($value))
			$arr[] = $value;
	}
	return $arr;
}

function cmp($a, $b)
{
	$a = strtolower($a);
	$b = strtolower($b);
	return ($a > $b);
}

if ($argc <= 1)
	exit(0);

$words = array();
for ($i=1; $i < $argc; $i++) { 
	$words = array_merge($words, explode(' ', $argv[$i]));
}
$words = array_filter($words);

$words_alpha = getAlfa($words);

$words_nbr = getNbr($words);
$words_rest = getRest($words);

usort($words_alpha, "cmp");
sort($words_nbr, SORT_STRING);
sort($words_rest, SORT_STRING);

$end = array();
$end = array_merge($end, $words_alpha);
$end = array_merge($end, $words_nbr);
$end = array_merge($end, $words_rest);


echo implode("\n", $end)."\n";