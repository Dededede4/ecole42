#!/Users/mprevot/.brew/opt/php@7.1/bin/php
<?php
include('vendor/autoload.php');

use MathPHP\Statistics\Correlation;
use MathPHP\Statistics\Descriptive;

error_reporting(E_ALL);

if (false)
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

    $len = count($xyDatas);
    $moyX = $sumX / $len;
    $moyY = $sumY / $len;

    $b = $moyY - $a * $moyX;
    /*var_dump('$b = '.$b); 

    var_dump("Covariance : ", $covariance);
    var_dump("Variance : ", $variance);

    var_dump('La moyenne des "'.$xyNames[0].'" est '.$moyX);
    var_dump('La moyenne des "'.$xyNames[1].'" est '.$moyY);
4


    var_dump("$a x + $b");
    var_dump('Pour une taille de 180cm le poid est de 67kg ', $a * 180 + $b);*/
    
    echo 'Compute finish'."\n";

    return [
    	'theta0' => round($b, 4),
    	'theta1' => round($a, 4),
    ];
}

function h($x, $t0, $t1)
{
	return $t0 + $t1 * $x;
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
	$result = ($sum / $m);
	return $result;
}

function standardise($xyDatas)
{
	$minX = $xyDatas[0][0];
	$minY = $xyDatas[0][1];
	$maxX = $xyDatas[0][0];
	$maxY = $xyDatas[0][1];
	foreach ($xyDatas as $data) {
		if ($minX > $data[0])
			$minX = $data[0];
		if ($minY > $data[1])
			$minY = $data[1];
		if ($maxX < $data[0])
			$maxX = $data[0];
		if ($maxY < $data[1])
			$maxY = $data[1];
	}
	$ratioX = $maxX - $minX;
	$ratioY = $maxY - $minY;
	$standardised = [];
	foreach ($xyDatas as $data) {
		$standardised[] = [
			($data[0] - $minX) / $ratioX,
			($data[1] - $minY) / $ratioY,
		];
	}
	return $standardised;
}

function destandardise($xyDatas, $t0, $t1)
{

	$minX = $xyDatas[0][0];
	$minY = $xyDatas[0][1];
	$maxX = $xyDatas[0][0];
	$maxY = $xyDatas[0][1];
	foreach ($xyDatas as $data) {
		if ($minX > $data[0])
			$minX = $data[0];
		if ($minY > $data[1])
			$minY = $data[1];
		if ($maxX < $data[0])
			$maxX = $data[0];
		if ($maxY < $data[1])
			$maxY = $data[1];
	}
	$ratioX = $maxX - $minX;
	$ratioY = $maxY - $minY;
	return [
		'theta0' => ($t0 * $ratioY) + $minY,
		'theta1' => $t1, 
	];
}


function trainnig($xyNames, $xyDatas)
{
	$teta0 = 0;
	$teta1 = 0;
	$a = 0.0001;
	$save = $xyDatas;
	$xyDatas = standardise($xyDatas);
	$i = 0;
	while ($i++ < 10000)
	{
		$t0 = $teta0 - $a * J($teta0, $teta1, $xyDatas);
		$t1 = $teta1 - $a * J($teta0, $teta1, $xyDatas, true);
		//var_dump($t0.' '.$t1)."\n";
		$teta0 = $t0;
		$teta1 = $t1;
	}

	echo 'Tranning finish'."\n";

	return destandardise($save, $teta0, $teta1); /*
	/*return [
		'theta0' => round($teta0, 4),
		'theta1' => round($teta1, 4),
	];*/


	
}

$options = getopt('', ['file:', 'traditionnal']);
if (!isset($options['file']))
{
	echo 'File missing'."\n"; die;
}

// On transorme le CSV `$argv[1]` en un tableuau en deux dimentions `$tab`
$handle = @fopen($options['file'], 'r');
if ($handle !== false) {
	$tab = [];
    while (($line = fgets($handle)) !== false) {
    	$tab[] = explode(',', trim($line));
    }

    $xyNames = array_shift($tab); // La première ligne corresponds au nom des collones

  	if (isset($options['traditionnal']))
    	$result = traditionnal($xyNames, $tab);
    else
    	$result = trainnig($xyNames, $tab);

	file_put_contents('theta.php', '<?php
		$vars = [
			\'theta0\' => '.$result['theta0'].',
			\'theta1\' => '.$result['theta1'].',
		];
	');

    fclose($handle);
}
else
{
	echo 'Error open file.'."\n";
}