<?php
$url="http://baike.sogou.com/Home.v";
$c=curl_init($url);
curl_setopt($c, CURLOPT_VERBOSE, true);
curl_setopt($c, CURLOPT_HEADER, true);
curl_setopt($c, CURLOPT_NOBODY, true);
curl_setopt($c,CURLOPT_RETURNTRANSFER,true);
//curl_setopt($c, CURLOPT_USERPWD, 'david:hax0r');
$page=curl_exec($c);
curl_close($c);


//print_r($page);

print_r($page);
//file_put_contents('E://t.log',$page);
