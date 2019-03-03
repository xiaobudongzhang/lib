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
function styleSet(){
    if(!document.getElementsByTagName) return false;
    var headers=document.getElementsByTagName("h1");
    var elem;
    for(var i=0;i<headers.length;i++){
	elem=getNextElement(headers[i].nextSibling);
	//console.log(headers[i].nextSibling.nextSibling);
	elem.style.fontWeight="bold";
	elem.style.fontSize="1.2em";
    }
}
function getNextElement(node){
    if(node.nodeType==1){
	return node;
    }
    if(node.nextSibling){
    return getNextElement(node.nextSibling);
    }
    return null;
}
addLoadEvent(styleSet);
