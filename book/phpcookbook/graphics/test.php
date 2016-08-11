<?php
$image=imagecreatefrompng('test.png');

$color=0x00FF00;
$string="this is my first string!";
$path='BlockFont.ttf';
//imagestring($image, 5, 100, 200, $string, $color);
imagefttext($image, 50, 0, 200, 400, $color, $path, $string);
//计算出字体占比大小

$color_t=imagecolorallocatealpha($image, 0, 0, 0, 127);
imagecolortransparent($image,$color_t);

header('Content-type:image/png');
ImagePNG($image);
ImagePSFreeFont($image);
ImageDestroy($image);