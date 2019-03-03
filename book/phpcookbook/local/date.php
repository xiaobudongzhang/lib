<?php
$when = 1376943432; 
$fmt = new IntlDateFormatter('zh_cn', IntlDateFormatter::FULL, IntlDateFormatter::FULL);
echo $fmt->format($when);