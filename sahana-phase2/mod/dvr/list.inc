<?php

/* $Id: list.inc,v 1.7 2008-01-30 04:35:20 prabath321 Exp $ */

/* $Id: list.inc,v 1.7 2008-01-30 04:35:20 prabath321 Exp $ */

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

 
function  list_all_groups()
{
   	
    global $global;
   	include_once ($global['approot'] . '/mod/dvr/data_access.inc');
    include_once ($global['approot'] . '/mod/dvr/lib.inc');
    $results=_shn_dvr_get_all_groups($_SESSION['user_pref_ims_incident_id'],null);
   	
   ?>
   <br>
   	 <div id ="result">
	<table>
        <thead>
        		
            <td><?=_t("Group Type")?></td>
            <td><?=_t("Group Head Name")?></td>
            <td><?=_t("Family Name")?></td>
           <!-- <td><?=_t("Local Name")?></td>-->
          	<td><?=_t("NIC")?></td>
            <td><?=_t("Address")?></td>
            <td></td>
            
        </thead>
        <?php
        while(!$results->EOF)
        {
        ?>
        
        <tr>
        
        <td><?=_shn_dvr_getoptiondescription($results->fields['group_type'])?></td>
            
            <td><?=$results->fields['full_name']?></td>
            <td><?=$results->fields['family_name']?></td>
           <!-- <td><?=$results->fields['local_name']?></td>-->
          	<td><?=$results->fields['serial']?></td>
            <td><?=$results->fields['address']?></td>
            
            <td><a href='index.php?mod=dvr&act=view_members&groupid=<?=$results->fields['group_id']?>'>View Members</a></td>

        
        </tr>
 <?php
    $results->MoveNext();
        }
        ?>
        </table>
        </div>
   <?php
   }
   
   
   function list_all_individuals()
   {
   	
   ?>
   	 <div id ="result">
	<table>
        <thead>
        		<td></td>
            <td><?=_t("Group Type")?></td>
            <td><?=_t("Group Head Name")?></td>
            <td><?=_t("Family Name")?></td>
            <td><?=_t("Local Name")?></td>
          	<td><?=_t("NIC")?></td>
            <td><?=_t("Address")?></td>
         <td><a href='index.php?mod=dvr&act=add_new_indv'>Edit</a></td>
        </thead>
        </table>
        </div>
   <?php
   }
 
?>
