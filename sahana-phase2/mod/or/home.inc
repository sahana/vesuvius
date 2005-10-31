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

<html>
    <head>	
        <center><h3><b> Welcome to Organization Registry</p><br></b></h3></center>
	</head>
    <body>
        <div>
            <h4>Organization Registry registers Organizations,Volunteers and maintain and display those information
            </h4>
        </div>
        <hr>
        </br></br></br>
        <center> 
            <div>
                <a href="index.php?mod=or&act=view_org">
                  <b> <?php echo $org_no ?></b>  Organizations have registered
                </a>
            </div>
        </center>
        </br>
        </br>
        <center>
            <div>
                 <a href="index.php?mod=or&act=view_vol">
                    <b><?php echo $vol_no?></b>  Volunteers have registered
                </a>
            </div>
        </center>
    </body>
</html>
