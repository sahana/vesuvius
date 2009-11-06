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
include_once($global['approot'].'/inc/lib_paging.inc');


/*General Camp Reports- if required to be provided when the Reports Main Menu is clicked
--currently no link from that*/
function _shn_cr_rpt_rst(){

	global $global;
	$db=$global['db'];
	 $q = "select * FROM camp_reg ";
	 
    
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
   			echo "<h2>"._t("Reports")."</h2>";
	  
 
			shn_form_fopen("rpt");
			shn_form_fsopen(_t("Report for all Shelters"));
			shn_form_hidden(array('seq'=>'commit'));
			shn_form_fsclose();
			shn_form_submit(_t("Generate Report"));
			shn_form_fclose();
}



/** To retrieve all the camps that has been registered and display in a table format*/

function _shn_cr_rpt_all(){
    global $global;
    $db=$global['db'];
    $q = "select * FROM camp_reg ";
?>
    <h1><?php echo _t("Shelter Information")?></h1>
<?php
    //$res_cmp =$db->Execute($q);
    $res_cmp = shn_paging_get_report($q,10);
?>
<div id ="result">
   <table>
        <thead>
            <td><?php echo _t("Shelter Name")?></td>
            <td><?php echo _t("Shelter Type")?></td>
            <td><?php echo _t("Address")?></td> 
            <td><?php echo _t("Location")?></td>
            <!--<td><?php echo _t("No: of Families")?></td>-->
            <td><?php echo _t("No: of Males")?></td>
            <td><?php echo _t("No: of Females")?></td>
            <td><?php echo _t("No: of Children")?></td>
            <td><?php echo _t("Total Count")?></td>
        </thead>
        <tbody>
<?php    
    	while (!$res_cmp->EOF){
    	$c_uuid  =$res_cmp->fields['c_uuid'];        
    	$qdetails  = "SELECT * FROM camp_reg WHERE c_uuid='{$c_uuid}'";
    	$res_maincmp =$db->Execute($qdetails);

    	$qcamp = "SELECT * FROM camp_general WHERE c_uuid='{$c_uuid}'";
    	$res_camp =$db->Execute($qcamp);

    	$loc  =$res_camp->fields['location_id'];   
    	$qloc = "SELECT * FROM location WHERE loc_uuid='{$loc}'";
    	$res_loc =$db->Execute($qloc);
    						
    						$type  =$res_camp->fields['opt_camp_type']; 
    						$qtype = "SELECT * FROM field_options WHERE option_code='{$type}'";
    						$res_type =$db->Execute($qtype);
    						 
    						
    						
    				  				
					?>
    				<tr>
					<td><a href="index.php?mod=cr&act=ecmp&seq=view&cmp_id=<?php echo $res_camp->fields['c_uuid']?>"><?php echo $res_camp->fields['name']?></a></td>
					<td><?php echo $res_type->fields['option_description']?></td>
  					<td><?php echo $res_camp->fields['address']?></td>
  					<td><?php echo $res_loc->fields['name']?></td>
    				<!--<td><?php echo $res_cmp->fields['family']?></td>-->
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
<h1><?php echo _t("Shelter Information by Location")?></h1>
  <div id ="result">
	   <table>
		   <thead>
		     	<td><?php echo _t("Location")?></td>
					<td><?php echo _t("Total Number of Victims in Shelters")?></td>
			 </thead>
			 <tbody>
<?php
	global $global;
	$module = $global['module'];	
	$db=$global['db'];
	$q = "SELECT SUM(b.total), a.location_id FROM camp_general as a, camp_reg as b WHERE b.c_uuid=a.c_uuid group by a.location_id";
	$res_cmp = $db->Execute($q);
	while (!$res_cmp->EOF){
		$loc_id =$res_cmp->fields[1];
                $location=_shn_cr_location_string($loc_id);
		//$qloc  = "select name FROM location WHERE loc_uuid='{$loc_id}'";
		//$res_loc =$db->Execute($qloc);
?>
				<tr>
					<td><a href="index.php?mod=<?php echo $module?>&act=ldrpt&seq=<?php echo $loc_id?>">
<?php 
    echo $location;
?>

                                        </a></td>
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
<h1><center><?php echo _t("Shelter Information by Location Drilled")?></center></h1>
<?php
echo "<h3>"._t("Shelters in")." : "._shn_cr_location_string($locate)." </h3>";

?>
<div id ="result">
<table>
<thead>
<td><?php echo _t("Shelter Name")?> </td>
<td><?php echo _t("Shelter Type")?></td>
<td><?php echo _t("Address")?></td>
<td><?php echo _t("Total Victims")?></td>
</thead>

<tbody>

<?php    
global $global;
$db=$global['db'];

$q = "SELECT c_uuid,name,opt_camp_type,address,location_id FROM camp_general WHERE location_id='{$locate}'";
$res_cmp = $db->Execute($q);
while (!$res_cmp->EOF){
				
$loc_id =$res_cmp->fields[4];        
$qloc  = "SELECT * FROM location WHERE loc_uuid='{$loc_id}'order by loc_uuid";
$res_loc =$db->Execute($qloc);
								
$cmp_id =$res_cmp->fields[0];        
$qreg  = "SELECT total FROM camp_reg WHERE c_uuid='{$cmp_id}'";
$res_reg =$db->Execute($qreg);

$type  =$res_cmp->fields[2]; 
$qtype = "SELECT * FROM field_options WHERE option_code='{$type}'";
$res_type =$db->Execute($qtype);
								
?>
<tr>
  					<td><a href="index.php?mod=cr&act=ecmp&seq=view&cmp_id=<?php echo $cmp_id;?>"><?php echo $res_cmp->fields[1]?></a></td>
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


				global $global;
				$db=$global['db'];
				
				$query = "SELECT d.name, a.admin_name, a.admin_no, b.contact_value, c.occupation FROM camp_reg a left outer join camp_admin z USING (c_uuid) inner join contact b on b.pgoc_uuid = z.contact_puuid left outer join person_details c on c.p_uuid = b.pgoc_uuid inner join camp_general d on a.c_uuid = d.c_uuid WHERE b.opt_contact_type='cmob'";
				//$resc = $db->Execute($query);
                                $resc = shn_paging_get_report($query,10);
?>
	<div id = "result">
		  <table>
			  <thead>
			    <td><?php echo _t("Shelter Name")?> </td>
			    <td><?php echo _t("Admin Name")?></td>
			    <td><?php echo _t("Admin Phone")?></td>
			    <td><?php echo _t("Admin Mobile")?></td>
			    <td><?php echo _t("Admin Occupation")?></td>
			  </thead>
	      <tbody>
				<?php
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
						 $q = "SELECT c_uuid,name,opt_camp_type,address,location_id FROM camp";
						 $res_cmp = $db->Execute($q);
						while (!$res_cmp->EOF){
     	   								
    						$loc_id =$res_cmp->fields[4];        
    						$qloc  = "SELECT * FROM location WHERE loc_uuid='{$loc_id}'order by loc_uuid";
    						$res_loc =$db->Execute($qloc);
    						    						
    						$cmp_id =$res_cmp->fields[0];        
    						$qreg  = "SELECT total FROM camp_reg WHERE c_uuid='{$cmp_id}'";
    						$res_reg =$db->Execute($qreg);
    						
    						$type  =$res_cmp->fields[2]; 
    						$qtype = "SELECT * FROM field_options WHERE option_code='{$type}'";
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
      
    
function _shn_cr_location_string($loc)
{
	global $global;
	$db=$global["db"];
	$loc_arr=array();
	include_once $global['approot']."/inc/lib_location.inc";
   	shn_get_parents($loc,&$loc_arr);
        if($loc=="-1")
            return _t('Unspecified Location');
   	if($loc_arr[0]=='unknown'){

   	}else{
   		
   		$max=count($loc_arr)-1;
   		array_pop($loc_arr);
   		for($count=0;$count<$max;$count++){
   			$x=array_pop($loc_arr);
   			$q="SELECT name FROM location WHERE loc_uuid='{$x}'";
    			$res=$db->Execute($q);
    			if($count==0 ){
    				$location=$location.$res->Fields("name");
    			}else{
   				$location=$location." --> ".$res->Fields("name");
    			}
    			
   		}
   	}
   	return $location;
}
?>

