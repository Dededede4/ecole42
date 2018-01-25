<h1>Vos archives</h1>
<?php

foreach ($view['archives'] as $time => $archive) {
	$total = 0;
	if (!$archive)
		continue;
?>
<p>Votre facture du <?php echo date('d/m/Y à H:i:s', strtotime($time)); ?> :
<table class="p100" style="margin-top:20px;">
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
   	foreach ($archive as $articles) {

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
<hr style="width: 40%; margin:auto;">
<?php
}