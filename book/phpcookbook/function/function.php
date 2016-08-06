<?php
/**function test(Object $x,$y=1){
var_dump(func_num_args());
var_export(func_get_args());
}

class Object{
}
$obj=new Object();
test($obj,2,3,4,5);
*/

$in=7;
$add = function($i,$j) use($in){
return $i+$j+$in;
};
$res=$add(1,2);
//print_r($res);


$add=create_function('$i,$j','return $i+$j+'.$in.';');
print_r($add(1,2));