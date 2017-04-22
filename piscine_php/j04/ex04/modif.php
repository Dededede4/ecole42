<?php
/*create.php et modif.php doivent afficher “OK” en cas de succés ET rediriger l’utilisateur
vers la page d’accueil au moyen d’un header “Location :”. L’utilisateur
devra ensuite s’identifier.*/
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

function testpassword($username, $password, $users)
{
	$secret = 'w~5q+},m{#mzJAby6XSB.QN55wVr?t(e$V478RXR6*28t2$3q93P85A,88mT(S&27{;CFz3b8yGCw?az{t5Anm3;4W$=}J4549p;sX(p]Zcpf<.(PSR6a6$7nQPP;';
	foreach ($users as $user) {
		if ($user['login'] === $username && hash('whirlpool', ($password . $secret)) === $user['passwd'])
			return (true);
	}
	return (false);
}

function editaccountpwd($username, $password, $users)
{
	$secret = 'w~5q+},m{#mzJAby6XSB.QN55wVr?t(e$V478RXR6*28t2$3q93P85A,88mT(S&27{;CFz3b8yGCw?az{t5Anm3;4W$=}J4549p;sX(p]Zcpf<.(PSR6a6$7nQPP;';
	$len = count($users);
	for ($i=0; $i < $len; $i++) { 
		if ($users[$i]['login'] === $username)
		{
			$users[$i]['passwd'] = hash('whirlpool', ($password . $secret));
			break;
		}
	}
	return ($users);
}

if ($_POST['submit'] !== 'OK')
	echo 'Error'."\n";
else
{
	if (!file_exists($path))
	{
		echo 'ERROR'."\n";
	}
	else
	{
		$users = unserialize(file_get_contents($path));
		if (!existaccount($_POST['login'], $users))
			echo 'ERROR'."\n";
		else
		{
			if (!testpassword($_POST['login'], $_POST['oldpw'], $users))
				echo 'ERROR'."\n";
			else
			{
				$users = editaccountpwd($_POST['login'], $_POST['newpw'], $users);
				file_put_contents($path, serialize($users));
				header('Location: ./');
				echo 'OK'."\n";
			}
		}
	}
}
