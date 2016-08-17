<?php
//utf8
$kr = '노크, 노크. 거기 누구입니까? R2D2!';
$kr_words=preg_match_all('/\w+/u', $kr,$matches);
//dump($matches);

//分组
$todo = "1. Get Dressed 2. Eat Jelly 3. Squash every week into a day";
preg_match_all("~\d\.([^\d]+)~", $todo,$matches2,PREG_PATTERN_ORDER);
//dump($matches2);

//非贪婪模式
$html = 'I simply <em>love</em> your <em>work</em>';
preg_match_all('~<em>.+</em>~U', $html,$match3);
//dump($match3);

dump(file('E:/t.log'));
