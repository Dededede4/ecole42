<h1>Connectez-vous</h1>
<?php
	if (isset($view['error']))
	{
		echo '<strong style="color:red;">'.$view['error'].'</strong>';
	}
?>
<form action="" method="POST">
<table class="p100" style="font-size: 20px;">
	<tr>
		<td class="right" style="width:20%;">Identifiant</td>
		<td class="left"><input type="text" name="login" class="p100" value="<?=$_POST['login']?>"/></td>
	</tr>
	<tr>
		<td class="right" style="width:20%;">Mot de passe</td>
		<td class="left"><input type="password" name="passwd" class="p100"/></td>
	</tr>
	<tr>
		<td class="right" style="width:20%;"></td>
		<td class="left"><input type="submit" name="submit" value="OK" class="p100" style="margin-top:5px;"></td>
	</tr>
</table>

