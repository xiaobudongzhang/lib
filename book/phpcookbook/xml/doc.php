<?php
header('content-type:text/xml');
$dom = new DOMDocument('1.0');

$book=$dom->appendChild($dom->createElement('book'));
$title=$book->appendChild($dom->createElement('title'));

$title->appendChild($dom->createTextNode('PHPBook'));
$title->setAttribute('e',3);

$dom->formatOutput=true;
$out= $dom->saveXML();
echo ($out);