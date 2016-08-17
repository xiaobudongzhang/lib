<?php
$timeout=0;
$mitime=500000;
$result=[];
$sockets=[];
$convenient_read_block=8192;

$delay=15;
$id=0;
while($delay>0){
	$s=stream_socket_client(
	"127.0.0.1:8009",
	$errorno,
	$errstr,
	STREAM_CLIENT_ASYNC_CONNECT|STREAM_CLIENT_CONNECT
	);
	if($s){
	$sockets[$id++]=$s;
	$http_message="GET /demonstration/delay?delay=" .$delay . " HTTP/1.0\r\nHost: phaseit.net\r\n\r\n"; 
	fwrite($s,$http_message);
	}else{
	
	}
$delay-=3;
}

//var_dump($sockets);

while(count($sockets)){
	$read=$sockets;
	 stream_select($read, $w=null, $e=null, $timeout,$mitime);
	 if(count($read)){
	 
		foreach($read as $r){
			      $id=array_search($r, $sockets); 
			      $data=fread($r,$convenient_read_block);
			      if(strlen($data)==0){
			       echo "Stream " . $id . " closes at " . date('h:i:s') . ".\n";
                        fclose($r); 
                        unset($sockets[$id]); 
			      }else{
			       $result[$id] = $data; 
			      }
		}
	 } else{
	 
	 }
}


print_r($result);