<?php
include ('bdd.php');
$sql = file_get_contents('dump.sql');
$conn = get_conn_notdb();
mysqli_multi_query($conn, $sql);

