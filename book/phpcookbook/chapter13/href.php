<?php
$html=<<<_HTML_
<html>
<head>
</head>
<body>
<p>Some things I enjoy eating are:</p>
<ul>
<li><a href="http://en.wikipedia.org/wiki/Pickle">Pickles</a></li>
<li><a href="http://www.eatingintranslation.com/2011/03/great_ny_noodle.html">
Salt-Baked Scallops</a></li>
<li><a href="http://www.thestoryofchocolate.com/">Chocolate</a></li>
</ul>
</body>
</html>
_HTML_;

$doc =new DOMDocument();
$doc->loadHTML($html);
$xpath=new DOMXPath($doc);
//print_r($xpath->query('//a/@href'));
//die;
foreach($xpath->query('//a/@href') as $node){
print_r($node->nodeValue);
echo PHP_EOL;

}