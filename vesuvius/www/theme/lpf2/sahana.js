//function used to expand or collaps the mod_sub_menu.
function switchLogin(from,to){
	var fromBlock=document.getElementById(from).style;
	var toBlock=document.getElementById(to).style;
	fromBlock.display='none';
	toBlock.display='block';
}



//function used to hide/show a DIV
function switchMode(from,to,mode_var,new_value){
	var mode_tmp=document.getElementsByName("mode");
	var fromBlock=document.getElementById(from).style;
	var toBlock=document.getElementById(to).style;
	fromBlock.display='none';
	toBlock.display='block';
	mode_tmp[0].value=new_value;
}



//function used to expand or collaps the mod_sub_menu.
function expand(id,el){
	var menu=document.getElementById(id).style;
	if(menu.display=='block') {
		el.className='smopen';
		menu.display='none';
		removeMenu(id);
	} else {
		el.className='smclose';
		menu.display='block';
		addMenu(id);	
	}
}



function changeClass(el) {
	var a=el.parentNode.getElementsByTagName('a');
	a[0].className='smclose';
}



//function used to show the mod sub menus in startup
function showMem(){
	//showMenuMouseOver();
	checkOnload();
	var check_pin = getCookie('pin');
	if(check_pin!='') {
		document.getElementById('modmenuwrap').getElementsByTagName('ul')[0].style.display="block";
		setLayout();
	} else {
		document.getElementById('modmenuwrap').getElementsByTagName('ul')[0].style.display="none";
		//alert("not set");
	}
	var list=getMenuList();
	var el;
	for (var i=0;i<list.length;i++) {
		if(list[i]=='') {
			continue;
		}
		// alert(list[i]);
		el = document.getElementById(list[i]);
		if (el) {
			//el.className='smclose';
			changeClass(el);
			el.style.display='block';
		} else {
			removeMenu(list[i]);
		}
	}
}



function addMenu(id) {
	var list=getMenuList();
	var st='';
	for (var i=0;i<list.length;i++) {
		if (list[i]==id||list[i]=='') {
			continue;
		}
		st=st+list[i]+"|";
	}
	st = st+id;
	document.cookie = "menulist="+st+" ; path=/";    
}



function removeMenu(id) {
	var list=getMenuList();
	var st='';
	for (var i=0;i<list.length;i++) {
		if(list[i]==id||list[i]=='')continue;
		st=st+list[i]+"|";
	}
	document.cookie = "menulist="+st+" ; path=/";
}



function getMenuList() {
	document.getElementById('menuwrap').getElementsByTagName('h2')[0].onmouseover=shoMenuOn;
	document.getElementById('menuwrap').getElementsByTagName('h2')[0].onclick=shoMenuOnclick;
	document.getElementById('content').onclick=shoMenuOnclickContent;
	document.getElementById('content').onmouseover=hideMenuOnmouseContent;
	document.getElementById('modmenuwrap').getElementsByTagName('h2')[0].onclick=shoSubmenuOnclick;
	document.getElementById('modmenuwrap').getElementsByTagName('h2')[0].onmouseover=shoSubmenuonover;
	document.getElementById('header').onclick=headOnclick;
	var nameEQ = "menulist=";
	var namelist="";
	var ca = document.cookie.split(';');
	for(var i=0;i < ca.length;i++) {
		var c = ca[i];
		while (c.charAt(0)==' ') c = c.substring(1,c.length);
		if (c.indexOf(nameEQ) == 0) {
			namelist=c.substring(nameEQ.length,c.length);
		}
	}
	return namelist.split('|');
}



 //mouse ovger action
function shoMenuOn() {
	var check=document.getElementById('menuwrap').getElementsByTagName('ul')[0].style;
	if(check.display=="block") {
		var check_pin=getCookie('pin');
		if(check_pin=='') {
			var check_sub=document.getElementById('modmenuwrap').getElementsByTagName('ul')[0].style.display="none";
			document.getElementById('modmenuwrap').style.paddingBottom="0px";

		}
	} else {
		check.display="block";
		document.getElementById('menuwrap').style.paddingBottom="0px"; // 12px
		var check_sub=document.getElementById('modmenuwrap').getElementsByTagName('ul')[0].style.display="block";
		document.getElementById('modmenuwrap').style.paddingBottom="0px"; // 12px
	}
}



function shoMenuOnclick() {
	var check=document.getElementById('menuwrap').getElementsByTagName('ul')[0].style;
	if(check.display=="block") {
		check.display="none";
		document.getElementById('menuwrap').style.paddingBottom="0";
		var check_pin=getCookie('pin');
		if(check_pin=='') {
			var check_sub=document.getElementById('modmenuwrap').getElementsByTagName('ul')[0].style.display="none";
			document.getElementById('modmenuwrap').style.paddingBottom="0px";
		}
	} else {
		check.display="block";
		document.getElementById('menuwrap').style.paddingBottom="0px"; // 12px
		var check_sub=document.getElementById('modmenuwrap').getElementsByTagName('ul')[0].style.display="block";
		document.getElementById('modmenuwrap').style.paddingBottom="0px"; // 12px
	}
}



function shoSubmenuOnclick() {
	var check_pin=getCookie('pin');
	if(check_pin=='') {
		var check_sub=document.getElementById('modmenuwrap').getElementsByTagName('ul')[0].style;
		if(check_sub.display=="none") {
			check_sub.display="block";
			document.getElementById('modmenuwrap').style.paddingBottom="0px"; // 12px
		} else {
			check_sub.display="none";
			document.getElementById('modmenuwrap').style.paddingBottom="0px";
		}
	}
}



function shoSubmenuonover() {
	var submod=document.getElementById('modmenuwrap').getElementsByTagName('ul')[0].style;
	if(submod.display=="none") {
		submod.display="block";
		document.getElementById('modmenuwrap').style.paddingBottom="0px"; // 12px
	}
}



//writing a cookie to track to check box is set or not
function writeCookie() {
	var pin=document.getElementById('pin').checked;
	if(pin) {
		document.cookie="pin=set";
		setLayout();
		document.getElementById('menuwrap').getElementsByTagName('ul')[0].style.display="none";
		document.getElementById('menuwrap').style.paddingBottom="0px";
	} else {
		deleteCookie();
		resetLayout();
	}
}



//checking weather the cookies are set
function getCookie( c_name ) {
	if (document.cookie.length>0) 	{
		c_start=document.cookie.indexOf(c_name + "=");
		if (c_start!=-1) {
			c_start=c_start + c_name.length+1;
			c_end=document.cookie.indexOf(";",c_start);
			if (c_end==-1) {
				c_end=document.cookie.length;
			}
			return unescape(document.cookie.substring(c_start,c_end));
		}
	}
	return "";
}



//deleting cookies
function deleteCookie() {
	var date = new Date();
	document.cookie = "pin=set;expires=" + date.toGMTString() + ";" + ";";
}



function setLayout() {
	document.getElementById('content').style.margin="0 0 0 208px";
}



function resetLayout() {
	document.getElementById('content').style.margin="0 0 0 0px";
}



function checkOnload() {
	var head=document.getElementById('modmenuwrap').getElementsByTagName('h2')[0].innerHTML;
	var checkbox=getCookie("pin");
	if (checkbox=='') {
		var testin=document.getElementById('modmenuwrap').getElementsByTagName('h2')[0].innerHTML=head+'&nbsp;&nbsp;<input type="checkbox" name="pin" id="pin" onclick="writeCookie()"/><a href="#" class="pinBox"></a>';
	} else {
		var testin=document.getElementById('modmenuwrap').getElementsByTagName('h2')[0].innerHTML=head+'&nbsp;&nbsp;<input type="checkbox" name="pin" id="pin" checked="true" onclick="writeCookie()"/><a href="#" class="pinBox"></a>';
	}
}



function shoMenuOnclickContent() {
	var check=document.getElementById('menuwrap').getElementsByTagName('ul')[0].style;
	if(check.display=="block") {
		check.display="none";
		document.getElementById('menuwrap').style.paddingBottom="0";
		var check_pin=getCookie('pin');
		if(check_pin == '') {
			document.getElementById('modmenuwrap').getElementsByTagName('ul')[0].style.display="none";
			document.getElementById('modmenuwrap').style.paddingBottom="0px";
		}
	} else {
		var check_pin=getCookie('pin');
		if(check_pin == '') {
			document.getElementById('modmenuwrap').getElementsByTagName('ul')[0].style.display="none";
			document.getElementById('modmenuwrap').style.paddingBottom="0px";
		}
	}
}



function hideMenuOnmouseContent() {
	var check=document.getElementById('menuwrap').getElementsByTagName('ul')[0].style;
	if(check.display=="block") {
		check.display="none";
		document.getElementById('menuwrap').style.paddingBottom="0";
	}
	var check_pin=getCookie('pin');
	if(check_pin == '') {
		document.getElementById('modmenuwrap').getElementsByTagName('ul')[0].style.display="none";
		document.getElementById('modmenuwrap').style.paddingBottom="0px";
	}
}



function headOnclick() {
	window.open("index.php","_self");
}



// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //
// checkbox pin styling


function toggleCheckbox(cbId,cbKey,ffId) {
	if ( cbKey == 0 || cbKey == 32) {
		var cbFF = document.getElementById(ffId);
		var cbFFValue = cbFF.checked;
		if (cbId.className.indexOf("CheckboxChecked")<0) {
			var checkBoxType = cbId.className.replace("CheckboxUnchecked","");
			cbFF.checked=true;cbId.className="CheckboxChecked"+checkBoxType;
		} else {
			var checkBoxType = cbId.className.replace("CheckboxChecked","");
			cbFF.checked=false;cbId.className="CheckboxUnchecked"+checkBoxType;
		}
		return false;
	}
}
