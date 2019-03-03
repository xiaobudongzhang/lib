<?php
$image=ImageCreateTrueColor(1000,800);

$color=0x00FF00;
$string="this is my first string!";
$path='BlockFont.ttf';
//imagestring($image, 5, 100, 200, $string, $color);
imagefttext($image, 50, 0, 200, 400, $color, $path, $string);
//计算出字体占比大小
//$box=imageftbbox(1,10,$path,$string);
//print_r($box);


header('Content-type:image/png');
ImagePNG($image);
ImagePSFreeFont($image);
ImageDestroy($image);