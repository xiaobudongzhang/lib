<?php
function test(Object $x,$y=1){
var_dump(func_num_args());
var_export(func_get_args());
}

class Object{
}
$obj=new Object();
test($obj,2,3,4,5);