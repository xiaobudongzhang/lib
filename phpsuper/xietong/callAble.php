<?php
class SystemCall {
	protected $callback;
	public function __construct(callable $callback) {
   		$this->callback = $callback;
	}
	/**
	 * 当对象作为函数调用时
	 */
	public function __invoke($s) {
		$callback = $this->callback;
 		return $callback ( $s );
	}
}


function calls($x='x'){
	echo "call\n";
	return new SystemCall(
					function(){
						file_put_contents('E:/call.log', "d");
					}
		);
}
/*$x=new SystemCall(
		function ($out){
			echo "d";
		}
		);
		*/
function y(){
	(yield '1');
	(yield calls("a"));
}
$y=y();
/* $call=calls();
$call('d'); */
var_dump($y->send('d'));
//$x('df');