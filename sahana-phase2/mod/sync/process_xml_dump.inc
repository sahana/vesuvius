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
$recorde=array();
$mem=array();


function startElement($parser, $name, $attrs)
{
    global $depth;
    global $mem;
    $depth++;
    switch ($depth){
        case 1:
            $_SESSION['timestamp']=$attrs['timestamp'];
            $_SESSION['instanceid']=$attrs['instanceid'];
            $_SESSION['contact']=$attrs['contact'];
            $_SESSION['owner']=$attrs['owner'];
        break;
        case 2:
            array_push($_SESSION['sync']['tables'],$name);
            $mem['table']=$name;
            create_tmp_table($name);
        break;
        case 3:
            $mem['recorde']=array();
        break;
        case 4:
            $GLOBALS['cref']=&$mem['recorde'][$name];
    }
}

function characterData($parser, $data)
{
    $GLOBALS['cref']=$data;
    $GLOBALS['cref']=&$c;
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
            insert_recorde($mem['recorde'],$mem['table']);
        break;
        case 4:
    }
    $depth--;
}

$xml_parser = xml_parser_create();
xml_parser_set_option($xml_parser, XML_OPTION_CASE_FOLDING, 0);
xml_set_element_handler($xml_parser, "startElement", "endElement");
xml_set_character_data_handler($xml_parser, "characterData");
if (!($fp = fopen($file, "r"))) {
    $global['xajax']->addAssign("console","innerHTML", "Can not open file......");
    return $global['xajax']->getXML();
}

while ($data = fread($fp, 4096)) {
    if (!xml_parse($xml_parser, $data, feof($fp))) {
        $error=sprintf("XML error: %s at line %d",
                    xml_error_string(xml_get_error_code($xml_parser)),
                    xml_get_current_line_number($xml_parser));
                $global['xajax']->addAssign("console","innerHTML", $error);
                return $global['xajax']->getXML();
    }
}
xml_parser_free($xml_parser);
return false;
?>