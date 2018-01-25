<?php
$_SESSION['user_id'] = '';
$_SESSION['flashmessage'] = 'Vous êtes déconnecté.';
header('Location: ./');
exit();