<?php
echo "<html><head></head><body>";
$db=new PDO('mysql:host:127.0.0.1;port:3306','root','666633');

$query=$db->query('select count(*) from test.user');
//print_r($result->fetchAll());
$offset = isset($_GET['offset'])?intval($_GET['offset']):1;
if(!$offset){ $offset=1; }
$per_page = 5;
$total = $query->fetchColumn(0);

$limitSql='select * from test.user  order by id '.
		  "limit $per_page offset ".($offset-1);
$lastRowNumber= $offset-1;

foreach( $db->query($limitSql) as $row){
	 $lastRowNumber++;
	 print "id:{$row['id']},age:{$row['age']}<br>";
}

indexed_links($total,$offset,$per_page);

print "<br/>";
print "(Dis $offset- $lastRowNumber of $total)";


function print_link($in,$text,$offset=''){
 if($in){
 print "<span class ='inactive'>$text</span>";
 }else{
 print "<span class='active'>".
       "<a href='".htmlentities($_SERVER['PHP_SELF']).
       "?offset=$offset'>$text</a></span>";
 }
}

function indexed_links($total,$offset,$per_page){
  $separator = '|';
  print_link($offset==1,'<< Prev',max(1,$offset-$per_page));
  
  for($start=1,$end =$per_page;
     $end<$total;
     $start+=$per_page,$end+=$per_page){
	print $separator;
	print_link($offset==$start,"$start-$end",$start);
     }
     //var_dump($start);
     $end =($total>$start)?"-$total":'';
     print $separator;
     print_link($offset==$start,"$start$end",$start);
     
     print $separator;
     print_link($offset==$start,"Next>>",$offset+$per_page);
}
echo "</body>";
echo "</html>";