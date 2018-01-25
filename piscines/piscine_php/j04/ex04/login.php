<?php
/*
• login.php en cas de succés doit afficher une iframe, splittée horizontalement, la
partie du haut doit mesurer 550px de la page et contenir “chat.php”, la partie du
bas doit mesurer 50px et contenir “speak.php”
*/
include('auth.php');

session_start();
if (auth($_POST['login'], $_POST['passwd']))
{
	$_SESSION['loggued_on_user'] = $_POST['login'];
	?>
<iframe name="chat" src="chat.php" width="100%" height="550px"></iframe>
<iframe name="speak" src="speak.php" width="100%" height="50px"></iframe>
	<?
}
else
{
	$_SESSION['loggued_on_user'] = '';
	echo 'Le mot de passe est mauvais. ¯\_(ツ)_/¯'."\n";
}