<?php
include('vendor/autoload.php');

use MathPHP\Statistics\Correlation;
use MathPHP\Statistics\Descriptive;

error_reporting(E_ALL);




if (2 != $argc)
{
	echo "Give me a arg.";
	die;
}

function traditionnal($xyNames, $xyDatas)
{
	$valsX = array_map(function($item) {
				return floatval($item[0]); 
			}, $xyDatas);

	$valsY = array_map(function($item) {
				return floatval($item[1]); 
			}, $xyDatas);    

    $sumX = array_sum($valsX);
    $sumY = array_sum($valsY);

    $covariance = Correlation::covariance($valsX, $valsY, true);
    $variance = Descriptive::populationVariance($valsX);

    $a = $covariance / $variance;
    var_dump('$a = '.$a);

    $len = count($xyDatas);
    $moyX = $sumX / $len;
    $moyY = $sumY / $len;

    $moyDot = 0;
    foreach ($tab as $dot) {
    	$moyDot += $dot[1] / $dot[0];
    }
    $moyDot = $moyDot / $len;

    $b = $moyY - $a * $moyX;
    var_dump('$b = '.$b); 

    var_dump("Covariance : ", $covariance);
    var_dump("Variance : ", $variance);

    var_dump('La moyenne des "'.$xyNames[0].'" est '.$moyX);
    var_dump('La moyenne des "'.$xyNames[1].'" est '.$moyY);

    var_dump('La moyenne points est "'.$moyDot);


    var_dump("$a x + $b");
    var_dump('Pour une taille de 180cm le poid est de 67kg ', $a * 180 + $b);
}

function h($x, $t0, $t1)
{
	return $t0 + $t1 * $x;
}

function jnew($t0, $t1, $xyDatas)
{
	$m = count($xyDatas);
	$sum = 0;

	foreach ($xyDatas as $data) {
		$tmp = (h($data[0], $t0, $t1) - $data[1]);
		$sum += $tmp * $tmp;
	}
	$result = (1 / (2 * $m)) * ($sum );
	var_dump($result);
	return $result;
}

function j ($t0, $t1, $xyDatas, $ist1 = false)
{
	$m = count($xyDatas);
	$sum = 0;

	foreach ($xyDatas as $data) {
		$tmp = (h($data[0], $t0, $t1) - $data[1]) ;
		if ($ist1)
		{	
			$sum += $tmp * $data[0];
		}
		else
		{
			
			$sum += $tmp;

		}
	}
	$result = (1 / $m) * ($sum );
	return $result;
}


function trainnig($xyNames, $xyDatas)
{
	$teta0 = 0;
	$teta1 = 0;
	$a = 0.0001;
	
	$i = 0;
	while ($i++ < 1000)
	{
		
		$t0 = $teta0 - $a * J($teta0, $teta1, $xyDatas);
		$t1 = $teta1 - $a * J($teta0, $teta1, $xyDatas, true);
		$teta0 = $t0;
		$teta1 = $t1;
		var_dump("t0 : ".$t0);
		var_dump("t1 : ".$t1);
	}
	var_dump("----");
	var_dump(round($teta0, 4));
	var_dump(round($teta1, 4));

}


// On transorme le CSV `$argv[1]` en un tableuau en deux dimentions `$tab`
$handle = fopen($argv[1], 'r');
if ($handle) {
	$tab = [];
    while (($line = fgets($handle)) !== false) {
    	$tab[] = explode(',', trim($line));
    }

    $xyNames = array_shift($tab); // La première ligne corresponds au nom des collones

    //traditionnal($xyNames, $tab);
    trainnig($xyNames, $tab);

    fclose($handle);
}