<?php
/**  create database
$db = new SQLite3('E:/tmp/sqlite/test.db');
$db->exec('CREATE TABLE foo (bar STRING)');
$db->exec("INSERT INTO foo (bar) VALUES ('This is a test')");
$result = $db->query('SELECT bar FROM foo');
**/


 header('Pragma:No-cache');
header('Cache-Control:No-cache');
header('Expires:0'); 
header('Content-Type: application/csv');
header('Content-Disposition:attachment;filename="sales.csv"'); 
//Content-Disposition:attachment;filename=abc.csv
$db = new PDO('sqlite:E:/tmp/sqlite/test.db');
 $query =$db->query('select * from foo',PDO::FETCH_NUM);
$sales_data=$query->fetchAll();

$output =fopen('php://output', 'wb') or die('can\'t open php://output ');
$total=0;

//header('Pragma:No-cache');
//header('Cache-Control:No-cache');
//header('Expires:0'); 



fputcsv($output, ['title']);
foreach ($sales_data as $value) {
	fputcsv($output, $value);
	$total++;
}

fputcsv($output, [$total]);

fclose($output)  or die('can\'t close php://output');