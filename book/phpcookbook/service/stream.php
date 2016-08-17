<?php
/* $read = fsockopen('127.0.0.1',
		8009,
		$errno,
		$errstr
		);
$read2 = fsockopen('127.0.0.1',
		8010,
		$errno,
		$errstr
		); */
$read=stream_socket_client("127.0.0.1:8009", $errno, $errstr, 1000,
		STREAM_CLIENT_ASYNC_CONNECT|STREAM_CLIENT_CONNECT);
$read2=stream_socket_client("127.0.0.1:8010", $errno, $errstr, 1000,
		STREAM_CLIENT_ASYNC_CONNECT|STREAM_CLIENT_CONNECT);
/* $tv_sec=0;
$tv_usec=1000;
$out = "GET / HTTP/1.1\r\n";
//$out .= "Host: www.example.com\r\n";
$out .= "Connection: Close\r\n\r\n";
fwrite($read, $out);
while (!feof($read)) {
	echo (fgets($read,1024));
}
fclose($read); */
//var_dump(file_get_contents($read));
$r=[$read,$read2];
$num=stream_select($r, null, null, $tv_sec, $tv_usec );