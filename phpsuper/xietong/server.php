<?php
$port=$argv[1];
echo "Starting server at port $port...\n";

$socket=stream_socket_server("tcp://localhost:$port", $errNo, $errStr); 
stream_set_blocking($socket,0);

while(true){

    $sock=stream_socket_accept($socket,-1);
    if(!$sock){
	die("accpect fail!");
    }
    $data = fread($sock, 8192);
    $msg = "Received following request:\n\n$data";
    $msgLength = strlen($msg);
 
    $response = <<<RES
HTTP/1.1 200 OK\r
Content-Type: text/plain\r
Content-Length: $msgLength\r
Connection: close\r
\r
$msg
RES;

    fwrite($sock, $response);
    fclose($sock);
}



//}
