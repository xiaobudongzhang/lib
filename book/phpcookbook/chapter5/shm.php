<?php
echo __FILE__.PHP_EOL;
$shmop_key=ftok(__FILE__,'p');
var_dump($shmop_key);
echo PHP_EOL;
$shmop_id=shmop_open($shmop_key,'c',0600,16388);
var_dump($shmop_id);
echo PHP_EOL;
//shmop_write($shmop_id,"testshm",0);
var_dump(shmop_read($shmop_id,0,0));
shmop_close($shmop_id);