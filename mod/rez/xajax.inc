<?
/**
 * @name         Resources
 * @version      16
 * @package      rez
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0213
 */

global $global;
require_once($global['approot'].'/mod/lpf/lib_lpf.inc');
require_once($global['approot'].'/mod/rez/handler_locale.inc');

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
array_push($global['xajax_functions'],'rez_perform_translate');
array_push($global['xajax_functions'],'rez_perform_insert');
array_push($global['xajax_functions'],'rez_perform_save');
array_push($global['xajax_functions'],'rez_perform_move_up');
array_push($global['xajax_functions'],'rez_perform_move_down');
array_push($global['xajax_functions'],'rez_perform_change_visibility');
array_push($global['xajax_functions'],'rez_perform_change_locale');

//Initialize locale array
global $global;
//@TODO: This should be built on a query.
$global['rez_locales'] = array(
		'en_US' => 'English US',
		'fr' => 'French',
		'es' => 'Spanish' );

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
	$htmlMain .= "<table class=\"mainTable\"><tr><td style=\"padding-left: 8px; width: 50px; text-align: center;\" ><b>"._t("ResourcePages-Table-Header|Page #")."</b></td>"
	."<td style=\"padding-left: 8px;\" ><b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"._t("ResourcePages-Table-Header|Menu/Page Title")."</b></td>"
	."<td style=\"text-align: center;\" ><b>"._t("ResourcePages-Table-Header|Visibility")."</b></td>"
	."<td style=\"text-align: center;\" ><b>"._t("ResourcePages-Table-Header|Locale")."</b></td>"
	."<td style=\"text-align: center;\" ><b>"._t("ResourcePages-Table-Header|Edit")."</b></td>"
	."<td style=\"text-align: center;\" ><b>"._t("ResourcePages-Table-Header|Delete")."</b></td>"
	."<td style=\"text-align: center;\" ><b>"._t("ResourcePages-Table-Header|Translate")."</b></td>"
	."<td style=\"text-align: center;\"><b>"._t("ResourcePages-Table-Header|Move")."</b></td></tr>";

	$currentlocale = shn_rez_getlocale();
	$q = "
	select rez_page_id, rez_locale, rez_menu_title, rez_menu_order, rez_visibility, rez_timestamp
	from rez_pages
	where rez_page_id > -1
	order by rez_menu_order asc;
	";
	$result = $global['db']->Execute($q);
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez show pages");
	}

	$pages = array();
	$count = 0;

	// find out how many pages we have so we can later build our pages table
	while($row = $result->FetchRow() ){
		$pages[$count] = $row;
		$count++;
	}
	$rez_locales = $global['rez_locales'];
	// build pages Table
	$i = 1;
	$eo = 0;
	while($i <= $count) {
		$row = $pages[$i-1];
		$page_id    = $row['rez_page_id'];
		$page_locale= $row['rez_locale'];
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
		$htmlMain .= "<tr><td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$page_id."</td>"
		."<td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"#\" onclick=\"rez_perform_edit(".$page_id.",'".$page_locale."');\">".$int.$menu_title."</a></td>"
		."<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><b><select name=\"visibility\" onchange=\"javascript: rez_perform_change_visibility(".$page_id.", this.value);\"><option value=\"Public\" ".(($visibility == 'Public')?'SELECTED':'').">"._t("ResourcePages-Visibility-Select|Public")."<option value=\"Hidden\" ".(($visibility == 'Hidden')?'SELECTED':'').">"._t("ResourcePages-Visibility-Select|Hidden")."<option value=\"INTERNAL\" ".(($visibility == 'INTERNAL')?'SELECTED':'').">"._t("ResourcePages-Visibility-Select|INTERNAL")."</select></b></td>";

		$htmlMain .= "<td style=\"padding-left: 8px; text-align: center;\" class=\"".$evenOddClass."\">".$rez_locales[$page_locale]."</td>";
		$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"rez_perform_edit(".$page_id.",'".$page_locale."');\" value=\""._t("ResourcePages-Button|Edit")."\"></td>";

		$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"rez_append_log('Deleting Page ".$page_id." ...<br>'); setTimeout('rez_perform_delete(".$page_id.",\'".$page_locale."\',confirm(\'"._t("ResourcePages-Delete-Confirm|Are you sure you want to delete this page?")."\'));', 100);\" value=\""._t("ResourcePages-Button|Delete")."\"></td>";
		$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"rez_perform_translate(".$page_id.",'".$page_locale."');\" value=\""._t("ResourcePages-Button|Translate")."\"></td>";

		// if its the first and only item, no move up/down controls
		if (($i == 1) && ($count == 1)) {
			$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\">-</td>";

			// if its the first item and there are more, show down control
		} elseif (($i == 1) && ($count > 1)) {
			$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"rez_perform_move_down(".$page_id.");\" value=\"⇣\"></td>";

			// if its the last item, only show up control
		} elseif ($i == $count) {
			$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"rez_perform_move_up(".$page_id.");\" value=\"⇡\"></td>";

			// its a normal item, show up and down controls
		} else {
			$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"rez_perform_move_up(".$page_id.");\" value=\"⇡\"> <input class=\"styleTehButton\" type=\"button\" onclick=\"rez_perform_move_down(".$page_id.");\" value=\"⇣\"></td>";
		}
		$htmlMain .= "</tr>";
		$i++;
		$eo++;
		$eo %= 2;
	}
	if ($count == 0) {
		$htmlMain .= "<tr><td colspan=7 class=\"mainRowEven\" style=\"text-align: center;\">"._t("ResourcePages-Message|No Pages have been created.")."</td></tr>";
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
	$htmlMain .= "<br><h2>"._t("ResourcePages-Heading|System Pages")."</h2>"
	."<table class=\"mainTable\"><tr><td style=\"padding-left: 8px; width: 50px; text-align: center;\" ><b>"._t("ResourcePages-Table-Header|Page #")."</b></td>"
	."<td style=\"padding-left: 8px;\" ><b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"._t("ResourcePages-Table-Header|Menu/Page Title")."</b></td>"
	."<td style=\"text-align: center;\" ><b>"._t("ResourcePages-Table-Header|Edit")."</b></td></tr>";

	$q = "
	select rez_page_id, rez_menu_title, rez_menu_order, rez_visibility, rez_timestamp
	from rez_pages
	where rez_page_id < 0
	order by rez_page_id desc;
	";
	$result = $global['db']->Execute($q);
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez system pages");
	}

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

		$htmlMain .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><input class=\"styleTehButton\" type=\"button\" onclick=\"rez_perform_edit(".$page_id.");\" value=\""._t("ResourcePages-Button|Edit")."\"></td>";

		$i++;
		$eo++;
		$eo %= 2;
	}
	if ($count == 0) {
		$htmlMain .= "<tr><td colspan=7 class=\"mainRowEven\" style=\"text-align: center;\">"._t("ResourcePages-Message|No Pages have been created.")."</td></tr>";
	}
	$htmlMain .= "</table>";
	//
	// END SYSTEM PAGES
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	$pageControlHtml = '<input class="styleTehButton" type="button" onclick="javascript: rez_append_log(\''._t("ResourcePages-Message|Creating a new page...").'<br>\'); rez_perform_edit(0);" value="'._t("ResourcePages-Button|Create a new Page").'">'
	.'&nbsp;&nbsp;&nbsp;&nbsp;';
	// <input class="controlButton" type="button" onclick="javascript: rez_append_log(\'Showing Help...<br>\'); rez_show_help();" value="Help">';

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
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez update visibility");
	}

	$global['xajax_res']->addAppend('rezLog','innerHTML',_t("ResourcePages-Changed-Message|Changed visibility of page").' <b>#'.$page_id.'</b> '._t('ResourcePages-Changed-Message|to').' <b>'.$value.'</b>.<br>');
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
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move down 1");
	}
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
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move down 2");
	}
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
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move down 3");
	}

	// update next page with page_id's menu order
	$q = "
	UPDATE rez_pages
	set rez_menu_order = '".$pageMenuOrder."'
	where `rez_page_id` = ".$nextPageID." ;
	";
	$result = $global['db']->Execute($q);
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move down 4");
	}

	$global['xajax_res']->addAppend('rezLog','innerHTML',_t("ResourcePages-Moved-Message|Moved page #").$page_id._t("ResourcePages-Moved-Message|down.").'<br>');
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
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move up 1");
	}
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
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move up 2");
	}
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
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move up 3");
	}

	// update previous page with page_id's menu order
	$q = "
	UPDATE rez_pages
	set rez_menu_order = '".$pageMenuOrder."'
	where `rez_page_id` = ".$previousPageID." ;
	";
	$res = $global['db']->Execute($q);
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez move up 4");
	}

	$global['xajax_res']->addAppend('rezLog','innerHTML',_t("ResourcePages-Moved-Message|Moved page #").$page_id._t("ResourcePages-Moved-Message|up.").'<br>');
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
	FROM rez_pages
	ORDER BY rez_menu_order DESC
	LIMIT 1;
	";
	$result = $global['db']->Execute($q);
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez new 1");
	}
	$row = $result->FetchRow();
	$mID = isset($row['rez_menu_order']) ? $row['rez_menu_order'] : 0;
	$mID++;

	// insert a new page
	$q = "
	INSERT INTO rez_pages (rez_locale,rez_menu_title, rez_menu_order, rez_content, rez_timestamp, rez_visibility)
	VALUES ('en_US','new page', '".$mID."','new page content', '".date('Y-m-d H:i:s')."', 'Hidden');
	";
	$result = $global['db']->Execute($q);
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez new 2");
	}

	// find id of newest page we just created
	$q = "
	SELECT *
	FROM rez_pages
	ORDER BY rez_page_id DESC;
	";
	$result = $global['db']->Execute($q);
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez new 3");
	}
	$row3 = $result->FetchRow();

	return $row3['rez_page_id'];
}



// saves the edit's page content/attributes to the database
function rez_perform_save($page_id, $r) {
	global $global;
	$q = "select rez_page_id from rez_pages
	where rez_page_id='{$page_id}'
	and rez_locale='{$r['locale']}'";
	$result = $global['db']->Execute($q);
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez save");
	}
	$row = $result->FetchRow();
	if ( isset($row['rez_page_id']) ) {
		// update table data
		$q = "
		update rez_pages
		set rez_menu_title = '".mysql_escape_string($r['menuTitle'])."', rez_content = '".mysql_escape_string($r['pageContent'])."', rez_timestamp = '".date('Y-m-d H:i:s')."' where `rez_page_id` = ".$page_id." and `rez_locale` = '".$r['locale']."' ;
		";
		$result = $global['db']->Execute($q);
		if($result === false) {
			daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez save");
		}
	}
	else {
		//Translation creates new page
		$q = "
		SELECT *
		FROM rez_pages
		ORDER BY rez_menu_order DESC
		LIMIT 1;
		";
		$result = $global['db']->Execute($q);
		if($result === false) {
			daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez new 1");
		}
		$row = $result->FetchRow();
		$mID = isset($row['rez_menu_order']) ? $row['rez_menu_order'] : 0;
		$mID++;
		$q = "
		INSERT INTO rez_pages (rez_page_id,rez_locale,rez_menu_title, rez_menu_order, rez_content, rez_timestamp, rez_visibility)
		VALUES ('{$page_id}','{$r['locale']}','{$r['menuTitle']}', '{$mID}','{$r['pageContent']}', '".date('Y-m-d H:i:s')."', 'Public');
		";
		$result = $global['db']->Execute($q);
		if($result === false) {
			daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez new 2");
		}
	}


	// update log to reflect the save
	$global['xajax_res']->addAppend('rezLog','innerHTML',_t("ResourcePages-Saved-Message|Page #").$page_id." <span style=\"color: green;\">"._t("ResourcePages-Saved-Message|Saved")."</span>.<b><br>");
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}


// presents a gui to edit a page and its corresponding fields
function rez_perform_edit($page_id, $locale) {
	global $global;

	// if page_id = 0, must create a new page then continue to edit it
	if($page_id == 0) {
		$page_id = rez_perform_new();
	}

	// get page info
	$q = "
	select *
	from rez_pages
	where rez_page_id = '".$page_id."'
	and rez_locale = '".$locale."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez edit 1");
	}
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
	<tr><td class=\"mainRowOdd\" style=\"text-align: center; text-weight: bold;\">"._t("ResourcePages-Table-Header|Page #")."</td><td class=\"mainRowOdd\"> &nbsp; <b>".$pageIdText."</b></td></tr>
	<tr><td class=\"mainRowEven\" style=\"text-align: center; text-weight: bold;\">"._t("ResourcePages-Table-Header|Menu/Page Title")."</td><td class=\"mainRowEven\"><input name=\"menuTitle\" type=\"text\" id=\"menuTitle\" value=\"".$row['rez_menu_title']."\" onchange=\"window.rezPageSaved = false;\" size=\"64\" /></td></tr>
	<tr><td class=\"mainRowOdd\" style=\"text-align: center; text-weight: bold;\">"._t("ResourcePages-Table-Header|Locale")."</td><td class=\"mainRowOdd\"><input name=\"locale\" type=\"text\" id=\"locale\" value=\"".$row['rez_locale']."\" onchange=\"window.rezPageSaved = false;\" size=\"64\" /></td></tr>
	<tr><td class=\"mainRowEven\" style=\"text-align: center; text-weight: bold;\">"._t("ResourcePages-Table-Header|Last Modified")."</td><td class=\"mainRowEven\"> &nbsp; ".$row['rez_timestamp']."</td></tr>
	</table>
	<div class=\"wysiwyg\"><textarea name=\"pageContent\" onchange=\"window.rezPageSaved = false;\" id=\"pageContent\" style=\"height: 300px; width: 100%;\">".$row['rez_content']."</textarea></div>
	</form>";

	$editControlHtml = '
	<input class="styleTehButton" type="button" onclick="javascript:  window.rezPageSaved = true; if(nicEditors.editors.length>0){nicEditors.findEditor(\'pageContent\').saveContent();} rez_perform_save('.$page_id.', xajax.getFormValues(\'editPageForm\'));" value="'._t("ResourcePages-EditForm-Button|Save and Publish Changes").'">
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
function rez_perform_delete($page_id, $locale, $confirm) {
	global $global;

	if($confirm == "true") {

		//---- delete the page from db table
		$q = "
		delete from rez_pages
		where rez_page_id = '".$page_id."'
		and rez_locale = '".$locale."';
		";
		$result = $global['db']->Execute($q);
		if($result === false) {
			daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez delete 1");
		}

		$global['xajax_res']->addAppend('rezLog','innerHTML',_t("ResourcePages-Deleted-Message|Page <b>#").$page_id."</b>"._t("ResourcePages-Deleted-Message| deleted.")."<br>");
	} else {
		$global['xajax_res']->addAppend('rezLog','innerHTML',_t("ResourcePages-Message|Delete operation aborted.")."<br>");
	}

	//---- update UI
	$global['xajax_res']->addAssign('rezControl','style.opacity','1.0');
	$global['xajax_res']->addAssign('rezMain','innerHTML',rez_show_pages(TRUE));
	$global['xajax_res']->addAssign('rezMain','style.opacity','1.0');
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");

	return $global['xajax_res']->getXML();
}

/**
 * Translate a single page
 * @param string $page_id
 */
function rez_perform_translate($page_id, $locale) {
	global $global;

	// get page info
	$q = "
	select *
	from rez_pages
	where rez_page_id = '".$page_id."'
	and rez_locale = '".$locale."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez edit 1");
	}
	$original_row = $result->FetchRow();

	if ( isset($_SESSION['rez_locale']) ) {
		$rez_locale = $_SESSION['rez_locale'];
	}
	else $rez_locale = shn_rez_getlocale();

	$q = "
	select *
	from rez_pages
	where rez_page_id = '".$page_id."'
	and rez_locale = '".$rez_locale."';
	";
	$result = $global['db']->Execute($q);
	if($result === false) {
		daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "rez edit 1");
	}
	$row = $result->FetchRow();
	if((int)$row['rez_page_id'] < 0) {
		$sistim = "SYSTEM";
	} else {
		$sistim = "";
	}

	$pageIdText = $sistim." ". abs($page_id);

	$editMainHtml =
	"<form id=\"editPageForm\" name=\"editPageForm\">
	<table class=\"mainTable\">
	<tr><td class=\"mainRowOdd\" style=\"text-align: center; text-weight: bold;\">"._t("ResourcePages-Table-Header|Page #")."</td><td class=\"mainRowOdd\"> &nbsp; <b>".$pageIdText."</b></td>
	<td class=\"mainRowOdd\" style=\"text-align: center; text-weight: bold;\">"._t("ResourcePages-Table-Header|Page #")."</td><td class=\"mainRowOdd\"> &nbsp; <b>".$pageIdText."</b></td></tr>
	<tr><td class=\"mainRowEven\" style=\"text-align: center; text-weight: bold;\">"._t("ResourcePages-Table-Header|Menu/Page Title")."</td><td class=\"mainRowEven\"><input name=\"old_menuTitle\" type=\"text\" id=\"menuTitle\" value=\"".$original_row['rez_menu_title']."\" onchange=\"window.rezPageSaved = false;\" size=\"64\" /></td>
	<td class=\"mainRowEven\" style=\"text-align: center; text-weight: bold;\">"._t("ResourcePages-Table-Header|Menu/Page Title")."</td><td class=\"mainRowEven\"><input name=\"menuTitle\" type=\"text\" id=\"menuTitle\" value=\"".$row['rez_menu_title']."\" onchange=\"window.rezPageSaved = false;\" size=\"64\" /></td></tr>
	<tr><td class=\"mainRowOdd\" style=\"text-align: center; text-weight: bold;\">"._t("ResourcePages-Table-Header|Locale")."</td><td class=\"mainRowOdd\"><input name=\"old_slocale\" type=\"text\" id=\"locale\" value=\"".$original_row['rez_locale']."\" onchange=\"window.rezPageSaved = false;\" size=\"64\" /></td>
	<td class=\"mainRowOdd\" style=\"text-align: center; text-weight: bold;\">"._t("ResourcePages-Table-Header|Locale")."</td><td class=\"mainRowOdd\"><input name=\"locale\" type=\"text\" id=\"locale\" value=\"".$rez_locale."\" onchange=\"window.rezPageSaved = false;\" size=\"64\" /></td></tr>
	<tr><td class=\"mainRowEven\" style=\"text-align: center; text-weight: bold;\">"._t("ResourcePages-Table-Header|Last Modified")."</td><td class=\"mainRowEven\"> &nbsp; ".$original_row['rez_timestamp']."</td>
	<td class=\"mainRowEven\" style=\"text-align: center; text-weight: bold;\">"._t("ResourcePages-Table-Header|Last Modified")."</td><td class=\"mainRowEven\"> &nbsp; ".$row['rez_timestamp']."</td></tr>
	</table>
	<div class=\"wysiwyg\"><table width=\"100%\" border=\"0\">"
	."<tr><td width=\"50%\"><div id=\"original\" style=\"height: 100%; width: 100%;\">".$original_row['rez_content']."</div></td>"
	."<td width=\"50%\"><textarea name=\"pageContent\" onchange=\"window.rezPageSaved = false;\" id=\"pageContent\" style=\"height: 300px; width: 90%;\">".$row['rez_content']."</textarea></td></tr>"
	."</table></div>
	</form>";
	$pageControlHtml = '
	<input class="styleTehButton" type="button" onclick="javascript:  window.rezPageSaved = true; if(nicEditors.editors.length>0){nicEditors.findEditor(\'pageContent\').saveContent();} rez_perform_save('.$page_id.', xajax.getFormValues(\'editPageForm\'));" value="'._t("ResourcePages-EditForm-Button|Save and Publish Changes").'">
	<input class="styleTehButton" type="button" onclick="checkSaved()" value="Close Editor">
	&nbsp; &nbsp; &nbsp; <span class="toggle">View editor as:
	<input id="wysiwyg" class="styleTehButton" type="button" onclick="javascript: document.getElementById(\'original\').innerHTML = unescape(\''.rawurlencode($original_row['rez_content']).'\'); document.getElementById(\'wysiwyg\').disabled = true; document.getElementById(\'htmlcode\').disabled = false; area2 = new nicEditor({fullPanel : true}).panelInstance(\'pageContent\');" value="WYSIWYG">
	<input id="htmlcode" class="styleTehButton" type="button" '
	.'onclick="javascript: var s = document.getElementById(\'original\').innerHTML;document.getElementById(\'original\').innerHTML = \'<textarea style=width:90%;height:300px disabled=disabled>\'+s+\'</textarea>\';'
	.'area2.removeInstance(\'pageContent\'); document.getElementById(\'wysiwyg\').disabled = false; document.getElementById(\'htmlcode\').disabled = true; nicEditors.editors = []; " value="HTML"></span>';
	$pageControlHtml .= "<select name=\"locale\" onchange=\"javascript: rez_perform_change_locale(this.value, '".$pageIdText."','".$locale."');\">";
	//@TODO: textarea values: disabled="yes" height="300px" width="100%"
	foreach ( $global['rez_locales'] as $key=>$value ) {
		if ($key == $rez_locale) {
			$pageControlHtml .= "<option value=\"".$key."\" selected=\"selected\">".$value."</option>";
		}
		else $pageControlHtml .= "<option value=\"".$key."\">".$value."</option>";
	}
	$pageControlHtml .= "</select>";

	$global['xajax_res']->addAssign('rezMain','style.opacity','1.0');
	$global['xajax_res']->addAssign('rezMain','innerHTML',$editMainHtml);
	$global['xajax_res']->addAssign('rezControl','style.opacity','1.0');
	$global['xajax_res']->addAssign('rezControl','innerHTML',$pageControlHtml);

	$global['xajax_res']->addScript('area2 = new nicEditor({fullPanel : true}).panelInstance(\'pageContent\'); document.getElementById(\'wysiwyg\').disabled = true;');

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
/**
 *
 * @param string $locale
 * @author Ramindu Deshapriya
 */
function rez_perform_change_locale($locale, $pageId, $oldLocale) {
	global $global;
	$_SESSION['rez_locale'] = $locale;
	rez_perform_translate($pageId, $oldLocale);
	$global['xajax_res']->addAssign('rezControl','style.opacity','1.0');
	$global['xajax_res']->addAssign('rezMain','style.opacity','1.0');
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'rezLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");

	return $global['xajax_res']->getXML();
}


