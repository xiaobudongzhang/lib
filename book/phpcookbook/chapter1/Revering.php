<?php
/**
 * resver string
 */
$string='This is not a book!';
print strrev($string);
echo PHP_EOL;
function str_reverse($str,$i){
return implode($i, array_reverse(explode($i, $str)));
}
print str_reverse($string, ' ');