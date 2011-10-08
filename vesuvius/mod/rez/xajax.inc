<?
/**
 * @name         Resources
 * @version      1.5
 * @package      rez
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.1004
 */


global $global;
require_once($global['approot'].'/mod/lpf/lib_lpf.inc');

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
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
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

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// NORMAL PAGES
	//
	$htmlMain .= "<table class=\"mainTable\"><tr><td style=\"padding-left: 8px; width: 50px; text-align: center;\" ><b>Page #</b></td><td style=\"padding-left: 8px;\" ><b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Menu/Page Title</b></td><td style=\"text-align: center;\" ><b>Visibility</b></td><td style=\"text-align: center;\" ><b>Edit</b></td><td style=\"text-align: center;\" ><b>Delete</b></td><td style=\"text-align: center;\"><b>Move</b></td></tr>";

	$q = "
		select rez_page_id, rez_menu_title, rez_menu_order, rez_visibility, rez_timestamp
		from rez_pages
		where rez_page_id > -1
		order by rez_menu_order asc;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez show pages"); }

	$pages = array();
	$count = 0;

	// find out how many pages we have so we can later build our pages table
	while($row = $result->FetchRow() ){
		$pages[$count] = $row;
		$count++;
	}

	// build pages Table
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
		$int = ($visibility == 'INTERNAL') ? "<b>INTERNAL</b> " : "";
		$htmlMain .= "<tr><td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$page_id."</td><td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"#\" onclick=\"rez_perform_edit(".$page_id.");\">".$int.$menu_title."</a></td><td style=\"text-align: center;\" class=\"".$evenOddClass."\"><b><select name=\"visibility\" onchange=\"javascript: rez_perform_change_visibility(".$page_id.", this.value);\"><option value=\"Public\" ".(($visibility == 'Public')?'SELECTED':'').">Public<option value=\"Hidden\" ".(($visibility == 'Hidden')?'SELECTED':'').">Hidden<option value=\"INTERNAL\" ".(($visibility == 'INTERNAL')?'SELECTED':'').">INTERNAL</select></b></td>";

		$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"rez_perform_edit(".$page_id.");\" value=\"Edit\"></td>";

		$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"rez_append_log('Deleting Page ".$page_id." ...<br>'); setTimeout('rez_perform_delete(".$page_id.",confirm(\'Are you sure you want to delete this page?\'));', 100);\" value=\"Delete\"></td>";

		// if its the first and only item, no move up/down controls
		if (($i == 1) && ($count == 1)) {
			$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\">-</td>";

		// if its the first item and there are more, show down control
		} elseif (($i == 1) && ($count > 1)) {
			$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"rez_perform_move_down(".$page_id.");\" value=\"⇩\"></td>";

		// if its the last item, only show up control
		} elseif ($i == $count) {
			$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"rez_perform_move_up(".$page_id.");\" value=\"⇧\"></td>";

		// its a normal item, show up and down controls
		} else {
			$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"rez_perform_move_up(".$page_id.");\" value=\"⇧\"> <input class=\"styleTehButton\" type=\"button\" onclick=\"rez_perform_move_down(".$page_id.");\" value=\"⇩\"></td>";
		}
		$htmlMain .= "</tr>";
		$i++;
		$eo++;
		$eo %= 2;
	}
	if ($count == 0) {
		$htmlMain .= "<tr><td colspan=7 class=\"mainRowEven\" style=\"text-align: center;\">No Pages have been created.</td></tr>";
	}
	$htmlMain .= "</table>";
	//
	// END NORMAL PAGES
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// SYSTEM PAGES
	//
	$htmlMain .= "<br><h2>System Pages</h2><table class=\"mainTable\"><tr><td style=\"padding-left: 8px; width: 50px; text-align: center;\" ><b>Page #</b></td><td style=\"padding-left: 8px;\" ><b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Menu/Page Title</b></td><td style=\"text-align: center;\" ><b>Edit</b></td></tr>";

	$q = "
		select rez_page_id, rez_menu_title, rez_menu_order, rez_visibility, rez_timestamp
		from rez_pages
		where rez_page_id < 0
		order by rez_page_id desc;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez system pages"); }

	$pages = array();
	$count = 0;

	// find out how many pages we have so we can later build our pages table
	while($row = $result->FetchRow() ){
		$pages[$count] = $row;
		$count++;
	}

	// build system pages Table
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
		$htmlMain .= "<tr><td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".abs($page_id)."</td><td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"#\" onclick=\"rez_perform_edit(".$page_id.");\">".$menu_title."</a></td>";

		$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"rez_perform_edit(".$page_id.");\" value=\"Edit\"></td>";

		$i++;
		$eo++;
		$eo %= 2;
	}
	if ($count == 0) {
		$htmlMain .= "<tr><td colspan=7 class=\"mainRowEven\" style=\"text-align: center;\">No Pages have been created.</td></tr>";
	}
	$htmlMain .= "</table>";
	//
	// END SYSTEM PAGES
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	$pageControlHtml = '<input class="styleTehButton" type="button" onclick="javascript: rez_append_log(\'Creating a new page...<br>\'); rez_perform_edit(0);" value="Create a new Page">'; // <input class="controlButton" type="button" onclick="javascript: rez_append_log(\'Showing Help...<br>\'); rez_show_help();" value="Help">';

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
	$q = "
		UPDATE rez_pages
		set rez_visibility = '".$value."'
		where `rez_page_id` = ".$page_id." ;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez update visibility"); }

	$global['xajax_res']->addAppend('rezLog','innerHTML','Changed visibility of page <b>#'.$page_id.'</b> to <b>'.$value.'</b>.<br>');
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}



// move page_id down on page in the menu order
function rez_perform_move_down($page_id) {
	global $global;

	// find the menu_order for $page_id
	$q = "
		SELECT rez_menu_order
		from rez_pages
		where rez_page_id = '".$page_id."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move down 1"); }
	$row = $result->FetchRow();
	$pageMenuOrder = $row['rez_menu_order'];

	// find the menu_order for the page below $page_id we are going to swap it with
	$q = "
		SELECT *
		from rez_pages
		where rez_menu_order > '".$pageMenuOrder."'
		order by rez_menu_order asc
		limit 1;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move down 2"); }
	$row2 = $result->FetchRow();
	$nextMenuOrder = $row2['rez_menu_order'];
	$nextPageID = $row2['rez_page_id'];

	// update page_id with new menu order
	$q = "
		UPDATE rez_pages
		set rez_menu_order = '".$nextMenuOrder."'
		where `rez_page_id` = ".$page_id." ;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move down 3"); }

	// update next page with page_id's menu order
	$q = "
		UPDATE rez_pages
		set rez_menu_order = '".$pageMenuOrder."'
		where `rez_page_id` = ".$nextPageID." ;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move down 4"); }

	$global['xajax_res']->addAppend('rezLog','innerHTML','Moved page #'.$page_id.' down.<br>');
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	$global['xajax_res']->addAssign('rezMain','innerHTML',rez_show_pages(TRUE));
	return $global['xajax_res']->getXML();
}



// move page_id up on page in the menu order
function rez_perform_move_up($page_id) {
	global $global;

	// find the menu_order for $page_id
	$q = "
		SELECT rez_menu_order
		from rez_pages
		where rez_page_id = '".$page_id."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move up 1"); }
	$row = $result->FetchRow();
	$pageMenuOrder = $row['rez_menu_order'];

	// find the menu_order for the page above $page_id we are going to swap it with
	$q = "
		SELECT *
		from rez_pages
		where rez_menu_order < '".$pageMenuOrder."'
		order by rez_menu_order desc
		limit 1;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move up 2"); }
	$row2 = $result->FetchRow();
	$previousMenuOrder = $row2['rez_menu_order'];
	$previousPageID = $row2['rez_page_id'];

	// update page_id with new menu order
	$q = "
		UPDATE rez_pages
		set rez_menu_order = '".$previousMenuOrder."'
		where `rez_page_id` = ".$page_id." ;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move up 3"); }

	// update previous page with page_id's menu order
	$q = "
		UPDATE rez_pages
		set rez_menu_order = '".$pageMenuOrder."'
		where `rez_page_id` = ".$previousPageID." ;
	";
	$res = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move up 4"); }

	$global['xajax_res']->addAppend('rezLog','innerHTML','Moved page #'.$page_id.' up.<br>');
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	$global['xajax_res']->addAssign('rezMain','innerHTML',rez_show_pages(TRUE));
	return $global['xajax_res']->getXML();
}



// create a new page with default content and return its new page_id
function rez_perform_new() {
	global $global;

	// find last menu order #, +1
	$q = "
		SELECT *
		from rez_pages
		order by rez_menu_order desc;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez new 1"); }
	$row = $result->FetchRow();
	$mID = isset($row['rez_menu_order']) ? $row['rez_menu_order'] : 0;
	$mID++;

	// insert a new page
	$q = "
		INSERT INTO rez_pages (rez_menu_title,rez_page_title,rez_menu_order,rez_content,rez_description,rez_timestamp,rez_visibility)
		VALUES ('new page', 'new page', '".$mID."','new page content', 'new page description', '".date('Y-m-d H:i:s')."', 'Hidden');
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez new 2"); }

	// find id of newest page we just created
	$q = "
		SELECT *
		from rez_pages
		order by rez_page_id desc;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez new 3"); }
	$row3 = $result->FetchRow();

	return $row3['rez_page_id'];
}



// saves the edit's page content/attributes to the database
function rez_perform_save($page_id, $r) {
	global $global;

	// update table data
	$q = "
		update rez_pages
		set rez_menu_title = '".mysql_escape_string($r['menuTitle'])."', rez_content = '".mysql_escape_string($r['pageContent'])."', rez_timestamp = '".date('Y-m-d H:i:s')."' where `rez_page_id` = ".$page_id." ;
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez save"); }

	// update log to reflect the save
	$global['xajax_res']->addAppend('rezLog','innerHTML',"Page #".$page_id." <span style=\"color: green;\">Saved</span>.<b><br>");
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}


// presents a gui to edit a page and its corresponding fields
function rez_perform_edit($page_id) {
	global $global;

	// if page_id = 0, must create a new page then continue to edit it
	if($page_id == 0) {
		$page_id = rez_perform_new();
	}

	// get page info
	$q = "
		select *
		from rez_pages
		where rez_page_id = '".$page_id."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez edit 1"); }
	$row = $result->FetchRow();

	if((int)$row['rez_page_id'] < 0) {
		$sistim = "SYSTEM";
	} else {
		$sistim = "";
	}
	$pageIdText = $sistim." ". abs($row['rez_page_id']);

	$editMainHtml =
"<form id=\"editPageForm\" name=\"editPageForm\">
<table class=\"mainTable\">
<tr><td class=\"mainRowOdd\" style=\"text-align: center; text-weight: bold;\">Page #</td><td class=\"mainRowOdd\"> &nbsp; <b>".$pageIdText."</b></td></tr>
<tr><td class=\"mainRowEven\" style=\"text-align: center; text-weight: bold;\">Menu/Page Title</td><td class=\"mainRowEven\"><input name=\"menuTitle\" type=\"text\" id=\"menuTitle\" value=\"".$row['rez_menu_title']."\" onchange=\"window.rezPageSaved = false;\" size=\"64\" /></td></tr>
<tr><td class=\"mainRowEOdd\" style=\"text-align: center; text-weight: bold;\">Last Modified</td><td class=\"mainRowOdd\"> &nbsp; ".$row['rez_timestamp']."</td></tr>
</table>
<div class=\"wysiwyg\"><textarea name=\"pageContent\" onchange=\"window.rezPageSaved = false;\" id=\"pageContent\" style=\"height: 300px; width: 100%;\">".$row['rez_content']."</textarea></div>
</form>";

	$editControlHtml = '
		<input class="styleTehButton" type="button" onclick="javascript:  window.rezPageSaved = true; if(nicEditors.editors.length>0){nicEditors.findEditor(\'pageContent\').saveContent();} rez_perform_save('.$page_id.', xajax.getFormValues(\'editPageForm\'));" value="Save and Publish Changes">
		<input class="styleTehButton" type="button" onclick="checkSaved()" value="Close Editor">
		&nbsp; &nbsp; &nbsp; <span class="toggle">View editor as:
		<input id="wysiwyg" class="styleTehButton" type="button" onclick="javascript: document.getElementById(\'wysiwyg\').disabled = true; document.getElementById(\'htmlcode\').disabled = false; area2 = new nicEditor({fullPanel : true}).panelInstance(\'pageContent\');" value="WYSIWYG">
		<input id="htmlcode" class="styleTehButton" type="button" onclick="javascript: area2.removeInstance(\'pageContent\'); document.getElementById(\'wysiwyg\').disabled = false; document.getElementById(\'htmlcode\').disabled = true; nicEditors.editors = []; " value="HTML"></span>';

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

	if($confirm == "true") {

		//---- delete the page from db table
		$q = "
			delete from rez_pages
			where rez_page_id = '".$page_id."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez delete 1"); }

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


