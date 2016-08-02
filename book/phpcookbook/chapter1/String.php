<?php
//heredoc连接heredoc 结束时换行
print "--heredoc--";
echo PHP_EOL;
print<<<T2
test
T2
.'test2'.<<<T3
test3
T3;
echo PHP_EOL;
//substr中文
print "--substr--";
echo PHP_EOL;
echo substr('123456789', -3,-1);
echo PHP_EOL;
print "--substr_replace--";
echo PHP_EOL;
print substr_replace('123456789', 'a',-3,-1);
echo PHP_EOL;
