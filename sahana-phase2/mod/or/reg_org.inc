<?php
/**Registration related forms for Organizations of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

global $global;
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_errors.inc";
require_once $global['approot']."/inc/lib_location.inc";
include_once $global['approot']."/inc/lib_security/lib_acl.inc";
include_once "lib_or.inc";

function _shn_or_regform_org($error=false)
{
    global $global;
    global $conf;
    $db=$global['db'];
    
   $tables= array(
				'field_options'=>'r',
				'org_main'=>'c'
				);
   if(shn_acl_check_table_only_perms($tables)==DENIED){
   	 return false;
   }
?>
<h2><?= _('Organization Registration')?></h2>
<?php
/*    if($error)
    display_errors();*/
?>  
<div id="formcontainer">
<?php
    shn_form_fopen("reg_org_gis_map");
    shn_form_fsopen(_("Primary Details"));
    $extra_opts['req']=true;
    ?><div class="info"><?= _("These are the basic details of an organization. Organization name is required ,
    but registration  no is optional");?> </div><br /><?
    if($error==true){
    		$extra_opts['value']=$_SESSION['org']['name'];
    }
    shn_form_text(_("Organization Name : "),'org_name','size="50"',$extra_opts); 
    $extra_opts['req']=false;
    if($error==true){
    		$extra_opts['value']=$_SESSION['org']['reg_no'];
    }
    $extra_opts['help']=_("If your organization is registered please enter your registration no");
    shn_form_text(_("Registration Number(if any) : "),'reg_no','size="50"',$extra_opts); 
    shn_form_fsclose();
    shn_form_fsopen("Organization Type");
   
    if($error==true){
    		_shn_or_display_org_type($error,false,$_SESSION['org']['type']);
    }else{
    		_shn_or_display_org_type($error,false);
    }
    shn_form_fsclose();
    shn_form_fsopen("Organization Sector");
    
    if($error==true){
    		_shn_or_display_sector($error,$_SESSION['org']['sector']);
    }else{
    		_shn_or_display_sector($error);
    }
    shn_form_fsclose();
    // base location
  //  $parent=_shn_or_get_start_loc();
  // $parent="fw1hlc-7";
  // 	$range= shn_or_get_loc_range();
  // 	$range=array('start'=>2,'end'=>3);
  // 	$extra_opts["camps"]=true;
  // 	$extra_opts["org"]=true;
 	shn_form_fsopen("Base Location <span class='req'>   *req </span>");
 	if($error==true){
 		shn_location(null,$_SESSION['org']['loc'],null,$extra_opts);
 	}else{
 		shn_location(null,null,null,$extra_opts);
 	} 
    shn_form_fsclose();
    // Contact infomation
    shn_form_fsopen("Contact Information");
    _shn_or_display_contact_person($error,false,null);
    shn_form_fsclose();
     shn_form_fsopen("Facilities Avaliable");
    _shn_or_display_org_facilities($error);
    shn_form_fsclose();
?>
<br />
<center>
<?php
//create the submit button
    shn_form_submit(_("Next"));
?>
</center>
<br />
<?php
    //close the form
    shn_form_hidden(array('org_type'=>'1'));
    shn_form_fclose();
?>				     
</div>
<?php
    // end of form
} 

function _shn_or_reg_gis_map()
{
	global $global;
	include_once $global['approot']."/mod/gis/gis_fns.inc";
	shn_form_fopen("reg_org_confirm",null,array('req'=>false));
	shn_form_hidden(array('seq'=>'img'));
    shn_gis_add_marker_map_form();
    ?>
    <br />
<center>
<?php
//create the submit button
    shn_form_submit(_("Next"));
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose();
	
    
}

function _shn_or_regconfirm_org()
{
	    global $global;
    global $conf;
    $db=$global['db'];
?>
<h2><?= _('Confirm Registration Details of ').$_SESSION['org']['name'] ?></h2>
<div id="formcontainer">
<?php
    if( $_SESSION['org']['parent_id']==null){
    		shn_form_fopen("reg_org_cr",null,array('req_message'=>false,'name'=>"confirm_reg"));
    }else{
    		shn_form_fopen("reg_operation_cr",null,array('req_message'=>false,'name'=>"confirm_reg"));	
    }
    shn_form_fsopen('Primary Details');
    shn_form_label(_("Organization Name : "),$_SESSION['org']['name']); 
    if($_SESSION['org']['parent_id']==null){
    		shn_form_label(_("Registration Number(if any) : "),$_SESSION['org']['reg_no']); 
    		$q="select option_description from field_options where field_name='opt_org_type' and option_code='{$_SESSION['org']['type']}'";
    }else{	
    		$q="select option_description from field_options where field_name='opt_org_sub_type' and option_code='{$_SESSION['org']['type']}'";
    }	
    	$res=$db->Execute($q);
    	shn_form_label(_("Organization Type"),$res->Fields("option_description"));
    
    $count=1;
    foreach ($_SESSION['org']['sector'] as $i){
    		$q="select option_description from field_options where field_name='opt_sector_type' and option_code='{$i}'";
    		$res=$db->Execute($q);
    		$sector=$sector." ".$count.".".$res->Fields("option_description"); 
    		$count++;
    }
    shn_form_label(_("Organization Sector"),$sector);
    shn_form_fsclose();
    /*
    // base location
    $parent=_shn_or_get_start_loc();
   	$range= shn_or_get_loc_range();
   	*/
   	shn_form_fsopen("Base Location");
	$location=_shn_org_location_string($_SESSION['org']['loc']);
	$map_location="Latitude= ".$_SESSION['org']['loc_x']." Longitude= ".$_SESSION['org']['loc_x'];
 	shn_form_label(_("Organization Location"),$location);
 	shn_form_label(_("Map Location"),$map_location);
   	shn_form_fsclose();
    
    // Contact infomation
    shn_form_fsopen("Contact Information");
    _shn_or_display_contact_person($error,true,null);
    shn_form_fsclose();
     shn_form_fsopen("Facilities Avaliable");
    _shn_or_display_org_facilities($error,true);
    shn_form_fsclose();
 ?>
<br />
<center>
<?php
//create the submit button
	$extra_opts['br'] = false;
    shn_form_button(_("Save"),"onClick='change_action(\"close\")'",$extra_opts);
	shn_form_button(_("Edit Details"),"onClick='change_action(\"edit\")'",$extra_opts);
    shn_form_hidden(array('action'=>'0'));
    _shn_or_action_change_javascript("confirm_reg","action");
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose();
?>				     
</div>
<?php
    // end of form
}

function _shn_or_regform_operation($error=false,$parent_org=null)
{
    global $global;
    global $conf;
    $db=$global['db'];
    $q="select name from org_main where o_uuid='{$parent_org}'";
    $res=$db->Execute($q);
?>
<h2><?=_("Add an Operation/Branch under the Organization ").$res->Fields("name")?> </h2>
<div id="note">
<?=_("Your Organization might be having branches or carrying out relief operations in this disaster. Then information of those operations is usefull ");?>
</div>
               
<div id="formcontainer">
<?php
    shn_form_fopen("reg_org_gis_map");
    shn_form_fsopen('Parent Entity');
     _shn_or_display_orgs(false,false,$parent_org);
    shn_form_fsclose();
    shn_form_fsopen('Primary Details');
    $extra_opts['req']=true;
    shn_form_text(_("Operation/Branch Name : "),'org_name','size="50"',$extra_opts); 
	shn_form_fsclose();
	shn_form_fsopen("Relationship to the parent Organization");
    _shn_or_display_org_sub_type($error);
    shn_form_fsclose();
    shn_form_fsopen("Organization Sector");
    _shn_or_display_sector($error);
    shn_form_fsclose();
  // base location
    shn_form_fsopen("Base Location <span class='req'>   *req </span>");
   	$parent=_shn_or_get_start_loc();
   	$range= shn_or_get_loc_range();
    shn_location($range,$_POST[$range["end"]],$parent); 
    shn_form_fsclose();
    shn_form_fsopen("Contact Information");
    _shn_or_display_contact_person($error,false,null);
	shn_form_fsclose();
     shn_form_fsopen("Facilities Avaliable");
   _shn_or_display_org_facilities($error);
    shn_form_hidden(array('org_type'=>'0'));
    shn_form_fsclose();
?>
<br />
<center>
<?php
//create the submit button
   shn_form_submit(_("Next"));
?>
</center>
<br />
<?php
        //close the form
    shn_form_fclose();
?>				     
</div>
<?php
    // end of form
  
} 
?>
