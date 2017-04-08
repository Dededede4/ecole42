<?php
$view = array();

if ($_SERVER['REQUEST_METHOD'] === 'POST')
{
	if (isset($_POST['login']) && isset($_POST['passwd']) && $_POST['login'] != '' && $_POST['passwd'] != '')
	{
		$id = auth_user($conn, $_POST['login'], $_POST['passwd']);
		if ($id)
		{
			$_SESSION['user_id'] = $id;
			$_SESSION['flashmessage'] = 'Vous êtes connecté.';
			header('Location: ./');
			exit();
		}
		else
		{
			$view['error'] = 'Votre mot de passe est mauvais.';
		}
	}
	else
		$view['error'] = 'Il manque un champ du formulaire.';
}
$view['path'] = 'connexion.php';
