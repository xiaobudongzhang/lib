<?php
$url='https://www.baidu.com';
$c=curl_init($url);
curl_setopt($c,CURLOPT_RETURNTRANSFER,true);
curl_setopt($c,CURLOPT_FOLLOWLOCATION, true);
$response=curl_exec($c);

print_r($response);
print_r(curl_getinfo($c));
curl_close($c);