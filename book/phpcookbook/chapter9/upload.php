<?php if($_SERVER['REQUEST_METHOD']=='GET'){ ?>
	<form method="post" action="<?php echo htmlentities($_SERVER['SCRIPT_NAME']) ?>" enctype="multipart/form-data">
	<input type="file" name="document"/>
	<input type="submit" value="Send File">
	</form>
<?php }else{
      //print_r($_FILEs);
	if(isset($_FILES['document'])&&($_FILES['document']['error']==0)){
		echo "me";
		$newPath='/tmp/img/'.basename($_FILES['document']['name']);
			if(move_uploaded_file($_FILES['document']['tmp_name'],$newPath)){
				print "File save in $newPath";
			}else{
				print "file move failed";
			}
		}else{
		print_r($_FILES['document']['error']);
		}
      	 }


