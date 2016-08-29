<?php
// 调度器
class Scheduler {
	protected $maxTaskId = 0;
	protected $taskMap = [ ];
	protected $taskQueue;
	public function __construct() {
		$this->taskQueue = new SplQueue ();
	}
	public function newTask(Generator $coroutine) {
		$tid = ++ $this->maxTaskId;
		$task = new Task ( $tid, $coroutine );
		$this->taskMap [$tid] = $task;
		$this->schedule ( $task );
		return $tid;
	}
	public function schedule(Task $task) {
		$this->taskQueue->enqueue ( $task );
	}
	public function run() {
		while ( ! $this->taskQueue->isEmpty () ) {
			$task = $this->taskQueue->dequeue ();//因为已经dequeue所以失败后再次加入到队列中
			$retval = $task->run ();
/* 			if ($retval instanceof SystemCall) {
				$retval ( $task, $this );
				continue;
			} */
		// echo "task schedule id ".$task->getTaskId ()."\n";
		//	 echo "finish status:".$task->isFinished()."\n"; */
			if ($task->isFinished ()) {
				unset ( $this->taskMap [$task->getTaskId ()] );
			} else {
				$this->schedule ( $task );
			}
		}
	}
}