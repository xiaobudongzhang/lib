<?php
$message = '{0,number} / {1,number}={2,number}';
$args = array(5327, 98, 5327/98);

$us = new MessageFormatter('fr_FR', $message);

//print $us->format($args);


$income=5549.3;
$debit=-25.95;
$pattern='{0,number,currency}  and {1,number,currency}';
$fmt= new MessageFormatter('en_US', $pattern);

//print $fmt->format([$income,$debit]);

$fmtnew=new NumberFormatter('en_US', NumberFormatter::CURRENCY);
print $fmtnew->formatCurrency($income, 'EUR');