<?php
/**
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Sheran Corera (sheran@opensource.lk) 
 * @copyright  Lanka Software Foundation (http://www.opensource.lk)
 * @package    mod
 * @subpackage hr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function shn_hr_list_menu1_and_menu2($search=false,$menu2=false,$no_dta=false)
{
  global $global;
  global $conf;
  $db = $global['db'];

  include_once $global['approot'].'/inc/lib_errors.inc';

  $q = "SELECT family_head_create_uid,family_head_name,damaged_house_destruction_level,damaged_house_location FROM hr_family_head_details_table,hr_damaged_house_basic_details_table,hr_damaged_house_location_details_table WHERE hr_family_head_details_table.family_head_create_uid=hr_damaged_house_basic_details_table.damaged_house_basic_details_uid AND hr_damaged_house_basic_details_table.damaged_house_basic_details_uid=hr_damaged_house_location_details_table.damaged_house_location_uid ORDER BY family_head_create_uid";
  $search_name_q = "SELECT family_head_create_uid,family_head_name,damaged_house_destruction_level,damaged_house_location FROM hr_family_head_details_table,hr_damaged_house_basic_details_table,hr_damaged_house_location_details_table WHERE hr_family_head_details_table.family_head_create_uid=hr_damaged_house_basic_details_table.damaged_house_basic_details_uid AND hr_damaged_house_basic_details_table.damaged_house_basic_details_uid=hr_damaged_house_location_details_table.damaged_house_location_uid AND hr_family_head_details_table.family_head_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_name']}' ORDER BY family_head_create_uid";
  $search_uid_q = "SELECT family_head_create_uid,family_head_name,damaged_house_destruction_level,damaged_house_location FROM hr_family_head_details_table,hr_damaged_house_basic_details_table,hr_damaged_house_location_details_table WHERE hr_family_head_details_table.family_head_create_uid='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_uid']}' AND hr_family_head_details_table.family_head_create_uid=hr_damaged_house_basic_details_table.damaged_house_basic_details_uid AND hr_damaged_house_basic_details_table.damaged_house_basic_details_uid=hr_damaged_house_location_details_table.damaged_house_location_uid ORDER BY family_head_create_uid";
  $search_name_and_uid_q = "SELECT family_head_create_uid,family_head_name,damaged_house_destruction_level,damaged_house_location FROM hr_family_head_details_table,hr_damaged_house_basic_details_table,hr_damaged_house_location_details_table WHERE hr_family_head_details_table.family_head_create_uid='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_uid']}' AND hr_family_head_details_table.family_head_create_uid=hr_damaged_house_basic_details_table.damaged_house_basic_details_uid AND hr_damaged_house_basic_details_table.damaged_house_basic_details_uid=hr_damaged_house_location_details_table.damaged_house_location_uid AND hr_family_head_details_table.family_head_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_name']}' ORDER BY family_head_create_uid";
  $search_damaged_house_q = "SELECT family_head_create_uid,family_head_name,damaged_house_destruction_level,damaged_house_location FROM hr_family_head_details_table,hr_damaged_house_basic_details_table,hr_damaged_house_location_details_table WHERE hr_family_head_details_table.family_head_create_uid=hr_damaged_house_basic_details_table.damaged_house_basic_details_uid AND hr_damaged_house_basic_details_table.damaged_house_basic_details_uid=hr_damaged_house_location_details_table.damaged_house_location_uid AND hr_damaged_house_basic_details_table.damaged_house_destruction_level='{$_SESSION['hr']['search_hf']['primary_detail_search']['optn_dstrctn_lvl']}' ORDER BY family_head_create_uid";
  $search_esntl_q2 = "SELECT contact_value FROM contact WHERE contact.opt_contact_type='fhd_adrs' AND contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}'";
  $search_esntl_q3 = "SELECT contact_value FROM contact WHERE contact.opt_contact_type='fhd_pcd' AND contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}'";
  $search_esntl_q4 = "SELECT contact_value FROM contact WHERE contact.opt_contact_type='fhd_hm_phn' AND contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}'";
  $search_esntl_q5 = "SELECT contact_value FROM contact WHERE contact.opt_contact_type='fhd_mbl' AND contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}'";

 if($search==false)
  {
  		$res=$db->Execute($q);
  }
  else if(($_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_name']!='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_uid']=='')) 
  {
  		$res=$db->Execute($search_name_q);
  }	
  else if(($_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_uid']!='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_name']=='')) 
  {
  		$res=$db->Execute($search_uid_q);
  }
  else if(($_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_name']!='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_uid']!='')) 
  {
  		$res=$db->Execute($search_name_and_uid_q);
  }
  else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_name']=='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_uid']==''))&&($menu2==false))
  {
		add_error("Please fill one or more given field(s) in the Homeless Famil(ies) Primary Detail Search");
		$res=$db->Execute($q);
  }
  else
  {
		$res=$db->Execute($search_damaged_house_q);
  }	

  if((!$res->EOF)&&(!$res==NULL))
  {
?>
<div id ="result">
       <table>
       <thead>
           <td><?php echo _t("Head Of Family Unique ID")?></td>
           <td><?php echo _t("Head Of Family Name")?></td>
           <td><?php echo _t("Contact Information")?></td>
           <td><?php echo _t("Damaged House Destruction Level")?></td>
           <td><?php echo _t("Damaged House Location")?></td>
       </thead>
       <tbody> 
<?php

      while(!$res->EOF)
       {
       ?>

       <tr>
	        <td><?php echo  $res->fields[0]?></td> 
           	<td><?php echo  $res->fields[1]?>
			<br>
			<a href="index.php?mod=hr&act=add_to_session&edit_seq=edit_registered_hf&hf_uid=<?php echo $res->fields[0] ?>"><?php print ("Edit");?></a>
		</td>
 	<?php 
		$dstrctn_lvl = $res->fields[2];
		$hf_and_damaged_house_contact_uid="hf_and_damaged_house_contact_".$res->fields[0];

		
  		$search_esntl_q = "SELECT contact_value FROM contact WHERE contact.opt_contact_type='fhd_adrs' AND contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}'";
  		$search_esntl_q2 = "SELECT contact_value FROM contact WHERE contact.opt_contact_type='fhd_pcd' AND contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}'";
  		$search_esntl_q3 = "SELECT contact_value FROM contact WHERE contact.opt_contact_type='fhd_hm_phn' AND contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}'";
  		$search_esntl_q4 = "SELECT contact_value FROM contact WHERE contact.opt_contact_type='fhd_mbl' AND contact.pgoc_uuid='{$hf_and_damaged_house_contact_uid}'";
  		$q5 = "SELECT option_description FROM field_options WHERE option_code='$dstrctn_lvl'";


	    $res1=$db->Execute($search_esntl_q);
	    $res2=$db->Execute($search_esntl_q2);
	    $res3=$db->Execute($search_esntl_q3);
	    $res4=$db->Execute($search_esntl_q4);
	    $res5=$db->Execute($q5);

		if((!$res1==NULL)&&(!$res1->EOF)&&(!$res2==NULL)&&(!$res2->EOF)&&(!$res3==NULL)&&(!$res3->EOF)&&(!$res4==NULL)&&(!$res4->EOF))
		{
			if(($res1->fields[0]=="")&&($res2->fields[0]=="")&&($res3->fields[0]=="")&&($res4->fields[0]==""))
			{
			?>
				<td><?php echo "--Not Applicable--"?></td><?php
 			}
 			else
 			{?>
				<td>
       		 	<?php echo  $res1->fields[0]." ".$res2->fields[0]." ".$res3->fields[0]." ".$res4->fields[0]?>
				</td><?php
			}
		}
		if((!$res5==NULL)&&(!$res5->EOF))
		{?>
			<td><?php echo  $res5->fields[0];	
		}?>
		
				<br>
				<a href="index.php?mod=hr&act=add_to_session&edit_seq=edit_registered_damaged_house&damaged_house_uid=<?php echo $res->fields[0] ?>"><?php print ("Edit");?></a>
			</td>
			<?php if($res->fields[3]=="unknown"||$res->fields[3]=="-1")
			{?>
				<td><?php echo "--Location Unknown--"?></td><?php
			}
			else
			{?>
			<td><?php echo  _shn_org_location_string($res->fields[3])?></td><?php
			}?>
	
      </tr>

      <?php

      $res->MoveNext();

       }
  }
  else if($no_dta && $menu2) 
  { 
     ?><div id="note">
    <strong><?php echo _t("Please Add One Or More Damaged House(s) Before Starting To Search")?></strong>
    </div>
    <?php 
  }
  else if($no_dta) 
  { 
     ?><div id="note">
    <strong><?php echo _t("Please Add One Or More Homeless Family(ies) Before Starting To Search")?></strong>
    </div>
    <?php 
  }
  else if(!$menu2)
  { 
  	add_error("The search did not return any results");	
    ?><div id="note">
    <strong><?php echo _t("No Homeless Family(ies) Found")?></strong>
    </div>
    <?php
  }
  else
  { 
  	add_error("The search did not return any results");	
    ?><div id="note">
    <strong><?php echo _t("No Damaged House(s) Found")?></strong>
    </div>
    <?php
  }
	session_unset(); 
       ?>
  </tbody>
 </table>
</div>



<?php
}

function shn_hr_list_menu3($search=false,$no_dta=false,$assign_to_site=false)
{
       global $global;
       global $conf;
       $db = $global['db'];
       
       include_once $global['approot'].'/inc/lib_errors.inc';
       
       $q = "SELECT
contractor_level,contractor_name,contractor_uid,assign_site_to_contractor FROM hr_contractor_table,hr_assign_site_to_contractor_table WHERE hr_contractor_table.contractor_uid=hr_assign_site_to_contractor_table.assign_site_to_contractor_uid ORDER BY contractor_uid";
	   $search_contractor_level_q = "SELECT
contractor_level,contractor_name,contractor_uid,assign_site_to_contractor FROM hr_contractor_table,hr_assign_site_to_contractor_table WHERE hr_contractor_table.contractor_uid=hr_assign_site_to_contractor_table.assign_site_to_contractor_uid AND hr_contractor_table.contractor_level='{$_SESSION['hr']['search_hf']['primary_detail_search']['optn_contractor_level']}' ORDER BY contractor_uid";
	   $search_contractor_name_q = "SELECT
contractor_level,contractor_name,contractor_uid,assign_site_to_contractor FROM hr_contractor_table,hr_assign_site_to_contractor_table WHERE hr_contractor_table.contractor_uid=hr_assign_site_to_contractor_table.assign_site_to_contractor_uid AND hr_contractor_table.contractor_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_name']}' ORDER BY contractor_uid";
	   $search_contractor_uid_q = "SELECT
contractor_level,contractor_name,contractor_uid,assign_site_to_contractor FROM hr_contractor_table,hr_assign_site_to_contractor_table WHERE hr_contractor_table.contractor_uid=hr_assign_site_to_contractor_table.assign_site_to_contractor_uid AND hr_contractor_table.contractor_uid='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_uid']}' ORDER BY contractor_uid";
	   $search_contractor_name_and_contractor_level_q = "SELECT
contractor_level,contractor_name,contractor_uid,assign_site_to_contractor FROM hr_contractor_table,hr_assign_site_to_contractor_table WHERE hr_contractor_table.contractor_uid=hr_assign_site_to_contractor_table.assign_site_to_contractor_uid AND hr_contractor_table.contractor_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_name']}' AND hr_contractor_table.contractor_level='{$_SESSION['hr']['search_hf']['primary_detail_search']['optn_contractor_level']}' ORDER BY contractor_uid";
	   $search_contractor_name_and_contractor_uid_q = "SELECT
contractor_level,contractor_name,contractor_uid,assign_site_to_contractor FROM hr_contractor_table,hr_assign_site_to_contractor_table WHERE hr_contractor_table.contractor_uid=hr_assign_site_to_contractor_table.assign_site_to_contractor_uid AND hr_contractor_table.contractor_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_name']}' AND hr_contractor_table.contractor_uid='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_uid']}' ORDER BY contractor_uid";
	   $search_contractor_uid_and_contractor_level_q = "SELECT
contractor_level,contractor_name,contractor_uid,assign_site_to_contractor FROM hr_contractor_table,hr_assign_site_to_contractor_table WHERE hr_contractor_table.contractor_uid=hr_assign_site_to_contractor_table.assign_site_to_contractor_uid AND hr_contractor_table.contractor_uid='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_uid']}' AND hr_contractor_table.contractor_level='{$_SESSION['hr']['search_hf']['primary_detail_search']['optn_contractor_level']}' ORDER BY contractor_uid";
	   $search_contractor_uid_contractor_level_and_contractor_name_q = "SELECT
contractor_level,contractor_name,contractor_uid,assign_site_to_contractor FROM hr_contractor_table,hr_assign_site_to_contractor_table WHERE hr_contractor_table.contractor_uid=hr_assign_site_to_contractor_table.assign_site_to_contractor_uid AND hr_contractor_table.contractor_uid='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_uid']}' AND hr_contractor_table.contractor_level='{$_SESSION['hr']['search_hf']['primary_detail_search']['optn_contractor_level']}' AND hr_contractor_table.contractor_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_name']}' ORDER BY contractor_uid";
	   
	   
	   if($search==false) $res=$db->Execute($q);
	   else if((($_SESSION['hr']['search_hf']['primary_detail_search']['optn_contractor_level']!="nt_slctd")&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_name']==''))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_uid']=='')) $res=$db->Execute($search_contractor_level_q);
	   else if((($_SESSION['hr']['search_hf']['primary_detail_search']['optn_contractor_level']=="nt_slctd")&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_name']!=''))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_uid']=='')) $res=$db->Execute($search_contractor_name_q);
	   else if((($_SESSION['hr']['search_hf']['primary_detail_search']['optn_contractor_level']=="nt_slctd")&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_name']==''))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_uid']!='')) $res=$db->Execute($search_contractor_uid_q);   
	   else if((($_SESSION['hr']['search_hf']['primary_detail_search']['optn_contractor_level']=="nt_slctd")&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_name']!=''))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_uid']!='')) $res=$db->Execute($search_contractor_name_and_contractor_uid_q);   
	   else if((($_SESSION['hr']['search_hf']['primary_detail_search']['optn_contractor_level']!="nt_slctd")&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_name']!=''))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_uid']=='')) $res=$db->Execute($search_contractor_name_and_contractor_level_q);
	   else if((($_SESSION['hr']['search_hf']['primary_detail_search']['optn_contractor_level']!="nt_slctd")&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_name']==''))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_uid']!='')) $res=$db->Execute($search_contractor_uid_and_contractor_level_q);	   
	   else if((($_SESSION['hr']['search_hf']['primary_detail_search']['optn_contractor_level']!="nt_slctd")&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_name']!=''))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_uid']!='')) $res=$db->Execute($search_contractor_uid_contractor_level_and_contractor_name_q);
	   else 
	   {
	  		add_error("Please fill one or more given field(s) in the Contractor(s) Primary Detail Search");
			$res=$db->Execute($q); 	
	   }
  	   if((!$res->EOF)&&(!$res==NULL))
	   {
?>
<div id ="result">
       <table>
       <thead>
           <td><?php echo _t("Unique ID")?></td>
           <td><?php echo _t("Level")?></td>
           <td><?php echo _t("Name")?></td>
           <td><?php echo _t("Contact Information")?></td>
           <td><?php echo _t("Assigned Sites")?></td>
       </thead>
       <tbody>
<?php 

	$check_acl_q="select value from config where module_id='admin' and confkey='acl_base'";
    $check_acl_res=$db->Execute($check_acl_q);
    if($res->fields[0]=='installed') $count=1;
    else $count=0;
      while(!$res->EOF)
       { 
       ?>

       <tr>
	       <td><?php echo  $res->fields[2]?></td> 
 <?php 
$cntrctr_lvl = $res->fields[0];
$contractor_contact_uid="contractor_contact_".$res->fields[2];

  		$search_esntl_q = "SELECT contact_value FROM contact WHERE contact.opt_contact_type='cnt_adrs' AND contact.pgoc_uuid='{$contractor_contact_uid}'";
  		$search_esntl_q2 = "SELECT contact_value FROM contact WHERE contact.opt_contact_type='cnt_pcd' AND contact.pgoc_uuid='{$contractor_contact_uid}'";
  		$search_esntl_q3 = "SELECT contact_value FROM contact WHERE contact.opt_contact_type='cnt_hm_phn' AND contact.pgoc_uuid='{$contractor_contact_uid}'";
  		$search_esntl_q4 = "SELECT contact_value FROM contact WHERE contact.opt_contact_type='cnt_mbl' AND contact.pgoc_uuid='{$contractor_contact_uid}'";
		$q5 = "SELECT option_description FROM field_options WHERE option_code='$cntrctr_lvl'";

	    $res1=$db->Execute($search_esntl_q);
	    $res2=$db->Execute($search_esntl_q2);
	    $res3=$db->Execute($search_esntl_q3);
	    $res4=$db->Execute($search_esntl_q4);
	    $res5=$db->Execute($q5);

	if((!$res5==NULL)&&(!$res5->EOF))
	{?>
	       <td><?php echo  $res5->fields[0]?></td> 
  <?}?>
               <td><?php echo  $res->fields[1]?>
		<br>
	<?php if(!$assign_to_site)
		{?>
	<a href="index.php?mod=hr&act=add_to_session&edit_seq=edit_registered_contractor&contractor_uid=<?php echo $res->fields[2] ?>"><?php print ("Edit");?></a>
	      <?}?>
		</td>
		<?php
		if((!$res1==NULL)&&(!$res1->EOF)&&(!$res2==NULL)&&(!$res2->EOF)&&(!$res3==NULL)&&(!$res3->EOF)&&(!$res4==NULL)&&(!$res4->EOF))
		{
			if(($res1->fields[0]=="")&&($res2->fields[0]=="")&&($res3->fields[0]=="")&&($res4->fields[0]==""))
			{?>
				<td><?php echo "--Not Applicable--"?></td><?php
 			}
 			else
 			{?>
				<td>
       		 	<?php echo  $res1->fields[0]." ".$res2->fields[0]." ".$res3->fields[0]." ".$res4->fields[0]?>
				</td><?php
			}
		}

		if($assign_to_site) 
		{
			$assign_site_to_contractor_string = array();
			$assign_site_to_contractor_string = explode(",",$res->fields[3]);
			$_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['optn_unq_site_name']=$assign_site_to_contractor_string;
		?>
	       <td>
		<?php $extra_opts['value']=$_SESSION['hr']['reg_new_contractor']['assign_site_to_contractor']['optn_unq_site_name'];
    		$extra_opts['req']=false;
    		?>
    		<form action="add_to_session">
    		<?php
    		
    		shn_form_opt_multi_select('optn_unq_site_name','&nbsp','multiple="true" id="x"',$extra_opts);
	        ?>
	        </form>
	<a href="index.php?mod=hr&act=add_to_session&edit_seq=assign_to_site&contractor_uid=<?php echo $res->fields[2] ?>" onClick=" javascript: return sbmt_assign_site_to_contractor(<?php echo $count?>,'<?php echo $res->fields[2]?>')" ><?php print ("Edit");?></a>
		</td> 
		<?php
		}
		else
 		{
 			$assign_site_to_contractor_string = array();
			$assign_site_to_contractor_string = explode(",",$res->fields[3]);
			$assign_site_to_contractor_string_rslt="";
			for($i=0;$i<count($assign_site_to_contractor_string);$i++)
			{
				$q3 = "SELECT option_description FROM field_options WHERE option_code='$assign_site_to_contractor_string[$i]' AND field_name='optn_unq_site_name'";
	       		$res3=$db->Execute($q3);
	       		$assign_site_to_contractor_string_rslt=$assign_site_to_contractor_string_rslt.$res3->fields[0].",".'<br />';
	       	}
	       	$assign_site_to_contractor_string_rslt=substr($assign_site_to_contractor_string_rslt, 0, -7);
			if ($assign_site_to_contractor_string_rslt=="") $assign_site_to_contractor_string_rslt="--None Assigned--";
 			?>
			<td>
       		 <?php echo  $assign_site_to_contractor_string_rslt?>
			</td><?php
		}?>
      </tr>

      <?php

      $count++;
      $res->MoveNext();

       }
  }
  else if($no_dta) 
  { 
     ?><div id="note">
    <strong><?php echo _t("Please Add One Or More Contractor(s) Before Starting To Search")?></strong>
    </div>
    <?php 
  }
  else 
  {
  	 add_error("The search did not return any results");
    ?><div id="note">
    <strong><?php echo _t("No Contractor(s) Found")?></strong>
    </div>
    <?php
  }
	session_unset(); 
       ?>
  </tbody>
 </table>
</div>



<?php
}

function shn_hr_list_menu4($search=false,$no_dta=false,$assign_contractor=false)
{
       global $global;
       global $conf;
       $db = $global['db'];
       
       include_once $global['approot'].'/inc/lib_errors.inc';
       
       $q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid ORDER BY site_uid";
       $search_site_name_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_name_and_uid_table.site_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']}' ORDER BY site_uid";
       $search_site_uid_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_name_and_uid_table.site_uid='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']}' ORDER BY site_uid";
       $search_site_allocated_organization_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_allocated_organization_table.site_allocated_organization='{$_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']}' ORDER BY site_uid";
	   $search_site_main_coordinator_name_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']}' ORDER BY site_uid";
	   $search_site_name_and_site_uid_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_name_and_uid_table.site_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']}' AND hr_site_name_and_uid_table.site_uid='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']}' ORDER BY site_uid";
       $search_site_name_and_site_allocated_organization_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_name_and_uid_table.site_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']}' AND hr_site_allocated_organization_table.site_allocated_organization='{$_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']}' ORDER BY site_uid";
       $search_site_name_and_site_main_coordinator_name_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_name_and_uid_table.site_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']}' AND hr_site_main_coordinator_details_table.site_main_coordinator_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']}' ORDER BY site_uid";
	   $search_site_uid_and_site_allocated_organization_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_name_and_uid_table.site_uid='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']}' AND hr_site_allocated_organization_table.site_allocated_organization='{$_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']}' ORDER BY site_uid";
	   $search_site_uid_and_site_main_coordinator_name_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_name_and_uid_table.site_uid='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']}' AND hr_site_main_coordinator_details_table.site_main_coordinator_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']}' ORDER BY site_uid";
       $search_site_allocated_organization_and_site_main_coordinator_name_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_allocated_organization_table.site_allocated_organization='{$_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']} AND hr_site_main_coordinator_details_table.site_main_coordinator_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']} ORDER BY site_uid";
	   $search_site_name_and_site_uid_and_site_allocated_organization_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_name_and_uid_table.site_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']}' AND hr_site_name_and_uid_table.site_uid='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']}' AND hr_site_allocated_organization_table.site_allocated_organization='{$_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']}' ORDER BY site_uid";
	   $search_site_name_and_site_uid_and_site_main_coordinator_name_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_name_and_uid_table.site_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']}' AND hr_site_name_and_uid_table.site_uid='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']}' AND hr_site_main_coordinator_details_table.site_main_coordinator_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']}' ORDER BY site_uid";
	   $search_site_name_and_site_main_coordinator_name_and_site_allocated_organization_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_name_and_uid_table.site_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']}' AND hr_site_main_coordinator_details_table.site_main_coordinator_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']}' AND hr_site_allocated_organization_table.site_allocated_organization='{$_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']}' ORDER BY site_uid";
	   $search_site_uid_and_site_main_coordinator_name_and_site_allocated_organization_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_name_and_uid_table.site_uid='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']}' AND hr_site_main_coordinator_details_table.site_main_coordinator_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']}' AND hr_site_allocated_organization_table.site_allocated_organization='{$_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']}' ORDER BY site_uid";
	   $search_site_name_and_site_uid_and_site_main_coordinator_name_and_site_allocated_organization_q = "SELECT
site_name,site_uid,site_allocated_organization,assign_contractor_to_site,site_main_coordinator_name,planned_houses,constructed_houses,vacant_houses,road,water,electricity,telephone_or_communication,sewer,site_location FROM hr_site_name_and_uid_table,hr_site_allocated_organization_table,hr_site_main_coordinator_details_table,hr_site_house_details_table,hr_site_infrastructure_details_table,hr_site_location_details_table,hr_assign_contractor_to_site_table WHERE hr_site_name_and_uid_table.site_uid=hr_site_allocated_organization_table.site_allocated_organization_uid AND hr_site_allocated_organization_table.site_allocated_organization_uid=hr_site_main_coordinator_details_table.site_main_coordinator_details_uid AND hr_site_main_coordinator_details_table.site_main_coordinator_details_uid=hr_site_house_details_table.site_house_details_uid AND hr_site_house_details_table.site_house_details_uid=hr_site_infrastructure_details_table.site_infrastructure_details_uid AND hr_site_infrastructure_details_table.site_infrastructure_details_uid=hr_site_location_details_table.site_location_uid AND hr_site_location_details_table.site_location_uid=hr_assign_contractor_to_site_table.assign_contractor_to_site_uid AND hr_site_name_and_uid_table.site_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']}' AND hr_site_name_and_uid_table.site_uid='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']}' AND hr_site_main_coordinator_details_table.site_main_coordinator_name='{$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']}' AND hr_site_allocated_organization_table.site_allocated_organization='{$_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']}' ORDER BY site_uid";


		if($search==false) $res=$db->Execute($q);
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']!='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']==''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']=='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']=='')) $res=$db->Execute($search_site_name_q);
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']=='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']!=''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']=='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']=='')) $res=$db->Execute($search_site_uid_q);
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']=='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']==''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']!='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']=='')) $res=$db->Execute($search_site_allocated_organization_q);
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']=='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']==''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']=='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']!='')) $res=$db->Execute($search_site_main_coordinator_name_q);
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']!='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']!=''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']=='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']=='')) $res=$db->Execute($search_site_name_and_site_uid_q);
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']!='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']==''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']!='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']=='')) $res=$db->Execute($search_site_name_and_site_allocated_organization_q);
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']!='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']==''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']=='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']!='')) $res=$db->Execute($search_site_name_and_site_main_coordinator_name_q);
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']=='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']!=''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']!='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']=='')) $res=$db->Execute($search_site_uid_and_site_allocated_organization_q);
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']=='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']!=''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']=='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']!='')) $res=$db->Execute($search_site_uid_and_site_main_coordinator_name_q);
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']=='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']==''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']!='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']!='')) $res=$db->Execute($search_site_allocated_organization_and_site_main_coordinator_name_q);
		
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']!='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']!=''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']!='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']=='')) $res=$db->Execute($search_site_name_and_site_uid_and_site_allocated_organization_q);
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']!='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']!=''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']=='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']!='')) $res=$db->Execute($search_site_name_and_site_uid_and_site_main_coordinator_name_q);
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']!='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']==''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']!='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']!='')) $res=$db->Execute($search_site_name_and_site_main_coordinator_name_and_site_allocated_organization_q );
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']=='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']!=''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']!='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']!='')) $res=$db->Execute($search_site_uid_and_site_main_coordinator_name_and_site_allocated_organization_q);
		else if((($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name']!='')&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid']!=''))&&(($_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization']!='nt_slctd'))&&($_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name']!='')) $res=$db->Execute($search_site_name_and_site_uid_and_site_main_coordinator_name_and_site_allocated_organization_q);
		else 
		{
			add_error("Please fill one or more given field(s) in the Site(s) Primary Detail Search");
			$res=$db->Execute($q); 	
		}
  	   if((!$res->EOF)&&(!$res==NULL))
	   {
?>
<div id ="result">
       <table>
       <thead>
           <td><?php echo _t("Unique ID")?></td>
           <td><?php echo _t("Site Name")?></td>
           <td><?php echo _t("Allocated Organization")?></td>
           <td><?php echo _t("Assigned Contractors")?></td>
           <td><?php echo _t("Main Coordinator")?></td>
           <td><?php echo _t("Planned / Constructed / Vacant Houses")?></td>
           <td><?php echo _t("Infrastructure")?></td>
           <td><?php echo _t("Location")?></td>
       </thead>
       <tbody>
<?php
	$check_acl_q="select value from config where module_id='admin' and confkey='acl_base'";
    $check_acl_res=$db->Execute($check_acl_q);
    if($res->fields[0]=='installed') $count=1;
    else $count=0;
      while(!$res->EOF)
       {
       ?>

       <tr>
	       <td><?php echo  $res->fields[1]?>
	       <td><?php echo  $res->fields[0]?>
		<br>
		<?php if(!$assign_contractor) 
		{ ?> 
			<a href="index.php?mod=hr&act=add_to_session&edit_seq=edit_registered_st&site_uid=<?php echo $res->fields[1] ?>"><?php print ("Edit");?></a>
		<?}?>
		</td> 
 <?php 
$site_allocated_organization = $res->fields[2];
$q2 = "SELECT option_description FROM field_options WHERE option_code='$site_allocated_organization'";
	       $res2=$db->Execute($q2);
?>   
               <td><?php echo  $res2->fields[0]?>
<?php
		if($assign_contractor) 
		{
			$assign_contractor_to_site_string = array();
			$assign_contractor_to_site_string = explode(",",$res->fields[3]);
			$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['optn_unq_contractor_name']=$assign_contractor_to_site_string;
		?>
	       <td>
   		<form action="add_to_session">
		<?php     
    $extra_opts['value']=$_SESSION['hr']['reg_new_site']['assign_contractor_to_site']['optn_unq_contractor_name'];
    $extra_opts['req']=false;
    shn_form_opt_multi_select('optn_unq_contractor_name','&nbsp','multiple="true" id="x"',$extra_opts);
		?> 
		</form>
	<a href="index.php?mod=hr&act=add_to_session&edit_seq=assign_contractor&site_uid=<?php echo $res->fields[1] ?>" onClick=" javascript: return sbmt_assign_contractor_to_site(<?php echo $count?>,'<?php echo $res->fields[1]?>')" ><?php print ("Edit");?></a>
		</td> 
		<?}
		else
 		{
 			$assign_contractor_to_site_string = array();
			$assign_contractor_to_site_string = explode(",",$res->fields[3]);
			$assign_contractor_to_site_string_rslt="";
			for($i=0;$i<count($assign_contractor_to_site_string);$i++)
			{
				$q3 = "SELECT option_description FROM field_options WHERE option_code='$assign_contractor_to_site_string[$i]' AND field_name='optn_unq_contractor_name'";
	       		$res3=$db->Execute($q3);
	       		$assign_contractor_to_site_string_rslt=$assign_contractor_to_site_string_rslt.$res3->fields[0].",".'<br />';
	       	}
	       	$assign_contractor_to_site_string_rslt=substr($assign_contractor_to_site_string_rslt, 0, -7);
	       	if ($assign_contractor_to_site_string_rslt=="") $assign_contractor_to_site_string_rslt="--None Assigned--";
 			?>
 			
			<td>
        		<?php echo  $assign_contractor_to_site_string_rslt?>
			</td> <?php
		}?>


	       <td><?php echo  $res->fields[4]?></td> 
		<?php 
		if(($res->fields[5]=="")&&($res->fields[6]=="")&&($res->fields[7]==""))
		{?>
			<td><?php echo "--Not Applicable--"?></td><?php
		}
		else
		{
			if($res->fields[5]=="") $res->fields[5]="--Not Applicable--";
			if($res->fields[6]=="") $res->fields[6]="--Not Applicable--";
			if($res->fields[7]=="") $res->fields[7]="--Not Applicable--"; 
		?> 
        	<td><?php echo  $res->fields[5]." / ".$res->fields[6]." / ".$res->fields[7]?></td><?php
        }?>
 <?php 
$infrastructure_str1="";
if(($res->fields[8]=="nt_slctd")&&($res->fields[9]=="nt_slctd")&&($res->fields[10]=="nt_slctd")&&($res->fields[11]=="nt_slctd")&&($res->fields[12]=="nt_slctd")) $infrastructure_str2="--Not Applicable--"; 
else if(($res->fields[8]=="no")&&($res->fields[9]=="no")&&($res->fields[10]=="no")&&($res->fields[11]=="no")&&($res->fields[12]=="no"))$infrastructure_str2="--None Available--";
else if(($res->fields[8]!="ys")&&($res->fields[9]!="ys")&&($res->fields[10]!="ys")&&($res->fields[11]!="ys")&&($res->fields[12]!="ys"))$infrastructure_str2="--N/A--";
else
{ 
	if($res->fields[8]=="ys") $infrastructure_str1 .= "Road".", ";
	if($res->fields[9]=="ys") $infrastructure_str1 .= "Water".", ";
	if($res->fields[10]=="ys") $infrastructure_str1 .= "Electricity".", ";
	if($res->fields[11]=="ys") $infrastructure_str1 .= "Telephone / Communication".", ";
	if($res->fields[12]=="ys") $infrastructure_str1 .= "Sewer".", ";
	$infrastructure_str2=substr($infrastructure_str1,0,-2);
}
?>
	       <td><?php echo  $infrastructure_str2?></td> 
	       	<?php if($res->fields[13]=="unknown"||$res->fields[13]=="-1")
			{?>
				<td><?php echo "--Location Unknown--"?></td><?php
			}
			else
			{?>
				<td><?php echo  _shn_org_location_string($res->fields[13])?></td><?php
			}?>
      </tr>

      <?php

      $count++;
      $res->MoveNext();

       }
  }
  else if($no_dta) 
  { 
     ?><div id="note">
    <strong><?php echo _t("Please Add One Or More Site(s) Before Starting To Search")?></strong>
    </div>
    <?php 
  }
  else 
  {
     add_error("The search did not return any results");
     ?><div id="note">
    <strong><?php echo _t("No Site(s) Found")?></strong>
    </div>
    <?php 	
  }	
	session_unset(); 
       ?>
  </tbody>
 </table>
</div>



<?php
}

?>


<script language="JavaScript">
function sbmt_assign_site_to_contractor(count,uid)
{ 
	count=count+2;//MAKE THIS 2 IF NO ACL BASE!!! IN THE LINUX IT's 2 :) THIS IS FIXED!! E NEW QUERY SHOULD WORK!!
	var slctd_string="";
	
	for(i=0;i<document.forms[count].x.options.length;i++)
	{
		if(document.forms[count].x.options[i].selected)
		{
			slctd_string+=document.forms[count].x.options[i].value+",";
		}
	}
	
	slctd_string=slctd_string.substring(0,slctd_string.length-1);
	window.location="index.php?mod=hr&act=add_to_session&edit_seq=assign_to_site&contractor_uid="+uid+"&slctd_string="+slctd_string;
	return false;
}

function sbmt_assign_contractor_to_site(count,uid)
{
	count=count+2;//MAKE THIS 2 IF NO ACL BASE!!! IN THE LINUX IT's 2 :) THIS IS FIXED E NEW QUERY SHOULD WORK
	var slctd_string="";

	for(i=0;i<document.forms[count].x.options.length;i++)
	{
		if(document.forms[count].x.options[i].selected)
		{
			slctd_string+=document.forms[count].x.options[i].value+",";
		}
	}
	
	slctd_string=slctd_string.substring(0,slctd_string.length-1);
	window.location="index.php?mod=hr&act=add_to_session&edit_seq=assign_contractor&site_uid="+uid+"&slctd_string="+slctd_string;
	return false;
}
</script>

