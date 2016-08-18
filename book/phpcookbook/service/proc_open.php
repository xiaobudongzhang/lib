<?php

$timeout=10;
$streams=[];
$handles=[];

$delay=3;
for($id=0;$id<=1;$id++){
	$error_log="/tmp/error".$id.".txt";
	$des=[
	0=>['pipe','r'],
	1=>['pipe','w'],
	2=>['file',$error_log,'w']
	];

	$cmd='sleep ' . $delay . '; echo "Finished with delay of ' .
                      $delay . '".';
        $handles[$id]=proc_open($cmd,$des,$pipes);
	$streams[$id]=$pipes[1];
	$all_pipes[$id]=$pipes;
	$delay-=2;
}

while(count($streams)){
	$read=$streams;
	stream_select($read,$w=null,$e=null,$timeout);
	foreach($read as $r){
	     $id=array_search($r,$streams);
	     echo stream_get_contents($all_pipes[$id][1]);
	     if(feof($r))
	     {
		fclose($all_pipes[$id][0]);
		fclose($all_pipes[$id][1]);
		$return_val=proc_close($handles[$id]);
		unset($streams[$id]);
	     }
	}
}