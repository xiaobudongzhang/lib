<?php
$client_id='47be746b9d7f133dc976';
$re_url="http://www.testesf.com:8888/authre.php";
echo $url="https://github.com/login/oauth/authorize?client_id={$client_id}&state=byz&redirect_uri={$re_url}";

//$re=file_get_contents($url);
//print_r($re);