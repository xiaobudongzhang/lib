<?php
include "Task.php";
include 'SystemCall.php';
include  'Scheduler.php';

 function task1(){
	for ($i=1;$i<=10;++$i){
		//echo "This is task 1 iternation $i.\n";
		yield ;
	}
}

function task2(){
	for ($i = 1; $i < 5; $i++) {
		echo "This is task 2 iteration $i.\n";
		yield ;
	}
} 

/* function task($max){
	$tid=(yield getTaskId());
	for ($i = 1; $i < $max; ++$i) {
		echo "This is task $tid iteration $i.\n";
		yield ;
	}
	
} */
$scheduler=new Scheduler();
//$scheduler->newTask(task1());
$scheduler->newTask(task2());

$scheduler->run();