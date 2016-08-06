<?php
class data{
      public static $x=1;
      const read=1;
      public function __get2($key){
      	    // return "a";
      }
      public function __set2($key,$value){
      echo "set";
      }

      public static function test(){
      
      }
	
      public function test32(){
      
      }
}

$data=new data();
$data->name=1;

echo $data::$x;