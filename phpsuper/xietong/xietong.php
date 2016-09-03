<?php
/**
 * 在PHP中使用协程实现多任务调度
 */

/* function xrange($start, $end, $step = 1) {
	for($i = $start; $i <= $end; $i += $step) {
		yield $i;
	}
}

 foreach ( xrange ( 1, 1000000 ) as $num ) {
	echo $num, "\n";
} 
/*
$range=xrange(1, 1000000);
var_dump($range);
var_dump($range instanceof Iterator);

echo $range->current(); */
 
/* function logger($filename){
	$fileHandle = fopen($filename, 'ab');
	while(true){
		fwrite($fileHandle, yield."\n");
	}
}

$logger = logger(__DIR__.'/log');
$logger->send('Foo');
$logger->send('Bar'); */


/* function gen(){
	$ret=(yield 'yield1');
	var_dump('gen1'.$ret);
	$ret =(yield 'yield2');
	var_dump('gen2'.$ret);
}
$gen=gen();
var_dump($gen->current());
var_dump($gen->send('ret1'));
var_dump($gen->send('ret2'));
*/
 function gen(){
	$i=0;
	while(1){
	$i++;
	echo "i:$i\n";
	$obj=new stdClass();
	$ret =(yield 'obj'.$i);
	
	var_dump("gen1:");
	var_dump($ret);
	}
//	$ret=(yield 'yield2');
	
//	var_dump("gen2:".$ret);
} 

$gen=gen();
//var_dump($gen->current());
var_dump("res_ret1:".$gen->send("ret1"));
//var_dump("res_ret2:".$gen->send("ret2"));
//var_dump($gen->current()); 

//for(;;){
//echo "111\n";	//dfdssdfs
//}
