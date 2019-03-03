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
function displayAbbr(){
 if(!document.getElementsByTagName||!document.createElement||!document.createTextNode) return false;
 var abbr =document.getElementsByTagName("abbr");
 if(abbr.length<1) return false;
 var defs=new Array();
 for(var i=0;i<abbr.length;i++){
     var current_abbr=abbr[i];
     if(current_abbr.childNodes.length<1) continue;
     var definition=current_abbr.getAttribute("title");
     var key=current_abbr.lastChild.nodeValue;
     defs[key]=definition;
 }
 var dlist=document.createElement("dl");
 for(key in defs){
     var definition=defs[key];
     var dtitle=document.createElement("dt");
     var dtitle_text=document.createTextNode(key);
     dtitle.appendChild(dtitle_text);

     var ddesc=document.createElement("dd");
     var ddesc_text=document.createTextNode(definition);
     ddesc.appendChild(ddesc_text);
     dlist.appendChild(dtitle);
     dlist.appendChild(ddesc);
 }
if(dlist.childNodes.length<1) return false;
    var header=document.createElement("h2");
    var header_text=document.createTextNode("abbr view");
    header.appendChild(header_text);
    document.body.appendChild(header);
    document.body.appendChild(dlist);

}
function displayCites(){
    if(!document.getElementsByTagName||!document.createElement||!document.createTextNode) return fasle;
    var quotes=document.getElementsByTagName("blockquote");
    for(var i=0;i<quotes.length;i++){
	if(!quotes[i].getAttribute("cite")) continue;
	var url=quotes[i].getAttribute("cite");
	var quoteChildren = quotes[i].getElementsByTagName("*");
	if(quoteChildren.length<1) continue;
	var elem =quoteChildren[quoteChildren.length-1];
	
	var link=document.createElement("a");
	var link_text=document.createTextNode("source");
	link.appendChild(link_text);
	link.setAttribute("href",url);
	var superscript=document.createElement("sup");
	superscript.appendChild(link);
	elem.appendChild(superscript);
    }
}
function displayAccess(){
    if(!document.getElementsByTagName||!document.createElement||!document.createTextNode) return false;
    var links=document.getElementsByTagName('a');
    var akeys=new Array();
    for(var i=0;i<links.length;i++){
	var current_link=links[i];
	if(!current_link.getAttribute("accesskey")) continue;
	var key=current_link.getAttribute("accesskey");
	var text=current_link.lastChild.nodeValue;
	akeys[key]=text;
    }

    var list=document.createElement("ul");
    for(key in akeys){
	var text=akeys[key];
	var str=key+":"+text;
	var item=document.createElement("li");
	var item_text=document.createTextNode(str);
	item.appendChild(item_text);
	list.appendChild(item);
    }

    var header=document.createElement("h3");
    var header_text=document.createTextNode("Accesskeys");
    header.appendChild(header_text);
    document.body.appendChild(header);
    document.body.appendChild(list);
}
addLoadEvent(displayAccess);
addLoadEvent(displayCites);
addLoadEvent(displayAbbr);
