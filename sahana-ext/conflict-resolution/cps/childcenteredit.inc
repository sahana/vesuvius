<script language='JavaScript'>
function confirmdelete(center_code)
{
return confirm('This record for center code'+center_code+' will be permanently deleted');
}
</script>
<?php
/* $Id; */

/**Update functions for  CPS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Isuru Samaraweera
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_validate.inc');
include_once($global['approot'].'/inc/lib_errors.inc');

function _shn_cps_print(){
global $conf;
$server= $conf['servername'] ;
$center=$_POST['center_code'];
$centername=$_POST['center_name'];
$date=$_POST['date'];
$filed_by=$_POST['filed_by'];
$func=$_POST['func'];

$text="1=$center&2=$centername&3=$date&4=$filed_by&5=$func";
?>
<a href="http://<?php print $server?>/sahana-phase2/mod/cps/print_child_center_data_excel.php?<?php print $text?>">View in Excel to Print</a>
<?php
}

function  _shn_cps_cedt_start($errors=false){
	if($errors)
	display_errors();
	global $global;
	$db = $global['db'];
?>
<h2>Update Existing ChildCenters</h2>
<?php
$module = $global['module'];
$center_name=$_POST['center_name'];
$recordCount=  _shn_cps_get_session($center_name);
$childcenterdata=$_SESSION['childcenterdata'];	
if($recordCount>0){
shn_form_fopen("edtchildcenter",null);
shn_form_fsopen('Child Center Details');
?>	
<table border="1" width=100% scrolling=true>
<th>Code</th><th>Name</th><th>Date</th><th>Filedby</th><th>Function</th><th>Dofreg</th>
<th>Reporters Name</th><th>Edit</th><th>Delete</th>

<?php 
for($k=0;$k<$recordCount;$k++){
?>
<tr><td ><?php print $childcenterdata[$k][0] ?></td><td><?php print  $childcenterdata[$k][1] ?></td><td><?php print  $childcenterdata[$k][2] ?></td><td><?php print  $childcenterdata[$k][3] ?></td><td><?php print  $childcenterdata[$k][4] ?></td><td><?php print  $childcenterdata[$k][5] ?></td><td><?php print  $childcenterdata[$k][6] ?></td><td><a href='index.php?mod=<?php print $module ?>&act=edtchildcenter&seq=cedt<?php print $childcenterdata[$k][0]?>' >Edit</a></td><td><a href='index.php?mod=<?php print $module ?>&act=edtchildcenter&seq=cdel<?php print $childcenterdata[$k][0]?>' onClick="javascript: return confirmdelete('<?php print $childcenterdata[$k][0]?>')">Delete</a></td></tr>
<?php
}
?>
</table>
<?php
shn_form_fsclose();
shn_form_fclose(); 
}
else
print 'Record Not Found for child center  '.$center_name.' Please insert the details using left navigation menu';
}


function  _shn_cps_cedt_showform($errors=false,$centercode){
	if($errors)
	display_errors();
 	global $global;
	$db = $global['db'];
?>
<h2>Update Existing ChildCenter</h2>

<?php
      
$centerdetails=  _shn_cps_get_centerdata($centercode);
//again storing from the db for the latest data


if(count($centerdetails)==5){
  //-----------------------------------------
   shn_form_fopen("edtchildcenter",null);
   shn_form_hidden(array('seq'=>'chck'));
   shn_form_fsopen('Initial Details');
   shn_form_text('Center','center_code','size="30"',array('value'=>$centerdetails[0],'req'=>true));
   shn_form_text('Center Name','center_name','size="30"',array('value'=>$centerdetails[1],'req'=>true));
   shn_form_text('Date','date','size="30"',array('value'=>$centerdetails[2]));
   shn_form_text('Filed by','filed_by','size="30"',array('value'=>$centerdetails[3]));
   shn_form_text('Function','function','size="30"',array('value'=>$centerdetails[4]));
   //shn_form_text('Date of first Registration','date_regd','size="30"',array('value'=>$centerdetails[5]));
 shn_form_fsclose();
 shn_form_submit('Update');
}

else 
print 'Record Deleted by another user for child center  '.$center_name.' Please insert the details using left navigation menu';
}



function _shn_cps_cedt_chk($errors=false){
  if($errors)
	display_errors;
	global $global;
 //todo remove session variables
	$_SESSION['center_code']=$_POST['center_code'];
	$_SESSION['center_name']=$_POST['center_name'];
	$_SESSION['date']=$_POST['date'];
	$_SESSION['filed_by']=$_POST['filed_by'];
	$_SESSION['function']=$_POST['function'];
}

function _shn_cps_cdel_childcenter($center_code){
global $global;
$module = $global['module'];
$db = $global['db'];
$query="delete  from child_center  where  center_code='{$center_code}'";
$queryf="delete from  field_options where option_code='{$center_code}'";
$res = $db->Execute($query);
$resf=$db->Execute($queryf);
if($res==false | resf==false){
$result=$db->ErrorMsg();
print 'error is'.$result;
}
else{
?>
<h2>You Have Succesfully  deleted the  Details of"<?=$_SESSION['center_name']?>"</h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue  </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildcenter&seq=disp'>
View All Child Centers</a>
<?php
}
}

    
function _shn_cps_cedt_commit(){
_shn_cps_cedt_chk();
_shn_cps_cedt_commit_db();
}


function _shn_cps_search_edt_frm(){
?><h2 align="center">Edit Existing ChildCenter</h2><?php
	shn_form_fopen("edtchildcenter");
	shn_form_fsopen("Edit ChildCenter");
	shn_form_hidden(array('seq'=>'disp'));
	shn_form_text('Name of the Center ','center_name','size="20"');
 	shn_form_fsclose();
	shn_form_submit("Search");
	shn_form_fclose();
}



function _shn_cps_validate_error(){
clean_errors();
$error_flag=false;
$center=$_POST['center_code'];
$centername=$_POST['center_name'];
$rep_full_name=$_POST['rep_full_name'];
$rep_relation=$_POST['rep_relation'];
$date=$_POST['date'];
$dor=$_POST['date_regd'];
$rep_address=$_POST['rep_address'];
$rep_phone=$_POST['rep_phone'];
$rep_email=$_POST['rep_email'];
if(trim($center)==''){
add_error(_("Please enter the center code"));

$error_flag=true;
 }


if(trim($centername)=='')
{
add_error(_("Please enter the center name"));
$error_flag=true;
}

if(trim($date)=='' | trim($date)==null )
{
add_error(_("Please enter the date"));
$error_flag=true;

}
else
{
if(!shn_valid_date(trim($date)))
{
add_error(_("Please Check the date Format "));
$error_flag=true;
}
}
return $error_flag;
}


/**
 * populate session variables from database
 * @param center_code	
*/
function _shn_cps_get_session($center_name){
	global $global;
	$db = $global['db'];

$query="select * from child_center  where  center_name like  '%$center_name%'";
$recordCount=0;
	$res = $db->Execute($query);
$recordCount=$res->RecordCount();
$childcenterdata= Array();
$i=0;//keep track of rows
$j=0;//keep track of columns 
while(!$res->EOF)
{
  
$childcenterdata[$i][$j++]=$res->fields[0];//center code
$childcenterdata[$i][$j++]=$res->fields[1];//center name
$childcenterdata[$i][$j++]=$res->fields[2];//date
$childcenterdata[$i][$j++]=$res->fields[3];//filed_by
$childcenterdata[$i][$j++]=$res->fields[4];//function
$j=0;
$i++;
$res->MoveNext();
}
$i=0;				
$_SESSION['childcenterdata']=$childcenterdata;
if($res==false){
$resulti=$db->ErrorMsg();
print 'error is'.$resulti;
}
return $recordCount;
}


function _shn_cps_get_centerdata($centercode)
{
global $global;
$db = $global['db'];
$query="select * from child_center  where  center_code='{$centercode}'";
$recordCount=0;
	$res = $db->Execute($query);
$recordCount=$res->RecordCount();
$j=0;
$childcenterdata= Array();
$childcenterdata[$j++]=$res->fields[0];//center code
$childcenterdata[$j++]=$res->fields[1];//center name
$childcenterdata[$j++]=$res->fields[2];//date
$childcenterdata[$j++]=$res->fields[3];//filed_by
$childcenterdata[$j++]=$res->fields[4];//function
if($res==false)
{
$resulti=$db->ErrorMsg();
print 'error is'.$resulti;
}
return $childcenterdata;
}




function _shn_cps_cedt_commit_db(){
//insert to database;
global $global;
$module = $global['module'];
$db = $global['db'];

$q="update child_center set center_name='{$_SESSION['center_name']}',date='{$_SESSION['date']}',filed_by='{$_SESSION['filed_by']}',function='{$_SESSION['function']}' where center_code='{$_SESSION['center_code']}'";
$res = $db->Execute($q);
if($res==false)
{
$result=$db->ErrorMsg();
print 'error is'.$result;
}
?>
<h2>You Have Succesfully Updated Center Details of"<?=$_SESSION['center_name']?>"</h2>
<br>
<ul>
</ul>
<br><br>
<p>Use the Navigation Menu to Continue to edit a new child center </p>
<br>
<a href='index.php?mod=<?php print $module ?>&act=edtchildcenter&seq=disp'>
View All Child Centers</a>
<?php	
}
?>

