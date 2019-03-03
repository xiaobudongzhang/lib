<?php
//函数类的有bug @todo
$mysql_sess_dbh = NULL;
//echo "44444".PHP_EOL;

//ini_set ("session.save_handler", "user");

//$x=new mysess();
//session_set_save_handler ($x,true);
/**"mysql_sess_open",
"mysql_sess_close",
"mysql_sess_read",
"mysql_sess_write",
"mysql_sess_destroy",
"mysql_sess_gc"
);*/


//register_shutdown_function('mysql_sess_close');


//session_start ();
//var_dump($_SESSION);
//if(isset($_SESSION["timestamp"])){
//	
//        echo $_SESSION["timestamp"];
//}else{
//	echo "dd";die;
 //       $_SESSION["timestamp"]="ddd";
//}


class mysess  implements SessionHandlerInterface{

function open ($save_path, $sess_name)
{//var_dump("open");
	global $mysql_sess_dbh;//var_dump($mysql_sess_dbh);
	# open connection to MySQL if it's not already open
	if ($mysql_sess_dbh === NULL)
	{
	
	
		try
		{

			$dsn = "mysql:host=localhost;dbname=test";
			$pass=file_get_contents("/tmp/mysqlpass");
			$mysql_sess_dbh  = new PDO ($dsn, "root", trim($pass));
			//$mysql_sess_dbh->prepare("show databases");
			 $mysql_sess_dbh->setAttribute (PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
		}
		catch (PDOException $e)
		{
			throw $e;
	
			//$mysql_sess_dbh = NULL;
			//return (FALSE);
		}
	}
	return (TRUE);
}


function close ()
{//var_dump("close");
	global $mysql_sess_dbh;//var_dump($mysql_sess_dbh);
	if ($mysql_sess_dbh !== NULL) # close connection if it's open
	$mysql_sess_dbh = NULL;
	return (TRUE);
}





function write ($sess_id, $sess_data)
{//var_dump("write");var_dump($sess_data);
	global $mysql_sess_dbh;//var_dump($mysql_sess_dbh);
	
	if($mysql_sess_dbh===null){
		return false;
	}	
	try
	{
		$stmt = "REPLACE php_session (id, data) VALUES(?,?)";
		$sth = $mysql_sess_dbh->prepare ($stmt);
		$sth->execute (array ($sess_id, $sess_data));
		return (TRUE);
	}
	catch (PDOException $e)
	{
		throw $e;
		//return (FALSE);
	}
}



function destroy ($sess_id)
{//var_dump("destroy");
	global $mysql_sess_dbh;//var_dump($mysql_sess_dbh);
	try
	{
		$stmt = "DELETE FROM php_session WHERE id = ?";
		$sth = $mysql_sess_dbh->prepare ($stmt);
		$sth->execute (array ($sess_id));
		return (TRUE);
	}
	catch (PDOException $e)
	{
	return (FALSE);
	}
}

function gc ($sess_maxlife)
{var_dump("gc");var_dump($sess_maxlife);
	global $mysql_sess_dbh;//var_dump($mysql_sess_dbh);
	try
	{
		$stmt = "DELETE FROM php_session
		WHERE update_time < NOW() - INTERVAL ? SECOND";
		$sth = $mysql_sess_dbh->prepare ($stmt);
		$sth->execute (array ($sess_maxlife));
	}
	catch (PDOException $e) { /* do nothing */ }
	return (TRUE); # ignore errors
}



function read ($sess_id)
{//var_dump("read");
	global $mysql_sess_dbh;//var_dump($mysql_sess_dbh);
	try
	{
		$stmt = "SELECT data FROM php_session WHERE id = ?";
		$sth = $mysql_sess_dbh->prepare ($stmt);
		$sth->execute (array ($sess_id));
		list ($data) = $sth->fetch (PDO::FETCH_NUM);
		//var_dump($data);
		if (isset ($data))
			return ($data);
	}
	catch (PDOException $e) { throw $e;/* do nothing */ }
	return ("");
}

}



//  $x=new mysess();
 //session_set_save_handler ($x,true);
//register_shutdown_function('mysql_sess_close');
session_cache_expire(300);
session_start ();
var_dump($_SESSION);
if(isset($_SESSION["timestamp"])){
	echo $_SESSION["timestamp"];
}else{
	var_dump("d");
	$_SESSION["timestamp"]="ddd";
}
