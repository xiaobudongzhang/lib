<?php
$str="3+2/7-9";

print_r(preg_split('~(?:[+\-*\/])~', $str,-1,PREG_SPLIT_DELIM_CAPTURE));