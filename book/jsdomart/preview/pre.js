function pre(){
console.log("pre");
if(!document.getElementsByTagName) return false;
if(!document.getElementById) return false;

if(!document.getElementById("linklist")) return false;
//if(!document.getElementById("preview")) return false;

//var  preview=document.getElementById("preview");


var slideshow=document.createElement("div");
slideshow.setAttribute("id","slideshow");
var preview=document.createElement("img");
preview.setAttribute("src","https://ss1.bdstatic.com/5eN1bjq8AAUYm2zgoY3K/r/www/cache/static/protocol/https/global/img/icons_0e814c16.png");
preview.setAttribute("id","preview");
slideshow.appendChild(preview);
var list=document.getElementById("linklist");


insertAfter(slideshow,list);

var links=document.getElementsByTagName("a");

links[0].onmouseover=function (){
    moveElement("preview",-100,0,10);
}
links[1].onmouseover=function (){
    moveElement("preview",-200,0,10);
}
links[2].onmouseover=function (){
    moveElement("preview",-300,0,10);
}

}

addLoadEvent(pre);
