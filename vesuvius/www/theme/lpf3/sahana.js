//function used to expand or collaps the mod_sub_menu.
function switchLogin(from,to){
	var fromBlock = document.getElementById(from).style;
	var toBlock   = document.getElementById(to).style;
	fromBlock.display = 'none';
	toBlock.display   = 'block';
}


// function to redirect to a new page after a different event is selected
function changeEvent(shortname) {
	var i       = 0;
	var j       = 0;
	var path    = '';
	var path2   = '';
	var p       = window.location.pathname;
	var pArray  = window.location.pathname.split('/');
	var pLength = pArray.length;

	// handle different url cases
	// case 1>> path = '/'
	// case 2>> path = '/index.php'
	// case 3>> path = '/shortname'
	// case 4>> path = '/shortname/'
	// case 5>> path = '/shortname/index.php'
	if(pLength<=3){
		path='/';
	}else{
		// case 6>> path = '/~gmiernicki/sahanaDev/www/'
		// case 7>> path = '/~gmiernicki/sahanaDev/www/index.php'
		// case 8>> path = '/~gmiernicki/sahanaDev/www/shortname'
		// case 9>> path = '/~gmiernicki/sahanaDev/www/shortname/'
		// case 10>>path = '/~gmiernicki/sahanaDev/www/shortname/index.php'
		for(i=0; i < pLength; i++) {
			if(pArray[i] == 'www') {
				path='/';
				for(j=1; j<=i; j++) {
					path = path+pArray[j]+'/';
				}
				break;
			}
		}
	}
	if(pArray[pLength-1] == 'index.php'){
		path2 = 'index.php';
	}
	var t = window.location.protocol+'//'+window.location.host+path+shortname+'/'+path2+window.location.search;
	window.location.href = t;
}

function checkEvent(shortname, defaultEvent) {
	if (shortname == '') {
		changeEvent(defaultEvent);
	}
}
