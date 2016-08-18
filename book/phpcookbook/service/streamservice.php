<?php
//file_put_contents('E:/stream.log',json_encode($_SERVER).PHP_EOL,FILE_APPEND);
$server = stream_socket_server("tcp://127.0.0.1:60005", $errno, $errstr);
if (!$server) {
  echo "$errstr ($errno)<br />\n";
} else {
	$conn = stream_socket_accept($server);
  //while ($conn = stream_socket_accept($server)) {
	$data='';
	//$alternate = stream_get_meta_data ($conn);
	//print_r($alternate);
	//print_r($_POST);
	echo "Received Out-Of-Band: '" . stream_socket_recvfrom($conn, 1500) . "'\n";
	sleep(1);
	/* Take a peek at the normal in-band data, but don't comsume it. */
	//echo $data=stream_socket_recvfrom($conn, 1500, STREAM_PEEK)."\n" ;

	/* Get the exact same packet again, but remove it from the buffer this time. */
	//echo $data.= stream_socket_recvfrom($conn, 1500)."\n" ;

	//file_put_contents('E:/stream.log',$data.PHP_EOL,FILE_APPEND);
	
	
    fwrite($conn, 'The local time is ' . date('n/j/Y g:i a') . "\n");
    fclose($conn);
  //}
  fclose($server);
}