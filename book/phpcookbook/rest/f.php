<?php
$url="http://php.net/";
$options=['timeout'=>6];
//$options=[];
$content=stream_context_create(['http'=>$options]);
print file_get_contents($url,false,$content);