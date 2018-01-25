<?php
$dir = '../private/';
$file = 'passwd';
$path = $dir.$file;
$secret = 'w~5q+},m{#mzJAby6XSB.QN55wVr?t(e$V478RXR6*28t2$3q93P85A,88mT(S&27{;CFz3b8yGCw?az{t5Anm3;4W$=}J4549p;sX(p]Zcpf<.(PSR6a6$7nQPP;';
function existaccount($username, $users)
{
	foreach ($users as $user) {
		if ($user['login'] == $username)
			return (true);
	}
	return (false);
}

if ($_POST['submit'] !== 'OK')
	echo 'Error'."\n";
else
{
	if (!file_exists($dir))
		mkdir($dir);
	if (!file_exists($path))
		$users = array();
	else
		$users = unserialize(file_get_contents($path));
	if (existaccount($_POST['login'], $users))
		echo 'ERROR'."\n";
	else
	{
		$users[] = array(
			'login' => $_POST['login'],
			'passwd' => hash('whirlpool', ($_POST['passwd'] . $secret)),
		);
		file_put_contents($path, serialize($users));
		echo 'OK'."\n";
	}
}
