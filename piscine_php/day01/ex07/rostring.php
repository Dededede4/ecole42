#!/usr/bin/php
<?php
$words = array_filter(explode(' ', $argv[1]));
$len = count($words);
for ($i=1; $i < $len; $i++) { 
	echo $words[$i]."\n";
}
echo $words[0]."\n";