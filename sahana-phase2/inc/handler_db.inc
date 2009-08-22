<?php
/* $Id: handler_db.inc,v 1.31 2009-08-22 17:17:25 ravithb Exp $ */

/**
 *
 * This is the database handler. A vital component of the framework.
 * This will be included from the front controller and the reset of the
 * application can use the database resourse, availabe in $global['db']
 * you may need to make it into a global scope. i.e global $global;
 *
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage database
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 * @todo       Enable Caching
 * @todo       Database Connection Nice Error handling
 */

//Include the ADOdb Library
require_once($global['approot'].'3rd/adodb/adodb.inc.php');

//Make the connection to $global['db']
$global['db'] = NewADOConnection($conf['db_engine']);
$_host_port = $conf['db_host'].(isset($conf['db_port'])?':'.$conf['db_port']:'');
$global['db']->Connect($_host_port,$conf['db_user'],$conf['db_pass'],$conf['db_name']);

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
function shn_db_clean($str)
{
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
function shn_db_update($arr,$table, $key){
    global $global, $conf;
    $sql = "UPDATE $table SET ";

    foreach($arr as $k => $v){
        if($v == '')
            $sql .= "$k = NULL, ";
        else
            $sql .= "$k = ".shn_db_clean($v).", ";
    }

    $sql = substr($sql,0,strlen($sql)-2);

    if($conf['debug']) {
        echo $sql."<hr>";
    }

    if($key)
        $sql .= " $key";
    if($key)
        $global['db']->Execute($sql);
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
function shn_db_insert($arr, $table, $audit=true, $primary_field=''){
    global $global,$conf;

    if($audit){
        $primary_field = trim($primary_field);
        //If Primary Field given then check for the value
        if( $primary_field != '' )
           $x_uuid = $arr[$primary_field];
        //if primary field is not given the look get the primary key
        //@TODO

        //if the $_SESSION['user_id'] is not set, $u_uuid =
        //$conf['guest_id']
        if (isset($_SESSION['user_id']))
            $u_uuid = $_SESSION['user_id'];
        else
            $u_uuid = $conf['guest_id'];
    }


    $sql = "INSERT INTO $table ";

    foreach($arr as $k => $v){
        $keys .= "$k , ";

        if($v == '')
            $values .= "'NULL', ";
        elseif ($v == 'TRUE')
            $values .= "TRUE, ";
        else
            $values .= shn_db_clean($v).", ";

        if($audit)
            $sql_audit[] = "INSERT INTO audit (x_uuid, u_uuid, change_type, ".
                     "change_table, change_field, new_val ) VALUES ( ".
                    "'$x_uuid' , '$u_uuid', 'ins' , '$table' , '$k' , " .
                    shn_db_clean($v) ." )";
    }

    $keys = substr($keys,0,strlen($keys)-2);
    $values = substr($values,0,strlen($values)-2);

    $sql .= "( $keys ) VALUES ( $values ) ";

    $global['db']->Execute($sql);

    if($conf['debug']) {
        echo $sql."<hr>";
    }
    #var_dump($sql_audit);
    if($audit){
        foreach($sql_audit as $sqls){
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
function shn_db_insert_phonetic($name,$pgl_uuid)
{
    global $global;
    //split the name
    $keywords = preg_split("/[\s]+/",$name);
    foreach($keywords as $keyword){
        $arr['encode1'] = soundex($keyword);
        $arr['encode2'] = metaphone($keyword);
        $arr['pgl_uuid'] = $pgl_uuid;

        //ignore if all the fields are there
        //@todo: clean
        if(! $global['db']->GetOne("SELECT * FROM phonetic_word WHERE encode1='{$arr['encode1']}' AND encode2='{$arr['encode2']}' AND pgl_uuid='{$arr['pgl_uuid']}'") )
            shn_db_insert($arr,'phonetic_word', true, 'pgl_uuid');
        //clear arr just incase ;-)
        $arr = null;
    }
}

function shn_db_config_update($module,$conf_key,$value)
{
    global $global;

    $arr['module_id'] = $module;
    $arr['confkey'] = $conf_key;
    $arr['value'] = $value;

    //delete
    $global['db']->Execute("DELETE FROM config WHERE module_id LIKE '$module' AND confkey LIKE '$conf_key'");
    //insert
    shn_db_insert($arr,'config',true,'module_id');
}

function shn_db_get_config($module,$conf_key)
{
    global $global;
    $rs = $global['db']->GetOne("SELECT value FROM config WHERE module_id LIKE '$module' AND confkey LIKE '$conf_key'");
    if($rs){
        return $rs;
    }else
        return false;
}

function shn_db_get_incident_select()
{
	global $global;
?>
<form method="post" action="index.php?mod=home&amp;act=incident_set" id='incident_changer' class="head" >
<label><?php echo _t("Incident") ?></label>
<select name="incident_id" onchange="changeIncident(this.value);" >
<?php
$sql_level1 = "SELECT incident_id, name FROM incident WHERE parent_id IS NULL";
$result_leve1 = $global['db']->Execute($sql_level1);
while($myresult_level1 = $result_leve1->FetchRow()){
?>
	<option value="<?php echo $myresult_level1['incident_id'];?>" <?php echo ($_SESSION['user_pref_ims_incident_id']==$myresult_level1['incident_id']?'selected="selected"':'');?> ><?php echo $myresult_level1['name'];?></option>
<?php
	$sql_level2 = "SELECT incident_id, name FROM incident WHERE parent_id = '{$myresult_level1['incident_id']}'";
	$result_leve2 = $global['db']->Execute($sql_level2);
	while($myresult_level2 = $result_leve2->FetchRow() ){
?>
		<option value="<?php echo $myresult_level2['incident_id'];?>"  <?php echo ($_SESSION['user_pref_ims_incident_id']==$myresult_level2['incident_id']?'selected="selected"':'');?>  >&nbsp;&nbsp;&#8211;&nbsp;<?php echo $myresult_level2['name'];?></option>
<?php
		$sql_level3 = "SELECT incident_id, name FROM incident WHERE parent_id = '{$myresult_level2['incident_id']}'";
		$result_level3 = $global['db']->Execute($sql_level3);
		while($myresult_level3 = $result_level3->FetchRow() ){
?>
			<option value="<?php echo $myresult_level3['incident_id'];?>"  <?php echo ($_SESSION['user_pref_ims_incident_id']==$myresult_level3['incident_id']?'selected="selected"':'');?>  >&nbsp;&nbsp;&nbsp;&nbsp;&#8211;&nbsp;<?php echo $myresult_level3['name'];?></option>
<?php
		}
	}

}
?>
</select>
<br/>
</form>
<?php
}

function shn_db_get_incident_list()
{
    global $global;

    $sql = "SELECT name FROM incident a inner JOIN user_preference b ON a.incident_id = b.value WHERE b.p_uuid = '{$_SESSION['user_id']}' AND b.pref_key = 'incident_id' ";

    $result = $global['db']->GetAll($sql);
	/*
?>
<select name="sel_incident">
<?php
	$sql_all = "SELECT incident_id, parent_id, name FROM incident WHERE parent_id is NULL";
	$result_all = $global['db']->Execute($sql_all);
	while($my_disasters = $global['db']->FetchRow($result_all)){

	}
?>
</select>
*/
?>
<div id="incident_name">
   <strong><?php echo $result[0]['name'];?> </strong>
</div>
<?php
}

function shn_db_get_all_incidents($incident_id)
{
    global $global;

    $return = array($incident_id);
    $sql = "SELECT incident_id FROM incident WHERE parent_id = '$incident_id'";
    $result = $global['db']->GetAll($sql);
    if($result){
        foreach($result as $result_id){
            $return[] = $result_id['incident_id'];
        }
        $global['db']->Execute("CREATE TEMPORARY TABLE tmp_incident (incident_id BIGINT)");
        $global['db']->Execute("INSERT INTO tmp_incident SELECT incident_id FROM incident WHERE parent_id = '$incident_id'");
        $result_child = $global['db']->GetAll("SELECT a.incident_id FROM incident a INNER JOIN tmp_incident b ON a.parent_id = b.incident_id");
        $global['db']->Execute("DROP TABLE tmp_incident");

        if($result_child){
            foreach($result_child as $result_id){
                $return[] = $result_id['incident_id'];
            }
        }
    }

    return $return;
}
function debug($str,$exit=false)
{
    echo "<hr>";
    if(is_array($str)){
        var_dump($str);
    }else{
        echo "<pre>$str</pre>";
    }
    echo "<hr>";
    if($exit)
        exit();
}


