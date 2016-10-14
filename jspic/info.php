<?php
$coord=isset($_GET['coord'])?$_GET['coord']:'-1';
$map=file_get_contents("map.json");
$content=isset($map[$coord])?$map[$coord]:'no content';

$html = <<<HTML
<!DOCTYPE html>
<html>
<head>
    <title>demo</title>
    <script>
	function getHttpObject(){
	    if(typeof XMLHTTPRequest =="undefinded")
		XMLHttpRequest =function(){
		    try{
		    return new ActiveXObject("Msxml2.XMLHTTP.6.0");
		    }catch(e){}
		    try{
		    return new ActiveXObject("Msxml2.XMLHTTP.3.0");
		    }catch(e){}
		    try{
		    return new ActiveXObject("Msxml2.XMLHTTP");
		    }catch(e){}
		    return false;
		}
	    return new XMLHttpRequest();
	}

	function getNewContent(content){
	    var request = getHttpObject();
	    if(request){
		request.open("POST","infoedit.php",true);
		request.onreadystatechange=function(){
		    if(request.readyState==4){
				var resTxt=request.responseText;
				console.log(resTxt);
				//alert("修改成功");
	   			//var textareaid=document.getElementById("textareaid");
				//textareaid.textContent =txt;
		    }else{
		    	alert("修改失败");
		    }
		};
		//request.setRequestHeader("Content-Length",content.lenght);  
       	request.setRequestHeader("Content-Type","application/x-www-form-urlencoded;");  //用POST的时候一定要有这句  
		request.send("info={'FullName':'王继军','Company':'上海天正','Address':'田林路388号'}");
	    }else{
	    console.log("no XMLHTTPRequest");
	    }
	}

   	function submitsome(){
   		var content=document.getElementById("textareaid").childNodes[0];
   		getNewContent(content);
   	}
    </script>
</head>

<body >
    <div>
    	<form>
	  		<textarea rows="30" cols="80" id="textareaid">
	 		{$content}
			</textarea>
			<input type="submit" onclick="submitsome()" value="修改" id="submitid">
    	</form>
    </div>
</body>

</html>
HTML;
echo $html;