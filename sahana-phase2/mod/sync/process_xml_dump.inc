<?php
/**
 * Handler to process XML dump files 
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
global $global;
include_once("lib_temp_data.inc");
$file=$_SESSION['sync']['file'];
$_SESSION['sync']['tables']=array();
$depth = 0;
$cref='';
$record=array();
$mem=array();


function startElement($parser, $name, $attrs)
{
    global $depth;
    global $mem;
    $depth++;
    switch ($depth){
        case 1:
            $_SESSION['sync_inst']['last_update']=date('Y-m-d H:i:s',$attrs['timestamp']);
            $_SESSION['sync_inst']['base_uuid']=$attrs['instanceid'];
            $_SESSION['sync_inst']['contact']=$attrs['contact'];
            $_SESSION['sync_inst']['owner']=$attrs['owner'];
        break;
        case 2:
            array_push($_SESSION['sync']['tables'],$name);
            $mem['table']=$name;
            create_tmp_table($name);
        break;
        case 3:
            $mem['record']=array();
        break;
        case 4:
            $mem['record'][$name]='';
            $GLOBALS['cref']=&$mem['record'][$name];
    }
}

function characterData($parser, $data)
{
    $GLOBALS['cref']=$data;
    unset($GLOBALS['cref']);
}

function endElement($parser, $name)
{
    global $depth;
    global $mem;
        switch ($depth){
        case 1:
        case 2:
            $mem['table']='';
        break;
        case 3:
            insert_record($mem['record'],$mem['table']);
        break;
        case 4:
            unset($GLOBALS['cref']);
    }
    $depth--;
}

$xml_parser = xml_parser_create();
xml_parser_set_option($xml_parser, XML_OPTION_CASE_FOLDING, 0);
xml_set_element_handler($xml_parser, "startElement", "endElement");
xml_set_character_data_handler($xml_parser, "characterData");
if (!($fp = $file_open($file, "r"))) {
    add_error(_t("Can not open file."));
    $global['xajax']->addAssign("console","innerHTML", display_errors(true));
    return $global['xajax']->getXML();
}

while ($data = $read($fp, 4096)) {
    set_time_limit(10);
    if (!xml_parse($xml_parser, $data, feof($fp))) {
        $error=sprintf(_t("XML error: %s at line %d"),  xml_error_string(xml_get_error_code($xml_parser)), xml_get_current_line_number($xml_parser));
        add_error(_t("Error in upload file: Unable to continue importing."));
        add_error($error);
        throw new Exception($error);
        return $global['xajax']->getXML();
    }
}
xml_parser_free($xml_parser);
$file_close($fp);

