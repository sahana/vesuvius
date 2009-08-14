<?php
/**
 * modRez xajax library
 *
 * @package	module
 * @subpackage	rez
 * @author 	Greg Miernicki
 * @copyright	www.nlm.nih.gov
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

global $global;

// create an array as it does not exist previosuly and will make warnings
$global['xajax_functions'] = array(); 

// publicly register accessible xajax funtions
array_push($global['xajax_functions'],'rez_append_log');
array_push($global['xajax_functions'],'rez_prepend_log');
array_push($global['xajax_functions'],'rez_show_message');
array_push($global['xajax_functions'],'rez_show_pages');
array_push($global['xajax_functions'],'rez_show_help');
array_push($global['xajax_functions'],'rez_perform_edit');
array_push($global['xajax_functions'],'rez_perform_delete');
array_push($global['xajax_functions'],'rez_perform_insert');
array_push($global['xajax_functions'],'rez_perform_save');
array_push($global['xajax_functions'],'rez_perform_move_up');
array_push($global['xajax_functions'],'rez_perform_move_down');
array_push($global['xajax_functions'],'rez_perform_change_visibility');

// adds a message to the log div @ tail
function rez_append_log($message = "no message specified?") {
	global $global;
	$global['xajax_res']->addAppend('rezLog','innerHTML',$message);
	//---- scroll the log to the bottom
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'logArea\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}


// adds a message to the log div @ head
function rez_prepend_log($message = "no message specified?") {
	global $global;
	$global['xajax_res']->addPrepend('rezLog','innerHTML',$message);
	return $global['xajax_res']->getXML();
}


// shows a status message before another ajax function is executed
function rez_show_message($message = "no message specified?") {
	global $global;
	$global['xajax_res']->addAssign('rezMain','innerHTML','<div class="loadingMessage"><center><blink>'.$message.'</blink></center></div>');
	return $global['xajax_res']->getXML();
}


// reloads the mainArea div with information of what pages we have
function rez_show_pages($internal = FALSE) {
	global $conf;
	global $global;
	$htmlLog = "";
	$htmlMain = "";

	$htmlMain .= "<table class=\"mainTable\"><tr><td style=\"padding-left: 8px; width: 40px; text-align: center;\" ><b>Page #</b></td><td style=\"padding-left: 8px;\" ><b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Menu Title</b></td><td style=\"text-align: center;\" ><b>Visibility</b></td><td style=\"text-align: center;\" ><b>Edit</b></td><td style=\"text-align: center;\" ><b>Clone</b></td><td style=\"text-align: center;\" ><b>Delete</b></td><td style=\"text-align: center;\"><b>Move</b></td><td style=\"padding-left: 8px; width: 40px; text-align: center; width: 15em;\" ><b>Last Modified</b></td></tr>";

	// get pages info
	$q = "select rez_page_id, rez_menu_title, rez_menu_order, rez_visibility, rez_timestamp from rez_pages order by rez_menu_order asc;";
	$res = $global['db']->Execute($q);

	$pages = array();
	$count = 0;

	// find out how many pages we have so we can later build our pages table
	while($row = $res->FetchRow() ){
		$pages[$count] = $row;
		$count++;
	}

	// build pages Table
	$burl = "<img src=\"theme/".$conf['theme']."/img/"; // base URL for images, (it chooses the /www/theme/THEME_NAME/img/ folder)
	$i = 1;
	$eo = 0;
	while($i <= $count) {
		$row = $pages[$i-1];
		$page_id    = $row['rez_page_id'];
		$menu_title = $row['rez_menu_title'];
		$menu_order = $row['rez_menu_order'];
		$visibility = $row['rez_visibility'];
		$timestamp  = $row['rez_timestamp'];
		if ( $eo == 0 ) {
			$evenOddClass = "mainRowEven";
		} else {
			$evenOddClass = "mainRowOdd";
		}
		$htmlMain .= "<tr><td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$page_id."</td><td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;".$menu_title."</td><td style=\"text-align: center; width: 100px;\" class=\"".$evenOddClass."\"><b><select name=\"visibility\" onchange=\"javascript: rez_perform_change_visibility(".$page_id.", this.value);\"><option value=\"Public\" ".(($visibility == 'Public')?'SELECTED':'').">Public<option value=\"Hidden\" ".(($visibility == 'Hidden')?'SELECTED':'').">Hidden<option value=\"External Page\" ".(($visibility == 'External Page')?'SELECTED':'').">External Page</select></b></td>";

		$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><a onclick=\"javascript: rez_perform_edit(".$page_id.");\">".$burl."edit24.png\" alt=\"Edit\">"."</a></td>";

		$negPageID = $page_id * -1;
		$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><a onclick=\"javascript: rez_append_log('Cloning Page ".$page_id." ...<br>'); rez_perform_edit(".$negPageID.");\">".$burl."clone24.png\" alt=\"Clone\">"."</a></td>";

		$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><a onclick=\"javascript: rez_append_log('Deleting Page ".$page_id." ...<br>'); setTimeout('rez_perform_delete(".$page_id.",confirm(\'Are you sure you want to delete this page?\'));', 100);\">".$burl."delete24.png\" alt=\"Delete\">"."</a></td>";

		// if its the first and only item, no move up/down controls
		if (($i == 1) && ($count == 1)) {
			$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\">-</td>";

		// if its the first item and there are more, show down control
		} elseif (($i == 1) && ($count > 1)) {
			$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><a onclick=\"javascript: rez_perform_move_down(".$page_id.");\">".$burl."down24.png\" alt=\"Down\">"."</a></td>";

		// if its the last item, only show up control
		} elseif ($i == $count) {
			$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><a onclick=\"javascript: rez_perform_move_up(".$page_id.");\">".$burl."up24.png\" alt=\"Up\">"."</a></td>";

		// its a normal item, show up and down controls
		} else {
			$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><a onclick=\"javascript: rez_perform_move_up(".$page_id.");\">".$burl."up24.png\" alt=\"Up\">"."</a> <a onclick=\"javascript: rez_perform_move_down(".$page_id.");\">".$burl."down24.png\" alt=\"Down\">"."</a></td>";
		}
		$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\">".$timestamp."</td></tr>";
		$i++;
		$eo++;
		$eo %= 2;
	}
	if ($count == 0) {
		$htmlMain .= "<tr><td colspan=7 class=\"mainRowEven\" style=\"text-align: center;\">No Pages have been created.</td></tr>";
	}
	$htmlMain .= "</table>";

	$pageControlHtml = '<input class="controlButton" type="button" onclick="javascript: rez_append_log(\'Creating a new page...<br>\'); rez_perform_edit(0);" value="Create a new Page">'; // <input class="controlButton" type="button" onclick="javascript: rez_append_log(\'Showing Help...<br>\'); rez_show_help();" value="Help">';

	//---- internally, no ajax, just pass back data
	if ( $internal ) {
		return $htmlMain;
	} else {
		$global['xajax_res']->addAssign('rezControl','style.opacity','1.0');
		$global['xajax_res']->addAssign('rezControl','innerHTML',$pageControlHtml);

		$global['xajax_res']->addAssign('rezMain','style.opacity','1.0');
		$global['xajax_res']->addAssign('rezMain','innerHTML',$htmlMain);

		$htmlLog .= "Found ".$count." page(s).<br>";
		$global['xajax_res']->addAppend('rezLog','innerHTML',$htmlLog);
		$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
		return $global['xajax_res']->getXML();
	}
}



// save a change in visibility for a certain page
function rez_perform_change_visibility($page_id, $value) {
	global $global;

	// update page's visibility
	$q = "UPDATE rez_pages set rez_visibility = '".$value."' where `rez_page_id` = ".$page_id." ;";
	$res = $global['db']->Execute($q);
	$global['xajax_res']->addAppend('rezLog','innerHTML','Changed visibility of page <b>#'.$page_id.'</b> to <b>'.$value.'</b>.<br>');
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}




// move page_id down on page in the menu order
function rez_perform_move_down($page_id) {
	global $global;

	// find the menu_order for $page_id
	$q = "SELECT rez_menu_order from rez_pages where rez_page_id = '".$page_id."';";
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	$pageMenuOrder = $row['rez_menu_order'];

	// find the menu_order for the page below $page_id we are going to swap it with
	$q2 = "SELECT * from rez_pages where rez_menu_order > '".$pageMenuOrder."' order by rez_menu_order asc limit 1;";
	$res2 = $global['db']->Execute($q2);
	$row2 = $res2->FetchRow();
	$nextMenuOrder = $row2['rez_menu_order'];
	$nextPageID = $row2['rez_page_id'];

	// update page_id with new menu order
	$q3 = "UPDATE rez_pages set rez_menu_order = '".$nextMenuOrder."' where `rez_page_id` = ".$page_id." ;";
	$res3 = $global['db']->Execute($q3);

	// update next page with page_id's menu order
	$q4 = "UPDATE rez_pages set rez_menu_order = '".$pageMenuOrder."' where `rez_page_id` = ".$nextPageID." ;";
	$res4 = $global['db']->Execute($q4);

	$global['xajax_res']->addAppend('rezLog','innerHTML','Moved page #'.$page_id.' down.<br>');
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	$global['xajax_res']->addAssign('rezMain','innerHTML',rez_show_pages(TRUE));
	return $global['xajax_res']->getXML();
}


// move page_id up on page in the menu order
function rez_perform_move_up($page_id) {
	global $global;

	// find the menu_order for $page_id
	$q = "SELECT rez_menu_order from rez_pages where rez_page_id = '".$page_id."';";
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	$pageMenuOrder = $row['rez_menu_order'];

	// find the menu_order for the page above $page_id we are going to swap it with
	$q2 = "SELECT * from rez_pages where rez_menu_order < '".$pageMenuOrder."' order by rez_menu_order desc limit 1;";
	$res2 = $global['db']->Execute($q2);
	$row2 = $res2->FetchRow();
	$previousMenuOrder = $row2['rez_menu_order'];
	$previousPageID = $row2['rez_page_id'];

	// update page_id with new menu order
	$q3 = "UPDATE rez_pages set rez_menu_order = '".$previousMenuOrder."' where `rez_page_id` = ".$page_id." ;";
	$res3 = $global['db']->Execute($q3);

	// update previous page with page_id's menu order
	$q4 = "UPDATE rez_pages set rez_menu_order = '".$pageMenuOrder."' where `rez_page_id` = ".$previousPageID." ;";
	$res4 = $global['db']->Execute($q4);

	$global['xajax_res']->addAppend('rezLog','innerHTML','Moved page #'.$page_id.' up.<br>');
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	$global['xajax_res']->addAssign('rezMain','innerHTML',rez_show_pages(TRUE));
	return $global['xajax_res']->getXML();
}


// create a new page with the contents of another page and return its new page_id
function rez_perform_clone($page_id) {
	global $global;

	// find last menu order #, +1
	$q = "SELECT * from rez_pages order by rez_menu_order desc;";
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	$mID = $row['rez_menu_order'];
	$mID++;

	// get cloned page data
	$q2 = "SELECT * from rez_pages where rez_page_id = '".$page_id."' ;";
	$res2 = $global['db']->Execute($q2);
	$row2 = $res2->FetchRow();

	// insert a new page
	$q3 = "INSERT INTO rez_pages (rez_menu_title,rez_page_title,rez_menu_order,rez_content,rez_description,rez_timestamp,rez_visibility) VALUES ('".$row2['rez_menu_title']."', '".$row2['rez_page_title']."', '".$mID."','".$row2['rez_content']."', '".$row2['rez_description']."', '".date('Y-m-d H:i:s')."', 'Hidden');";
	$res3 = $global['db']->Execute($q3);

	// find id of newest page we just created
	$q4 = "SELECT * from rez_pages order by rez_page_id desc;";
	$res4 = $global['db']->Execute($q4);
	$row4 = $res4->FetchRow();
	return $row4['rez_page_id'];
}


// create a new page with default content and return its new page_id
function rez_perform_new() {
	global $global;

	// find last menu order #, +1
	$q = "SELECT * from rez_pages order by rez_menu_order desc;";
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();
	$mID = isset($row['rez_menu_order']) ? $row['rez_menu_order'] : 0;
	$mID++;

	// insert a new page
	$q2 = "INSERT INTO rez_pages (rez_menu_title,rez_page_title,rez_menu_order,rez_content,rez_description,rez_timestamp,rez_visibility) VALUES ('new page', 'new page', '".$mID."','new page content', 'new page description', '".date('Y-m-d H:i:s')."', 'Hidden');";
	$res2 = $global['db']->Execute($q2);

	// find id of newest page we just created
	$q3 = "SELECT * from rez_pages order by rez_page_id desc;";
	$res3 = $global['db']->Execute($q3);
	$row3 = $res3->FetchRow();
	return $row3['rez_page_id'];
}


// saves the edit's page content/attributes to the database
function rez_perform_save($page_id, $r) {
	global $global;

	// update table data
	$q = "update rez_pages set rez_menu_title = '".mysql_escape_string($r['menuTitle'])."', rez_page_title = '".mysql_escape_string($r['pageTitle'])."', rez_content = '".mysql_escape_string($r['pageContent'])."', rez_description = '".mysql_escape_string($r['pageDescription'])."', rez_timestamp = '".date('Y-m-d H:i:s')."' where `rez_page_id` = ".$page_id." ;";
	$res = $global['db']->Execute($q);

	// update log to reflect the save
	$global['xajax_res']->addAppend('rezLog','innerHTML',"Page #".$page_id." <span style=\"color: green;\">Saved</span>.<b><br>");
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}


// presents a gui to edit a page and its corresponding fields
function rez_perform_edit($page_id) {
	global $global;

	// if page_id = 0, must create a new page then continue to edit it
	if ($page_id == 0) {
		$page_id = rez_perform_new();

	// if page_id < 0 then this |page_id| is the page_id to clone ~ encoding 2 data items in 1 :)
	} elseif ($page_id < 0) {
		$page_id = rez_perform_clone(abs($page_id));
	}

	// get page info
	$q = "select * from rez_pages where rez_page_id = '".$page_id."';";
	$res = $global['db']->Execute($q);
	$row = $res->FetchRow();

	$editMainHtml =
"<form id=\"editPageForm\" name=\"editPageForm\">
<table class=\"mainTable\"><tr><td class=\"mainRowOdd\" style=\"text-align: center; text-weight: bold;\">Menu Title</td><td class=\"mainRowOdd\"><input name=\"menuTitle\" type=\"text\" id=\"menuTitle\" value=\"".$row['rez_menu_title']."\" size=\"64\" /></td></tr>
<tr><td class=\"mainRowEven\" style=\"text-align: center; text-weight: bold;\">Page Title</td><td class=\"mainRowEven\"><input name=\"pageTitle\" type=\"text\" id=\"pageTitle\" value=\"".$row['rez_page_title']."\" size=\"64\" /></td></tr>
<tr><td class=\"mainRowOdd\" style=\"text-align: center; text-weight: bold;\">Page Description</td><td class=\"mainRowOdd\"><input name=\"pageDescription\" type=\"text\" id=\"pageDescription\" value=\"".$row['rez_description']."\" size=\"64\" /></td></tr></table>
<div style=\"background-color: #fff;\"><textarea name=\"pageContent\" id=\"pageContent\" style=\"height: 300px; width: 100%;\">".$row['rez_content']."</textarea></div>
</form>";

	$editControlHtml = '
		<input class="controlButton" type="button" onclick="javascript:  if (nicEditors.editors.length>0){nicEditors.findEditor(\'pageContent\').saveContent();} rez_perform_save('.$page_id.', xajax.getFormValues(\'editPageForm\'));" value="Save/Publish">
		<input class="controlButton" type="button" onclick="javascript: rez_append_log(\'Closing editor...<br>\');  area2.removeInstance(\'pageContent\'); setTimeout(\'rez_show_pages();\', 500);" value="Close">
		<span class="toggle">View as:
		<input id="wysiwyg" class="controlButton" type="button" onclick="javascript: document.getElementById(\'wysiwyg\').disabled = true; document.getElementById(\'htmlcode\').disabled = false; area2 = new nicEditor({fullPanel : true}).panelInstance(\'pageContent\');" value="WYSIWYG">
		<input id="htmlcode" class="controlButton" type="button" onclick="javascript: area2.removeInstance(\'pageContent\'); document.getElementById(\'wysiwyg\').disabled = false; document.getElementById(\'htmlcode\').disabled = true; nicEditors.editors = []; " value="HTML"></span>';

	$global['xajax_res']->addAssign('rezMain','style.opacity','1.0');
	$global['xajax_res']->addAssign('rezMain','innerHTML',$editMainHtml);

	$global['xajax_res']->addAssign('rezControl','style.opacity','1.0');
	$global['xajax_res']->addAssign('rezControl','innerHTML',$editControlHtml);

	$global['xajax_res']->addScript('area2 = new nicEditor({fullPanel : true}).panelInstance(\'pageContent\'); document.getElementById(\'wysiwyg\').disabled = true;');

	return $global['xajax_res']->getXML();
}


// delete a page
function rez_perform_delete($page_id, $confirm) {
	global $global;

	if ($confirm == "true") {
		//---- delete the page from db table
		$q = "delete from rez_pages where rez_page_id = '".$page_id."';";
		$res = $global['db']->Execute($q);
		$global['xajax_res']->addAppend('rezLog','innerHTML',"Page <b>#".$page_id."</b> deleted.<br>");
	} else {
		$global['xajax_res']->addAppend('rezLog','innerHTML',"Delete operation aborted.<br>");
	}

	//---- update UI
	$global['xajax_res']->addAssign('rezControl','style.opacity','1.0');
	$global['xajax_res']->addAssign('rezMain','innerHTML',rez_show_pages(TRUE));
	$global['xajax_res']->addAssign('rezMain','style.opacity','1.0');
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}


// presents a gui to edit a page and its corresponding fields
function rez_show_help() {
	global $global;

	$editControlHtml = '<input class="controlButton" type="button" onclick="javascript: rez_append_log(\'Closing help...<br>\'); setTimeout(\'rez_show_pages();\', 250);" value="Close Help">';

	$global['xajax_res']->addAssign('rezMain','style.opacity','1.0');
	$global['xajax_res']->addAssign('rezMain','innerHTML',$editMainHtml);

	$global['xajax_res']->addAssign('rezControl','style.opacity','1.0');
	$global['xajax_res']->addAssign('rezControl','innerHTML',$editControlHtml);

	return $global['xajax_res']->getXML();
}
