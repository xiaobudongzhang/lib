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
function tb(){
    if(!document.getElementsByTagName) return false;
    var tables=document.getElementsByTagName("table");
    var odd,rows;
    for(var i=0;i<tables.length;i++){
	odd=false;
	rows=tables[i].getElementsByTagName("tr");
	for(var j=0;j<rows.length;j++){
	    if(odd==true){
	    //rows[j].style.backgroundColor="#2fc";
		addClass(rows[j],"odds");
	    odd=false;
	    }else{
	    odd=true;
	    }
	    
	    rows[j].onmouseover=function(){
		this.style.fontSize="20px";
	    }
	    rows[j].onmouseout=function(){
		this.style.fontSize="1px";
	    }
	    
	}
    }
}
function addClass(element,value){
    if(!element.className){
	element.className=value;
    }else{
	newClassName=element.className;
	newClassName+="";
	newClassName+=value;
	element.className=newClassName;
    }

}
addLoadEvent(tb);
