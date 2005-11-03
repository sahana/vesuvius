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

/*Displaying Results for the Search*/

function _shn_cr_srch_rst($camp_name){
		?>
		<div id ="result">
    	<h2>Search Results</h2>
    	<table>
        <thead>
        		<td>Camp Name</td>
            <td>Location</td>
            <td>Address</td>
         	<td>Camp Type</td>
            <td>No: of Families</td>
            <td>No: of Males</td>
            <td>No: of Females</td>
            <td>No: of Families</td>
            <td>Total Count</td>
        </thead>
        
        <tbody>
        <?php
        
         /* Search for a given Camp Name*/
         
			global $global;
			$db=$global['db'];
   		$q = "select * from camp where name='{$camp_name}'";	 
     		$res_cmp =$db->Execute($q);
   	
   	           while (!$res_cmp->EOF){
    						$c_uuid  =$res_cmp->fields[0];        
    						$qdetails  = "select * from camp where c_uuid='{$c_uuid}'";
    						$res_maincmp =$db->Execute($qdetails);
    						$loc  =$res_maincmp->fields[2];   
    						$qloc = "select * from location where location_id='{$loc}'";
    						$res_loc =$db->Execute($qloc);
    					
    		?> 
			<tr>
    				<td><?php echo $res_cmp->fields[1]?></td>
  					<td><?php echo $res_loc->fields[4]?></td>
  					<td><?php echo $res_maincmp->fields[4]?></td>
  					<td><?php echo $res_maincmp->fields[3]?></td>
  					<td><?php echo $res_cmp->fields[9]?></td>
  					<td><?php echo $res_cmp->fields[7]?></td>
  					<td><?php echo $res_cmp->fields[8]?></td>
  					<td><?php echo $res_cmp->fields[10]?></td>
  					<td><?php echo $res_cmp->fields[11]?></td>
    		</tr>
    		<?php
    				$res_cmp->MoveNext();
   	  		   } 
   	  		   	 
   	  		   ?>
   </tbody>
   </div>
   </table>
   <?php
	}

/*The Form to handle the Search Functionality*/
	
function _shn_cr_srch(){		
?>
	 	  <h2>Search for a Camp</h2>
 <?php
			shn_form_fopen("srch");
			shn_form_fsopen("SEARCH");
			shn_form_hidden(array('seq'=>'commit'));
			shn_form_text('Name of the Camp','cmp_id','size="20"');
 			?>
 			<br>		
			<?php
         shn_form_opt_select("opt_camp_type","Camp Type");
			shn_form_fsclose();
			shn_form_submit("Search");
			shn_form_fclose();
				

}

?>

