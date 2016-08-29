<?php
include 'Task.php';

function task1(){
	for ($i=1;$i<=10;++$i){
		echo "This is task 1 iternation $i.\n";
		yield ;
	}
}
$task=new Task(1,task1());
$task->run(); 