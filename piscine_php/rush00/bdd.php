<?php

// Test username / password combinaison, return id

function shit($result)
{
	$all = array();

	while(($row = mysqli_fetch_assoc($result))) {
	    $all[] = $row;
	}
	return ($all);
}


function auth_user($conn, $username, $password){
	$req = 'SELECT id FROM user WHERE username=\''.mysqli_real_escape_string($conn, $username).'\' AND password=\''.my_crypt($password).'\' LIMIT 1';
	$result = mysqli_query($conn, $req);
	if (mysqli_num_rows($result) == 0)
		return 0;
	$line = mysqli_fetch_assoc($result);
	return (int)$line['id'];
}

function user_infos($conn, $id)
{
	$req = 'SELECT * FROM user WHERE id=\''.mysqli_real_escape_string($conn, $id).'\' LIMIT 1';
	$result = mysqli_query($conn, $req);
	if (mysqli_num_rows($result) == 0)
		return 0;
	return mysqli_fetch_assoc($result);
}

function new_category($conn, $name)
{
	$req = 'INSERT INTO category (name) VALUES (\''.mysqli_real_escape_string($conn, $name).'\');';
	$result = mysqli_query($conn, $req);
}

function new_product($conn, $id_categories, $name, $price, $picture, $description)
{
	$req = 'INSERT INTO product (name, price, picture, description)
	VALUES ( \''.mysqli_real_escape_string($conn, $name).'\',
			 \''.mysqli_real_escape_string($conn, intval($price * 100)).'\',
			 \''.mysqli_real_escape_string($conn, $picture).'\',
			 \''.mysqli_real_escape_string($conn, $description).'\'
			 );';
	mysqli_query($conn, $req);
	$last_id = mysqli_insert_id($conn);
	$id_categories = explode(',', $id_categories);
	$sql = '';
	foreach ($id_categories as $id_category) {
		$sql .= 'INSERT INTO category_product (id_product, id_category) VALUES (
			\''.mysqli_real_escape_string($conn, $last_id).'\', \''.mysqli_real_escape_string($conn, $id_category).'\'
		);';
	}
	//echo $sql;
	mysqli_multi_query($conn, $sql);
}

function edit_product($conn, $id, $id_categories, $name, $price, $picture, $description)
{
	$id_categories = explode(',', $id_categories);
	$sql = 'DELETE FROM category_product WHERE id_product = \''.mysqli_real_escape_string($conn, $id).'\'; ';

	foreach ($id_categories as $id_category) {
		$sql .= 'INSERT INTO category_product (id_product, id_category) VALUES (
			\''.mysqli_real_escape_string($conn, $id).'\', \''.mysqli_real_escape_string($conn, $id_category).'\'
		);';
	}

	$sql .= 'UPDATE product SET
			name = \''.mysqli_real_escape_string($conn, $name).'\',
			price = \''.mysqli_real_escape_string($conn, intval($price * 100)).'\',
			picture =  \''.mysqli_real_escape_string($conn, $picture).'\',
			description = \''.mysqli_real_escape_string($conn, $description).'\'
			WHERE id = \''.mysqli_real_escape_string($conn, $id).'\' LIMIT 1;';

	//var_dump($sql);
	$result = mysqli_multi_query($conn, $sql);
}

function all_categories($conn)
{
	$req = 'SELECT * FROM category;'; 
	return shit(mysqli_query($conn, $req));
}

function all_produits($conn)
{
	$req = 'SELECT id, name, ROUND(price / 100, 2) as price, picture, description FROM product;'; 
	return shit(mysqli_query($conn, $req));
}

function all_produits_cat($conn, $cat)
{
	$req = 'SELECT * FROM `category_product` LEFT JOIN product ON product.id = category_product.id_product WHERE id_category = \''.mysqli_real_escape_string($conn, $cat).'\''; 
	return shit(mysqli_query($conn, $req));
}

function get_produit($conn, $id)
{
	$req = 'SELECT id, name, ROUND(price / 100, 2) as price, picture, description FROM product WHERE id = \''.mysqli_real_escape_string($conn, $id).'\' LIMIT 1;';
	$req = mysqli_query($conn, $req);
	if (mysqli_num_rows($req) == 0)
		return false;
	$sql = 'SELECT id_category FROM category_product WHERE  id_product = \''.mysqli_real_escape_string($conn, $id).'\';';
	$product_data = mysqli_fetch_assoc($req);
	$req = mysqli_query($conn, $sql);
	if (mysqli_num_rows($req))
	{
		$tab = shit($req);
		$cat = array();
		foreach ($tab as $val) {
			$cat[] = $val['id_category'];
		}
		$product_data['id_category'] =  implode(',', $cat);
	}
	//var_dump($product_data['category']);
	return $product_data;
}

function del_produit($conn, $id)
{
	$req = 'DELETE FROM product WHERE id = \''.mysqli_real_escape_string($conn, $id).'\' LIMIT 1';
	mysqli_query($conn, $req);
}

function all_category($conn)
{
	$req = 'SELECT * FROM category;';
	return shit(mysqli_query($conn, $req));
}

function new_archive($conn, $user_id, $products)
{
	$req = 'INSERT INTO user_archive (id_user, time) VALUES (\''.mysqli_real_escape_string($conn, $user_id).'\', NOW());';
	mysqli_query($conn, $req);
	$last_id = mysqli_insert_id($conn);
	$sql = '';
	foreach ($products as $product) {
		$sql .= 'INSERT INTO archive_product (id_archive, id_product, price, quantity)
		VALUES (\''.$last_id.'\', \''.$product['id'].'\', \''.$product['price'].'\', \''.$product['quantity'].'\');';
	}
	mysqli_multi_query($conn, $sql);
}

function get_archives($conn, $user_id)
{
	$req = 'SELECT id, time FROM user_archive WHERE id_user =\''.mysqli_real_escape_string($conn, $user_id).'\'';
	$result = mysqli_query($conn, $req);
	if (mysqli_num_rows($result) == 0)
		return 0;
	$data = array();
	$archives = shit($result);
	foreach ($archives as $archive) {

		$req = 'SELECT * FROM archive_product LEFT JOIN product ON product.id = archive_product.id_product WHERE id_archive =\''.$archive['id'].'\'';
		$data[$archive['time']] = shit(mysqli_query($conn, $req));
	}
	return ($data);
}










