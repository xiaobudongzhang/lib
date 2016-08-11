<?php
$image=ImageCreateTrueColor(1000,800);
$color=0xCCCFFF;
$grey=ImageColorAllocate($image, 123, 90, 204);
//矩形
ImageFilledRectangle($image,0,0,800,600,$grey);
//线
imageline($image, 0, 0, 680, 588, $color);
//多边形
$points=[    0, 0,
                    100, 200,
                    300, 200];
imagepolygon($image, $points, count($points)/2, $color);
//椭圆弧
imagearc($image, 100, 100, 200, 200, 30, 1000, $color);
//椭圆
imageellipse($image, 200, 200, 50, 100, $color);
header('Content-type:image/png');
ImagePNG($image);
ImageDestroy($image);