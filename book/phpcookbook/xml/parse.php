<?php
$sx=simplexml_load_file('./test.xml');
//print_r($sx->title);
foreach($sx as $y){
//print($y->nodeValue);
//print_r($y->nodeType);
//print_r($y->__toString());
}


$dom=new DOMDocument();
$dom->load('./test.xml');

foreach($dom->getElementsByTagname('title')  as $title){
print_r($title->nodeValue);
}


