<?php
// auth
function auth($login, $passwd)
{
	$dir = '../private/';
	$file = 'passwd';
	$path = $dir.$file;
	$secret = 'w~5q+},m{#mzJAby6XSB.QN55wVr?t(e$V478RXR6*28t2$3q93P85A,88mT(S&27{;CFz3b8yGCw?az{t5Anm3;4W$=}J4549p;sX(p]Zcpf<.(PSR6a6$7nQPP;';

	if (!file_exists($path))
		return (false);
	$users = unserialize(file_get_contents($path));
	foreach ($users as $user) {
		if ($user['login'] === $login && hash('whirlpool', ($passwd . $secret)) === $user['passwd'])
			return (true);
	}
	return (false);
}