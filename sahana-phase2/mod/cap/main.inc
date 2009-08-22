<?php
/*
 * Sahana CAP alert aggregator Module
 * PHP version 5
 * LICENSE: This source file is subject to LGPL license 
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 * @author     Shree Kant Bohra <skbohra123@gmail.com> 
 * @package    Sahana - http://sahana.lk/
 * @module     CAP
 * @copyright  Lanka Software Foundation - http://www.opensource.lk 
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 */ 
global $global;
include_once ($global['approot']."/inc/lib_menu.inc");
include_once ($global['approot']."/inc/lib_paging.inc");
include_once ($global['approot']."/mod/cap/main_fns.inc");


/*Default function, it calls another function which displays the main ui of the module
 * @param void
 * @return void 
 */
function shn_cap_default()
{
	_shn_cap_show_alerts();
}
 
/*Function to build the main menu of the module
 * @param void
 * @return void 
 */
function shn_cap_mainmenu()
{
 	global $global;
 	$module = $global['module'];
 	shn_mod_menuopen(_t("CAP Aggregator"));
 	shn_mod_menuitem("default", _t("Home"));
 	shn_mod_menuitem("cap_subscribe", _t("Settings"));
	shn_mod_menuclose();
	include $global['approot']."/inc/handler_mainmenu.inc";
	
}

/*Function to display the subscribe form 
 * @param void
 * @return void 
 */
function shn_cap_cap_subscribe()
{
	include_once ('handler_cap_subscribe.inc');
}


/*Function to extend html head to put a javascript in the header
 * this javascript calls the update function every few minutes
 * @param void
 * @return void 
 */
function shn_cap_html_head()
{
    global $global;
    include $global['approot']."/inc/lib_xhtml.inc";
 	$js=$global['approot']."/mod/cap/cap.js";
    $capjavascript = array ('<script type="text/javascript" src="index.php?stream=text&mod=cap&act=javascript" ></script>');
    shn_display_xhtml_head($capjavascript);
}


/*Function to stream javascript code
 * @param void
 * @return void 
 */
function shn_text_cap_javascript()
{
	global $global;
	include $global['approot']."/mod/cap/cap.js";
}


/*Function to display cap alert and performing xslt transformation
 * @param void
 * @return void 
 */

function shn_text_cap_alert()
{	 global $global;
	 include_once ($global['approot']."/mod/cap/lib_cap.inc");
	 $capfile = $global['approot']."/mod/cap/capalerts/".$_GET{"url"}; //the the file name of cap alert is taken from the url
	 $proc = new XSLTProcessor() or die ("Error No XSLT Processor module installed! Please refer to PHP Manual"); //creating an instance of xslt processor
	 $xml = new DOMDocument(); //a new dom document
	 $xml->load($capfile) or die ("Error Loading Document"); //loading the cap file 
	 $xsl = new DOMDocument(); 
	 $xslfile = $global['approot']."/mod/cap/res/stylesheet.xsl"; //getting the xsl stylesheet
	 $xsl->load($xslfile) or die("Error Loading Document");//loading the stylesheet
	 $proc->importStylesheet($xsl) or die("errors"); 
	 $result = $proc->transformToXML($xml) or die("error"); //transform the xml 
	 print $result;	 //print the final results
	
}

 
