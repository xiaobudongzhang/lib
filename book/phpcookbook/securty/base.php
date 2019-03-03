<?php
$algorithm=MCRYPT_BLOWFISH;
$key='test key';
$data='test data';
$mode=MCRYPT_MODE_CBC;

$iv=mcrypt_create_iv(mcrypt_get_iv_size($algorithm,$mode),MCRYPT_DEV_URANDOM);
$en=mcrypt_encrypt($algorithm, $key, $data, $mode,$iv);
$base=base64_decode($en);

header("Content-type:text/html; charset=UTF-8");
//echo $en.PHP_EOL;
echo $base.PHP_EOL;