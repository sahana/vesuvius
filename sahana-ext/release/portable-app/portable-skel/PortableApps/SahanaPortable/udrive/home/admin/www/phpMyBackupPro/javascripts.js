<script type="text/javascript">
/*
 +--------------------------------------------------------------------------+
 | phpMyBackupPro                                                           |
 +--------------------------------------------------------------------------+
 | Copyright (c) 2004-2006 by Dirk Randhahn                                 |                               
 | http://www.phpMyBackupPro.net                                            |
 | Version information can be found in definitions.php.                     |
 |                                                                          |
 | This program is free software; you can redistribute it and/or            |
 | modify it under the terms of the GNU General Public License              |
 | as published by the Free Software Foundation; either version 2           |
 | of the License, or (at your option) any later version.                   |
 |                                                                          |
 | This program is distributed in the hope that it will be useful,          |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of           |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            |
 | GNU General Public License for more details.                             |
 |                                                                          |
 | You should have received a copy of the GNU General Public License        |
 | along with this program; if not, write to the Free Software              |
 | Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,USA.|
 +--------------------------------------------------------------------------+
*/

// pops up a window showing the file 'path', having 'title' as window title
function popUp(path,title,confirmation,question) {
    var popwin;
	var input=true;
	if (confirmation) input=confirm(question);
	if (input) {
	    if (title!="view") {
	        // small window
	        leftval=(screen.width)?(screen.width-400)/2:100;
	        topval=(screen.height)?(screen.height-500)/2:100;
	        popwin=window.open(path, title, "width=400,height=500,top=" + topval + ",left=" + leftval + ",toolbar=0,scrollbars=1,directories=no,location=0,statusbar=0,menubar=0,resizable=0");
	    } else {
	        // big window
	        leftval=(screen.width)?(screen.width-750)/2:100;
	        topval=(screen.height)?(screen.height-750)/2:100;
	        popwin=window.open(path, title, "width=750,height=750,top=" + topval + ",left=" + leftval + ",toolbar=0,scrollbars=1,directories=no,location=0,statusbar=0,menubar=0,resizable=1");
	    }
	    popwin.focus();
	}
}

// selects all entries in the selectbox 'select_name' in the form 'form_name'
function setSelect(form_name, select_name) {
    var select_field=document.forms[form_name].elements[select_name];
    for (var i=0; i < select_field.length; i++) select_field.options[i].selected=true;
    return true;
}

// opens a dialog box with 'title' as title
// when user clicks ok, he will be forwarded to file 'path'
function confirmClick(title,path) {
    var input=confirm(title);
    if (input) window.location.href=path;
}

// changes the color of table row 'tr'
function changeColor(row, new_color) {
    var cells=null;
    var i=null;

    // go sure that row is available
    if (typeof(row.style)=='undefined') return false;

    // trie to get all fields of current row
    if (typeof(document.getElementsByTagName)!='undefined') {
        cells=row.getElementsByTagName('td');
    } else if (typeof(row.cells)!='undefined') {
        cells=row.cells;
    } else {
        return false;
    }

    // change border color
    if (typeof(cells[0].style.setAttribute)!='undefined') {
    for (i=0; i<cells.length; i++) cells[i].style.setAttribute('borderColor',new_color,false);
    } else  if (typeof(cells[0].style.borderColor)!='undefined') {
        for (i=0; i<cells.length; i++) cells[i].style.borderColor=new_color;
    } else {
        return false;
    }
    return true;
} 

// changes the visibility attribute of an element to visible
function showElement(id)
{
  var element = document.getElementById(id);
    element.style.display = 'block';
}

// show ff add on internet explorers
window.onload = function() {	
	if(document.defaultCharset) showElement('ffadd');
}

</script>
