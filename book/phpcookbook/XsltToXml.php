<?php
$base_path='data'.DIRECTORY_SEPARATOR.'xml'.DIRECTORY_SEPARATOR;
$xsl = new DOMDocument();
$xsl->load($base_path.'test.xsl');
//加载样式表
$xslt = new XSLTProcessor();
$xslt->importStylesheet($xsl);
//加载文档
$xml=new DOMDocument();
$xml->load($base_path.'data.xml');
//输出
echo $results =$xslt->transformToXml($xml);