<?php
//xdebug_start_trace();

function factorial($x) {
return ($x == 1) ? 1 : $x * factorial($x - 1);
}
print factorial(10);
xdebug_stop_trace();