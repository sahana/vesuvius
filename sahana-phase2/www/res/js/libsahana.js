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
            tabList[k]=li;
            root.removeChild(tabFieldSet[k]);
            div.appendChild(tabFieldSet[k++]);
        }
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