<?
/**
 * @name         Database Handler
 * @version      1.0
 * @package      framework
 * @author       Janaka Wickramasinghe <janaka@opensource.lk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license      http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.713
 *
 * @todo         Enable Caching
 * @todo         Database Connection Nice Error handling
 */



global $global;

//Include the ADOdb Library
require_once($global['approot'].'3rd/adodb/adodb.inc.php');

// Make the connection to $global['db']
$global['db'] = NewADOConnection($conf['db_engine']);
$_host_port   = $conf['db_host'].(isset($conf['db_port']) ? ':'.$conf['db_port']:'');
$global['db']->Connect($_host_port, $conf['db_user'], $conf['db_pass'], $conf['db_name']);
$global['db']->EXECUTE("set names 'utf8'");



/**
 * Cleans the given value to avoid SQL Injections
 *
 * Different databases uses different escape charaters, e.g mysql, postgres uses \ sqlite uses '
 * SQL Injection is done by supplying the escape character followed by the SQL to inject, in order to
 * prevent this you need to escape the escape charater as well. Using this function you will NOT have to
 * worry about different escape sequences used in different databases
 *
 * @param string $str
 * @access public
 * @return string
 */
function shn_db_clean($str) {
	global $global;
	$str = trim($str);
	$str = $global['db']->qstr($str,get_magic_quotes_gpc());
	return $str;
}



/**
 * DB Update Array functions
 *
 * You could create an associative array containing
 * 'file_name' => 'value' to update a table. You will have to provide
 * table name, also you may want to provide a clause as well.
 *
 * @param array $arr
 * @param string $table
 * @param string $key
 * @access public
 * @return void
 *
 * @todo check keys and see the field exists or not
 * @todo integrate the auditing
 */
function shn_db_update($arr,$table, $key) {
	global $global, $conf;
	$sql = "UPDATE $table SET ";

	foreach($arr as $k => $v){
		if($v == '') {
			$sql .= "$k = NULL, ";
		} else {
			$sql .= "$k = ".shn_db_clean($v).", ";
		}
	}

	$sql = substr($sql,0,strlen($sql)-2);

	if($key) {
		$sql .= " $key";
	}
	if($key) {
		$global['db']->Execute($sql);
	}
}



/**
 * DB Insert Array functions
 *
 * You could create an associative array containing
 * 'file_name' => 'value' to insert into a table. You will have to provide
 * table name. if you are auditing you need to specify the primary field
 *
 * @param array $arr
 * @param string $table
 * @param bool $audit
 * @param string $primary_field
 * @access public
 * @return void
 */
function shn_db_insert($arr, $table, $audit=false, $primary_field='') {
	global $global;
	global $conf;
	$keys = "";
	$values = "";

	if($audit) {
		$primary_field = trim($primary_field);

		//If Primary Field given then check for the value
		if( $primary_field != '' ) {
			$p_uuid = $arr[$primary_field];
		}
		if (isset($_SESSION['user_id'])) {
			$u_uuid = $_SESSION['user_id'];
		} else {
			$u_uuid = $conf['guest_id'];
		}
	}

	$sql = "INSERT INTO $table ";

	foreach($arr as $k => $v) {
		$keys .= "$k , ";

		if($v == '') {
			$values .= "'NULL', ";
		} elseif ($v == 'TRUE') {
			$values .= "TRUE, ";
		} else {
			$values .= shn_db_clean($v).", ";
		}

		if($audit) {
			$sql_audit[] = "
				INSERT INTO audit (p_uuid, u_uuid, change_type, change_table, change_field, new_val )
				VALUES ('$p_uuid' , '$u_uuid', 'ins' , '$table' , '$k' , ".shn_db_clean($v) ." );
			";
		}
	}

	$keys = substr($keys, 0, strlen($keys)-2);
	$values = substr($values, 0, strlen($values)-2);

	$sql .= "( $keys ) VALUES ( $values ) ";

	$global['db']->Execute($sql);
        $msg = $global['db']->ErrorMsg();
        if (!empty($msg)) {
            throw new RuntimeException($msg);
        }

	#var_dump($sql_audit);
	if($audit) {
		foreach($sql_audit as $sqls) {
			//echo $sqls ."<hr>";
			$global['db']->Execute($sqls);
		}
	}
}



/**
 * Soundex and methaphone values of a given string will be inserted.
 *
 * @param string $name
 * @param string $pgl_uuid
 * @access public
 * @return void
 */
function shn_db_insert_phonetic($name, $p_uuid) {
	global $global;
	//split the name
	$keywords = preg_split("/[\s]+/", $name);
	foreach($keywords as $keyword){
		$arr['encode1'] = soundex($keyword);
		$arr['encode2'] = metaphone($keyword);
		$arr['p_uuid'] = $p_uuid;

		//ignore if all the fields are there
		if(! $global['db']->GetOne("SELECT * FROM phonetic_word WHERE encode1='{$arr['encode1']}' AND encode2='{$arr['encode2']}' AND p_uuid='{$arr['p_uuid']}'") ) {
			shn_db_insert($arr,'phonetic_word', true, 'p_uuid');
		}
		//clear arr just in case ;-)
		$arr = null;
	}
}



function shn_db_config_update($module, $conf_key, $value) {
	global $global;

	$arr['module_id'] = $module;
	$arr['confkey'] = $conf_key;
	$arr['value'] = $value;

	//delete
	$global['db']->Execute("DELETE FROM config WHERE module_id LIKE '$module' AND confkey LIKE '$conf_key'");

	//insert
	shn_db_insert($arr,'config',true,'module_id');
}



function shn_db_get_config($module,$conf_key) {
	global $global;
	$rs = $global['db']->GetOne("SELECT value FROM config WHERE module_id LIKE '$module' AND confkey LIKE '$conf_key'");
	if($rs) {
		return $rs;
	} else {
		return false;
	}
}


