<?php

function ft_split($str)
{
	$tab = explode(' ', $str);
	sort($tab);
	return ($tab);
}