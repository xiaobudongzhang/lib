<?php
$filename='tx.PNG';
header("Content-Type:image/png");
readfile($filename);//读取文件并写入输出缓存