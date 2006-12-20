<?php
/* $id$ */

/**Pre-defined Reports for the Camps Registry 
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

/*General Camp Reports- if required to be provided when the Reports Main Menu is clicked
--currently no link from that*/
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
	 	  <h2>Reports</h2>
	  
 <?php
			shn_form_fopen("rpt");
			shn_form_fsopen(_("Report for all camps"));
			shn_form_hidden(array('seq'=>'commit'));
			shn_form_fsclose();
			shn_form_submit(_("Generate Report"));
			shn_form_fclose();
}



/** To retrieve all the camps that has been registered and display in a table format*/

function _shn_cr_rpt_all(){
	?>
	<h1><center><?=_("Camp Information")?></center></h1>
	<div id ="result">
   <table>
        <thead>
            <td><?=_("Camp Name")?></td>
            <td><?=_("Camp Type")?></td>
            <td><?=_("Address")?></td> 
            <td><?=_("Location")?></td>
            <td><?=_("No: of Families")?></td>
            <td><?=_("No: of Males")?></td>
            <td><?=_("No: of Females")?></td>
            <td><?=_("No: of Children")?></td>
            <td><?=_("Total Count")?></td>
            
        </thead>
        		<tbody>
				<?php    
   					 global $global;
						 $db=$global['db'];
 						 $q = "select * from camp_reg ";
	 
         			$res_cmp =$db->Execute($q);
    						while (!$res_cmp->EOF){
    						$c_uuid  =$res_cmp->fields['c_uuid'];        
    						$qdetails  = "select * from camp_reg where c_uuid='{$c_uuid}'";
    						$res_maincmp =$db->Execute($qdetails);
    						
    						$qcamp = "select * from camp_general where c_uuid='{$c_uuid}'";
    						$res_camp =$db->Execute($qcamp);
    						
    						$loc  =$res_camp->fields['location_id'];   
    						$qloc = "select * from location where loc_uuid='{$loc}'";
    						$res_loc =$db->Execute($qloc);
    						
    						$type  =$res_camp->fields['opt_camp_type']; 
    						$qtype = "select * from field_options where option_code='{$type}'";
    						$res_type =$db->Execute($qtype);
    						 
    						
    						
    				  				
					?>
    				<tr>
					<td><a href="index.php?mod=cr&act=ecmp&seq=view&cmp_id=<?php echo $res_camp->fields['name']?>"><?php echo $res_camp->fields['name']?></a></td>
					<td><?php echo $res_type->fields['option_description']?></td>
  					<td><?php echo $res_camp->fields['address']?></td>
  					<td><?php echo $res_loc->fields['name']?></td>
    				<td><?php echo $res_cmp->fields['family']?></td>
    				<td><?php echo $res_cmp->fields['men']?></td>
    				<td><?php echo $res_cmp->fields['women']?></td>
    				<td><?php echo $res_cmp->fields['children']?></td>
  					<td><?php echo $res_cmp->fields['total']?></td>
  					 					
    				</tr>
    				<?php
    				$res_cmp->MoveNext();
   	  		   } 	
			?>	    	    	    	
	  		</tbody>

     </table>
        </div>

    </table>
    </div>

<?php
}

function _shn_cr_drill_location(){
?>
<h1><center><?=_("Camp Information by Location")?></center></h1>
  <div id ="result">
	   <table>
		   <thead>
		     	<td><?=_("Location")?></td>
					<td><?=_("Total Number of Victims in Camps")?></td>
			 </thead>
			 <tbody>
<?php
	global $global;
	$module = $global['module'];	
	$db=$global['db'];
	$q = "select sum(b.total), a.location_id from camp_general as a, camp_reg as b where b.c_uuid=a.c_uuid group by a.location_id";
	$res_cmp = $db->Execute($q);
	while (!$res_cmp->EOF){
		$loc_id =$res_cmp->fields[1];
		$qloc  = "select name from location where loc_uuid='{$loc_id}'";
		$res_loc =$db->Execute($qloc);
?>
				<tr>
					<td><a href="index.php?mod=<?=$module?>&act=ldrpt&seq=<?php echo $res_loc->fields[0]?>"><?php echo $res_loc->fields[0]?></a></td>
					<td><?php echo $res_cmp->fields[0]?></td>
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

//To Display the camps based on the location

function _shn_cr_rpt_loc($locate){
?>
<h1><center><?=_("Camp Information by Location Drilled")?></center></h1>
<div id ="result">
<table>
<thead>
<td><?=_("Location")?></td>
<td><?=_("Camp Name")?> </td>
<td><?=_("Camp Type")?></td>
<td><?=_("Address")?></td>
<td><?=_("Total Victims")?></td>
</thead>

<tbody>

<?php    
global $global;
$db=$global['db'];
echo "<strong>"._("Camps in ").$locate." </strong>";

$loc_q = "select loc_uuid from location where name='{$locate}'";
$loc_r = $db->Execute($loc_q);
if(!$loc_r->EOF){
	$location_id=$loc_r->fields[0];
}

$q = "select c_uuid,name,opt_camp_type,address,location_id from camp_general where location_id='{$location_id}'";
$res_cmp = $db->Execute($q);
while (!$res_cmp->EOF){
				
$loc_id =$res_cmp->fields[4];        
$qloc  = "select * from location where loc_uuid='{$loc_id}'order by loc_uuid";
$res_loc =$db->Execute($qloc);
								
$cmp_id =$res_cmp->fields[0];        
$qreg  = "select total from camp_reg where c_uuid='{$cmp_id}'";
$res_reg =$db->Execute($qreg);

$type  =$res_cmp->fields[2]; 
$qtype = "select * from field_options where option_code='{$type}'";
$res_type =$db->Execute($qtype);
								
?>
<tr>
    				<td><?php echo $res_loc->fields['name']?></td>
  					<td><a href="index.php?mod=cr&act=ecmp&seq=view&cmp_id=<?php echo $res_cmp->fields[1]?>"><?php echo $res_cmp->fields[1]?></a></td>
  					<td><?php echo $res_type->fields[2]?></td>
  					<td><?php echo $res_cmp->fields['address']?></td>
  					<td><?php echo $res_reg->fields['total']?></td>
  					
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


function _shn_cr_contact(){

?>
	<div id = "result">
		  <table>
			  <thead>
			    <td><?=_("Camp Name")?> </td>
			    <td><?=_("Admin Name")?></td>
			    <td><?=_("Admin Phone")?></td>
			    <td><?=_("Admin Mobile")?></td>
			    <td><?=_("Admin Occupation")?></td>
			  </thead>
	      <tbody>
				<?php
				global $global;
				$db=$global['db'];
				
				$query = "select d.name, a.admin_name, a.admin_no, b.contact_value, c.occupation from camp_reg a left outer join camp_admin z USING (c_uuid) inner join contact b on b.pgoc_uuid = z.contact_puuid left outer join person_details c on c.p_uuid = b.pgoc_uuid inner join camp_general d on a.c_uuid = d.c_uuid where b.opt_contact_type='cmob'";
				$resc = $db->Execute($query);
				while (!$resc->EOF){
				?>
					<tr>
						<td><?php echo $resc->fields['name']?></td>
						<td><?php echo $resc->fields['admin_name']?></td>
						<td><?php echo $resc->fields['admin_no']?></td>
						<td><?php echo $resc->fields['contact_value']?></td>
						<td><?php echo $resc->fields['occupation']?></td>
					</tr>
					<?php 
							$resc->MoveNext();
				}
					?>
				</tbody>
			</table>
		</div>
<?php																																								 
}

function _shn_cr_rpt_summary(){
	?>
	<div id ="displaycr">
	<div id = "result">
    <table>
        <thead>
            <td>Camp Name </td>
            <td>Camp Type</td>
            <td>Location</td>
            <td>Total Victims</td>
         </thead>
        
        <tbody>
        
				<?php    
   					 global $global;
						 $db=$global['db'];
						 $q = "select c_uuid,name,opt_camp_type,address,location_id from camp";
						 $res_cmp = $db->Execute($q);
						while (!$res_cmp->EOF){
     	   								
    						$loc_id =$res_cmp->fields[4];        
    						$qloc  = "select * from location where loc_uuid='{$loc_id}'order by loc_uuid";
    						$res_loc =$db->Execute($qloc);
    						    						
    						$cmp_id =$res_cmp->fields[0];        
    						$qreg  = "select total from camp_reg where c_uuid='{$cmp_id}'";
    						$res_reg =$db->Execute($qreg);
    						
    						$type  =$res_cmp->fields[2]; 
    						$qtype = "select * from field_options where option_code='{$type}'";
    						$res_type =$db->Execute($qtype);
    		    					   				
    				?>
    				<tr>
    				<td><?php echo $res_cmp->fields[1]?></td>
  					<td><?php echo $res_type->fields[2]?></td>
  					<td><?php echo $res_loc->fields[4]?></td>
  					<td><?php echo $res_reg->fields[0]?></td>
  					
  					</tr>
  					<?php
    				$res_cmp->MoveNext();		
   	  		   } 	
   	  			?>	    	    	    	
	  		</tbody>
            </table>
       </div>
       </div>

      </table>
     </div>

      <?php
}
      
    
  
?>

