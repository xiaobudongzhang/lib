function inputSupport(type){
    if(!document.createElement) return false;
    var input =document.createElement('input');
    input.setAttribute("type",type);
    //console.log(type);
    //console.log(input.type);
    if(input.type=='text'&&type!='text'){
	return false;
    }else{
	return true;
    }
}
console.log(inputSupport('button'));
