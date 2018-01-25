#!/usr/bin/php
<?php
if ($argc <= 1)
	exit(0);
$words = array();
for ($i=1; $i < $argc; $i++) { 
	$words = array_merge($words, explode(' ', $argv[$i]));
}
$arr = array_filter($words);
sort($arr);
echo implode("\n", $arr)."\n";