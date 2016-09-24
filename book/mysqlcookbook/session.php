<?php
session_start ();
var_dump($_SESSION);
if(isset($_SESSION["timestampd"])){
        echo $_SESSION["timestampd"];
}else{
        var_dump("d");
        $_SESSION["timestampd"]="ddd2";
}
