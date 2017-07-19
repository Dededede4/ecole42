<?php

// Test username / password combinaison, return id

function get_conn()
{
	$servername = "localhost";
	$username = "root";
	$password = "root";
	$dbname = "bde42";
	$conn = mysqli_connect($servername, $username, $password, $dbname);
	if (!$conn) {
	    die("Connection failed: " . mysqli_connect_error());
	}
	return $conn;
}

function get_conn_notdb()
{
	$servername = "localhost";
	$username = "root";
	$password = "root";
	$conn = mysqli_connect($servername, $username, $password);
	if (!$conn) {
	    die("Connection failed: " . mysqli_connect_error());
	}
	return $conn;
}


function shit($result)
{
	if (!$result)
		return array();
	$all = array();

	while(($row = mysqli_fetch_assoc($result))) {
	    $all[] = $row;
	}
	return ($all);
}

function check_user($conn, $username)
{
	$req = 'SELECT id FROM user WHERE username=\''.mysqli_real_escape_string($conn, $username).'\' LIMIT 1';
	$result = mysqli_query($conn, $req);
	if (mysqli_num_rows($result) == 0)
		return 1;
	return 0;
}

function new_user($conn, $username, $password, $address, $tel, $is_admin)
{
	$hashed_pass = my_crypt($password);
	$req = 'INSERT INTO user (username, password, address, tel, is_admin)
	VALUES ( \''.mysqli_real_escape_string($conn, $username).'\',
			 \''.mysqli_real_escape_string($conn, $hashed_pass).'\',
			 \''.mysqli_real_escape_string($conn, $address ? $address : "").'\',
			 \''.mysqli_real_escape_string($conn, $tel ? $tel : "").'\',
			 \''.mysqli_real_escape_string($conn, $is_admin).'\'
			 );';
	mysqli_query($conn, $req);
}

function edit_user($conn, $old_id, $username, $password, $address, $tel, $is_admin)
{
	$hashed_pass = $password != '' ? my_crypt($password) : $password;
	$req = 'UPDATE user SET
			user.password='.(($password != '') ? '\''.mysqli_real_escape_string($conn, $hashed_pass).'\'' : 'user.password').',
			user.address='.(($address != '') ? '\''.mysqli_real_escape_string($conn, $address).'\'' : 'user.address').',
			user.tel='.(($tel != '') ? '\''.mysqli_real_escape_string($conn, $tel).'\'' : 'user.tel').',
			user.is_admin='.(($is_admin != '') ? '\''.mysqli_real_escape_string($conn, $is_admin).'\'' : 'user.is_admin').',
			user.username='.(($username != '') ? '\''.mysqli_real_escape_string($conn, $username).'\'' : 'user.username').'
			WHERE user.id=\''.mysqli_real_escape_string($conn, $old_id).'\' LIMIT 1';
	mysqli_query($conn, $req);
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

function edit_category($conn, $cat_id, $name)
{
	$sql = 'UPDATE category SET
			name = \''.mysqli_real_escape_string($conn, $name).'\' WHERE id=\''.mysqli_real_escape_string($conn, $cat_id).'\'';
	$result = mysqli_query($conn, $sql);
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
	$req = 'SELECT id, name, ROUND(price / 100, 2) as price, picture, description FROM `category_product` LEFT JOIN product ON product.id = category_product.id_product WHERE id_category = \''.mysqli_real_escape_string($conn, $cat).'\'';
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
	$req = 'DELETE FROM category_product WHERE id_product = \''.mysqli_real_escape_string($conn, $id).'\'';
	mysqli_query($conn, $req);
}

function del_user($conn, $id)
{
	$req = 'DELETE FROM user WHERE id = \''.mysqli_real_escape_string($conn, $id).'\' LIMIT 1';
	mysqli_query($conn, $req);
}

function del_category($conn, $cat_id)
{
	$req = 'DELETE FROM category WHERE id = \''.mysqli_real_escape_string($conn, $cat_id).'\' LIMIT 1';
	mysqli_query($conn, $req);
	$req = 'DELETE FROM category_product WHERE id_category = \''.mysqli_real_escape_string($conn, $cat_id).'\'';
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
		VALUES (\''.$last_id.'\', \''.$product['id'].'\', \''.($product['price'] * 100).'\', \''.$product['quantity'].'\');';
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

		$req = 'SELECT id_archive, id_product, ROUND(archive_product.price / 100, 2) as price, quantity FROM archive_product LEFT JOIN product ON product.id = archive_product.id_product WHERE id_archive =\''.$archive['id'].'\'';
		$data[$archive['time']] = shit(mysqli_query($conn, $req));
	}
	return ($data);
}

function get_all_archives($conn)
{
	$req = 'SELECT id, time FROM user_archive';
	$result = mysqli_query($conn, $req);
	if (mysqli_num_rows($result) == 0)
		return 0;
	$data = array();
	$archives = shit($result);
	foreach ($archives as $archive) {

		$req = 'SELECT id_archive, id_product, ROUND(archive_product.price / 100, 2) as price, quantity FROM archive_product LEFT JOIN product ON product.id = archive_product.id_product WHERE id_archive =\''.$archive['id'].'\'';
		$data[$archive['time']] = shit(mysqli_query($conn, $req));
	}
	return ($data);
}