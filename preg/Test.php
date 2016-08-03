<?php
$pattern='~d{0}~';
$str=$argv[1];
preg_match($pattern, $str,$matchs);
print_r($matchs);