<?php
$cookie_jar='/tmp/cookie/testcookie';//tempnam('/tmp/cookie','cookie');

/**$c=curl_init('http://www.haijiayou.net/test.php');
curl_setopt($c,CURLOPT_RETURNTRANSFER,false);
curl_setopt($c,CURLOPT_COOKIEJAR,$cookie_jar);
$page=curl_exec($c);
curl_close($c);
*/

$c=curl_init('http://www.haijiayou.net/test.php');
curl_setopt($c,CURLOPT_RETURNTRANSFER,false);
curl_setopt($c,CURLOPT_COOKIEFILE,$cookie_jar);
$page=curl_exec($c);
curl_close($c);

