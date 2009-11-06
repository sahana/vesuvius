/**
 * synchronization module javascript library 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage sync
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * This function will check to see the sahana server exist
 */
function connect(server_url){
    //get the url
   // var server_url=document.getElementById("server_url").value;
    //print inner html
    var console=document.getElementById("console");
    var html="<h2>Add Sahana Server</h2><center><b>"+server_url+"</b><br /><img src='res/img/sahana_server.png' /><br /><div id='status'><img src='res/img/wait.gif' />Connecting.... </div></center>";
    console.innerHTML=html;
    xajax__shn_server_ajax_connect(server_url);
    //call the server
}

function selectAll(el,arr){
    var child=document.getElementsByName(arr);
    var st=false;
    if(el.checked == true)
        st=true;
    else
        st=false;
    for (var i=0;i<child.length;i++){
    child[i].checked=st;
    }
}

function checkHead(hname){
    var he=document.getElementById(hname);
    var arr=hname+"[]";
    var child=document.getElementsByName(arr);
    var st=true;
    for (var i=0;i<child.length;i++){
     if(child[i].checked==false){
      st=false;
      break;
     }
    }
    he.checked=st;
}

function check(st){
    var box=document.getElementsByTagName('input');
    for(var i=0;i<box.length;i++){
        if(box[i].type=='checkbox')
            box[i].checked=st;
    }
}

function expandblock(id){
    var el=document.getElementById(id);
    if(el.style.display=='block')
        el.style.display='none';
    else
        el.style.display='block';
}