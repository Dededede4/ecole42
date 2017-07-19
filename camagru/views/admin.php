<h1>Bienvenue, chef !</h1>
<a href="?page=admin_archives">Voir toutes les factures de tous les clients de toute la terre</a>
<h2>Ajouter une catégorie</h2>
<form action="" method="POST">
	<table class="p100" style="font-size: 20px;">
		<tr>
			<td class="right" style="width:20%;">Nom de la catégorie</td>
			<td class="left"><input type="text" name="categorie_new" class="p100" value=""/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;"></td>
			<td class="left"><input type="submit" name="submit" value="OK" class="p100" style="margin-top:5px;"></td>
		</tr>
	</table>
</form>


<h2>Modifier une catégorie</h2>
<form action="" method="POST">
	<table class="p100" style="font-size: 20px;">
		<tr>
			<td class="right" style="width:20%;">ID de la catégorie à modifer</td>
			<td class="left"><input type="text" name="old_cat_id" class="p100" value=""/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;">Nouveau nom de la catégorie</td>
			<td class="left"><input type="text" name="new_cat_name" class="p100" value=""/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;"></td>
			<td class="left"><input type="submit" name="submit" value="OK" class="p100" style="margin-top:5px;"></td>
		</tr>
	</table>
</form>



<h2>Listing des catégories</h2>
	<table class="p100" style="font-size: 20px;">
		<tr>
			<td class="right" style="width:20%;">ID</td>
			<td class="left">NAME</td>
		</tr>
		<?php
		$i = 0;
		foreach ($view['categories'] as $line) {
			?>
			<tr><form action="" method="POST">
				<input type="hidden" name='id' value="<?=$line['id']?>">
				<td class="right" style="width:20%;"><?=$line['id']?></td>
				<td class="left"><?=$line['name']?></td>
				<td><input type="submit" name="close" value='Supprimer' class="p100" style="margin-top:5px;"></td>
			</form></tr>
			<?php
		}
		?>
	</table>


<h2>Ajouter un utiliateur</h2>
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
			<td class="right" style="width:20%;">Adresse</td>
			<td class="left"><input type="text" name="address" class="p100" value="<?=$_POST['address']?>"/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;">Téléphone</td>
			<td class="left"><input type="text" name="tel" class="p100"/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;">Admin (1 ou 0)</td>
			<td class="left"><input type="text" name="is_admin" class="p100"/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;"></td>
			<td class="left"><input type="submit" name="submit" value="OK" class="p100" style="margin-top:5px;"></td>
		</tr>
	</table>
</form>


<h2>Modifier un utilisateur</h2>
<form action="" method="POST">
	<table class="p100" style="font-size: 20px;">
		<tr>
			<td class="right" style="width:20%;">Identifiant à modifier</td>
			<td class="left"><input type="text" name="old_id_user" class="p100" value="<?=$_POST['login']?>"/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;">Identifiant</td>
			<td class="left"><input type="text" name="new_id_user" class="p100" value=""/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;">Mot de passe</td>
			<td class="left"><input type="password" name="new_passwd" class="p100"/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;">Adresse</td>
			<td class="left"><input type="text" name="new_address" class="p100" value="<?=$_POST['address']?>"/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;">Téléphone</td>
			<td class="left"><input type="text" name="new_tel" class="p100"/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;">Admin (1 ou 0)</td>
			<td class="left"><input type="text" name="new_is_admin" class="p100"/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;"></td>
			<td class="left"><input type="submit" name="submit" value="OK" class="p100" style="margin-top:5px;"></td>
		</tr>
	</table>
</form>

<h2>Listing des utilisateurs</h2>
	<table class="p100" style="font-size: 20px;">
		<tr>
			<td class="right" style="width:20%;">ID_user</td>
			<td class="left">Identifiant</td>
		</tr>
		<?php
		$users = array();
		$req = 'SELECT * FROM user';
		$users = shit(mysqli_query($conn, $req));
		foreach ($users as $user) {
			?>
			<tr><form action="" method="POST">
				<input type="hidden" name='id' value="<?=$user['id']?>">
				<td class="right" style="width:20%;"><?=$user['id']?></td>
				<td class="left"><?=$user['username']?></td>
				<td><input type="submit" name="user_close" value='Supprimer' class="p100" style="margin-top:5px;"></td>
			</form></tr>
			<?php
		}
		?>
	</table>


<h2>Ajouter un produit</h2>
<!-- new_product($conn, $_POST['id_category'], $_POST['name'], $_POST['price'], $_POST['picture'], $_POST['description']); -->
<?php
include('_form_product.php');
