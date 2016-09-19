<?php

function gen(){
	$ret=(yield 'yield1');
	var_dump('gen1'.$ret);
	$ret =(yield 'yield2');
	var_dump('gen2'.$ret);
}
$gen=gen();
var_dump($gen->current());
var_dump($gen->send('ret1'));
var_dump($gen->send('ret2'));
