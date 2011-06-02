<?
/**
 * @name         Localization Library
 * @version      1.0
 * @package      framework
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */



include_once $global['approot']."/inc/lib_form.inc";

/**
 * Set the 'locale' value in the 'config' table
 *
 * @param string $locale
 * @access protected
 * @return bool
 */
function _shn_lc_setdblc($locale) {
	global $global;
	$sql = "SELECT * FROM config WHERE module_id = 'admin' AND confkey = 'locale'";
	$res = $global['db']->Execute($sql);
	if($res){
		$res->MoveFirst();
		// check if previous value exists.
		if(!$res->EOF){
			// update value
			$sql = "UPDATE config SET value = '$locale' " .
              "WHERE module_id = 'admin' " .
              "AND confkey = 'locale'";
		}else{
			// insert value
			$sql = "INSERT INTO config (module_id,confkey,value)" .
		   "VALUES('admin', 'locale', '$locale')";
		}

		$global['db']->Execute($sql);

		if (!$global['db']->ErrorNo())
		{
			print $global['db']->ErrorMsg();
			return false;
		}
		return true;
	}else{
		add_error(_t("Unknown error in updating configuration value."));
		return false;
	}
}



/**
 * Get the 'locale' value from the database
 *
 * @access protected
 * @return mixed
 */
function _shn_lc_getdblc() {
	global $global;

	$sql = "SELECT value FROM config " .
			"WHERE module_id = 'admin' " .
			"AND confkey = 'locale'";

	$rs = $global['db']->Execute($sql);

	if(!$rs)
	{
		print "Error : " . $global['db']->ErrorMsg();
		return false;
	}
	else if(1>$rs->RecordCount())
	{
		return false;
	}
	else
	{
		$rs = $rs->getArray();
		return $rs[0][0];
	}
}



/**
 * Checks whether the 'locale' value is set or not in the database
 *
 * @access protected
 * @return bool
 */
function _shn_lc_issetdblc() {
	global $global;
	$res = _shn_lc_getdblc();

	if(!$res) {
		return false;
	} else {
		return true;
	}
}



function _shn_lc_issetcookie() {
	return isset($_COOKIE['locale']);
}



function _shn_lc_setcookielc($locale) {
	$_COOKIE['locale'] = $locale;
}



function _shn_lc_setsessionlc($locale) {
	$_SESSION["locale"] = $locale;
}



function _shn_lc_issetsession() {
	return isset($_SESSION['locale']);
}



/**
 * Displays the list of available languages
 */
function _shn_lc_lang_list($mode = 1) {
	global $conf;
	$lc_list = _shn_get_lang_list();

	$locale = $_SESSION['locale'];
	global $global;
	//shn_form_fopen("lc_set",null,array('req_message'=>false,'id'=>"language"));

	// this prevents Sahana Security Bulletin 2009:1210 by cleaning the module variable before outputting it
	$mod = substr($global['module'], 0, 6);
	if (!preg_match("/\A[0-9a-z]{2,6}\Z/", $mod)) {
		$mod = "";
	}

	echo "<div id=\"language\"><form method=\"post\" action=\"index.php?mod=".$mod."&amp;act=lc_set\" id=\"language_form\">";
	shn_form_hidden(array('seq'=>'set_locale'));
	shn_form_select($lc_list, "Language", "locale", 'onchange="submit(this);"', array('value'=>"$locale"));
	echo "</form></div>";
}



function _shn_lc_get_dbpo() {
	global $global;
	$db_po_str = '';
	$list = _shn_lc_get_db_strlist();
	foreach ($list as $str=>$comments) {
		$string = $str;
		$comment = $comments['table'] . "/" . $comments['field'] . ", ";

		$db_po_str .= "#: $comment\n" .
                         "msgid \"$string\"\n" .
                         "msgstr \"\"\n\n";
	}
	return $db_po_str;
}



function _shn_lc_is_dbl10n_tbl_empty() {
	global $global;
	$sql = "SELECT tablename,fieldname FROM  lc_fields";
	$rs = $global['db']->Execute($sql);

	if(!$rs) {
		print "Error : " . $global['db']->ErrorMsg();
		return null;
	} else if($rs->RecordCount()==0) {
		//No records
		return true;
	}
	return false;
}



function _shn_lc_get_db_strlist() {
	global $global;

	$str_list = array();
	$sql = "SELECT tablename,fieldname FROM  lc_fields";
	$rs = $global['db']->Execute($sql);

	if(!$rs) {
		print "Error : " . $global['db']->ErrorMsg();
		return false;
	} else if(1>$rs->RecordCount()) {
		print ">>>>>>>>>>>no db lc";
		return false;
	} else {
		$rs = $rs->getArray();
		foreach ($rs as $r)
		{
			$strs = _shn_lc_get_db_tblstrings($r[0],$r[1]);
			foreach ($strs as $str)
			{
				// avoid duplicates coming from multiple tables
				// using the key as the index.
				$str_list["$str"] = array(
                                    'table' => $r[0],
                                    'field' => $r[1]
				);
			}
		}
	}
	return $str_list;
}



function _shn_lc_get_db_tblstrings($table, $field) {
	global $global;

	$str_list = '';
	$sql = "SELECT DISTINCT($field) FROM $table";
	$rs = $global['db']->Execute($sql);

	if(!$rs) {
		return array();
	} else if(1>$rs->RecordCount()) {
		return array();
	} else {
		$ret_arr = array();
		while(!$rs->EOF){
			array_push($ret_arr,$rs->fields[0]);
			$rs->MoveNext();
		}
		return $ret_arr;
	}
}



function _shn_get_lang_list() {
	$handle = fopen("../res/locale/locale", "r");
	$l_list = array();
	while ($localeinfo = fscanf($handle,"%s\t%s\t%s\n")) {
		list ($locale, $name, $ex_name) = $localeinfo;
		if($ex_name!=null){
			$name = $name." ".$ex_name;
		}
		$l_list[$locale] = $name;
	}
	fclose($handle);
	asort($l_list);
	return $l_list;
}



/**
 * Replaces the CHARSET with the given charset in a po_file's contents.
 *
 * @param String $po_file The PO file as a string.
 * @param String $charset The charset as a string.
 * @return String The modified po file as a string.
 */
function _shn_replace_charset($po_file,$charset = "UTF-8") {
	$string = 'charset=CHARSET';

	//  $position = strpos($_SESSION['admin']['locale']['charset'],$string);
	$replace = 'charset='.$charset;
	return str_replace($string,$replace,$po_file);
}


