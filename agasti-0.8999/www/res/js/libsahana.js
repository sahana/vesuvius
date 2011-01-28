/**
 * SAHANA javascript library
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author      J P Fonseka <jo@opensource.lk>
 * @copyright   Lanka Software Foundation - http://www.opensource.lk
 */

//incident changing functions
var req;
function changeIncident(ivalue)
 {
     if (window.XMLHttpRequest)
     {
         req = new XMLHttpRequest();
     }
     else if (window.ActiveXObject)
     {
         req = new ActiveXObject("Microsoft.XMLHTTP");
     }
     if(req)
     {
 	 req.onreadystatechange = changed;
         req.open('GET', 'index.php?mod=pref&act=ims_set_incident&stream=text&incident_id='+ivalue, true);
         req.setRequestHeader("content-type","application/x-www-form-urlencoded");
         req.send(' ');
         
     }
     else
     {
         alert('Your browser does not seem to support XMLHttpRequest.');
     }
 }

function changed(){
    var incident;
    if (req.readyState==4)
    {
    incident=req.responseText;
    var ni = document.getElementById('incident_change_id');
    if(ni==null){
    var ni = document.getElementById('content');
    var newdiv = document.createElement('div');
    var divIdName = 'confirmation message';
    newdiv.setAttribute('class',divIdName);
    newdiv.setAttribute('className',divIdName);
    newdiv.setAttribute('id','incident_change_id');
//    ni.appendChild(newdiv);
    ni.insertBefore(newdiv,ni.childNodes[0]);

    var newp=document.createElement('p');
    var emel=document.createElement('em');
    emel.innerHTML = 'Submission Successful';

    var newul=document.createElement('ul');
    var newli=document.createElement('li');
    newli.setAttribute('id','inci');
    newdiv.appendChild(newp);
    newp.appendChild(emel);
    newdiv.appendChild(newul);
    //newli.innerHTML = 'Incident was successfully changed to '+incident+'.';
    newul.appendChild(newli);
    }
    remove_loading();
    document.getElementById('inci').innerHTML = 'Incident was successfully changed to '+incident+'.';
    }
    else{
            loading('Changing the incident. Please wait......');
    }
        //alert('Incident was changed successfully.');
}
//create loading information
function loading(message){

   var load = document.getElementById('loading_div');
    if(load==null){
    var newdiv = document.createElement('div');
    newdiv.innerHTML = message;
    var loadId = 'loading_div';
    newdiv.setAttribute('id',loadId);
    newdiv.setAttribute('class','loading');
    newdiv.setAttribute('className','loading');
    var ni = document.getElementById('content');
    ni.insertBefore(newdiv,ni.childNodes[0]);
    }
    else{
    document.getElementById('loading_div').innerHTML=message;
    document.getElementById('loading_div').setAttribute('class','loading');
    document.getElementById('loading_div').setAttribute('className','loading');
    }
}
function remove_loading(){
    document.getElementById('loading_div').innerHTML='';
    document.getElementById('loading_div').setAttribute('class','');
    document.getElementById('loading_div').setAttribute('className','');
}
//functions related to tabs
var tabFieldSet=new Array();
var tabList=new Array();
var curTab;


function tabFieldset(id){
    var div,ul,root,li,legend;
    div=document.getElementById("tabPosition");
    ul=document.createElement("ul");
    root=document.getElementById(id);
    children=root.childNodes;
    ul.id="tab";
    tabList=ul;
    div.appendChild(ul);
    for(var j=0,k=0;j<children.length;j++)
        if(children[j].nodeName.toLowerCase()=="fieldset"){
            tabFieldSet[k]=children[j];
            tabFieldSet[k].style.display = 'none';
            li=document.createElement('li');
            legend=tabFieldSet[k].getElementsByTagName("legend").item(0);
            li.innerHTML="<a href='#' onclick='changeTab("+k+");'>"+legend.innerHTML+"</a>";
            tabFieldSet[k].removeChild(legend);
            ul.appendChild(li);
            tabList[k++]=li;
        }
    for(var i=0;i<tabFieldSet.length;i++)
        div.appendChild(tabFieldSet[i]);
    curTab=0;
    changeTab(0);
}

function changeTab(n){
    tabFieldSet[curTab].style.display='none';
    tabList[curTab].id='';
    curTab=n;
    tabFieldSet[curTab].style.display='block';
    tabList[curTab].id='activeTab';
}

function toggle_visibility(id){
    var el=document.getElementById(id).style;
    if(el.display=='block'){
	el.display='none';
    } 
    else{
        el.display='block';
    }
}

function ie_hack_for_large_tables(){

	var browser_name=navigator.appName;
	var agent = navigator.userAgent;
	if ((browser_name=="Microsoft Internet Explorer") && ( 7 == getIEVersion(agent))){
		resize_wrapper_ie7();
	}
	if ((browser_name=="Microsoft Internet Explorer") && ( 6 == getIEVersion(agent) )){
		resize_wrapper();
	}
}


function getIEVersion(versionString){
	return parseFloat(versionString.substr(30,3));
}

function resize_wrapper(){
       	var result=document.getElementById('result');
	var content=document.getElementById('content');
       	var wrapper=document.getElementById('wrapper');
	
       	if(result){ 
       		if(document.documentElement.clientWidth < document.body.clientWidth)
       			wrapper.style.width=(document.body.clientWidth+3)+"px";
       	}
       	if(content){
       		if(document.documentElement.clientWidth < document.body.clientWidth)
       			wrapper.style.width=(document.body.clientWidth+3)+"px";
       	}
}

function resize_wrapper_ie7(){
   var table = null;   
   var map = document.getElementById('map');
	var wrapper = document.getElementById('wrapper');
	
	 if ( document.getElementById('result') ) {
			table = document.getElementById('result').getElementsByTagName('table')[0];
	 } 

	if(table != null){
		if((document.documentElement.clientWidth) > (document.body.clientWidth -205)){
			wrapper.style.width=(document.documentElement.clientWidth+210)+"px";
		}
	}
       	if(map != null){
		if((document.documentElement.clientWidth) > (document.body.clientWidth -205)){
			wrapper.style.width=(document.documentElement.clientWidth+210)+"px";}
	}
}

