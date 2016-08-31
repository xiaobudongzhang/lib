<?php
class SystemCall {
	protected $callback;
	public function __construct(callable $callback) {
   		$this->callback = $callback;
	}
	/**
	 * 当对象作为函数调用时
	 */
	public function __invoke(Task $task, Scheduler $scheduler) {
		
		$callback = $this->callback;
 		return $callback ( $task, $scheduler );
	}
}