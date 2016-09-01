<?php
// 调度器
class Scheduler {
	protected $maxTaskId = 0;
	protected $taskMap = [ ];
	protected $taskQueue;
protected $waitingForRead = [];
protected $waitingForWrite = [];

	public function __construct() {
		$this->taskQueue = new SplQueue ();
        //  echo "scheduler__\n";
	}
	public function newTask(Generator $coroutine) {
		$tid = ++ $this->maxTaskId;
		$task = new Task ( $tid, $coroutine );
		$this->taskMap [$tid] = $task;
		$this->schedule ( $task );
      	return $tid;
	}
    public function killTask($tid){
        if(!isset($this->taskMap[$tid])){
            return false;
        }
        
        unset($this->taskMap[$tid]);
        
        foreach($this->taskQueue as $i=>$task){
            if($task->getTaskId()===$tid){
                unset($this->taskQueue[$i]);
                break;
            }
        }
        
        return true;
    }
	public function schedule(Task $task) {
		$this->taskQueue->enqueue ( $task );
	}
public function waitForRead($socket, Task $task) {

     echo "schedule waitForRead $socket\n";
    
    if (isset($this->waitingForRead[(int) $socket])) {
        $this->waitingForRead[(int) $socket][1][] = $task;
    } else {
        echo "schedule waitforread else\n";
        $this->waitingForRead[(int) $socket] = [$socket, [$task]];
    }
 var_dump($this->waitingForRead);
}
 
public function waitForWrite($socket, Task $task) {
 echo "schedule waitForWrite $socket\n";

    if (isset($this->waitingForWrite[(int) $socket])) {
        $this->waitingForWrite[(int) $socket][1][] = $task;
    } else {
        $this->waitingForWrite[(int) $socket] = [$socket, [$task]];
    }

 var_dump($this->waitingForWrite);
}

protected function ioPoll($timeout) {
    $rSocks = [];
    foreach ($this->waitingForRead as list($socket)) {
        $rSocks[] = $socket;
    }
 
    $wSocks = [];
    foreach ($this->waitingForWrite as list($socket)) {
        $wSocks[] = $socket;
    }
 
    $eSocks = []; // dummy
    echo "stream_select before\n"; 
    var_dump($timeout);
    if(!$rSocks&&!$wSocks){
        echo "r and w empty\n";
        return;
    }
    echo "rsocks\n";
    var_dump($rSocks);
    echo "wsocks\n";
    var_dump($wSocks);
    if (!stream_select($rSocks, $wSocks, $eSocks, $timeout)) {
        echo "error stream_sock/n";
        var_dump($eSocks);
        return;
    }
    echo "stream_select after\n";
    foreach ($rSocks as $socket) {
        echo "iopoll read socket:\n";
        var_dump($socket);
        
        list(, $tasks) = $this->waitingForRead[(int) $socket];
        unset($this->waitingForRead[(int) $socket]);
        var_dump($this->waitingForRead);
        var_dump($tasks);
        foreach ($tasks as $task) {
            $this->schedule($task);
        }
    }
 
    foreach ($wSocks as $socket) {
        echo "iopoll write socket:\n";
        var_dump($socket);
        list(, $tasks) = $this->waitingForWrite[(int) $socket];
        unset($this->waitingForWrite[(int) $socket]);
        var_dump($this->waitingForWrite);
        var_dump($tasks);
        foreach ($tasks as $task) {
            $this->schedule($task);
        }
    }
}



protected function ioPollTask() {
    while (true) {
        if ($this->taskQueue->isEmpty()) {
            echo "iopolltask taskqueue empty\n";
            $this->ioPoll(null);
        } else {
            $this->ioPoll(0);
        }
        yield;
    }
}

	public function run() {
        $this->newTask($this->ioPollTask());
      		while ( ! $this->taskQueue->isEmpty () ) { 
			$task = $this->taskQueue->dequeue ();//因为已经dequeue所以失败后再次加入到队列中

            echo date('Y-m-d H:i:s',time())."   ---scheduler run:{$task->getTaskId()}\n";
			$retval = $task->run ();
 			var_dump($retval);
            if ($retval instanceof SystemCall) {
                // echo "dddddd\n";
				$retval ( $task, $this );
                
				continue;
			}
            //echo "ddd3\n";
			if ($task->isFinished ()) {
                 echo "schedule finish\n";
				unset ( $this->taskMap [$task->getTaskId ()] );
			} else {
                 echo "schedule finsh else\n";
				$this->schedule ( $task );
			}
		}
	}
}