<?php
//throw new LogicException('test',22);
function xrange($start,$limit,$step=1){
	if($start<$limit){
		if($step<=0){
			throw new LogicException('step must be +ve');
		}
		
		for ($i = $start; $i < $limit; $i+=$step) {
			yield $i;
		}
	}else{
		if($step>=0){
			throw new LogicException('step must be +ve');
		}
		for ($i = $start; $i >= $limit; $i+=$step) {
			yield  $i;
		}
	}
}
//10000000
 $xrange=xrange(1, 20, 2);
print_r($xrange->key());
echo PHP_EOL;
//echo 'Single digit odd numbers from xrange(): ';
foreach ($xrange as $number) {
    echo "$number ";
    echo PHP_EOL;
}
//print_r($result);
echo PHP_EOL;
echo memory_get_usage();
echo PHP_EOL; 