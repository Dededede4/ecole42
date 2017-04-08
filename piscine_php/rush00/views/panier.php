<h1>Votre panier</h1>
<?php
$total = 0;

if($view['panier'])
{

	/*foreach ($view['panier'] as $articles) {
		$price = $articles['quantity'] * $articles['price'];
		echo $articles['name'].' '. $articles['quantity'] .' '. $articles['price'] .' ' .$price.'<br/>';
		$total += $price;
	}*/
	//echo $total;

	?>
	<table class="p100">
	   <thead>
	       <tr>
	           <th class="left">Produit</th>
	           <th class="left">Quantité</th>
	           <th class="left">Prix unitaire</th>
	           <th class="left">Prix Total</th>
	       </tr>
	   </thead>
	   <tbody>
	   	<?php
	   	foreach ($view['panier'] as $articles) {
		$price = $articles['quantity'] * $articles['price'];
		$total += $price;
		?>
	       <tr>
	           <td style="width: 60%;"><?=$articles['name']?></td>
	           <td><?=$articles['quantity']?></td>
	           <td><?=$articles['price']?> €</td>
	           <td><?=$price?> €</td>
	       </tr>
	       <?php } ?>
	    <tr>
	    <td colspan="3"><strong>Prix total :</strong></td>
	    <td colspan="1"><strong><?=$total?> €</strong></td>
	    </tr>
	   </tbody>
	</table>
	<?php
	if ($current_user)
		echo '<a href="?page=panier&action=archive">Archiver</a>';
	else
		echo 'Connectez-vous pour archiver.'
	?>
	<?php
}
else
	echo '<p>Votre panier est vide.</p>';