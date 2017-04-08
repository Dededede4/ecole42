<?php
$view = array();
$view['path'] = 'archives.php';
$view['archives'] = get_archives($conn, $current_user['id']);