<?php
$options=[
'options'=>[
	'max_range'=>50,
	],
'flags'=>FILTER_FLAG_ALLOW_OCTAL
];

echo filter_var(50,FILTER_VALIDATE_INT,$options);
echo PHP_EOL;
function foo($str){
return $str.'ok';
}
$var=filter_var('a',FILTER_CALLBACK,array('options'=>'foo'));
print_r($var);


