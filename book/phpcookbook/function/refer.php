<?php
function &array_find_value($needle,&$stack){
	 foreach($stack as $key=>$value){
	 		if($needle==$value){
			return $stack[$key];
			}
	 }
}
$arr=[
'a',
'b',
'the door'
];
$band=&array_find_value('the door',$arr);
$band='ddd';
var_export($arr);