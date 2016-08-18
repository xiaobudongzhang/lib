<?php
foreach(new DirectoryIterator('/etc')  as $file){
	  if(!$file->isDot()){
		    $file."\n";
	  }
}


$d=opendir('/etc');
while(false!==($f=readdir($d))){
 $f."\n";
}
closedir($d);

$dir=glob('/etc/');
//print_r($dir);


$dir=new RecursiveDirectoryIterator('/etc/');
//print_r($dir);
foreach(new RecursiveIteratorIterator($dir) as $file){
	     $file."\n";

}