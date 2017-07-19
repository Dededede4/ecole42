<?php
$view = array();
if ($current_user['is_admin'])
{
	$view['path'] = 'admin_archives.php';
	$view['archives'] = get_all_archives($conn);
}
else
{
	$view['path'] = '404.php';
}
