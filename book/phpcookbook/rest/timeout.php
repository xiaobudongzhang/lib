<?php
//phpinfo();
$url='http://m.fangdd.net/test/timeout/set?time=5';
ini_set('default_socket_timeout', 1);
//file_get_contents($url);
//die;
//ini
/* ini_set('default_socket_timeout', 12);
file_get_contents($url); */

/* //curl
$c=curl_init($url);
curl_setopt($c, CURLOPT_RETURNTRANSFER, false);
//curl_setopt($c, CURLOPT_TIMEOUT, 1);
$page=curl_exec($c);
$error=curl_errno($c);
curl_close($c);
//print_r($page);
die; */
//file_get_contents($filename);
//stream
 $stream=fopen($url, 'rb');
stream_set_blocking($stream, TRUE);
//$set=stream_set_timeout($stream,1);
var_dump($set);
$response=stream_get_contents($stream);
$info = stream_get_meta_data($stream);
fclose($stream);
var_dump($info);

if ($info['timed_out']) {
	echo 'Connection timed out!';
	echo PHP_EOL;
} else {
	//print_r($response);
} 

/* $fp=fopen('php://stdin','r');
stream_set_timeout($fp,10) or die ('Failed');
echo 'Success'; */
