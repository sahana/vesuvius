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
   

?>
<h2>
	<?php echo  _t('Register an Organization')?>
</h2>
<?php
/*    if($error)
    display_errors();*/
?>  
<div class="form-container">
<?php
    shn_form_fopen("reg_org_gis_map");
    shn_form_fsopen(_t("Main Details"));
    $extra_opts['req']=true;
    ?>
	<div class="info">
	  <?php echo  _t('These are the basic details of the organization.').' '.
          _t('A name is required, but a registration number is optional.');?>
	</div>
	<br /><?php
    if($error==true){
    		$extra_opts['value']=$_SESSION['org']['name'];
    }
    shn_form_text(_t("Organisation Name").': ','org_name','size="40"',$extra_opts); 
    $extra_opts['req']=false;
    if($error==true){
    		$extra_opts['value']=$_SESSION['org']['reg_no'];
    }
    $extra_opts['help']=_t("Please enter a registration number if appropriate.").' '.
                        _t("If this organization has multiple registration numbers,
                            please select the one which is most relevant to the
                            situation.").'<br /><br />'.
                        _t("If the organization is unregistered, 
                            then please leave the field blank.");
    shn_form_text(_t("Registration Number").': ','reg_no','size="40"',$extra_opts); 
    shn_form_fsclose();
    shn_form_fsopen(_t("Organization Type").': ');
   
    if($error==true){
    		_shn_or_display_org_type($error,false,$_SESSION['org']['type']);
    }else{
    		_shn_or_display_org_type($error,false);
    }
    shn_form_fsclose();
    shn_form_fsopen(_t("Organization Sector"));
    
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
    $extra_opts['help']=(_t("Please select your location, moving from country to
                          city.")."<br /><br />"._t("Available locations are 
                          set by administrators.").' '.("Please contact them if 
                          your district or city is missing."));//display help icon only once
 	shn_form_fsopen(_t("Base Location")); ?>
         <div class="info">
	  <?php echo  _t("Please first select the country, area and city of this
                          organization. Once these are entered, a street address
                          may be entered in the field below.");
          ?>
	</div>
<?php
 	if($error==true){
 		shn_location(null,$_SESSION['org']['loc'],null,$extra_opts);
 	}else{
 		shn_location(null,null,null,$extra_opts);
 	} 
 	$extra_opts['help']=(_t("
                                ."));
 	shn_form_text(_t("Street Address"),'loc_txt','size="40"', $extra_opts);
    shn_form_fsclose();

    // Contact infomation
    shn_form_fsopen(_t("Contact Infomation"));
    _shn_or_display_contact_person($error,false,null);
    shn_form_fsclose();
    shn_form_fsopen(_t("Facilities Available"));
    _shn_or_display_org_facilities($error);
    shn_form_fsclose();
?>
	<br />
	<center>
		<?php   shn_form_submit(_t("Next")); ?>
	</center>
	<br />
<?php
    shn_form_hidden(array('org_type'=>'1'));
    shn_form_fclose();
?>				     
</div>
<?php
} // closes _shn_or_regform_org()


// This function brings up the map, so that orgs
// can select their location by clicking.
function _shn_or_reg_gis_map()
{
	global $global;
	include_once $global['approot']."/inc/lib_gis/gis_fns.inc";
	shn_form_fopen("reg_org_confirm",null,array('req'=>false));
	shn_form_hidden(array('seq'=>'img'));
    shn_gis_add_marker_map_form("Area Map","",null,array('marker'=>'single'));
    ?>
    <br />
	<center>
		<?php shn_form_submit(_t("Next")); ?>
	</center>
	<br />
<?php
    shn_form_fclose();
}  // closes _shn_or_reg_gis_map()



function _shn_or_regconfirm_org()
{
	global $global;
    global $conf;
    $db=$global['db'];
?>
<h2>
	<?php echo  _t('Confirm Registration Details of ').$_SESSION['org']['name'] ?>
</h2>

<div class="form-container">
<?php
	if( $_POST['action']=='confirm_edit'){
			shn_form_fopen("view_org_submit",null,array('req_message'=>false,'name'=>"confirm_reg"));
	}else if( $_SESSION['org']['parent_id']==null){
    		shn_form_fopen("reg_org_cr",null,array('req_message'=>false,'name'=>"confirm_reg"));
        }else{
    		shn_form_fopen("reg_operation_cr",null,array('req_message'=>false,'name'=>"confirm_reg"));	
        }
    shn_form_fsopen(_t('Primary Details'));
    $q="SELECT o_uuid FROM org_main WHERE name='{$_SESSION['org']['name']}'";
    $res=$db->Execute($q);
	if(($res==NULL) || ($res->EOF)){
	
	}else{
		// do not show the warning when confirm edit.
		if($_POST['action']!='confirm_edit'){
			$msg= $_SESSION['org']['name']._t(" already exists in the database.").' '.
			_t("Please consider changing the name to something unique.").' '.
			_t("If the organisation you are registering is a part of").' '.$_SESSION['org']['name']._t(", consider registering it as a branch or department.");
			add_warning($msg);
		}
	}
    shn_form_label(_t("Organization Name : "),$_SESSION['org']['name']); 
    if($_SESSION['org']['parent_id']==null){
    		shn_form_label(_t("Registration Number(if any) : "),$_SESSION['org']['reg_no']); 
    		$q="SELECT option_description FROM field_options WHERE field_name='opt_org_type' and option_code='{$_SESSION['org']['type']}'";
    }else{	
    		$q="SELECT option_description FROM field_options WHERE field_name='opt_org_sub_type' and option_code='{$_SESSION['org']['type']}'";
    }	
    	$res=$db->Execute($q);
    	shn_form_label(_t("Organization Type"),$res->Fields("option_description"));
    
    $count=1;
    foreach ($_SESSION['org']['sector'] as $i){
    		$q="SELECT option_description FROM field_options WHERE field_name='opt_sector_type' and option_code='{$i}'";
    		$res=$db->Execute($q);
    		$sector=$sector." ".$count.".".$res->Fields("option_description"); 
    		$count++;
    }
    shn_form_label(_t("Organization Sector"),$sector);
    shn_form_fsclose();
    /*
    // base location
    $parent=_shn_or_get_start_loc();
   	$range= shn_or_get_loc_range();
   	*/
   	shn_form_fsopen(_t("Base Location"));
	$location=_shn_org_location_string($_SESSION['org']['loc']);
	$map_location=_t("Latitude= ").$_SESSION['org']['loc_y']._t(" Longitude= ").$_SESSION['org']['loc_x'];
 	shn_form_label(_t("Organization Location"),$location);
 	shn_form_label(_t("Organization Location Address"),$_SESSION['org']['loc_txt']);
 	shn_form_label(_t("Map Location"),$map_location);
   	shn_form_fsclose();
    
    // Contact infomation
    shn_form_fsopen(_t("Contact Information"));
    _shn_or_display_contact_person($error,true,null);
    shn_form_fsclose();
     shn_form_fsopen(_t("Facilities Avaliable"));
    _shn_or_display_org_facilities($error,true);
    shn_form_fsclose();
 ?>
<br />
<center>
<?php
//create the submit button
	$extra_opts['br'] = false;
    shn_form_button(_t("Save"),"onClick='change_action(\"save\")'",$extra_opts);
	shn_form_button(_t("Edit Details"),"onClick='change_action(\"edit\")'",$extra_opts);
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
    $q="SELECT name FROM org_main WHERE o_uuid='{$parent_org}'";
    $res=$db->Execute($q);
?>
<h2>
	<?php echo _t("Add a Branch or Department under").' '.$res->Fields("name")?>
</h2>
<div class="information message">
	<?php echo _t("If you wish to create a branch, department, field team or another 
	sub-entity of this organization, do so here.")." "._t("Creating sub-entities is useful, 
	because you will be able to track progress of the team, seperate from the rest of 
	the organization."); ?>
</div>

<div class="form-container">
<?php
    shn_form_fopen("reg_org_gis_map");
    shn_form_fsopen(_t('Parent Organization'));
    _shn_or_display_orgs(false,false,$parent_org);
    shn_form_fsclose();
    shn_form_fsopen(_t('Primary Details'));
    $extra_opts['req']=true;
    shn_form_text(_t("Branch, Department or Field Team's Name : "),'org_name','size="50"',$extra_opts); 
	shn_form_fsclose();
	shn_form_fsopen(_t("Relationship to the Parent Organisation"));
    _shn_or_display_org_sub_type($error);
    shn_form_fsclose();
    shn_form_fsopen(_t("Organization Sector"));
    _shn_or_display_sector($error);
    shn_form_fsclose();
  // base location
    shn_form_fsopen(_t("Base Location <span class='req'>   * </span>"));
   	$parent=_shn_or_get_start_loc();
   	$range= shn_or_get_loc_range();
    shn_location($range,$_POST[$range["end"]],$parent); 
    shn_form_fsclose();
    shn_form_fsopen(_t("Contact Information"));
    _shn_or_display_contact_person($error,false,null);
	shn_form_fsclose();
     shn_form_fsopen(_t("Facilities Avaliable"));
   _shn_or_display_org_facilities($error);
    shn_form_hidden(array('org_type'=>'0'));
    shn_form_fsclose();
?>
<br />
<center>
<?php
//create the submit button
   shn_form_submit(_t("Next"));
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

