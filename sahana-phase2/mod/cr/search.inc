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

function _shn_cr_srch_rst($camp_name,$type){
		global $global;
		$db=$global['db'];
		?>
		<h1><center><?php echo _("Search Results")?></center></h1>
		<div id ="result">
    	<table>
        <thead>
        		<td><?php echo _("Camp Name")?></td>
            <td><?php echo _("Location")?></td>
            <td><?php echo _("Address")?></td>
         	<td><?php echo _("Camp Type")?></td>
            <td><?php echo _("No: of Males")?></td>
            <td><?php echo _("No: of Females")?></td>
            <td><?php echo _("No: of Children")?></td>
            <td><?php echo _("No: of Families")?></td>
            <td><?php echo _("Total Count")?></td>
        </thead>
        
        <tbody>
        
        <?php
       	if($_REQUEST['edt']=='true')
					$edt=true;
             /* Search for a given Camp Name with the matching for the specific Camp Type*/
	
			if($type != "all"){
					        	global $global;
								$db=$global['db'];

						if((!null==$camp_name) && (!null==$type)){
								
   					$q = "select * from camp_general where name='{$camp_name}'AND opt_camp_type='{$type}'";	
    		     		$res_cmp =$db->Execute($q);
						}
						else if((null==$camp_name) && (!null==$type)){
   					$q = "select * from camp_general where opt_camp_type='{$type}'";	
    		     		$res_cmp =$db->Execute($q);
						}
   	
   	           while (!$res_cmp->EOF){
   	           		$c_uuid  =$res_cmp->fields[0];   
   	           		 
   	           		$qdetails  = "select * from camp_reg where c_uuid='{$c_uuid}'";
   						$res_maincmp =$db->Execute($qdetails);
    						$loc  =$res_cmp->fields[2];   
    						$qloc = "select * from location where loc_uuid='{$loc}'";
    						$res_loc =$db->Execute($qloc);
    						$type  =$res_cmp->fields[3]; 
    						$qtype = "select * from field_options where option_code='{$type}'";
    						$res_type =$db->Execute($qtype);
    					
    		?> 
			<tr>
    				<td><a href="index.php?mod=cr&act=ecmp&seq=view&cmp_id=<?php echo $res_cmp->fields['c_uuid']?>">
						<?php echo $res_cmp->fields['name']?>&nbsp;</a><?php if($edt)?>
							<a href="index.php?mod=cr&act=ecmp&seq=disp&cmp_id=<?php echo $res_cmp->fields['c_uuid']?>">[<?php echo _("edit")?>]</a><?php ;?></td>
  					<td><?php echo $res_loc->fields['name']?></td>
  					<td><?php echo $res_cmp->fields['address']?></td>
  					<td><?php echo $res_type->fields['option_description']?></td>
  					<td><?php echo $res_maincmp->fields['men']?></td>
  					<td><?php echo $res_maincmp->fields['women']?></td>
  					<td><?php echo $res_maincmp->fields['children']?></td>
  					<td><?php echo $res_maincmp->fields['family']?></td>
  					<td><?php echo $res_maincmp->fields['total']?></td>
    		</tr>
    		<?php
    				$res_cmp->MoveNext();
   	  		   } 
   	  		   	 
   	  		   ?>
   </tbody>
   </table>
     </div>
  <?php
      
  }
  
  else
  {		global $global;
			$db=$global['db'];

			if($camp_name!=null)
   		$q = "select * from camp_general where name='{$camp_name}'";	
			else
   		$q = "select * from camp_general";	
   		 
   		     		$res_cmp =$db->Execute($q);
   	
   	           while (!$res_cmp->EOF){
   	           		$c_uuid  =$res_cmp->fields[0];     
   	           		$qdetails  = "select * from camp_reg where c_uuid='{$c_uuid}'";
   	           		
    						$res_maincmp =$db->Execute($qdetails);
    						$loc  =$res_cmp->fields[2];   
    						$qloc = "select * from location where loc_uuid='{$loc}'";
    						$res_loc =$db->Execute($qloc);
    						$type  =$res_cmp->fields[3]; 
    						$qtype = "select * from field_options where option_code='{$type}'";
    						$res_type =$db->Execute($qtype);
    					
    		?> 
			<tr>
    				<td><a href="index.php?mod=cr&act=ecmp&seq=view&cmp_id=<?php echo $res_cmp->fields[1]?>">
						<?php echo $res_cmp->fields[1]?>&nbsp;</a><?php if($edt)?><a href="index.php?mod=cr&act=ecmp&seq=d
						isp&cmp_id=<?php echo $res_cmp->fields[1]?>">[<?php echo _("edit")?>]</a></td>
  					
  					<td><?php echo $res_loc->fields['name']?></td>
  					<td><?php echo $res_cmp->fields['address']?></td>
  					<td><?php echo $res_type->fields['option_description']?></td>
  					<td><?php echo $res_maincmp->fields['men']?></td>
  					<td><?php echo $res_maincmp->fields['women']?></td>
  					<td><?php echo $res_maincmp->fields['children']?></td>
  					<td><?php echo $res_maincmp->fields['family']?></td>
  					<td><?php echo $res_maincmp->fields['total']?></td>
  					<!--
  					<td><?php echo $res_loc->fields[4]?></td>
  					<td><?php echo $res_cmp->fields[4]?></td>
  					<td><?php echo $res_type->fields[2]?></td>
  					<td><?php echo $res_maincmp->fields[9]?></td>
  					<td><?php echo $res_maincmp->fields[7]?></td>
  					<td><?php echo $res_maincmp->fields[8]?></td>
  					<td><?php echo $res_maincmp->fields[10]?></td>
  					<td><?php echo $res_maincmp->fields[11]?></td>
  					-->
    		</tr>
    		<?php
    				$res_cmp->MoveNext();
   	  		   } 
   	  		   	 
   	  		   ?>
   </tbody>
   </table>
        </div>
   <?php
  }
  
  
			
	}

/*The Form to handle the Search Functionality*/
	
function _shn_cr_srch($edit=false){		
?>
	 	  <h1><center><?=_("Search for a Camp")?></center></h1>
 <?php
			shn_form_fopen("srch");
			shn_form_fsopen(_("SEARCH"));
			shn_form_hidden(array('seq'=>'commit'));
			shn_form_text(_("Name of the Camp"),'cmp_id','size="20"');
 			?>
 			<br>		
			<?php
		   shn_form_opt_select("opt_camp_type",_("Camp Type"),null,array('all'=>true));
			 if($edit=='true')
			 	shn_form_hidden(array('edt'=>'true'));
		   shn_form_fsclose();
			shn_form_submit(_("Search"));
			shn_form_fclose();
				

}

?>

