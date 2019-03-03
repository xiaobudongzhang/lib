<?php
$dbh=dba_open('/tmp/dba/fish.db','c','db4');

if(dba_exists('fl',$dbh)){
 $fl_count = dba_fetch('fl',$dbh);
 $fl_count++;
 dba_replace('fl',$fl_count,$dbh);
 print "update ;";
}else{
 dba_insert('fl',1,$dbh);
 print "insert";
}

for( $key=dba_firstkey($dbh);$key!=false;$key=dba_nextkey($dbh)){
 $value=dba_fetch($key,$dbh);
 print "$key:$value".PHP_EOL;
}

dba_close($dbh);