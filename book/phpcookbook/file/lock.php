<?php
$fh=fopen('lock.txt','a');
for($i=0;$i<100;$i++){
//	$fh=fopen('lock.txt','a');
	$x=flock($fh,LOCK_EX);
	fwrite($fh,'456'."\n");
	sleep(1);
	var_dump('d');
}

#fclose($fh);


/**$fh=fopen('lock.txt','w');
if(flock($fh,LOCK_EX)){
flock($fh,LOCK_EX);
fwrite($fh,'456'."\n");
fclose($fh);
}
*/