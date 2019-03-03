<?php
$username = 'foo411';
$start=microtime(true);
if(!preg_match('/^[a-z0-9]+/i', $username)){
	echo 'error';
}

$preg_len=microtime(true)-$start;

$start=microtime(true);
if(!ctype_alnum($username)){
	echo "error";
}
$ctype_len=microtime(true)-$start;

echo "preg_time:{$preg_len}";

echo PHP_EOL;


echo "ctype_time:{$ctype_len}";
echo PHP_EOL;
echo bcdiv($ctype_len,1,1000);
