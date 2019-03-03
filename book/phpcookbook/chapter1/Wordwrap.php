<?php
$s = "Four score and seven years ago
a new nation, conceived in liberty an
that all men are created equal.";
print $s;
print PHP_EOL;
print wordwrap($s,3,"\n",true);