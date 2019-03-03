<?php
//x.jpg to 533.png
$image=imagecreatefrompng('553.png');
$stamp=imagecreatefromjpeg('x.jpg');

$margin=['right'=>10,'bottom'=>10];
//one method
/**imagecopy($image, $stamp,
		imagesx($image)-imagesx($stamp)-$margin['right'], 
		imagesy($image)-imagesy($stamp)-$margin['bottom'], 
		0,
		0,//$src_y,
		imagesx($stamp),//$src_w
		imagesy($stamp)//, $src_h
		);
		*/
//two method
imagecopymerge(
		$image, $stamp,
		imagesx($image)-imagesx($stamp)-$margin['right'],
		imagesy($image)-imagesy($stamp)-$margin['bottom'],
		0,
		0,//$src_y,
		imagesx($stamp),//$src_w
		imagesy($stamp),//, $src_h
		30
		);

header('Content-type:image/png');
ImagePNG($image);
ImagePSFreeFont($image);
ImageDestroy($image);