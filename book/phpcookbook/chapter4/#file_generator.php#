<?php
function FileLineGenerator($file){
	 if(!$fh=fopen($file,'rb')){
	 return ;
	 }
	 while(false!==($line=fgets($fh))){
		yield $line;
	 }
	 fclose($fh);
}

$file = FileLineGenerator('log.txt');
foreach($file as $line ){
	     if(preg_match('/^a/',$line)){
	     print $line;
	     print PHP_EOL;
	     }
}