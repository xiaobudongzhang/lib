<?php
class CoSocket{
	protected $socket;
	
	public function __construct($socket){
		$this->socket=$socket;
	}
	
	public function accept(){
		echo "cosocket accept\n";
		yield  waitForRead($this->socket);
		echo "cosocket accept waitforead after\n";
		yield  retval(new CoSocket(stream_socket_accept($this->socket,0)));
		echo "cosocket accept retval after";
	}
	
	public function read($size){
		echo "cosocket read\n";
		yield waitForRead($this->socket);
		yield retval(fread($this->socket,$size));
	}
	
	public function write($string){
		echo "cosocket write\n";
		yield waitForWrite($this->socket);
		fwrite($this->socket, $string);
	}
	
	public function close(){
		echo "cosocket close\n";
		fclose($this->socket);
	}
}
