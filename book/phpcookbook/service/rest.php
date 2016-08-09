<?php
//no redirect*******
$json=[
'id'=>1,
'name'=>'byz'
];

$url="https://www.baidu.com";
http_response_code(201);
header("Location:$url");
print json_encode($json);