<?php
$sales =[
		['byz','2015-01-10','2016-01-02',12.54],
		['zhang','2013-01-10','2016-01-02',10.54],
		['wang','2011-01-10','2016-01-02',9.54],
];

$filename='../data/sales.csv';

$fh=fopen($filename, 'wb') or die('can\'t open file');
foreach ($sales as $sale_line) {
	if(FALSE===fputcsv($fh, $sale_line)){
		die(' can\'t write file');
	}
}

fclose($fh);


$sales =[
		['byz','2015-01-10','2016-01-02',12.54],
		['zhang','2013-01-10','2016-01-02',10.54],
		['wang','2011-01-10','2016-01-02',9.54],
];

$filename='../data/sales.csv';
ob_start();
$fh=fopen('php://output', 'a+b') or die('can\'t open file');
foreach ($sales as $sale_line) {
	if(FALSE===fputcsv($fh, $sale_line)){
		die(' can\'t write file');
	}
}

fclose($fh);

$output=ob_get_contents();
ob_end_clean();
var_dump($output);