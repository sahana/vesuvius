<?php
/**
 * This Library contains functions to dump data from the database.
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


function _shn_sync_dump_xml($tables){
    global $global;
    global $conf;
    echo "<?xml version='1.0' ?>\n";
    //print the meta data
    echo "<sahana_data_dump timestamp='".time()."' 
    instanceid='".htmlspecialchars($conf['base_uuid'],ENT_QUOTES)."' 
    owner='".htmlspecialchars($conf['root_name'],ENT_QUOTES)."' 
    contact='".htmlspecialchars($conf['root_email'].",".$conf['root_tel'],ENT_QUOTES)."'>\n";
    //loop through each table
    foreach($tables as $table)
        _dump_xml_table($table);
    echo "</sahana_data_dump>";
}


function _dump_xml_table($table){
    global $global;
//create sql
    $sql="SELECT * FROM ".$table;
//get the record set
    $rs=$global['db']->Execute($sql);
    if($rs){
    //get the field names
        $fc=$rs->FieldCount();
        for($x=0;$x<$fc;$x++)
        $fields[$x]=$rs->FetchField($x)->name;
    //ouput the xml
    //print container
        echo "\t<".$table.">\n";
    //itrate through record set
        foreach($rs as $row){
            echo "\t\t<record>\n";
            foreach($fields as $k=>$field){
                $row[$k]=(isset($row[$k]))?$row[$k]:'null';
                echo "\t\t\t<".$field."><![CDATA[".$row[$k]."]]></".$field.">\n";
            }
            echo "\t\t</record>\n";
        }
        echo "\t</".$table.">\n";
    }
}


function shn_sync_dump_xml($tables,$tmp_file,$open,$close,$write){
    global $global;
    global $conf;
    $fp=$open($tmp_file,'w');
    $write($fp,"<?xml version='1.0' ?>\n");
    //print the meta data
    $write($fp,"<sahana_data_dump timestamp='".time()."' 
    instanceid='".htmlspecialchars($conf['base_uuid'],ENT_QUOTES)."' 
    owner='".htmlspecialchars($conf['root_name'],ENT_QUOTES)."' 
    contact='".htmlspecialchars($conf['root_email']." , ".$conf['root_tel'],ENT_QUOTES)."'>\n");
    //loop through each table
    foreach($tables as $table){
        if($table=='image'){
            dump_xml_image_table($write,$fp);
            continue;
        }
        dump_xml_table($table,$write,$fp);
    }
    $write($fp,"</sahana_data_dump>");
}


function dump_xml_table($table,$write,$fp){
    global $global;
    //create sql
    $sql="SELECT * FROM ".$table;
    //get the record set
    $rs=$global['db']->Execute($sql);
    if($rs){
    //get the field names
        $fc=$rs->FieldCount();
        for($x=0;$x<$fc;$x++)
        $fields[$x]=$rs->FetchField($x)->name;
        //ouput the xml
        //print container
        $write($fp,"\t<".$table.">\n");
        //itrate through record set
        foreach($rs as $row){
            $write($fp,"\t\t<record>\n");
            foreach($fields as $k=>$field){
                $row[$k]=(isset($row[$k]))?$row[$k]:'null';
                $write($fp,"\t\t\t<".$field."><![CDATA[".$row[$k]."]]></".$field.">\n");
            }
            $write($fp,"\t\t</record>\n");
        }
        $write($fp,"\t</".$table.">\n");
    }
}

function dump_xml_image_table($write,$fp){
    global $global;
    //create sql
    $sql="SELECT * FROM image";
    //get the record set
    $rs=$global['db']->Execute($sql);
    if($rs){
    //get the field names
        $fc=$rs->FieldCount();
        for($x=0;$x<$fc;$x++)
        $fields[$x]=$rs->FetchField($x)->name;
        //ouput the xml
        //print container
        $write($fp,"\t<image>\n");
        //itrate through record set
        foreach($rs as $row){
            $write($fp,"\t\t<record>\n");
            foreach($fields as $k=>$field){
                if($field=='image')$row[$k]="-";
                $row[$k]=(isset($row[$k]))?$row[$k]:'null';
                $write($fp,"\t\t\t<".$field."><![CDATA[".$row[$k]."]]></".$field.">\n");
            }
            $write($fp,"\t\t</record>\n");
        }
        $write($fp,"\t</image>\n");
    }
}
