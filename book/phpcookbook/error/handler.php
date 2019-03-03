<?php


set_exception_handler ( 'error_manager' );
function error_manager($e) {
	print "error open!";
} 

throw new Exception('test',989);