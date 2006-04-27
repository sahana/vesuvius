<?php
/**
* This library helps uses phpgacl library to manage ACL
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra De Silva
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $global;
include_once $global['approot']."/inc/handler_form.inc";
include_once $global['approot']."/inc/lib_location.inc";

function shn_admin_location_form(){
?>
<h1 align="center"><?=_("Add Locations")?></h1>
<div id="note">
<?=_("Fields marked with * are required (entry is compulsory)")?>
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    shn_form_fopen("add_loc_cr");
    _shn_admin_location_form();
 ?>
</center>
<br />
<center>
<?php
 	shn_form_submit("Submit");
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose(false);
?>
</div>
<?php
    // end of form

}

function shn_admin_location_view_form(){
?>
<h1 align="center"><?=_("First select the location to Edit & Delete")?></h1>
<div id="note">
<?=_("Fields marked with * are required (entry is compulsory)")?>
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php

    	shn_form_fopen("view_loc_cr");
    	_shn_or_update_loc();
    	?>
    	<div id="note">
	<?=_("Select location and then select the level(province,district,ect)," .
			"the selected location field at the end of the form will be updated")?>
	</div>
	<?


    $select_opts="onClick='update_loc(this.options[this.selectedIndex].value,this.options[this.selectedIndex].text)'";
    shn_form_hidden(array('loc_sel'=>'0'));
    shn_form_fsclose();
 // base location
    shn_form_fsopen(" Location");
	$range= shn_get_range();
    shn_location($range,null,null);; 
    shn_form_fsclose();
    ?><fieldset><?
    shn_form_opt_select('opt_location_type','Location Level',$select_opts,null,null);
    ?></fieldset><?
    
    shn_form_fsopen(_("Selected Location for Edit/Delete"));
    $extra_options['value']="All Locations";
    $extra_options['size']=60;
    shn_form_text(_("location"),'loc',"size=50",$extra_options);
    shn_form_fsclose();
 ?>
</center>
<br />
<center>
<?php
 	shn_form_submit("Submit");
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose(false);
?>
</div>
<?php
    // end of form

}

function shn_admin_location_edit_form($loc){
	 global $global;
     $db=$global['db'];
     $q="select name,description,iso_code from location where location_id=$loc";
    
     $res=$db->Execute($q);
	?>
<h1 align="center"><?=_("Edit Location")?></h1>
<div id="note">
<?=_("Fields marked with * are required (entry is compulsory)")?>
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
	$form_opts['name']='view';	
    shn_form_fopen("edit_loc_cr",null,$form_opts);
    shn_form_fsopen(_("Location Details"));
    $extra_opts['req']=true;
    $extra_opts['value']=$res->fields["name"];
    shn_form_text(_("Location Name : "),'loc_name','size="50"',$extra_opts);
    $extra_opts['req']=false;
    $extra_opts['value']=$res->fields["description"];
    shn_form_text(_("Description : "),'desc','size="50"',$extra_opts);
    $extra_opts['value']=$res->fields["iso_code"];
    shn_form_text(_("ISO code : "),'iso','size="50"',$extra_opts);
    shn_form_fsclose();
    
 ?>
</center>

<?php
 	

//create the submit button
    shn_form_button(_("Close"),"onClick='change_action(\"close\")'");
	shn_form_button(_("Save"),"onClick='change_action(\"edit\")'");
    shn_form_button(_("Delete"),"onClick='change_action(\"del\")'");
    shn_form_hidden(array('action'=>'0'));
     shn_form_hidden(array('loc_id'=>$loc));
    _shn_admin_action_change_javascript("action");
    //close the form
    
?>
</center>
<br />
<?php
	shn_form_fclose(false);
?>
</div>
<?php
    // end of form
	
}

function _shn_admin_location_form()
{
    global $global;
    $db=$global["db"];
    shn_form_fsopen(_("New Location Details"));
    $extra_opts['req']=true;
    shn_form_text(_("Location Name : "),'loc_name','size="50"',$extra_opts);
    $extra_opts['req']=false;
    shn_form_text(_("Description : "),'desc','size="50"',$extra_opts);
    shn_form_text(_("ISO code : "),'iso','size="50"',$extra_opts);
    shn_form_fsclose();
    shn_form_fsopen(_("Location Type (level)"));
    shn_form_opt_select('opt_location_type','',$select_opts,array('req'=>true));
    shn_form_fsclose();
    shn_form_fsopen(_("Now Select the parent Location"));
    $range= shn_get_range();
    shn_location($range,null,null);
    shn_form_fsclose();
}

function _shn_or_update_loc(){
?>
<script type="text/javascript">
    function update_loc(action,desc){
        var x=document.getElementsByName(action);
        var loc_val=x[0].options[x[0].selectedIndex].value;
        var loc_desc=x[0].options[x[0].selectedIndex].text;
        var x=document.getElementsByName('loc_sel');
        x[0].value=loc_val;
        loc_desc=desc+"->"+loc_desc;
        var x=document.getElementsByName('loc');
        x[0].value=loc_desc;
        return;
    }
</script>
<?php
}


function _shn_admin_action_change_javascript($change)
{
?>
<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName("<?php echo $change?>");
         x[0].value=action;
         document.view.submit();
         return;
    }
</script>
<?php
}
