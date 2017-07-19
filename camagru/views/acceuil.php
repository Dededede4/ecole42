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
 	echo '<table style="p100"><tr><td><img src="'.$product['picture'].'" alt="" style="width:300px;"/></td><td valign="top">'.nl2br($product['description']).'<br/><br/><a class="btn" href="?page=product&id='.$product['id'].'">Plus d\'informations</a></td></tr></table>';
 	echo '<hr>';
 }
