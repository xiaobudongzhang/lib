<?php
$arrContextOptions=array(
		"ssl"=>array(
				//"cafile" => "/path/to/bundle/cacert.pem",
				"verify_peer"=> false,
				"verify_peer_name"=> false,
		),
);
$url='https://github.com/';
$response = file_get_contents($url, false, stream_context_create($arrContextOptions));

echo $response;//显示登陆界面