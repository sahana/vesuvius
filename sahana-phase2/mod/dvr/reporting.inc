<?php

/**
 * 
 * This file represents the reports  of the DVR module
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Isuru Samaraweera 
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
 
 
 
 
function _shn_dvr_drill_downby_group() {
?>	
 	 <h2><?php echo _t("Disaster Victim Report by group") ?></h2>
 	 
 	 <?php
 	 
    global $global;
   	include_once ($global['approot'] . '/mod/dvr/data_access.inc');
	include_once ($global['approot'] . '/mod/dvr/lib.inc');
	$incident_id=$_GET['incident_id'];
	$camp_id=$_GET['camp_id'];
	if($incident_id!=null)
	{
		$results=_shn_dvr_get_all_groups($incident_id,null);
	}
	else if($camp_id!=null)
	{
		$results=_shn_dvr_get_all_groups(null,$camp_id);
	}
    else
    {$results=_shn_dvr_get_all_groups(null);
    }
   ?>
   <br>
   	 <div id ="result">
	<table>
        <thead>
        	<!--  <td><?php echo _t("Group Id")?></td>-->
            <td><?php echo _t("Group Type")?></td>
            <td><?php echo _t("Group Head Name")?></td>
            <td><?php echo _t("Family Name")?></td>
           <!-- <td><?php echo _t("Local Name")?></td>-->
          	<td><?php echo _t("NIC")?></td>
            <td><?php echo _t("Address")?></td>
            
        </thead>
        <?php
        while(!$results->EOF)
        {
        ?>
        
        <tr>
           <!-- <td><a href='index.php?mod=dvr&act=view_members&groupid=<?php echo $results->fields['group_id']?>'><?php echo $results->fields['group_id']?></a></td>-->
        <td><?php echo _shn_dvr_getoptiondescription($results->fields['group_type'])?></td>
            
            <td><a href='index.php?mod=dvr&act=view_members&groupid=<?php echo $results->fields['group_id']?>'><?php echo $results->fields['full_name']?></a></td>
            <td><?php echo $results->fields['family_name']?></td>
           <!-- <td><?php echo $results->fields['local_name']?></td>-->
          	<td><?php echo $results->fields['serial']?></td>
            <td><?php echo $results->fields['address']?></td>
            
            

        
        </tr>
 <?php
    $results->MoveNext();
        }
        ?>
        </table>
        </div>
   <?php
   }
   
function _shn_dvr_drill_downby_shelter() 
{
    global $global;
   	include_once ($global['approot'] . '/mod/dvr/data_access.inc');
    $camps=_shn_dvr_get_camps();

?>
 	  <h2><?php echo _t("Disaster Victim Report by Shelter") ?></h2>
   	 <div id ="result">
	<table>
        <thead>
        		
            <!--<td><?php echo _t("Camp Id")?></td>-->
            <td><?php echo _t("Camp Name")?></td>
            <td><?php echo _t("Address")?></td>
            <td><?php echo _t("Capacity")?></td>
         
        </thead>
        
<?php
        while(!$camps->EOF)
{
	
?>
<tr>
	<!-- <td><a href='index.php?mod=dvr&act=drill_downby_group&camp_id=<?php echo  $camps->fields['c_uuid']?>'><?php echo  $camps->fields['c_uuid']?></a></td>-->
	<td><a href='index.php?mod=dvr&act=drill_downby_group&camp_id=<?php echo  $camps->fields['c_uuid']?>'><?php echo $camps->fields['name']?></td>
	<td><?php echo $camps->fields['address']?></td>
	<td><?php echo $camps->fields['capacity']?></td>
</tr>
<?php
    $camps->MoveNext();
}
?>        
        </table>
        </div>
   <?php



}

function _shn_dvr_drill_downby_incident() {
		 
    global $global;
   	include_once ($global['approot'] . '/mod/dvr/data_access.inc');
    $incidents=_shn_dvr_get_incidents();

?>
 	  <h2><?php echo _t("Disaster Victim Report by Incident") ?></h2>
   	 <div id ="result">
	<table>
        <thead>
        		
            <!-- <td><?php echo _t("Incident Id")?></td>-->
            <td><?php echo _t("Incident Name")?></td>
            
         
         
        </thead>
        
<?php
        while(!$incidents->EOF)
{
	
?>
<tr>
	<!-- <td><a href='index.php?mod=dvr&act=drill_downby_group&incident_id=<?php echo  $incidents->fields['incident_id']?>'><?php echo  $incidents->fields['incident_id']?></a></td>-->
	<td><a href='index.php?mod=dvr&act=drill_downby_group&incident_id=<?php echo  $incidents->fields['incident_id']?>'><?php echo $incidents->fields['name']?></td>
</tr>
<?php
    $incidents->MoveNext();
}
?>        
        </table>
        </div>
   <?php


}
