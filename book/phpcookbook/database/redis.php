<?php
$redis = new Redis();
$redis->connect('127.0.0.1');
$redis->set('c',0);
$redis->incrBy('c',7);
$c=$redis->get('c');
echo $c;