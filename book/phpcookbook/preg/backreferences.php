<?php
//后向引用  s匹配换行
$html=file_get_contents('ok.html');
preg_match_all('@<h([1-6])>(?<tas>.+?)</h\g<tas>>@is', $html,$matches);

dump($matches);