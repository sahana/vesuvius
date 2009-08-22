<?php

/* $Id: list.inc,v 1.10 2009-08-22 17:17:22 ravithb Exp $ */

/* $Id: list.inc,v 1.10 2009-08-22 17:17:22 ravithb Exp $ */

/**
 * 
 * List groups in disaster victims registry
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Isuru Samaraweera <isuru@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

 
function  _shn_dvr_list_all_groups()
{
   	
    global $global;
   	include_once ($global['approot'] . '/mod/dvr/data_access.inc');
    include_once ($global['approot'] . '/mod/dvr/lib.inc');
    $results=_shn_dvr_get_all_groups($_SESSION['dvr']['incident_id'],null);
   	
   ?>
   <br>
   	 <div id ="result">
	<table>
        <thead>
        		
            <td><?php echo _t("Group Type")?></td>
            <td><?php echo _t("Group Head Name")?></td>
            <td><?php echo _t("Family Name")?></td>
           <!-- <td><?php echo _t("Local Name")?></td>-->
          	<td><?php echo _t("NIC")?></td>
            <td><?php echo _t("Address")?></td>
            <td></td>
            
        </thead>
        <?php
        while(!$results->EOF)
        {
        ?>
        
        <tr>
        
        <td><?php echo _shn_dvr_getoptiondescription($results->fields['group_type'])?></td>
            
            <td><?php echo $results->fields['full_name']?></td>
            <td><?php echo $results->fields['family_name']?></td>
           <!-- <td><?php echo $results->fields['local_name']?></td>-->
          	<td><?php echo $results->fields['serial']?></td>
            <td><?php echo $results->fields['address']?></td>
            
            <td><a href='index.php?mod=dvr&act=view_members&groupid=<?php echo $results->fields['group_id']?>'>View Members</a></td>

        
        </tr>
 <?php
    $results->MoveNext();
        }
        ?>
        </table>
        </div>
   <?php
   }
   
   
   function _shn_dvr_list_all_individuals()
   {
   	
   ?>
   	 <div id ="result">
	<table>
        <thead>
        		<td></td>
            <td><?php echo _t("Group Type")?></td>
            <td><?php echo _t("Group Head Name")?></td>
            <td><?php echo _t("Family Name")?></td>
            <td><?php echo _t("Local Name")?></td>
          	<td><?php echo _t("NIC")?></td>
            <td><?php echo _t("Address")?></td>
         <td><a href='index.php?mod=dvr&act=add_new_indv'>Edit</a></td>
        </thead>
        </table>
        </div>
   <?php
   }
 

