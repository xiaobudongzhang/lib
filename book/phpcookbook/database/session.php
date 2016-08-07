<?php
session_start();
session_regenerate_id();
$_SESSION['x']=100;
print_r(SID);
print_r($_SESSION);
//echo "<a href=session.php>session</a>";