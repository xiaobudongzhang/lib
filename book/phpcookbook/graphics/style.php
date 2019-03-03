<?php
$black=0x000000;
$white=0xFFFFFF;

$image=ImageCreateTrueColor(1000,800);
/* 画一条虚线，5 个红色像素，5 个白色像素 */
$style=[$white, $black];
imagesetstyle($image, $style);

imageline($image, 0, 0, 50, 50, IMG_COLOR_STYLED);
imagefilledrectangle($image, 50, 50, 100, 100, IMG_COLOR_STYLED);

header('Content-type:image/png');
ImagePNG($image);
ImageDestroy($image);