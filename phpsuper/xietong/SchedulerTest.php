<?php
include 'SystemCall.php';
include "Task.php";
include  'Scheduler.php';

function  getTaskId(){
      return new SystemCall(function(Task $task,Scheduler $scheduler)    {
echo "gettaskid id {$task->getTaskId()}\n";
	            $task->setSendValue($task->getTaskId());

				$scheduler->schedule($task);
		});
}

function newTask(Generator $coroutine){
echo "newTask\n";
     return new SystemCall(
         function(Task $task,Scheduler $scheduler) use($coroutine)         {
echo "newtask call\n";
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
echo "childtask\n";
  $tid=(yield getTaskId());
  while(true){
  echo "Child task $tid still alive!\n";
  sleep(3);
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


function waitForRead($socket) {
    return new SystemCall(
        function(Task $task, Scheduler $scheduler) use ($socket) {
            $scheduler->waitForRead($socket, $task);
        }
    );
}


function waitForWrite($socket) {
    return new SystemCall(
        function(Task $task, Scheduler $scheduler) use ($socket) {
            $scheduler->waitForWrite($socket, $task);
        }
    );
}



function server($port) {
    echo "Starting server at port $port...\n";
 
    $socket = stream_socket_server("tcp://localhost:$port", $errNo, $errStr);
    if (!$socket) throw new Exception($errStr, $errNo);
 
    stream_set_blocking($socket, 0);
 
    while (true) {
        yield waitForRead($socket);
        $clientSocket = stream_socket_accept($socket, 0);
        yield newTask(handleClient($clientSocket));
    }
}


function handleClient($socket) {
echo "hanleClinet $socket\n";
    yield waitForRead($socket);
    $data = fread($socket, 8192);
 
   $msg = "Received following request:\n\n$data\n";
    $msgLength = strlen($msg);
 
    $response = <<<RES
HTTP/1.1 200 OK\r
Content-Type: text/plain\r
Content-Length: $msgLength\r
Connection: close\r
\r
$msg
RES;
 
    yield waitForWrite($socket);
    fwrite($socket, $response);

    fclose($socket);
}
  $scheduler=new Scheduler();
// $scheduler->newTask(task());
$scheduler->newTask(server(8002));
 $scheduler->run();

