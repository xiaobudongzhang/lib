<?php
/**
 * 实现lookandsay
 1
 11
 21
 1211
 111221
 312211
 13112221
 1113213211
 31131211131221
 13211311123113112211
 */
function lookandsay($s) {
	$r = '';
	$m = $s [0];
	$n = 1;
	for($i = 1, $j = strlen ( $s ); $i < $j; $i ++) {
		if ($s [$i] == $m) {
			$n ++;
		} else {
			$r.=$n.$m;
			$m=$s[$i];
			$n=1;
		}
	}
	return $r.$n.$m;
}

for($i = 0, $s = 1; $i < 10; $i ++) {
	$s = lookandsay ( $s );
	print "$s\n";
}
