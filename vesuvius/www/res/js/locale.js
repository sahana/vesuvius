/**
 * SAHANA Dyanmic Localization javascript library
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author      Prabath Kumarasinghe <prabath321@gmail.com>
 * @copyright   Lanka Software Foundation - http://www.opensource.lk
 */

var request = null;
function  createRequest(){
try {
  request = new XMLHttpRequest();
} catch (trymicrosoft) {
  try {
    request = new ActiveXObject("Msxml2.XMLHTTP");
  } catch (othermicrosoft) {
    try {
      request = new ActiveXObject("Microsoft.XMLHTTP");
    } catch (failed) {
      request = null;
    }
  }
}

if (request == null)
  alert("Error creating request object!");
}

var imptarg;
var tname3;
var locale;

function whichElement(e,set_locale){
locale = set_locale;
if (e.button==2){
	var targ
	if (!e) var e = window.event
	if (e.target) targ = e.target
	else if (e.srcElement) targ = e.srcElement
	if (targ.nodeType == 3) // defeat Safari bug
   		targ = targ.parentNode
	var tname;	
	imptarg = targ;
	tname=targ.nodeName
	tname3 = targ.textContent
		
	if(imptarg.tagName=='SELECT'){
		var i=0;
		while(i<targ.length){
			disp_promt_for_select(targ[i].textContent,imptarg.name);
			i++;
		}
			
	}else if(imptarg.type=='text'){
		alert('Text boxes tags cannot be translate');
	}else if(imptarg.type=='submit'){
		tname3 = imptarg.value;
		submitValuesForCheck(tname3);		
	}else{
		submitValuesForCheck(tname3);
	}
	
	
 	}
}

function disp_promt_for_select(tname3,tagname){
	var translateword = prompt(tname3,"");
	if(translateword!=null && translateword!="")
		submitSelectValues(translateword,tname3,tagname);
	
	
}

function submitSelectValues(translateword,tname3,tagname){
createRequest();
//var url = "testing.inc?msgid=" + escape(tname3) + "?msgstr=" + escape(important);
var url = "index.php?mod=admin&stream=locale";
//var url = "index.php?stream=locale";
//var url = "processrequest.php";
request.open("POST", url, true);
//request.open("GET", url, true);
request.onreadystatechange = getResponseForSelect;
request.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
request.send("translateword="+translateword+"&dropdownvalue="+tname3+"&tagname="+tagname+"&request="+'select');
//request.send(null);
}

function getResponseForSelect(){
	if(request.readyState==4){
		if(request.status==200){	
		alert("I am ahere");
		var test = request.responseText;
		
		}else{
			//alert("From else" + request.status);
		}
	}else{
		//alert("Erro! Request status is " + request.status);
	}
}


function submitValuesForCheck(tname3){
createRequest();
//var url = "testing.inc?msgid=" + escape(tname3) + "?msgstr=" + escape(important);
//var url = "index.php?stream=locale";
var url = "index.php?mod=admin&stream=locale";
//var url = "processrequest.php";
request.open("POST", url, true);
//request.open("GET", url, true);
request.onreadystatechange = getResponse;
request.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
request.send("msgid="+tname3+"&request="+'first');
//request.send(null);
}

function getResponse(){
if(request.readyState==4){
	if(request.status==200){	
		
		var restext = request.responseText;
				
			tag = restext.substring(0,6);			
			if(tag == 'tag111'){				
				disp_prompt_second(restext.substring(6),tname3);
			}else if(tag == 'tag222'){
				imptarg.textContent = restext.substring(6);
				disp_first_prompt();
			}else{
				imptarg.textContent = tname3;
				disp_prompt(tname3);
			}
			
	}
	else{
		//alert("From else" + request.status);
	}
	}else{
		//alert("Erro! Request status is " + request.status);
	}
}

var forcetext;
function disp_prompt_second(tname3,defaulttext){
	forcetext = tname3;   
	var translateword = prompt(tname3,defaulttext)
	if(translateword!=null && translateword!="")
		showResultTextTwo(translateword);
	
/*Ext.MessageBox.show({
           title: 'Sahana Localization',
           msg: tname3,
           width:600,
           buttons: Ext.MessageBox.OKCANCEL,
           multiline: true,
	   fn: showResultTextTwo,
	   value: defaulttext, 
	   //animEl: tname
        });*/
}

var importantTwo;
function showResultTextTwo(text){
	importantTwo = text;
	finalTwo();
	
};


function finalTwo(){
	
	if(importantTwo==''){
		imptarg.textContent = forcetext;
	}
	else{
		imptarg.textContent = importantTwo;
	}
	submitValuesTwo();		
}

function submitValuesTwo(){
createRequest();
//var url = "testing.inc?msgid=" + escape(tname3) + "?msgstr=" + escape(important);
//var url = "index.php?stream=locale";
var url = "index.php?mod=admin&stream=locale";
request.open("POST", url, true);
//request.open("GET", url, true);
request.onreadystatechange = requestSuccess;
request.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
request.send("msgid="+forcetext+"&msgstr="+importantTwo+"&request="+'second');
//request.send(null);
}


function requestSuccess(){
	if(request.readyState==4){
		if(request.status==200){		
		var test = request.responseText;		
		}else{
			//alert("From else" + request.status);
	 	}
	}else{
		//alert("Erro! Request status is " + request.status);
	}
}


function disp_first_prompt(){
alert('This word pharse already translated');
/*Ext.MessageBox.show({
           title: 'Sahana Localization',
           msg: "This word pharse already translated",
           width:230,
           buttons: Ext.MessageBox.OK,
           //multiline: true,
           //fn: showResultText,
           //animEl: tname
        });*/

}



function disp_prompt(tname3){
	var translateword = prompt(tname3,"");
	if(translateword!=null && translateword!="")
		showResultText(translateword);        

	/*Ext.MessageBox.show({
           title: 'Sahana Localization',
           msg: tname3,
           width:600,
           buttons: Ext.MessageBox.OKCANCEL,
           multiline: true,
           fn: showResultText,
	   //animEl: tname
        });*/
}



var important;
function showResultText(text){
       	important = text;
	final();	
};



function final(){
	if(important==''){
		imptarg.textContent = tname3;
	}
	else{
		imptarg.textContent = important;
	}
	submitValues();	
}


function submitValues(){
createRequest();
//var url = "testing.inc?msgid=" + escape(tname3) + "?msgstr=" + escape(important);
//var url = "index.php?stream=locale";
var url = "index.php?mod=admin&stream=locale";
request.open("POST", url, true);
//request.open("GET", url, true);
request.onreadystatechange = requestSuccess;
request.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
request.send("msgid="+tname3+"&msgstr="+important+"&request="+'third');
//request.send(null);
}
