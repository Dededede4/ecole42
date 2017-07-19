<?php

function addCart($product_id, $quantity)
{
	$finded = false;
	$articles = $_SESSION['cart'];
	if (!$articles)
		$articles = array();
	$len = count($articles);
	for ($i=0; $i < $len; $i++) { 
		if ($articles[$i]['id'] == $product_id)
		{
			$articles[$i]['quantity'] += $quantity;
			if ($articles[$i]['quantity'] > 9)
				$articles[$i]['quantity'] = 9;
			$finded = true;
		} 
	}
	if (!$finded)
	{
		$articles[] = array(
			'id' => $product_id,
			'quantity' => $quantity,
		);
	}
	$_SESSION['cart'] = $articles;
}



$view = array();
// current_user['is_admin']
$product = get_produit($conn, $_GET['id']);
if ($product)
{
	$view['path'] = 'product.php';
	$view['product'] = $product;
	if ($current_user['is_admin'] && $_GET['action'] === 'del')
	{
		del_produit($conn, $product['id']);
		$_SESSION['flashmessage'] = 'Le produit « '.$product['name'].' » a bien été supprimé.';
		header('Location: ./');
		exit();
	}
	if ($current_user['is_admin'] && $_POST['create_product'] === 'ok')
	{
		edit_product($conn, $product['id'], $_POST['id_category'], $_POST['name'], $_POST['price'], $_POST['picture'], $_POST['description']);
		$_SESSION['flashmessage'] = 'Le produit « '.$product['name'].' » a bien été modifié.';
		header('Location: ./?page=product&id='.$product['id']);
		exit(0);
	}
	if ($_POST['buy_product'] === 'ok')
	{
		if (ctype_digit($_POST['quantity']) && $_POST['quantity'] > 0 && $_POST['quantity'] < 10)
		{
			addCart($product['id'], $_POST['quantity']);
			$_SESSION['flashmessage'] = 'Le produit « '.$product['name'].' » a été ajouté à votre panier.';
			header('Location: ./?page=panier');
			exit(0);
		}
/*
		$cart = get_cart($conn, $current_user['id']);
		//var_dump($_POST);
		if (!$cart)
		{
			var_dump('bite');
			new_cart($conn, $current_user['id']);
		}*/
		//var_dump($_POST);
	}
	/*
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
	$view['categories'] = all_category($conn);*/
}
else
{
	$view['path'] = '404.php';
}