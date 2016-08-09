<?php
$url="http://127.0.0.1:8888/test.php";
$c=curl_init($url);
curl_setopt($c,CURLOPT_RETURNTRANSFER,true);
curl_setopt($c, CURLOPT_USERPWD, 'david:hax0r');
$page=curl_exec($c);
curl_close($c);

//print_r($page);