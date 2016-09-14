<?php 
function stackedCoroutine(Generator $gen) {
   
	$stack = new SplStack;
    echo "stack------\n";
    $i=0;
    $exception=null;

	for (;;) {
        try{
        $i++;
        echo "i:::$i\n";

        if($exception){
            echo "stack exception \n ";
            var_dump($exception);
            $gen->throw($exception);
            $exception=null;
            continue;
        }
		$value = $gen->current();
		
		echo "stacked current  value:\n";
		var_dump($value);
		if ($value instanceof Generator) {
			echo "stacked is generator\n";
			$stack->push($gen);
			$gen = $value;
			continue;
		}

		$isReturnValue = $value instanceof CoroutineReturnValue;
		if (!$gen->valid() || $isReturnValue) {
            echo "stack empty\n";
			if ($stack->isEmpty()) {
				return;
			}
           echo "stacked pop\n";
           var_dump($isReturnValue);
			$gen = $stack->pop();
			var_dump($gen);
			$gen->send($isReturnValue ? $value->getValue() : NULL);
			continue;
		}
        echo "stacked before end\n";
        //$gen->send("stack send 1");
        //  yield ;
        try{
        $s=(yield $gen->key() => $value);
        echo "stacked before end -----$s\n";
        }catch(Exception $e){
            echo "stack sendvalue exception\n";
            var_dump($e);
            $gen->throw($e);
            continue;
        }
        
        $re=$gen->send($s);
  
	    var_dump("stack:");
        var_dump($re);
        echo "stacked  end\n";
        }catch(Exception $e){
            echo "stack exception last\n";
            var_dump($e);
            if($stack->isEmpty()){
                throw $e;
            }

            $gen=$stask->pop();
            $exception=$e;
        }
	}
}