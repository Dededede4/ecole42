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
		if ($_POST['old_cat_id'] != '' && $_POST['new_cat_name'] != '')
		{
			edit_category($conn, $_POST['old_cat_id'], $_POST['new_cat_name']);
			$_SESSION['flashmessage'] = 'Catégorie modifiée.';
		}
		if ($_POST['create_product'] != '')
		{
			new_product($conn, $_POST['id_category'], $_POST['name'], $_POST['price'], $_POST['picture'], $_POST['description']);
			$_SESSION['flashmessage'] = 'Nouveau produit crée.';
		}
		if ($_POST['login'] != '' && $_POST['passwd'] != '')
		{
			new_user($conn, $_POST['login'], $_POST['passwd'], $_POST['address'], $_POST['tel'], $_POST['is_admin']);
			$_SESSION['flashmessage'] = 'Nouveau utilisateur crée.';
		}
		if ($_POST['old_id_user'] != '' && ($_POST['new_id_user'] != '' || $_POST['new_passwd'] != '' || $_POST['new_address'] != '' || $_POST['new_tel'] != '' || $_POST['new_is_admin'] != ''))
		{
			edit_user($conn, $_POST['old_id_user'], $_POST['new_id_user'], $_POST['new_passwd'], $_POST['new_address'], $_POST['new_tel'], $_POST['new_is_admin']);
			$_SESSION['flashmessage'] = 'Utilisateur modifié.';
		}
		if ($_POST['close'] != '')
		{
			del_category($conn, $_POST['id']);
			$_SESSION['flashmessage'] = 'Catégorie supprimée.';
		}
		if ($_POST['user_close'] != '')
		{
			del_user($conn, $_POST['id']);
			$_SESSION['flashmessage'] = 'Utilisateur supprimé.';
		}
	}
	$view['categories'] = all_category($conn);
}
else
{
	$view['path'] = '404.php';
}
