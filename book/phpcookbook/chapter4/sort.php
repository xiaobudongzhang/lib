<?php
$tests = array('test1.php', 'test10.php', 'test11.php', 'test2.php');
$test2=$tests;
sort($test2);
print_r($test2);
usort($tests,function($a,$b){
	return  strnatcmp($a,$b);
});
print_r($tests);

$s=array('Boston', 'New York', 'Chicago');
sort($s);
print_r($s);

$colors = array('Red', 'White', 'Blue');
$cities = array('Boston', 'New York', 'Chicago');
array_multisort($colors,SORT_STRING , SORT_ASC,
		 $cities,SORT_REGULAR ,SORT_ASC );
print_r($colors);
print_r($cities);

$names = array('firstname' => "Baba",
'lastname' => "O'Riley");

array_walk($names,function(&$value,$key){
	$value=htmlentities($value,ENT_QUOTES);
});

print_r($names);


$names = array('firstnames' => array("Baba", "Bill"),
'lastnames' => array("O'Riley", "O'Reilly"));

array_walk_recursive($names,function(&$value,$key){
	$value=htmlentities($value,ENT_QUOTES);
});

print_r($names);