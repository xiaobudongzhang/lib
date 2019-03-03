<?php
//file open read write
/* $handle = fopen('http://127.0.0.1:8009/composer.json','rb') or die($php_errormsg);
// echo fwrite($fh, '123');
//fclose($fh); 
 $i=0;
while (false!==($s=fgets($handle))) {
	echo $s;
	$i++;
	if($i>3){
		die;
	}
}
fclose($handle);  */


//tmpfile
/* $temp_fh=tmpfile();
print_r($temp_fh);
fwrite($temp_fh, "333");
fclose($temp_fh);
print_r($temp_fh);
fwrite($temp_fh, "333"); */

//
/* print tempnam('E:/tmp', 'testme');
 */

//stdin	
/* $handle=fopen("php://stdin",'rb')   or die($php_errormsg);
while ($s=fgets($handle)) {
	print $s."\n";
} */

//readfile 读取到缓存
/* readfile('E:/file.log');// */

/* $handle = fopen ( 'E://file.log', 'rb' ) or die ( $php_errormsg );
echo $total = filesize ( 'E://file.log' );
$next_read = $last_write = 0;
while ( $next_read < $total ) {
	@fseek ( $handle, $next_read );
	 $s = fgets ( $handle ) ;
	 $next_read = ftell ( $handle ) . "\n";
}
fclose ( $handle ); */

/* //echo 'hi';
$handle=fopen('E://file.log', 'wb');
fwrite($handle, 'hi');
//fflush($handle); */

/* $handle=fopen("php://stdout", 'wb');
fwrite($handle, 'test');
fclose($handle); */

/* system(escapeshellcmd('ls -al')); */


$handle=popen('ls --t 2>&1', 'r');
while (!feof($handle)) {
	echo fgets($handle);
}

pclose($handle);