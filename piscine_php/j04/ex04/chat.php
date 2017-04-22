<?php
session_start();
/*
chat.php permet d’afficher le contenu du fichier /private/chat en le formatant. Voir
l’exemple (attention à la timezone, http ://www.php.net/manual/en/timezones.php)
<script langage="javascript">top.frames['chat'].location = 'chat.php';</script>
*/

$dir = '../private/';
$file = 'chat';
$path = $dir.$file;

if ($_SESSION['loggued_on_user'] == '')
{
	echo 'Error'."\n";
}
else
{
		if (!file_exists($path))
			$msgs = array();
		else
			$msgs = unserialize(file_get_contents($path));
		for ($i=count($msgs) - 1; $i >= 0; $i--) { 
			echo '<p>'.date('d/m/Y à H:i:s', $msgs[$i]['time']).' <strong>'.$msgs[$i]['usr'].'</strong>: '.$msgs[$i]['msg'].'</p>';
		}
	?>
	<script type="text/javascript">
		setTimeout(function(){
		   window.location.reload(1);
		}, 2000);

	</script>
	<?php
}