<?php
//任务（一个任务就是用任务ID标记的一个协程(函数)）
class Task {
	protected $taskId;
	protected $coroutine; // 协同生成器
	protected $sendValue = null;
	protected $beforeFirstYield = true;
	public function __construct($taskId, Generator $coroutine) {
		$this->taskId = $taskId;
		$this->coroutine = $coroutine;
        //  echo "task__\n";
    }
	public function getTaskId() {		
        return $this->taskId;
 
	}
	public function setSendValue($sendValue) {
		$this->sendValue = $sendValue;
	}
	public function run() {
        	echo "task run  id:".$this->getTaskId()."\n";
		if ($this->beforeFirstYield) {
			$this->beforeFirstYield = false;
            	echo "task first run\n";
			return $this->coroutine->current ();
		} else {
            	echo "task send value $this->sendValue\n";
			$retval = $this->coroutine->send ( $this->sendValue );
			$this->sendValue = null;
			return $retval;
		}
        
	}
	public function isFinished() {
		return ! $this->coroutine->valid ();
	}
}


