#!/usr/bin/php
<?PHP
 
/* A Random equation generator, by tpaulmye */
 
/* Let's set the degree of equation */
 
if (isset($argv[1]))
    $degree1 = abs(intval($argv[1]));
else
    $degree1 = mt_rand(0, 3);
 
$plusminus = array( 0 => " + ", 1 => " - ");
 
$i = 0;
 
/* Let's build first part of equ */
 
while ($i <= $degree1)
{
    /* Let's put float numbers. Or not */
    $comma_or_not = mt_rand(0, 5);
    if ($comma_or_not === 5)
        $ret = $ret.mt_rand(-9, 9).".".mt_rand(1, 99)." * X^".$i;
    else
        $ret = $ret.mt_rand(-9, 9)." * X^".$i;
    if ($i < $degree1)
    {
        $op = array_rand($plusminus);
        $ret = $ret.$plusminus[$op];
    }
    $i++;
}
 
/* Concatenate the equal. I like the word "concatenate"... */
 
$ret = $ret." = ";
 
/* Set the degree of second equation part */
 
if (isset($argv[2]))
    $degree2 = abs(intval($argv[2]));
else if (isset($argv[1]))
    $degree2 = abs(intval($argv[1]));
else
    $degree2 = mt_rand(0, 3);
 
/* Build the second part of equation */
 
$i = 0;
 
while ($i <= $degree2)
{
    /* Let's put float numbers. Or not */
    $comma_or_not = mt_rand(0, 5);
    if ($comma_or_not === 5)
        $ret = $ret.mt_rand(-9, 9).".".mt_rand(1, 99)." * X^".$i;
    else
        $ret = $ret.mt_rand(-9, 9)." * X^".$i;
    if ($i < $degree2)
    {
        $op = array_rand($plusminus);
        $ret = $ret.$plusminus[$op];
    }
    $i++;
}
 
echo $ret.PHP_EOL;