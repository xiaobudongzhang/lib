<?php
$str='\n';
var_dump(strpos($str,'\n'));
echo PHP_EOL;
//int(0)

$str='\n';
var_dump(strpos($str,"\n"));
echo PHP_EOL;
//bool(false)

$str="\n";
var_dump(strpos($str,'\n'));
echo PHP_EOL;
//bool(false)

$str="\n";
var_dump(strpos($str,"\n"));
echo PHP_EOL;
//int(0)