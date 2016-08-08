<?php
$reader = new XMLReader();
$reader->open('./test.xml');
while($reader->read()){
//	print_r($reader->nodeType);
	echo PHP_EOL;
	print_r($reader->value);

}