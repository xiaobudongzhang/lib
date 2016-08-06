<?php
trait T1{
      public function getName(){
       }
}

trait T2{
      public function getAge(){

      }
}

interface Aw{
public function getA();
}
class Person implements Aw{
      use T1;
      use T2;
      public function getA(){

      }
}
$x=new Person();
$x->getName();

print_r(class_implements('Person'));


$rc=new ReflectionClass('Person');

print_r($rc);