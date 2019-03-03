<?php
function profile($display = false) {
	static $times;
	$len = [ ];
	
	switch ($display) {
		case false :
			$times [] = microtime ( true );
			break;
		case true :
			
			$start_total = array_shift ( $times );
			
			foreach ( $times as $stop ) {
				$stop_total = $stop;
				$len [] = $stop_total - $start_total;
			}
			
			unset ( $times );
			return $len;
			break;
	}
}

register_tick_function ( 'profile' );

declare ( ticks = 1 ) {
	foreach ( $_SERVER ['argv'] as $arg ) {
		"$arg:" . strlen ( $arg ) . "\n";
	}
}
// (profile ( true ) );
print "---\n";
$i = 0;

foreach ( profile ( true ) as $time ) {
	$i ++;
	print "Line $i:$time\n";
}   