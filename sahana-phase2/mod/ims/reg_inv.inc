<?php
/**Registration related forms for Inventories of the Inventory Management System 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
	       Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

global $global;
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_errors.inc";
require_once $global['approot']."/inc/lib_location.inc";
include_once $global['approot']."/mod/gis/gis_fns.inc";
include_once "lib_ims.inc";

function _shn_ims_regform_org($error=false)
{
    global $global;
   // global $conf;
    $db=$global['db'];
?>
<h2><?= _('Add an Inventory')?></h2>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    //shn_form_fopen("reg_inv_cr");
    shn_form_fopen("reg_inv_gis");
    shn_form_fsopen('Primary Details');
    $extra_opts['req']=true;
    shn_form_text(_("Inventory Name : "),'org_name','size="50"',$extra_opts); 
   // shn_form_text(_("Registration Number : "),'reg_no','size="50"'); 
    shn_form_fsclose();
   // shn_form_fsopen("Inventory Type");
   // _shn_or_ims_display_org_type($error);
   // shn_form_fsclose();
   // shn_form_fsopen("Inventory Sector");
   // _shn_or_ims_display_sector($error);
   // shn_form_fsclose();
    // base location
	//$extra_opts["camps"]=true;
$parent=_shn_ims_get_start_loc();
//print $parent;
   	//$range= shn_or_get_loc_range();
//print_r($range);
/*$range=array("start"=>1,"end"=>5);
shn_form_fsopen("Base Location");
shn_location($range,$_SESSION['inv']['loc'],null,true);
//shn_location($range,$_POST[$range["end"]],null,true);
//shn_location($range,$_SESSION['inv']['loc'],null,$extra_opts);
//shn_location($range,null,null,$extra_opts);
shn_form_fsclose();*/

	//shn_form_fsopen("Base Location");
        $range=array("start"=>1,"end"=>5);
	shn_form_fsopen(_("Location"));
	//shn_location_form_org(1,5);
	shn_location($range,$value=null,$parent=null,$extra_opts=null);
	shn_form_fsclose();
	//shn_form_fsclose();

/*shn_form_fsopen("Base Location");
 	if($error==true){
 		shn_location(null,$_SESSION['inv']['loc'],null,$extra_opts);
 	}else{
 		shn_location(null,null,null,$extra_opts);
 	} 
    shn_form_fsclose();*/

/**
*********************************
*/


   	/*$range=array("start"=>1,"end"=>3);
	//$end=$_POST[$range['end']];
 	shn_form_fsopen("Base Location");
 	shn_location($range,$_POST[$range["end"]],null,true);
//shn_location($range,$_SESSION['org']['loc'],null,true);
//shn_location($range,null,null,true); 
    shn_form_fsclose();*/
    // Contact infomation
    shn_form_fsopen("Contact Information");
    _shn_ims_display_contact_person($error,true,null);
    shn_form_fsclose();
     shn_form_fsopen("Facilities Avaliable");
    _shn_ims_display_org_facilities($error);
    shn_form_fsclose();

	
 	//shn_form_fsopen("Extra Information");
    //_shn_or_ims_display_extra($error);
    //shn_form_fsclose();
?>
<br />
<center>
<?php
//create the submit button
   // shn_form_hidden(array('range'=>$range));
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

function _shn_ims_regform_operation($error=false)
{
    global $global;
    global $conf;
    $db=$global['db'];
?>
<h2><?=_("Add an Operation/Branch under the Inventory ").$_SESSION["parent_name"]?> </h2>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
    shn_form_fopen("reg_operation_cr");
    shn_form_fsopen('Primary Details');
    $extra_opts['req']=true;
    shn_form_text(_("Operation/Branch Name : "),'org_name','size="50"',$extra_opts); 
	shn_form_fsclose();
    shn_form_fsopen("Inventory Sector");
    _shn_ims_display_sector($error);
    shn_form_fsclose();
  // base location
    shn_form_fsopen("Base Location");
   	$parent=_shn_ims_get_start_loc();
   	$range= shn_ims_get_loc_range();
    shn_location($range,$_POST[$range["end"]],$parent); 
    shn_form_fsclose();
    shn_form_fsopen("Contact Information");
    _shn_ims_display_contact_person($error,true,null);
shn_form_fsclose();
     shn_form_fsopen("Facilities Avaliable");
   _shn_ims_display_org_facilities($error);
    shn_form_fsclose();
 	shn_form_fsopen("Extra Information");
    _shn_ims_display_extra($error);
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
<?php
    // end of form
  


function _shn_ims_reg_inv_gis()
{

	//$bsd_village=trim($_POST[$range["end"]]);
    //$end=trim($_POST[$range["end"]]);
    $org_name=trim($_POST{"org_name"});
    $contact_name=trim($_POST{"contact_name"});
    $contact_add=trim($_POST{"contact_add"});
    $contact_phone=trim($_POST['contact_phone']);
    $contact_mobile=trim($_POST{"contact_mobile"});
    $contact_fax=trim($_POST{"contact_fax"});
    $contact_mail=trim($_POST{"contact_mail"});
    $contact_web=trim($_POST{"contact_web"});
    $man_power=trim($_POST{"man_power"});
    $equipment=trim($_POST{"equipment"});
    $resources=trim($_POST{"resources"});
    $space=trim($_POST{"space"});
	//$range=trim($_POST["range"]);

    //$range1= array();
    //$range1=trim($_POST['range']);
    //$bsd_village=array();
    //$range= shn_ims_get_loc_range();
    
    //print $bsd_village;
   // print ("Mahesh");

    $_SESSION['ims_1']=$_POST['1'];
    $_SESSION['ims_2']=$_POST['2'];
    $_SESSION['ims_3']=$_POST['3'];
    $_SESSION['ims_4']=$_POST['4'];
    $_SESSION['ims_5']=$_POST['5'];

    $bsd_village=_shn_ims_get_locid();
    

    shn_form_fopen("reg_inv_cr",null,array('req'=>false));
    //optionally, add additional form details, sequence information
    shn_form_hidden(array('seq'=>'img'));
    //call appropriate gis api method
    shn_gis_add_marker_map_form();
    //shn_form_fclose();

    //shn_form_hidden(array('end'=>$end));
    shn_form_hidden(array('org_name'=>$org_name));
    shn_form_hidden(array('contact_name'=>$contact_name));
    shn_form_hidden(array('contact_add'=>$contact_add));
    shn_form_hidden(array('contact_phone'=>$contact_phone));
    shn_form_hidden(array('contact_mobile'=>$contact_mobile));
    shn_form_hidden(array('contact_fax'=>$contact_fax));
    shn_form_hidden(array('contact_mail'=>$contact_mail));
    shn_form_hidden(array('contact_web'=>$contact_web));
    shn_form_hidden(array('man_power'=>$man_power));
    shn_form_hidden(array('equipment'=>$equipment));
    shn_form_hidden(array('resources'=>$resources));
    shn_form_hidden(array('space'=>$space));
    shn_form_hidden(array('bsd_village'=>$bsd_village));
    //shn_form_hidden(array('range'=>$range));
    shn_form_submit(_("Next"));
    shn_form_fclose();
}

function _shn_ims_validate_reg_inv()
{
    $error_flag=false;
    $VARCHAR=100;

	//$bsd_village=trim($_POST[$range["end"]]);
    //$end=trim($_POST[$range["end"]]);
    $inv_name=trim($_POST{"org_name"});
    $contact_name=trim($_POST{"contact_name"});
    $contact_add=trim($_POST{"contact_add"});
    $contact_phone=trim($_POST['contact_phone']);
    $contact_mobile=trim($_POST{"contact_mobile"});
    $contact_fax=trim($_POST{"contact_fax"});
    $contact_mail=trim($_POST{"contact_mail"});
    $contact_web=trim($_POST{"contact_web"});
    $man_power=trim($_POST{"man_power"});
    $equipment=trim($_POST{"equipment"});
    $resources=trim($_POST{"resources"});
    $space=trim($_POST{"space"});

    if($inv_name==null)
    {
	add_error("Inventory Incompleted");
	$error_flag=true;
    }
    if (strlen($contact_name) > $VARCHAR)
    {
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag=true;
    }

    //$contact_address=$_POST{"contact_add"};
    if (strlen($contact_phone) > $VARCHAR)
    {
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag=true;
    }
    if (strlen($contact_mobile) > $VARCHAR)
    {
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag=true;
    }
    if (strlen($contact_fax) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag=true;
    }
    if (strlen($contact_mail) > $VARCHAR){
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag=true;
    }
    if(!shn_valid_email($contact_mail))
    {
        add_error(SHN_ERR_or_ims_EMAIL);
        $error_flag=true;
    }
    if (strlen($contact_web) > $VARCHAR)
    {
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag=true;
    }
    if (strlen($man_power) > $VARCHAR)
    {
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag=true;
    }
    if (strlen($equipment) > $VARCHAR)
    {
        add_error(SHN_ERR_or_ims_REG_MAX);
        $error_flag=true;
    }
    //$resources=$_POST{"resources"};
    if (strlen($space)>$VARCHAR)
    {
	add_error(SHN_ERR_ims_SPACE);
	$error_flag=true;
    }

    return $error_flag;

}

?>
