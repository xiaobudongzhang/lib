<?php
$sx=simplexml_load_file('./test.xml');
//print_r($sx->title);
foreach($sx as $y){
print_r($y->__toString());
}