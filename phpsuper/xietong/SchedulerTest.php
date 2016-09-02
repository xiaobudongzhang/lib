<?php
include 'SystemCall.php';
include "Task.php";
include  'Scheduler.php';
include 'CoroutineReturnValue.php';
include 'CoSocket.php';

function retval(){
    return new CoroutineReturnValue($value);
}
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
 
/*     while (true) {
        echo "server wait for read\n";
        var_dump($socket);
        yield waitForRead($socket);
        $clientSocket = stream_socket_accept($socket, 0);
        yield newTask(handleClient($clientSocket));
    } */
    $socket=new CoSocket($socket);
    while(true){
    	echo "server before newTask\n";
    	yield newTask(
    			handleClient(yield $socket->accept())
    			);
    }
}


function handleClient($socket) {
/* echo "hanleClinet $socket\n";
    yield waitForRead($socket); 
    $data = fread($socket, 8192);*/
	echo "hanleClinet $socket\n";
	$data=(yield $socket->read(8192));
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
/*     echo "client before write\n";
    yield waitForWrite($socket);
    fwrite($socket, $response);
    echo "client after write\n";

    fclose($socket); */
    
    yield $socket->write($response);
    yield $socket->close();
}




function echoTimes($msg,$max){
    for($i=1;$i<$max;++$i){
        echo "$msg iteration $i\n";
        yield;
    }

}
function taskTest(){
    $x=echoTimes('foo',10);
    $x->send("dd");
    $x->send("dd");
    $x->send("dd");
    echo "----\n";
    echoTimes('bar',5);
    yield;
}

function stackedCoroutine(Generator $gen) {
	$stack = new SplStack;
echo "stack------\n";
	for (;;) {
		$value = $gen->current();
		
		echo "stacked current:\n";
		var_dump($value);
		if ($value instanceof Generator) {
			echo "stacked is generator\n";
			$stack->push($gen);
			$gen = $value;
			continue;
		}

		$isReturnValue = $value instanceof CoroutineReturnValue;
		if (!$gen->valid() || $isReturnValue) {
			if ($stack->isEmpty()) {
				return;
			}
           echo "stacked pop\n";
			$gen = $stack->pop();
			var_dump($gen);
			$gen->send($isReturnValue ? $value->getValue() : NULL);
			continue;
		}

		$gen->send(yield $gen->key() => $value);
	    echo "stacked for end\n";
	}
}
  $scheduler=new Scheduler();
//$scheduler->newTask(taskTest());
$scheduler->newTask(server(8008));
$scheduler->run();
//server(8002);
