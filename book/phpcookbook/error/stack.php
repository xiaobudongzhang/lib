<?php
function test1(){
	test2();
	print_r(debug_backtrace());
}
function test2(){
	test3();
}
function test3(){
//debug_print_backtrace();	

}

test1();
