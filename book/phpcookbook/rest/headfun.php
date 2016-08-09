<?php
class test {
	public function head($ch, $data) {
		//var_dump($ch);
		 print_r($data);
	//	file_put_contents ( 'E:\head.log', $data );
	}
}


/* function testhead(){
	echo "test";
} */

$url = 'http://www.so.com/';
$test = new test ();
$ch = curl_init ( $url );
curl_setopt($ch, CURLOPT_HEADER, true);
curl_setopt ( $ch, CURLOPT_HEADERFUNCTION,[$test,'head']);
curl_setopt ( $ch, CURLOPT_RETURNTRANSFER, true );
$page = curl_exec ( $ch );
//print_r($page);
curl_close ( $ch );