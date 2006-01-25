<?php 
/* $Id: handler_db.inc,v 1.11 2006-01-25 06:21:43 janakawicks Exp $ */

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
$global['db']->Connect($conf['db_host'].($conf['db_port']?':'.$conf['db_por
t']:''),$conf['db_user'],$conf['db_pass'],$conf['db_name']);

if($conf['enable_monitor_sql'])
    $global['db']->LogSQL();

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
 * @todo: check keys and see the field exists or not
 * @todo: integrate the auditing
 */
function shn_db_update($arr,$table, $key){
    global $global;
    $sql = "UPDATE $table SET ";

    foreach($arr as $k => $v){
        if($v == '')
            $sql .= "$k = NULL, ";
        else
            $sql .= "$k = ".shn_db_clean($v).", ";
    }

    $sql = substr($sql,0,strlen($sql)-2);

    if($key)
        $sql .= " $key";
    if($key)
        $global['db']->Execute($sql);
#    echo $sql;
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
    #echo $sql."<hr>";
    #var_dump($sql_audit);
    if($audit){
        foreach($sql_audit as $sqls){
            #echo $sqls ."<hr>";
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

?>
