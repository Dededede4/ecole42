<h1>Page produit</h1>
<div style="float:right;width:150px;
	">
	<form action="" method="POST">
		<input type="hidden" name="buy_product" value="ok">
		Quantité :
		<select name="quantity">
		   <option>1</option>
		   <option>2</option>
		   <option>3</option>
		   <option>4</option>
		   <option>5</option>
		   <option>6</option>
		   <option>7</option>
		   <option>8</option>
		   <option>9</option>
		</select> <br/>

		<input type="submit" name="submit" value="Ajouter au panier" class="p100" style="margin-top:5px;">
	</form>
</div>
<?php
	echo '<h2>'.$view['product']['name'].' : '.$view['product']['price'].' €</h2>';
 	echo '<table style="p100"><tr><td><img src="'.$view['product']['picture'].'" alt="" style="width:300px;"/></td><td valign="top">'.nl2br($view['product']['description']).'</td></tr></table>';

if ($current_user['is_admin'])
{
	?>
	<hr style="margin-bottom:15px;">
	Partie administration :
<?php
	echo '<a href="?page=product&id='.$view['product']['id'].'&action=del">Supprimer</a>';
	include ('_form_product.php');
}
?>
