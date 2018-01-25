#!/usr/bin/php
<?php
if ($argc != 2)
{
	echo 'Incorrect Parameters'."\n";
	exit();
}

function err()
{
	echo 'Syntax Error'."\n";
	exit(0);
}

$query = trim($argv[1]);

$arr = explode('*', $query);
if (count($arr) == 2)
{
	$arr[0] = trim($arr[0]);
	$arr[1] = trim($arr[1]);
	if (is_numeric($arr[0]) && is_numeric($arr[1]))
		echo $arr[0] * $arr[1]."\n";
	else
		err();
	exit(0);
}

$arr = explode('/', $query);
if (count($arr) == 2)
{
	$arr[0] = trim($arr[0]);
	$arr[1] = trim($arr[1]);
	if (is_numeric($arr[0]) && is_numeric($arr[1]))
		echo $arr[0] / $arr[1]."\n";
	else
		err();
	exit(0);
}

$arr = explode('+', $query);
if (count($arr) == 2)
{
	$arr[0] = trim($arr[0]);
	$arr[1] = trim($arr[1]);
	if (is_numeric($arr[0]) && is_numeric($arr[1]))
		echo $arr[0] + $arr[1]."\n";
	else
		err();
	exit(0);
}

$arr = explode('-', $query);
if (count($arr) == 2)
{
	$arr[0] = trim($arr[0]);
	$arr[1] = trim($arr[1]);
	if (is_numeric($arr[0]) && is_numeric($arr[1]))
		echo $arr[0] - $arr[1]."\n";
	else
		err();
	exit(0);
}


$arr = explode('%', $query);
if (count($arr) == 2)
{
	$arr[0] = trim($arr[0]);
	$arr[1] = trim($arr[1]);
	if (is_numeric($arr[0]) && is_numeric($arr[1]))
		echo $arr[0] % $arr[1]."\n";
	else
		err();
	exit(0);
}

err();
/*
if ($sign == '+')
	echo $argv[1] + $argv[3]."\n";
if ($sign == '-')
	echo $argv[1] - $argv[3]."\n";
if ($sign == '*')
	echo $argv[1] * $argv[3]."\n";
if ($sign == '/')
	echo $argv[1] / $argv[3]."\n";
if ($sign == '%')
	echo $argv[1] % $argv[3]."\n";*/