#!/usr/bin/php
/**
* Description for file
* http://sahana.sourceforge.net
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana ASP
* @subpackage  
* @author     Pradeeper <pradeeper@opensource.lk>
*/
<?php
// handler_options.inc

include_once "config.inc";
include_once "lib_file.inc";

global $conf;

// This is to check the vars that use to collect user input
//function chk_usr_input($usr_base, $usr_doc_root, $usr_rel, $usr_inst)
function chk_base($usr_base)
{
	//global $conf;
	/*$x=$conf['doc_root'];
	echo "doc-root is ".$x."\n";
	$conf['doc_root']=null;*/
	//echo $usr_base;
	echo "checking\n";
	check_dir($usr_base);
	if($usr_base==null) echo "Hey! --base is null\n";	
}// end of chk_var


