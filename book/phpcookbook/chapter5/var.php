<?php
$res=apc_store('pop','aaa',10);
var_dump($res);
$pop=apc_fetch('pop');
var_dump($pop);