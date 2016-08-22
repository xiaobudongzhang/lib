function showPic(whichpic){
    if(!document.getElementById("placeholder")) return false;
    var source=whichpic.getAttribute("href");
    var placeholder=document.getElementById("placeholder");
    placeholder.setAttribute("src",source);
    if(document.getElementById("desc")){
    var text = whichpic.getAttribute("title")? whichpic.getAttribute("title"):"default";
    var desc=document.getElementById("desc");
    desc.firstChild.nodeValue=text;
    }
    return true;
}

function prepareGallery(){
//console.log(document.getElementsByTagName);
if(!document.getElementsByTagName) return false;
if(!document.getElementById) return false;
if(!document.getElementById("imagegallery")) return false;
var gallery = document.getElementById("imagegallery");
console.log(gallery);
var links = gallery.getElementsByTagName("a");
    for(var i=0;i<links.length;i++){
	links[i].onclick=function(){
	return !showPic(this);
	}
    }
}
 
function addLoadEvent(func){
 var oldonload = window.onload;
 if(typeof window.onload !='function'){
     window.onload=func;
     }else{
   window.onload=function(){
       oldonload();
       func();
   }
 }

}
function insertAfter(newElement,targetElement){
    var parent=targetElement.parentNode;
    if(parent.lastChild==targetElement){
	parent.appendChild(newElement);
    }else{
	parent.insertBefore(newElement,targetElement.nextSibling);
    }
}
function preparePlaceholder(){
    if(!document.createElement) return false;
    if(!document.createTextNode) return false;
    if(!document.getElementById) return false;
    if(!document.getElementById("imagegallery")) return false;

    var placeholder = document.createElement("img");
    placeholder.setAttribute("id","placeholder");
    placeholder.setAttribute("src","4.jpg");
    placeholder.setAttribute("alt","my gallery");
    
    var desc=document.createElement("p");
    desc.setAttribute("id","desc");
    var desctext=document.createTextNode("choos a img");
    desc.appendChild(desctext);
    
    var gallery=document.getElementById("imagegallery");
    insertAfter(placeholder,gallery);
    insertAfter(desc,placeholder);
}
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
function getNewContent(){
    var request = getHttpObject();
    if(request){
	request.open("GET","test.txt",true);
	request.onreadystatechange=function(){
	    if(request.readyState==4){
		var para=document.createElement("p");
		var txt=document.createTextNode(request.responseText);
		para.appendChild(txt);
		document.body.appendChild(para);
	    }
	};
	request.send(null);
    }else{
    console.log("no XMLHTTPRequest");
    }
}
addLoadEvent(preparePlaceholder);
addLoadEvent(prepareGallery);
addLoadEvent(getNewContent);
