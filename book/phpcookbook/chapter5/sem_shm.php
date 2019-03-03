<?php
$sem_id=100;
$seg_id=200;

$sem=sem_get($sem_id,1,0600);
sem_acquire($sem)  or die("cant aquire sem");

$shm=shm_attach($sem_id,16333,0600);
$var_id=3476;
//shm_put_var($shm,$var_id,"sem_shm");
var_dump(shm_get_var($shm,$var_id));
shm_detach($shm);
sem_release($sem);