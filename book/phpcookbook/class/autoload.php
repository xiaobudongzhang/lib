<?php
function __autoload($class_name){
	 include "$class_name.php";
}

new test();

var_dump($argv);