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


$birthday = new DateTime('March 10, 1975');
$human_gestation =new DateInterval('P40W');
$birthday->sub($human_gestation);
print $birthday->format(DateTime::ISO8601);
echo PHP_EOL;

$elephant_gestation = new DateInterval('P365D');
$birthday->add($elephant_gestation);
print $birthday->format(DateTime::ISO8601);
echo PHP_EOL;

$year = 2016;
$when = new DateTime("November 1,$year");
print_r($when);
echo PHP_EOL;
if($when->format('D')!='Mon'){
	$when->modify("next Monday");
}
print_r($when);
echo PHP_EOL;
$when->modify("next Tuesday");
print_r($when);
echo PHP_EOL;

$nowInNewYork = new DateTime('now',new DateTimeZone('America/New_York'));
$nowInCalifornia = new DateTime('now',new DateTimeZone('America/Los_Angeles'));
printf("New York:%s  \nCalifornia:%s",$nowInNewYork->format(DateTime::RFC850),$nowInCalifornia->format(DateTime::RFC850));
echo PHP_EOL;

function microtime_float()
{
	list($usec, $sec) = explode(" ", microtime());
	return ((float)$usec + (float)$sec);
}
echo microtime();
echo PHP_EOL;
echo microtime(true);
echo PHP_EOL;
echo microtime_float();
echo PHP_EOL;
print_r(gettimeofday());
echo PHP_EOL;
$datetime=new DateTime();
print_r($datetime);
echo PHP_EOL;
echo $datetime->format('u');
echo PHP_EOL;

//DatePeriod
$start =new DateTime('August 1, 2014');
$end = new DateTime('September 1, 2014');
$interval =new DateInterval('P1D');
$range1 =new DatePeriod($start, $interval, $end);
foreach ($range1 as $d) {
	//print "day:".$d->format('d');
	//echo PHP_EOL;
}
//过去六个月
$end =new DateTime();
$start = new DateTime('-6 months ');
echo $start->format('m');
echo PHP_EOL;
$interval =new DateInterval('P1M');
$range3 =new DatePeriod($start, $interval, $end);
//print_r($range3);
foreach ($range3 as $m) {
	print "day:".$m->format('m');
	echo PHP_EOL;
}
echo PHP_EOL;
print_r(cal_info());