<?php
$image_path='tx.PNG';
/* print_r(exif_read_data('x.jpg'));
die; */
$scale=0.2;


$image=imagecreatefrompng($image_path);
$thumb=imagecreatetruecolor(imagesx($image)*$scale, imagesy($image)*$scale);

imagecolortransparent($thumb,imagecolorallocatealpha($thumb, 0, 0, 0, 127));
imagealphablending($thumb, false);
imagesavealpha($image, true);

imagecopyresampled(
		$thumb,//$dst_image, 
		$image,//$src_image, 
		0,//$dst_x, 
		0,//$dst_y, 
		0,//$src_x, 
		0,//$src_y, 
		imagesx($thumb),//$dst_w, 
		imagesy($thumb),//$dst_h, 
		imagesx($image),//$src_w, 
		imagesy($image)//$src_h
		);



header('Content-type:image/png');
ImagePNG($thumb);
ImageDestroy($image);
ImageDestroy($thumb);