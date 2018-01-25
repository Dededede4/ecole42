<h1>Page d'acceuil</h1>
<?php 
$cat = $view['categories'];

echo '<table class="p100" style="margin-top:20px;"><tr>';
foreach ($cat as $val) {
	echo '<td style="text-align:center;"><a href="./?category='.$val['id'].'">'.$val['name'].'</a></td>';
}
echo '</tr></table>';

$products = $view['products'];

foreach ($products as $product) {
 	echo '<h2>'.$product['name'].' : '.$product['price'].' €</h2>';
 	echo '<img src="'.$product['picture'].'" style="width:300px;" alt=""/>';
 	echo '<p>'.$product['description'].'</p>';
 	echo '<p><a href="?page=product&id='.$product['id'].'">Plus d\'informations</a></p>';
 	echo '<hr>';
 } 