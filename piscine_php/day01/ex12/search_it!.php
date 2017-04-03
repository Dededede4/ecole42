#!/usr/bin/php
<?php
for ($i=2; $i < $argc; $i++) {
	$arr = explode(":", $argv[$i]);
	if (count($arr) != 2)
		exit();
	if ($arr[0] == $argv[1])
	{
		echo $arr[1]."\n";
		exit(0);
	}
}