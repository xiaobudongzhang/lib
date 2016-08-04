<?php
/**
 * 按权重随机
 * @var unknown
 */
$ads = array (
		'ford' => 12234, // a
		'att' => 33424,
		'ibm' => 16823 
);
$ad = rand_weight ( $ads );
print $ad;
echo PHP_EOL;
function rand_weight($numbers = []) {
	$total = 0;
	foreach ( $numbers as $number => $weight ) {
		$total += $weight;
		$dis [$number] = $total;
	}
	print_r($dis);
	echo PHP_EOL;
	$rand = mt_rand ( 0, $total - 1 );
	
	foreach ( $dis as $number => $weight ) {
		if ($rand < $weight) {
			return $number;
		}
	}
}