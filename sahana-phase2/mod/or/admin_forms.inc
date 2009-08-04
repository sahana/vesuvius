<?php
/**Admin forms of the Organization Registry 
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

include_once($global['approot'] . '/inc/lib_form.inc');
include_once "lib_or.inc";

function shn_or_adm_location_form()
{
    global $global;
    $db = $global["db"];
?>
<h2><?php echo _t("Set the Starting Location")?></h2>
<div id="note">
<?php echo _t("When a Disaster happens,typically organizations located in a certain region get involved. Therefore when you select a location its a waste of time to always start from country. If you know the country ,give it in this form,and you can start with sub-divisions of that country. Furthermore ,if the Disaster is confined to a much smaller geographical area, select the appropriate location to start with.")?>
</div>
<?php
    if ($error == true){
        display_errors();
    }
?>
<div id="formcontainer">
    <?php
    shn_form_fopen("adm_location_cr");
	
	shn_form_fsopen(_t("I want all the Locations ,so don't set a starting point"));
	    shn_form_checkbox('','chk_start',null,$chkbox_opts);
	shn_form_fsclose();
	
	shn_form_fsopen(_t("Select the Location Level you want fix"));
	    shn_form_opt_select('opt_location_type','',$select_opts,array('req'=>true));
	shn_form_fsclose();
	
	shn_form_fsopen(_t("Now Select the Location"));
	    $range = shn_or_get_loc_range();
	    shn_location($range,null,null);
	shn_form_fsclose();
   // shn_form_add_component_list($location_inf,$section=true,$legend='Now Select the Location',$return=false,$default_val_req=$error);
    ?>
        <br />
        <center>
	    <?php shn_form_submit(_t("Save")); ?>
	</center>
	<br />
    <?php shn_form_fclose(); ?>				     
</div>
<?php
}

function shn_or_adm_location_range_form()
{
    global $global;
    $db = $global["db"];
?>
    <h2><?php echo _t("Set the Location Range")?></h2>

    <div id="note">
        <?php echo _t("In a Disaster,all the location levels might not be important ,set the range here")?>
    </div>

<?php
    if ($error == true){
        display_errors();
    }
?>
    <div id = "formcontainer">
<?php
    $range = shn_or_get_loc_range();

    shn_form_fopen("adm_location_range_cr",NULL,array('req_message'=>false));
	shn_location_level_range_form('start',_t('Set Starting Level'),$range["start"]);
	shn_location_level_range_form('end',_t('Set End Level'),$range["end"]);
?>
	<br />
	<center>
	    <?php shn_form_submit(_t("Save")); ?>
	</center>
	<br />
<?php shn_form_fclose(); ?>				     
    </div>
<?php
}  // end of function shn_or_adm_location_range_form()

function shn_or_adm_or_type_form()
{
	global $global;
	include_once($global['approot'].'/inc/lib_misc.inc');
	include_once("api.inc"); 
?>
<h2><?php echo _t('Organization Types')?></h2>
<?php
    if ($error==true){
        display_errors();
    }
?>
<div id="formcontainer">
<?php
    $type_arr = shn_or_type_list();
    $types = array();
    foreach($type_arr as $type){
    	
    	array_push($types, $type["name"]);
    }
    $form_opts['name'] = 'add_type';
    shn_form_fopen("adm_type_cr",null,$form_opts);
    shn_add_remove_javascript("opt_org_type[]",$types);
  //  shn_form_fsopen("Add New Type Information");

    shn_form_hidden(array("added"=>','));
    shn_form_hidden(array("removed"=>','));
 
 //   shn_form_fsclose();
 ?>
    <center>
    <?php
    shn_form_fsopen(_t("Add and Remove Types"));
    _shn_or_display_org_type($error,true,null,false);
    shn_form_button(_t("Remove"),"onClick='remove_types()'");
    
      
    shn_form_text(_t("New Organization Type : "),'type','size="40"',null);
    shn_form_button(_t("Add More"),"onClick='add_types()'");
    shn_form_fsclose();
    ?>
    </center>
    <br />
    
    <center>
    <?php
	$extra_opts['br']=false;
	    $extra_opts['req']=false;
	shn_form_button(_t("Update"),"onClick='change_action(\"save\")'",$extra_opts);
	shn_form_button(_t("Undo"),"onClick='change_action(\"reset\")'",$extra_opts);
	shn_form_hidden(array('action'=>'0'));
	shn_reset_form_javascript("add_type","opt_org_type[]");
    ?>
    </center>
    <br />
    <?php shn_form_fclose(); ?>
</div>
<?php
} //shn_or_adm_or_type_form()

function shn_or_adm_or_sector_form()
{
	global $global;
	include_once($global['approot'] . '/inc/lib_misc.inc') ;
	include_once("api.inc");
?>
<h2><?php echo _t("Organization Sectors")?></h1>
<?php
    if($error == true){    
        display_errors();
    }
?>
<div id="formcontainer">
<?php
	$service_arr=shn_or_service_list();
	$services=array();
    foreach($service_arr as $service){
    	
    	array_push($services, $service["name"]);
    }
	$form_opts['name']='add_sector';
	shn_form_fopen("adm_sector_cr",null,$form_opts);
    shn_add_remove_javascript("opt_sector_type[]",$services);
//    shn_form_fsopen("Add New Sector Information");
   
    shn_form_hidden(array("added"=>','));
    shn_form_hidden(array("removed"=>','));

   // shn_form_fsclose();
 ?>
    <center>
<?php
    shn_form_fsopen(_t("Add & Remove Sectors"));
    _shn_or_display_sector($error,null,false);
    shn_form_button(_t("Remove"),"onClick='remove_types()'");
    shn_form_text(_t("New Organization Sector : "),'type','size="40"',null);
    shn_form_button(_t("Add More"),"onClick='add_types()'");
    shn_form_fsclose();
 ?>
    </center>
    <br />
    <center>
    <?php
	$extra_opts['br'] = false;
	    $extra_opts['req'] = false;
	shn_form_button(_t("Update"),"onClick='change_action(\"save\")'",$extra_opts);
	shn_form_button(_t("Undo"),"onClick='change_action(\"reset\")'",$extra_opts);
	shn_form_hidden(array('action'=>'0'));
	shn_reset_form_javascript("add_sector","opt_sector_type[]");
    ?>
</center>
    <br />
    <?php shn_form_fclose(); ?>
</div>
<?php
} // shn_or_adm_or_sector_form()
