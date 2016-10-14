function showCoords(evt) {
	//定位
	console.log("clientX value: " + evt.clientX + "\n" + "clientY value: "
			+ evt.clientY + "\n");
	//弹窗
	window.open("http://127.0.0.1:8899/info.php", "DescriptiveWindowName",
			"resizable,scrollbars,status");
	//修改
}


//drags
var dragged;
var dragId=document.getElementById("draggable");
/* events fired on the draggable target */
dragId.addEventListener("drag", function( event ) {
	
console.log("action:drag--"+"clientX value: " + event.clientX + "\n" + "clientY value: "
		+ event.clientY + "\n");
}, false);

dragId.addEventListener("dragstart", function( event ) {
    // store a ref. on the dragged elem
    dragged = event.target;
    // make it half transparent
    event.target.style.opacity = .5;
    console.log("action:dragstart--"+"clientX value: " + event.clientX + "\n" + "clientY value: "
    		+ event.clientY + "\n");
}, false);

dragId.addEventListener("dragend", function( event ) {
	var mimg=event.target;
	 console.log(mimg);
	 var myimg=document.getElementById("myimg");
	 myimg.appendChild( mimg );
    // reset the transparency
   // event.target.style.opacity = "";
    console.log("action:dragend--"+"clientX value: " + event.clientX + "\n" + "clientY value: "
    		+ event.clientY + "\n");
}, false);

/* events fired on the drop targets */
dragId.addEventListener("dragover", function( event ) {
    // prevent default to allow drop
    event.preventDefault();
    console.log("action:dragover--"+"clientX value: " + event.clientX + "\n" + "clientY value: "
    		+ event.clientY + "\n");
}, false);

dragId.addEventListener("dragenter", function( event ) {
    // highlight potential drop target when the draggable element enters it
    if ( event.target.className == "dropzone" ) {
        event.target.style.background = "purple";
    }
    console.log("action:dragenter--"+"clientX value: " + event.clientX + "\n" + "clientY value: "
    		+ event.clientY + "\n");
}, false);

dragId.addEventListener("dragleave", function( event ) {
    // reset background of potential drop target when the draggable element leaves it
    if ( event.target.className == "dropzone" ) {
        event.target.style.background = "";
    }
    console.log("action:dragleave--"+"clientX value: " + event.clientX + "\n" + "clientY value: "
    		+ event.clientY + "\n");
}, false);

dragId.addEventListener("drop", function( event ) {
    // prevent default action (open as link for some elements)
    event.preventDefault();
    // move dragged elem to the selected drop target
  //  if ( event.target.className == "dropzone" ) {
   // console.log(event.target);
  //      event.target.style.background = "";
    //    dragged.parentNode.removeChild( dragged );
    //    event.target.appendChild( dragged );
 //   }
    console.log("action:drop--"+"clientX value: " + event.clientX + "\n" + "clientY value: "
    		+ event.clientY + "\n");
}, false);