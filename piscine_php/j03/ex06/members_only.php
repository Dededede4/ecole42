<?php
$error = true;
if ($_SERVER['PHP_AUTH_USER'])
	$error = !($_SERVER['PHP_AUTH_USER'] === 'zaz' && $_SERVER['PHP_AUTH_PW'] === 'jaimelespetitsponeys');

if ($error)
{
	header('WWW-Authenticate: Basic realm=\'\'Espace membres\'\'');
    header('HTTP/1.0 401 Unauthorized');
    echo '<html><body>Cette zone est accessible uniquement aux membres du site</body></html>'."\n";
}
else
{
	$img = base64_encode(file_get_contents('../img/42.png'));
?>
<html><body>
Bonjour Zaz<br />
<img src='data:image/png;base64,<?=$img?>'>
</body></html>
<?php
}