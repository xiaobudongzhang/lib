<?php
function tab_expand($text) {
	while ( strstr ( $text, "\t" ) ) {
		$text = preg_replace_callback ( '@^([^\t\n]*)(\t+)@m', 'tab_expand_helper', $text );
	}
	return $text;
}
function tab_expand_helper($matchs) {
	$tab_stop = 8;
	return $matchs [1] . str_repeat ( '  ', strlen ( $matchs [2] ) * $tab_stop - (strlen ( $matchs [1] ) % $tab_stop) );
}
$str= 'abc
		def\t' ;
echo $str;
$spaced = tab_expand ($str );
echo $spaced;
echo PHP_EOL;
echo PHP_EOL;
echo PHP_EOL;

