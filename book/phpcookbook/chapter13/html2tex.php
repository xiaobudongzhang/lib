<?php
require_once '/home/xiaoxiaojie/class.html2text.inc';
$html=file_get_contents('./bad.html');
$convert=new html2text($html);
//echo $convert->get_text();



$stream = fopen(__DIR__.'/bad.html','rb');
stream_filter_append($stream, 'string.strip_tags',STREAM_FILTER_READ,'b,i');
print stream_get_contents($stream);