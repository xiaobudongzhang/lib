<?php
$fh=fopen("compress.zlib://lock.txt.gz",'r');
if($fh){
	while($line=fgets($fh)){
		echo $line."\n";
	}
	fclose($fh);
}