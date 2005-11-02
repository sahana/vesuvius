<?php

/**Search for  CR
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

include_once($global['approot'].'/inc/lib_form.inc');

function _shn_cr_rpt_rst(){

	global $global;
	$db=$global['db'];
  $q = "select * from camp_reg ";
	 
    
    $res_cmp =$db->Execute($q);
    if(!$res_cmp->EOF){
    $cmp_name =$res_cmp->fields[1]; 
    $cmp_services=$res_cmp->fields[6];    
    $cmp_men=$res_cmp->fields[7];
    $cmp_women=$res_cmp->fields[8];

  }
	
	echo  $res_cmp->fields[1];
	echo  $res_cmp->fields[6];
	echo  $res_cmp->fields[7];
	echo  $res_cmp->fields[8];

		 
}

	
function _shn_cr_rpt(){		
?>
	 	  <h2>Camp Information</h2>
 <?php
			shn_form_fopen("rpt");
			shn_form_fsopen("Report for all camps");
			shn_form_hidden(array('seq'=>'commit'));
			shn_form_fsclose();
			shn_form_submit("Generate Report");
			shn_form_fclose();
}

function _shn_cr_rpt_all(){
	echo "all";
}

function _shn_cr_rpt_loc(){
	echo "location";
}
  
?>

