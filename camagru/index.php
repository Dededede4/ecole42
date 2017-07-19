<?php
session_start();
include('bdd.php');
$conn = get_conn();

function my_crypt($str)
{
	$secret = 'w~5q+},m{#mzJAby6XSB.QN55wVr?t(e$V478RXR6*28t2$3q93P85A,88mT(S&27{;CFz3b8yGCw?az{t5Anm3;4W$=}J4549p;sX(p]Zcpf<.(PSR6a6$7nQPP;';
	return hash('whirlpool', ($str . $secret));
}

$page_name = empty($_GET['page']) ? 'acceuil' : $_GET['page'];
$valides_pages = array('acceuil', 'archives', 'connexion', 'inscription', 'panier', 'deconnexion', 'admin', 'product', 'admin_archives');
$page_name = (!in_array($page_name, $valides_pages)) ? '404' : $page_name;

$current_user = false;
if (!empty($_SESSION['user_id']))
{
	$current_user = user_infos($conn, $_SESSION['user_id']);
	if ($current_user == 0)
		header ('Location: ./?page=deconnexion');
}

if (file_exists('controllers/'.$page_name.'.php'))
	include('controllers/'.$page_name.'.php');
else
{
	$view = array();
	$view['path'] = $page_name.'.php';
}
if (isset($view))
	include('views/base.php');
