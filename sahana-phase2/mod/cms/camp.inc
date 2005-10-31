<?php
/* $Id; */

/**Camp library for  CMS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Chathra Hendehewa <chathra@opensource.lk>
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

//include yaml
include_once($global['approot'].'/3rd/spyc/spyc.php');

function _shn_cms_cadd_form(){
	global $global;
?>
<? echo "<h2>"._("Add New Camp")."</h2>"; ?>
<?
	$open_frm = array('method'=>"post",'action'=>"");
	shn_form_open($open_frm);


	$sections = Spyc::YAMLLoad($global['approot'].'/mod/cms/map.yml');
	foreach($sections as $k => $v){
		$array = Spyc::YAMLLoad($global['approot'].'/mod/cms/'.$v);
		//if($error)
		//  shn_form_add_component_list($array,true,$k,false,true);
		//else
		  shn_form_add_component_list($array,true,$k);
	}
	$subarray= array('type'=>'submit','name'=>'','value'=>'Create Camp');
	shn_form_add_component($subarray);	
	shn_form_close();
}

function _shn_cms_cadd_guide(){
	global $global;
	//attach guidelines;
	include($global['approot'].'/mod/cms/guide.inc');
?>
<form method='post' action=''>
 <input type='hidden' name='seq' value='chk'>
 <input type='submit' value='ACCEPT>>'>
</form>
<?
}

function _shn_cms_cadd_chk(){
	global $global;
	echo "<h2>"._("Camp Checklist")."</h2>";
	$open_frm = array('method'=>"post",'action'=>"");
	shn_form_open($open_frm);
	$category = _("Camp Checklist");
	$array = Spyc::YAMLLoad($global['approot'].'/mod/cms/chklst.yml');
	shn_form_add_component_list($array,true,$category);
	$subarray= array('type'=>'submit','name'=>'NEXT','value'=>'NEXT>>');
	shn_form_add_component($subarray);
	shn_form_close();
}

function _shn_cms_cedt(){
	global $global;
?>
<h2>Edit Existing Camp</h2>
<?
}

function _shn_cms_exit(){
	global $global;
?>
<h2>Camp Exit Procedure</h2>
<?
}
?>
