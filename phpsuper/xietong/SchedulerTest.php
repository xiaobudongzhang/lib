<?php
include 'SystemCall.php';
include "Task.php";
include  'Scheduler.php';

function  getTaskId(){
      return new SystemCall(function(Task $task,Scheduler $scheduler)    {
	            $task->setSendValue($task->getTaskId());
				$scheduler->schedule($task);
		});
}

function newTask(Generator $coroutine){
     return new SystemCall(
         function(Task $task,Scheduler $scheduler) use($coroutine)         {
            $task->setSendValue($scheduler->newTask($coroutine));
            $scheduler->schedule($task);
         }
      );
}

function killTask($tid){
        return new SystemCall(
              function (Task $task,Scheduler $scheduler) use($tid)              {
                $task->setSendValue($scheduler->killTask($tid));
                $scheduler->schedule($task);
              }
        );
}

function childTask(){
  $tid=(yield getTaskId());
  while(true){
    echo "Child task $tid still alive!\n";
    yield;
 }
}
  function xrange($start, $end, $step = 1) {
        for($i = $start; $i <= $end; $i += $step) {
                yield $i;
        }
}

function task(){
   $tid=(yield getTaskId());
   $childTid=(yield newTask(childTask()));

   for ($i = 1; $i <= 6; ++$i) {
        echo "parent task $tid iteration $i.\n";
		yield ;


        if($i==3){

                 yield killTask($childTid);
         }
	}

} 


  $scheduler=new Scheduler();
  $scheduler->newTask(task());
  $scheduler->run();

