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

function _shn_cr_srch_rst($camp_name){
	//echo $camp_name;
	global $global;
	$db=$global['db'];
   $q = "select * from camp_reg where name='{$camp_name}'";
	 
    
    $res_cmp =$db->Execute($q);
    if(!$res_cmp->EOF){
    $cmp_id =$res_cmp->fields[0]; 
    $cmp_name=$res_cmp->fields[1];    
    $cmp_contact=$res_cmp->fields[3];
    $cmp_no=$res_cmp->fields[4];

  }
	
	echo $res_cmp->fields[0];
}

	
function _shn_cr_srch(){		
?>
	 	  <h2>Search for a Camp</h2>
 <?php
			shn_form_fopen("srch");
			shn_form_fsopen("SEARCH");
			shn_form_hidden(array('seq'=>'commit'));
			shn_form_text('Name of the Camp','cmp_id','size="20"');
 ?>
 <br>		<?php
         shn_form_opt_select("opt_location_type","Location Type");
			shn_form_fsclose();
			shn_form_submit("Search");
			shn_form_fclose();
			//get_all_location('opt_location_type');
			//get_all_location_names('opt_location_type');
			//get_all_location_parent('opt_location_type');
				

}

function get_all_location($loc_type){
		$sql = "SELECT location_id FROM location WHERE opt_location_type = $loc_type";	
		$rs  = mysql_query($sql) or die('Query failed: ' . mysql_error());
		
		while ($line = mysql_fetch_array($rs , MYSQL_ASSOC)) {
      foreach ($line as $col_value) {
       echo "$col_value";
      }
  }
mysql_free_result($rs);

}

function get_all_location_names($loc_type){
		$sql = "SELECT description FROM location WHERE opt_location_type = $loc_type";	
		$rs1  = mysql_query($sql) or die('Query failed: ' . mysql_error());
		
		while ($line = mysql_fetch_array($rs1 , MYSQL_ASSOC)) {
      foreach ($line as $col_value) {
       echo "$col_value";
      }
  }
mysql_free_result($rs1);

}
  
?>

