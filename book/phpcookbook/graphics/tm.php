<?php
$image=imagecreatefrompng('tx.PNG');

$color=0x00FF00;
$string="this is my first string!";
$path='BlockFont.ttf';
//imagestring($image, 5, 100, 200, $string, $color);
imagefttext($image, 50, 0, 200, 400, $color, $path, $string);
//计算出字体占比大小
//$box=imageftbbox(1,10,$path,$string);
//print_r($box);
$color_t=imagecolorallocatealpha($image, 0, 0, 0, 0);//透明色
imagecolortransparent($image,$color_t);//设置image透明色
imagealphablending($image, false);//混色模式
imagesavealpha($image, true);//

header('Content-type:image/png');
ImagePNG($image);
ImagePSFreeFont($image);
ImageDestroy($image);