function collapse(item){
	if (document.getElementById){
		var new_item = document.getElementById(item).style;
		if (new_item.display == "block"){
			new_item.display = "none";
		}else{
			new_item.display = "block";
		}
		return false;
	}else{
		return true;
	}
}

function hide(item){
	var new_item = document.getElementById(item).style;
	new_item.display = "none";
}