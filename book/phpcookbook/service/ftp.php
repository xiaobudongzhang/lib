<?php
/* $c=ftp_connect('127.0.0.1') or die('cant connect');
ftp_login($c,'root', '666666') or die('cant login');
print_r(ftp_rawlist($c,'/')); */


$c=curl_init('ftp://root:666666@127.0.0.1/sql/www_fangdd_com.sql');
$fh=fopen('E:/test.log', 'wb') or die('d'); ;
curl_setopt($c, CURLOPT_FILE, $fh);
curl_exec($c);
curl_close($c);
//print_r($php_errormsg);