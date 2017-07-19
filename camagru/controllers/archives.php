<?php
if (!$current_user)
{
	$_SESSION['flashmessage'] = 'Vous devez être connecté.';
	header('Location: ./?page=connexion');
	exit(0);
}
$view = array();
$view['path'] = 'archives.php';
$view['archives'] = get_archives($conn, $current_user['id']);
