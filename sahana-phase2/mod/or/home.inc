<?php
/*
*
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra <ravindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/
include_once "view.inc";
global $global;
$db=$global["db"];
$q="select count(o_uuid) as cnt from org_main";
$res=$db->Execute($q);
if(!$res->EOF){
    $org_no=$res->fields[0];
}
$q="select count(person_uuid.p_uuid) as cnt from person_uuid,person_status where person_status.isReliefWorker=1 and person_status.p_uuid=person_uuid.p_uuid";
$res=$db->Execute($q);
if(!$res->EOF){
    $vol_no=$res->fields[0];
}

?>
		<div id="home">
        	<h2>Welcome to Organization Registry</h2>
			<div>Organization Registry does registration of Organizations and Volunteers while maintaining and displaying those information.
            </div>
            <div>This module maintains a database of organizations and services that are involved in managing/ supporting response/recovery in an occurrence of a disaster.
			</div>
			<br />
			<div>
				<strong>Facilities</strong>
                <div>
				<ul>
                    <li>Register and Manage organization information</li>
                    <li>Register and Manage organization operation information</li>
                    <li>Register and Manage Volunteer information</li>
                    <li>Provide reports and searching facilities on organizational information </li>
                </ul>
				</div>
			</div>
		</div>
        <br />
		<table>
        <thead>
        <td><strong>Organizations</strong></td>
        <td><strong>Please Register</strong></td>
        <td><strong>Volunteers</strong></td>
        </thead>
        <tbody>
        <tr>
			<td>
				<div>
                <a href="index.php?mod=or&act=view_org">
                  <strong> <?php echo $org_no ?></strong>  Organizations have registered
                </a>
				</div>
			</td>
			<td>
				<div>
					Registering your organization allows us to know who is doing what where and allows us to operate more effectively as one.	    
				</div>
			</td>
			<td>
			    <div>
				<a href="index.php?mod=or&act=view_vol">
                    <strong><?php echo $vol_no?></strong>  Volunteers have registered
                </a>
                </div>
            </td>
        </tr>
        </tbody>
        </table>
        <br />
        <div id="note">
           <strong> Last 10 Organizations to Register</strong>
        </div>
<?php
        shn_or_viewform_allorg(10);
?>
        
<?php
//        shn_or_viewform_allorg(10);
?>
