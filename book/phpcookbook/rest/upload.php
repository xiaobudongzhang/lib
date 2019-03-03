<?php
$fh=fopen('test.txt','rb') or die('cant open');
$filename='test.txt';


$c=curl_init("http://127.0.0.1:8888/test.php");
curl_setopt($c,CURLOPT_PUT,true);
curl_setopt($c,CURLOPT_INFILE,$fh);
curl_setopt($c,CURLOPT_INFILESIZE,filesize($filename));
curl_setopt($c, CURLOPT_RETURNTRANSFER, true);
$page=curl_exec($c);
print_r($page);
//print_r(curl_getinfo($c));
curl_close($c);