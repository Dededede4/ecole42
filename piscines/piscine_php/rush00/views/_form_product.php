<form action="" method="POST">
	<input type="hidden" name="create_product" value="ok">
	<table class="p100" style="font-size: 20px;">
		<tr>
			<td class="right" style="width:20%;">ID de category</td>
			<td class="left"><input type="text" name="id_category" class="p100" value="<?=$view['product']['id_category'];?>"/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;">Nom du produit</td>
			<td class="left"><input type="text" name="name" class="p100" value="<?=$view['product']['name'];?>"/></"/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;">Prix du produit (ex : 5.42)</td>
			<td class="left"><input type="text" name="price" class="p100" value="<?=$view['product']['price'];?>"/></"/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;">URL de la photo (soit http soit ./)</td>
			<td class="left"><input type="text" name="picture" class="p100" value="<?php
			echo ($view['product']['picture']) ? $view['product']['picture'] : 'img/products'; ?>"/></td>
		</tr>
		<tr>
			<td class="right" style="width:20%;">Description du produit</td>
			<td class="left">
			<textarea name="description" class="p100" rows="10"><?=$view['product']['description']?></textarea>
			</td>
		</tr>
		<tr>
			<td class="right" style="width:20%;"></td>
			<td class="left"><input type="submit" name="submit" value="OK" class="p100" style="margin-top:5px;"></td>
		</tr>
	</table>
</form>