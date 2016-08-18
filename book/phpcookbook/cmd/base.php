<?php
//echo fgets(STDIN,1024);

//fwrite(STDOUT,"dsfs");

//fwrite(STDERR,"hi");

//print_r($argv);

//print_r(getopt('abc'));


$last=false;
while(!$last){
	$next=fgets(STDIN,1024);
	if(".\n"==$nex){
	$last=true;
	}else{
	echo $next."\n";
	}
}