<?php
abstract class Database {
	 abstract public function connect();
 	 abstract public function query();
}

class Mysql extends Database{
      public function connect(){

      }

      public function query(){
      

      }
}
$mysql=new Mysql();
$sqlite =clone $mysql;