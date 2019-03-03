<?php
$choices = array('eggs' => 'Eggs Benedict',
'toast' => 'Buttered Toast with Jam',
'coffee' => 'Piping Hot Coffee');
print_r($_GET['food']);
//print_r($_POST);
//print_r(file_get_contents('php://input'));
//die;
print_r(array_keys($choices));
print_r(array_intersect($_GET['food'],array_keys($choices)));
if(array_intersect($_GET['food'],array_keys($choices))!=$_GET['food']){
echo "not valid!";
}