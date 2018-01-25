<h1>Bienvenue, chef !</h1>
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





<h2>Listing des catégories</h2>
<form action="" method="POST">
	<table class="p100" style="font-size: 20px;">
		<tr>
			<td class="right" style="width:20%;">ID</td>
			<td class="left">NAME</td>
		</tr>
		<?php
		foreach ($view['categories'] as $line) {
			?>
			<tr>
				<td class="right" style="width:20%;"><?=$line['id']?></td>
				<td class="left"><?=$line['name']?></td>
			</tr>
			<?php
		}
		?>
	</table>
</form>


<h2>Ajouter un produit</h2>
<!-- new_product($conn, $_POST['id_category'], $_POST['name'], $_POST['price'], $_POST['picture'], $_POST['description']); -->
<?php
include('_form_product.php');