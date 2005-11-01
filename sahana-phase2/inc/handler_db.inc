<?php 
/* $Id: handler_db.inc,v 1.6 2005-11-01 09:21:39 janakawicks Exp $ */

/**
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Janaka Wickramasinghe <janaka@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

#remove this
define(DB_DEBUG,0);

//Include the ADOdb Library
require_once($global['approot'].'3rd/adodb/adodb.inc.php');
/* }}} */

//Make the connection to $global['db']
$global['db'] = NewADOConnection($conf['db_engine']);
$global['db']->Connect($conf['db_host'].($conf['db_port']?':'.$conf['db_por
t']:''),$conf['db_user'],$conf['db_pass'],$conf['db_name']);
//Error handle baby!!!

//enable logging sql
#if($conf['enable_monitor_sql'])
#    $global['db']->LogSQL();
/* }}} */

/* LATER DUDES 
if($conf['enable_cache']){
    $ADODB_CACHE_DIR = $global['approot'].$conf['cache_dir'];
    //@todo : Set the cache to 24hours need to change this later
    $global['db']->cacheSecs = 3600*24;
}

//create another connection for the SQLite database (our cache layer ;-)
$global['db_cache'] = NewADOConnection('sqlite');
$global['db_cache']->Connect($global['approot'].$conf['cache_dir'].'/cache.db');

#to remove creating initial tables of cb_cache
#$global['db_cache']->Execute("CREATE TABLE table_status (tablename TEXT, updated TIMESTAMP)");
#exit(0);

//check for dirty tables
shn_db_cache_sync();

function shn_db_cache_sync()
{
    global $global;
    
    $rs = $global['db']->Execute("SELECT * FROM dirty_tables");
    
    //check with the cache table
    $results=$rs->GetAll();
    foreach($results as $res){
        $result_cache = $global['db_cache']->Execute("SELECT updated FROM table_status WHERE tablename = '".$res['tablename']."'");
#        shn_db_sync_cache($res['tablename'],$res['updated']);
        if($result_cache->RecordCount()){
            $rs_cache = $result_cache->FetchRow();
            if(_shn_db_extract_date_upto_sec($res['updated']) != _shn_db_extract_date_upto_sec($rs_cache['updated']) ){
                if(DB_DEBUG)
                    echo "Table '{$res['tablename']}' Is NOT in sync and Syncing<br>";
                shn_db_sync_cache($res['tablename'],$res['updated']);
            }else{    
                if(DB_DEBUG)
                    echo "Table '{$res['tablename']}' Is in sync<br>";
            }
        }else{
            shn_db_sync_cache($res['tablename'],$res['updated']);
        }
    }
        
}   

function shn_db_sync_cache($tablename,$last_updated)
{
    //@todo need to make this more
    //@todo Need to error check

    global $global;

    // the cache table
    $fs = $global['db']->MetaColumns($tablename);
    $flds = array();
    foreach ($fs as $fsh){
        $tmparr = array($fsh->name,$fsh->type);
        if($fsh->max_length && $fsh->max_length != -1)
            array_push($tmparr,$fsh->max_length);
        array_push($flds,$tmparr);
    }
    
    $dict = NewDataDictionary($global['db_cache']);

    //add primary key
    $fs = $global['db']->MetaPrimaryKeys($tablename);
    if($fs)
        $primary_keys = ', PRIMARY KEY ('.implode(",",$fs).')';

    //add foregin keys 
    $fs = $global['db']->MetaForeignKeys($tablename);
    if($fs){
        foreach ($fs as $key => $value){
            list($ref,$ref1) = split("=",$value[0]);
            $foregin_keys .= ', FOREIGN KEY ('.$ref.') REFERENCES '. $key . ' (' .$ref1.')';
        }
    }
    if($primary_keys)
        $constraints = $primary_keys;
    if($foregin_keys)
        $constraints .= $foregin_keys;
    if($constraints)
        $taboptarray = array('constraints' => $constraints, 'REPLACE');
    else
        $taboptarray = array('REPLACE');

    //REPLACE the current cache table
    $dict->ExecuteSQLArray($dict->CreateTableSQL($tablename,$flds,$taboptarray));

    //Sync with the Main table from the main database
    //@todo Need to seed up things here
    
    $rs = $global['db']->Execute("SELECT * FROM $tablename");
    while(!$rs->EOF){
        $result = $rs->GetRowAssoc(false);
        $global['db_cache']->Execute(shn_db_get_insert_sql($tablename, $result, $global['db_cache']));
        $rs->MoveNext();
    }

    //Update the table_status
    $global['db_cache']->Execute("DELETE FROM table_status WHERE tablename = '".$tablename."'");
#    $global['db_cache']->Execute("INSERT INTO table_status (tablename, updated) VALUES('".$tablename."','".$last_updated."')");
    $global['db_cache']->Execute("INSERT INTO table_status (tablename, updated) VALUES('".$tablename."','"._shn_db_extract_date_upto_sec($last_updated)."')");
}
function _shn_db_extract_date_upto_sec($date)
{
    preg_match("/(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})/",$date,$match);
    return $match[1];
}

function shn_db_get_insert_sql( $table, &$hash, $db) {
    $fmtsql = "insert into $table ( %s ) values( %s ) ";
    foreach ($hash as $k => $v) {
        if (is_array($v) or is_object($v)) {
            continue;
        }
        $fields[] = $k;
        if(!empty($v))
            $values[] = _shn_db_escape(strip_tags( $v ), $db) ;
        else
            $values[] = 'NULL';
    }
    $sql = sprintf( $fmtsql, implode( ",", $fields ) ,  implode( ",", $values ) 
);
    return $sql;
}

function _shn_db_escape( $str, $db ) {
    return $db->qstr( $str );
}
*/

?>
