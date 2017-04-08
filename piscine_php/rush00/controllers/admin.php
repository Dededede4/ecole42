<?php
$view = array();
if ($current_user['is_admin'])
{
	$view['path'] = 'admin.php';
	if ($_SERVER['REQUEST_METHOD'] === 'POST')
	{
		if ($_POST['categorie_new'] != '')
		{
			new_category($conn, $_POST['categorie_new']);
			$_SESSION['flashmessage'] = 'Nouvelle categorie crée.';
		}
		if ($_POST['create_product'] != '')
		{
			new_product($conn, $_POST['id_category'], $_POST['name'], $_POST['price'], $_POST['picture'], $_POST['description']);
			$_SESSION['flashmessage'] = 'Nouveau produit crée.';
		}
	}
	$view['categories'] = all_category($conn);
}
else
{
	$view['path'] = '404.php';
}