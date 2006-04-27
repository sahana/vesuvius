window.onload=hide;

//function used to expand or collaps the mod_sub_menu.
function expand(id){
	var menu=document.getElementById(id).style;
	if(menu.display=='none')
	{
		menu.display='block';	
	} 
	else{
		menu.display='none';	
	}
}

//function used to hide mod_sub_menu when the page loads. 
function hide(){
	el=document.getElementById("modmenu");
	var child=el.getElementsByTagName("ul");
	for (var i=0;i<child.length;i++){
	child[i].style.display='none';
	}	
}

