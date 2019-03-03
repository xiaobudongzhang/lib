<?php
//$myql = new PDO('mysql:host=127.0.0.1;prot=3306','root','666633');

$mysql2 = new PDO('mysql:unix_socket=/var/run/mysqld/mysqld.sock','root','666633');

$st=$mysql2->query('select  id,age from test.user',PDO::FETCH_BOUND);
//print_r($st->fetchAll());
$st->bindColumn(2,$age2);

while($st->fetch()){
//print $age2;
//print PHP_EOL;
}
//FETCH_INTO
$row = new StdClass();
$st=$mysql2->query('select  id,age from test.user',PDO::FETCH_INTO,$row);

while($st->fetch()){
//	print_r($row);
}
//echo "__LINE__";
//exec
 $line=__LINE__;
//$exc= $mysql2->exec("insert into test.user (id,age) values ($line//,$line)");
//var_dump($exc);
//$st=$st=$mysql2->query('select  id,age from test.user');
//print_r($st->fetchAll());


//preare
//$st = $mysql2->prepare('insert into test.user (id,age) values (:t//e,:test)');
//$res=$st->execute(array('te'=>9,'test'=>9));
//var_dump($res);

//bind
$st = $mysql2->prepare('select * from test.user where  id =:id');
$st->bindParam(':id',$id);
//$st->bindParam(':test',11);
$id=9;
//$res=$st->execute();
//var_dump($res);
//print_r($st->fetchAll());


//rowcount
$st = $mysql2->prepare('select * from test.user where  id =:id');
//var_dump($st);
//$st->execute(array('id'=>9));
//print_r($mysql2->errorInfo());
//echo $st->rowCount();
//print_r($st->fetchAll());

//error
try{
$mysql2->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
$st = $mysql2->prepare('select * from test.user where  ids =9');
$st->execute();
while($row = $st->fetch(PDO::FETCH_NUM)){
print_r($row);
}
}catch(Exception $e){
		 print_r($e->getCode());
}