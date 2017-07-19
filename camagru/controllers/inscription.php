<?php
$view = array();

if ($_SERVER['REQUEST_METHOD'] === 'POST')
{
	if (isset($_POST['login']) && isset($_POST['passwd']) && $_POST['login'] != '' && $_POST['passwd'] != '')
	{
		if (!check_user($conn, $_POST['login']))
		{
			$_SESSION['flashmessage'] = 'Cet identifiant est déjà pris.';
			header('Location: ./?page=inscription');
		}
		else
		{
			new_user($conn, $_POST['login'], $_POST['passwd'], $_POST['address'], $_POST['tel'], 0);
			$_SESSION['flashmessage'] = 'Vous êtes inscrit.';
			header('Location: ./?page=connexion');
		}
	}
	else
		$view['error'] = 'Il manque un champ du formulaire.';
}
$view['path'] = 'inscription.php';
