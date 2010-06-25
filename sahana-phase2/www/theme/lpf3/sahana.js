//function used to expand or collaps the mod_sub_menu.
function switchLogin(from,to){
	var fromBlock = document.getElementById(from).style;
	var toBlock   = document.getElementById(to).style;
	fromBlock.display = 'none';
	toBlock.display   = 'block';
}


// function to redirect to a new page after a different event is selected
function changeEvent(shortname) {
	var i;
	var t;
	var found = false;
	var pathArray = window.location.pathname.split('/');
	var newPathname = '';
	for (i=0; i < pathArray.length; i++) {
		if (pathArray[i] == 'index.php') {
			found = true;
			break;
		}
	}
	if (found) {
		newPathname = pathArray[i];
	} else {
		newPathname = '';
	}
	t = window.location.protocol + '//' + window.location.host + '/' + shortname + '/' + newPathname + window.location.search;
	window.location.href = t;
}

function checkEvent(shortname, defaultEvent) {
	if (shortname == '') {
		changeEvent(defaultEvent);
	}
}