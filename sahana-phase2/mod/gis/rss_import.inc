<?php
/** 
* 
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* 
* Handles Generic RSS Imports
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @package module
* @subpackage gis
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

$filename ="http://slashdot.org/index.rss";

$xml_parser = xml_parser_create();

//set basic handler
xml_set_element_handler($xml_parser,"startElement","endElement");

//set char handler
xml_set_character_data_handler($xml_parser,"charachterData");

$fp = fopen($filename,"r")
	or die(_("Error Reading RSS Feed"));
	
//Read with 4KB buffer
while ($data=fread($fp,4096)){
	xml_parse($xml_parser,$data,feof($fp))
	or die(sprintf("XML error: %s at line %d",  
           xml_error_string(xml_get_error_code($xml_parser)),  
           xml_get_current_line_number($xml_parser)));
}

fclose($fp);
xml_parser_free($xml_parser);
	
function startElement()
{
	
}

function endElement()
{
	
}

function charachterData()
{
	
}
?>
