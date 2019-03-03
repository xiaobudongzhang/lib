<?php
declare(ticks=1);

// A function called on each tick event
function tick_handler()
{
	echo "tick_handler() called\n";
}


register_tick_function('tick_handler');

