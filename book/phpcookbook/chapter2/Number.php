<?php
$number='1234.56';
//print_r(localeconv());
echo PHP_EOL;
$usa=new NumberFormatter('en-US', NumberFormatter::CURRENCY);
echo $usa->format($number); 
 echo PHP_EOL;
 
 //echo 12/13;
 echo PHP_EOL;
 $sum=gmp_add('1111','2222');
 echo $sum;
 echo PHP_EOL;
 echo gmp_add($sum,2);
 echo PHP_EOL;