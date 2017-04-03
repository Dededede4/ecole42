#!/usr/bin/php
<?php
if ($argc != 4)
{
	echo 'Incorrect Parameters'."\n";
	exit();
}
$sign = trim($argv[2]);
if ($sign == '+')
	echo $argv[1] + $argv[3]."\n";
if ($sign == '-')
	echo $argv[1] - $argv[3]."\n";
if ($sign == '*')
	echo $argv[1] * $argv[3]."\n";
if ($sign == '/')
	echo $argv[1] / $argv[3]."\n";
if ($sign == '%')
	echo $argv[1] % $argv[3]."\n";