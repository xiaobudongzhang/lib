<?php
$pantry = array('sugar' => '2 lbs.','butter' => '3 sticks');
$fp=fopen('/tmp/testvar','rb') or die(' cant open file');
fputs($fp,serialize($pantry));
while($buffer=fgets($fp,4096)){
var_dump(unserialize($buffer));
}
//var_dump(unserialize(fgets($fp)));
fclose($fp);
//var_dump(unserialize(file_get_contents('/tmp/testvar')));
//var_dump(json_decode(file_get_contents('/tmp/testvar'),true));