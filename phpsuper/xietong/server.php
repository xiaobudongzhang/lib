<?php


//while(true){


$port=$argv[1];
    echo "Starting server at port $port...\n";


 $socket=stream_socket_server("tcp://localhost:$port", $errNo, $errStr); 

stream_set_blocking($socket,1);

while($socket){

//$clientSocket=stream_socket_accept($socket,0);
$socketR=[$socket];
 stream_select($r=null, $socketR, $e=null, 1); 
var_dump($socketR);
//if(!$e) {
//die("stream_socket_accept failed!\n");
//}
foreach($socketR as $sock){


  $data = fread($sock, 8192);
 
    $msg = "Received followi
ng request:\n\n$data";
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
//sleep(2); 
    fclose($sock);
}


}



//}
