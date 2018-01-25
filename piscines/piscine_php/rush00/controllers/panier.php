<?php
$view = array();
$view['path'] = 'panier.php';

$panier = array();
if (!empty($_SESSION['cart']))
{
	foreach ($_SESSION['cart'] as $product_data) {
		$data = get_produit($conn, $product_data['id']);
		$panier[] = array_merge($product_data, $data);
	}
}
if ($_GET['action'] === 'archive')
{
	new_archive($conn, $current_user['id'], $panier);
	$_SESSION['cart'] = 0;
	$panier = array();
	$_SESSION['flashmessage'] = 'Vous avez bien claqué votre fric.';
	header('Location: ./?page=archives');
	exit(0);
}

$view['panier'] = $panier;