<?php
$view = array();
$view['path'] = 'acceuil.php';

$view['products'] = (!ctype_digit($_GET['category'])) ? all_produits($conn) : all_produits_cat($conn, $_GET['category']);
$view['categories'] = all_categories($conn);
