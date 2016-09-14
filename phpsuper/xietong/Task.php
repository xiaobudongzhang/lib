<?php
// 任务（一个任务就是用任务ID标记的一个协程(函数)）
class Task {
	protected $taskId;
	protected $coroutine; // 协同生成器
	protected $sendValue = null;
	protected $beforeFirstYield = true;
    protected $exception =null;
	public function __construct($taskId, Generator $coroutine) {
		$this->taskId = $taskId;
		$this->coroutine = stackedCoroutine($coroutine);
       	echo "task  __construct\n";
	}
	public function getTaskId() {
		return $this->taskId;
	}
	public function setSendValue($sendValue) {
		$this->sendValue = $sendValue;
	}
	public function run() {
		echo "task run  id:" . $this->getTaskId () . "\n";
		if ($this->beforeFirstYield) {
			$this->beforeFirstYield = false;
			echo "task first run\n";
			return $this->coroutine->current ();
		} elseif($this->exception){
            $retval=$this->coroutine->throw($this->exception);
            $this->exception=null;
            return $retval;
        }else {
			echo "task send value $this->sendValue\n";
			$retval = $this->coroutine->send ( $this->sendValue );
			$this->sendValue = null;
			return $retval;
		}
	}
	public function isFinished() {
		return ! $this->coroutine->valid ();
	}
	public function setException($exception){
        $this->exception=$exception;
    }



}


