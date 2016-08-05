<?php
// 注意空格
$text = "Birthday: May 11, 1918.";
$when = DateTime::createFromFormat ( "*: F j, Y.|", $text );
// var_dump ( $when );
echo $when->format ( DateTime::RFC850 );
echo PHP_EOL;

$when=new DateTime("@946684800",new DateTimeZone('America/Los_Angeles'));
//$when->setTimezone(new DateTimeZone('America/Los_Angeles'));
echo $when->format('Y-m-d H:i:s');
echo PHP_EOL;


$first = new DateTime("1962-10-10 7:32:56pm",
		new DateTimeZone('America/New_York'));
// 4:29:11 am on November 20, 1962
$second = new DateTime("1962-11-10 4:29:11am",
		new DateTimeZone('America/New_York'));

$diff=$second->diff($first);
print_r($diff->format('%a'));
echo PHP_EOL;
$datetime1 = new DateTime('2009-10-11');
$datetime2 = new DateTime('2009-10-13');
$interval = $datetime1->diff($datetime2);
echo $interval->format('%R%a days');
echo PHP_EOL;