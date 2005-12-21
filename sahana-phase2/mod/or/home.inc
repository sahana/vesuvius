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

        <center><h2><b> Welcome to Organization Registry</b></h2></center>
		<div id="home">
<!--            <img src="theme/default/img/org.png"/>-->
            <p>Organization Registry does registration of Organizations and Volunteers while maintaining and displaying those information.
            </p>
             <p>This module maintains a database of organizations and services that are involved in managing/ supporting response/recovery in an occurrence of a disaster.</p> 
            <p><u><b>Facilities</b></u><br>
                <ul>
                    <li>Register and Manage organization information</li>
                    <li>Register and Manage organization operation information</li>
                    <li>Register and Manage Volunteer information</li>
                    <li>Provide reports and searching facilities on organizational information </li>
                </ul>
            </p>
		</div>
        <div id="left">
            <div id="heading">
                Organizations
            </div>
                <a href="index.php?mod=or&act=view_org">
                  <b> <?php echo $org_no ?></b>  Organizations have registered
                </a>
        </div>
        <div id="center">
            <div id="heading">
            Please register 
            </div>
 	Registering your organization allows us to know who is doing what where and allows us to operate more effectively as one.	    
	    </div>

        <div id="right">
            <div id="heading">
                Volunteers
            </div>
                 <a href="index.php?mod=or&act=view_vol">
                    <b><?php echo $vol_no?></b>  Volunteers have registered
                </a>
        </div>
              </br></br></br>
		<div id="display">
        <center>
            <h3>Last 10 Organizations to Register</h3>
            </center>
        </br>
<?php
        shn_or_viewform_allorg(10);
?>
		</div>
        </div>
