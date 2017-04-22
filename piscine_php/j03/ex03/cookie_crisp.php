<?php
if ($_GET['name'] == '')
	exit();
if ($_GET['action'] == 'set')
{
	if ($_GET['value'] == '')
		exit();
	setcookie($_GET['name'], $_GET['value'], time() + (86400 * 30));
}
elseif ($_GET['action'] == 'get')
{
	if ($_COOKIE[$_GET['name']] != '')
		echo $_COOKIE[$_GET['name']]."\n";
}
if ($_GET['action'] == 'del')
	setcookie($_GET['name'], "", 1);
