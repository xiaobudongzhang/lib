<?php
function times_33_hash($str){
	 $h=5381;
	 for($i=0,$j=strlen($str);$i<$j;$i++){
	 $h+=($h<<5)+ord($str[$i]);
	 }
	 return $h&0xFFFFFFFF;
}

echo times_33_hash("Once,I ate papaya.");
echo PHP_EOL;
