<?php
$url='https://www.baidu.com';
$fp=fopen($url, 'rb');
$metadata=stream_get_meta_data($fp);
print_r($metadata);
$body=stream_get_contents($fp);
print_r($body);