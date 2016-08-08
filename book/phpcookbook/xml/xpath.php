<?php
//xpath
$s=simplexml_load_file('./test.xml');
$titles=$s->xpath('/book/title');

foreach($titles as $title){
		print_r($title->__toString());
		echo PHP_EOL;
}

//dom
$dom=new  DOMDocument();
$dom->load('./test.xml');
$xpath=new DOMXPath($dom);
$titles=$xpath->query('/book/title');

foreach($titles as $title){
		print_r($title->nodeValue);
		echo PHP_EOL;
}