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

include_once($global['approot'].'/inc/lib_form.inc');
include_once $global['approot']."/inc/handler_form.inc";
include_once "lib_or.inc";

function shn_or_adm_location_form(){
?>
<h1 align="center">Set the Starting Location</h1>
<div id="note">
Fields marked with * are required (entry is compulsory)
</div>
<div id="note">
When a Disaster happens,typically organizations located in a certain region get involved. Therefore when you select a location its a waste of time to always start from country. If you know the country ,give it in this form,and you can start with sub-divisions of that country. Furthermore ,if the Disaster is confined to a much smaller geographical area, select the appropriate location to start with.
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    $header=array('name'=>'sahana','method'=>'POST','action'=>'index.php?mod=or&act=adm_location_cr','id'=>'formset');
shn_form_open($header,false);
global $global;
$db=$global["db"];
$q = "select option_code,option_description from field_options where field_name='opt_location_type'";
$res=$db->Execute($q);
$options=array();
while(!$res==NULL && !$res->EOF){
                array_push(
                    $options,
                    array(  'drop_desc'=>$res->fields[1],
                        'value'=>$res->fields[0],
                     )       
                );
                $res->MoveNext();
            }
$loc=array('desc'=>_("Location Type(level)"),'type'=>"dropdown",'name'=>'level','options'=>$options,'br'=>'1');   
$loc_options=array();
array_push(
$loc_options,
$loc
);
$all = array('desc'=>_("I want all the Locations ,so don't set a starting point"),'type'=>'checkbox','name'=>'chk_start','value'=>'add','algin'=>'right','select'=>1,'br'=>4
                    
            );
array_push(
$loc_options,
$all
);
shn_form_add_component_list($loc_options,$section=true,$legend='Select the Location Level you want fix',$return=false,$default_val_req=$error);
$location_inf=shn_location_all();
shn_form_add_component_list($location_inf,$section=true,$legend='Now Select the Location',$return=false,$default_val_req=$error);
 ?>
</center>
<br />
<center>
<?php

//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Save');
	shn_form_add_component($submit,false,false);
?>
</center>
<br />
<?php
    //close the form
    shn_form_close(false);
?>				     
</div>
<?php
    // end of form
	
}



function shn_or_adm_or_type_form()
{
?>
<h1 align="center">Organization Types</h1>
<div id="note">
Fields marked with * are required (entry is compulsory)
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    $header=array('name'=>'sahana','method'=>'POST','action'=>'index.php?mod=or&act=adm_type_cr','id'=>'formset');
shn_form_open($header,false);
shn_or_admin_javascript("org_type[]");
$add=array();
 $or_name=array('desc'=>_("* Organization Type : "),'type'=>"text",'size'=>50,'name'=>'type','br'=>0,'br'=>'1'); 
$type=array('desc'=>_("* Abbrevation [3 letter unique abbr. to store in the database]: "),'type'=>"text",'size'=>50,'name'=>'type_abbr','br'=>0,'br'=>'1'); 
 $add_button=array('value'=>_("Add"),'type'=>"button",'size'=>50,'name'=>'add','br'=>0,'br'=>'1','onClick'=>'add_types()'); 
array_push(
            $add,
            $or_name
            );
array_push(
            $add,
            $type
            );
array_push(
            $add,
            $add_button
            );
?>
<center>
<?php
shn_form_add_component_list($add,$section=true,$legend='',$return=false,$default_val_req=$error);
 ?>
</center>
<?php
$edit=array();
   $or_type=_shn_or_display_org_type($error,true);

$rem_button=array('value'=>_("Remove"),'type'=>"button",'size'=>50,'name'=>'rem','br'=>0,'br'=>'1','onClick'=>'remove_types()'); 
array_push(
            $edit,
            $or_type
            );
array_push(
            $edit,
            $rem_button
            );
?>
<center>
<?php
	shn_form_add_component_list($edit,$section=true,$legend='',$return=false,$default_val_req=$error);
 ?>
</center>
<br />
<center>
<?php
$added=array('type'=>"hidden",'name'=>'added'); 
shn_form_add_component($added,$return=false,$default_val_req=false);
$removed=array('type'=>"hidden",'name'=>'removed'); 
shn_form_add_component($removed,$return=false,$default_val_req=false);

//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Save');
	shn_form_add_component($submit,false,false);
?>
</center>
<br />
<?php
    //close the form
    shn_form_close(false);
?>				     
</div>
<?php
    // end of form
} 

function shn_or_adm_or_sector_form()
{
?>
<h1 align="center">Organization Sectors</h1>
<div id="note">
Fields marked with * are required (entry is compulsory)
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    $header=array('name'=>'sahana','method'=>'POST','action'=>'index.php?mod=or&act=adm_sector_cr','id'=>'formset');
shn_form_open($header,false);
shn_or_admin_javascript("sector[]");
$add=array();
 $or_name=array('desc'=>_("* Organization Sector : "),'type'=>"text",'size'=>50,'name'=>'type','br'=>0,'br'=>'1'); 
$type=array('desc'=>_("* Abbrevation [3 letter unique abbr. to store in the database]: "),'type'=>"text",'size'=>50,'name'=>'type_abbr','br'=>0,'br'=>'1'); 
 $add_button=array('value'=>_("Add"),'type'=>"button",'size'=>50,'name'=>'add','br'=>0,'br'=>'1','onClick'=>'add_types()'); 
array_push(
            $add,
            $or_name
            );
array_push(
            $add,
            $type
            );
array_push(
            $add,
            $add_button
            );
?>
<center>
<?php
shn_form_add_component_list($add,$section=true,$legend='',$return=false,$default_val_req=$error);
 ?>
</center>
<?php
$edit=array();
   $or_type=_shn_or_display_sector($error,true);

$rem_button=array('value'=>_("Remove"),'type'=>"button",'size'=>50,'name'=>'rem','br'=>0,'br'=>'1','onClick'=>'remove_types()'); 
array_push(
            $edit,
            $or_type
            );
array_push(
            $edit,
            $rem_button
            );
?>
<center>
<?php
	shn_form_add_component_list($edit,$section=true,$legend='',$return=false,$default_val_req=$error);
 ?>
</center>
<br />
<center>
<?php
$added=array('type'=>"hidden",'name'=>'added'); 
shn_form_add_component($added,$return=false,$default_val_req=false);
$removed=array('type'=>"hidden",'name'=>'removed'); 
shn_form_add_component($removed,$return=false,$default_val_req=false);

//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Save');
	shn_form_add_component($submit,false,false);
?>
</center>
<br />
<?php
    //close the form
    shn_form_close(false);
?>				     
</div>
<?php
    // end of form
} 
