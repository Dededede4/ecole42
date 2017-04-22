<?php
session_start();
/* speak.php permet d’ajouter un message au chat. Il doit vérifier que l’utilisateur est
correctement loggué. C’est un formulaire qui s’appelle lui-même avec simplement
le champ msg passé en POST. L’identité de l’utilisateur est tiré de la session.
speak.php doit remplir un tableau serializé dans un fichier /private/chat. Chaque
élèment du tableau est un tableau contenant : “login”, “time”, “msg”. Le champ
“login” est bien sûr le login de l’utilisateur qui a posté le message. Le champ time
est la date/heure à laquelle le message a été envoyé, au format timestamp. Le
champ msg est évidement le message. 

Attention ! Vous devez locker le fichier avec flock durant toute son utilisation (lecture
/ écriture) pour ne pas le corrompre en cas d’écriture simultanée par 2 utilisateurs,
ni de lecture partielle pendant l’écriture par un autre processus
*/

$dir = '../private/';
$file = 'chat';
$path = $dir.$file;

if ($_SESSION['loggued_on_user'] == '')
{
	echo 'Error'."\n";
}
else
{
	if ($_POST['submit'] === 'OK')
	{
		$newmessage = array(
			'time' => time(),
			'msg'  => $_POST['msg'],
			'usr'  => $_SESSION['loggued_on_user'],
		);
		if (!file_exists($path))
		{
			$msgs = array();
			mkdir($dir);
		}
		else
			$msgs = unserialize(file_get_contents($path));
		$msgs[] = $newmessage;

		$fp = fopen($path, "w");
		if (flock($fp, LOCK_EX)) {
			file_put_contents($path, serialize($msgs));
			flock($fp, LOCK_UN);
			fclose($fp);
		}
	}
	?>
	<form action="#" method="post">
	Dites un truc: <input type="text" name="msg" value="" autofocus/>
	<br />
	<input type="submit" name="submit" value="OK"/>
	</form>
	<script langage="javascript">top.frames['chat'].location = 'chat.php';</script>
	<?php
}