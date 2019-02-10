<?php

$vars = [];

include('theta.php');

$t0 = isset($vars['theta0']) ? $vars['theta0'] : 0;
$t1 = isset($vars['theta1']) ? $vars['theta1'] : 0;

$value = readline('Enter value :');
if (is_numeric($value))
{
	echo $t0 + $t1 * $value."\n"; 
}
else
{
	echo 'No numeric value'."\n";
}