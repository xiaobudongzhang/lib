<?php

$packed = pack('S4',1974,106,28225,32725);
print_r($packed);

print_r(unpack('S1a/S1b/', $packed));
echo PHP_EOL;