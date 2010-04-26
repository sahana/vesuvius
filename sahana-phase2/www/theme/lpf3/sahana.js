//function used to expand or collaps the mod_sub_menu.
function switchLogin(from,to){
	var fromBlock=document.getElementById(from).style;
	var toBlock=document.getElementById(to).style;
	fromBlock.display='none';
	toBlock.display='block';
}

