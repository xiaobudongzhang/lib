<?php
$client_id='47be746b9d7f133dc976';
$re_url="http://www.testesf.com:8888/auth2.php";
$url="https://github.com/login/oauth/authorize?client_id={$client_id}&state=byz&redirect_uri={$re_url}";
header("Location:$url");
/* $arrContextOptions=array(
		"ssl"=>array(
				//"cafile" => "/path/to/bundle/cacert.pem",
				"verify_peer"=> false,
				"verify_peer_name"=> false,
		),
);
$re=file_get_contents($url,false,stream_context_create($arrContextOptions));
print_r($re); */