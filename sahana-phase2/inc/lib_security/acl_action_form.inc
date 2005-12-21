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
include_once "acl_form_lib.inc";
include_once "lib_js.inc";

function shn_acl_form_add_action($module)
{
?>
<h1 align="center">New Action</h1>
<div id="note">
Fields marked with * are required (entry is compulsory)
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    $header=array('name'=>'sahana','method'=>'POST','action'=>"index.php?mod=admin&act=acl_action_cr&sel=$module",'id'=>'formset');
shn_form_open($header,false);

_shn_action_javascript("actions[]");
$add=array();
 $action_name=array('desc'=>_("* New Action : "),'type'=>"text",'size'=>50,'name'=>'action_name','br'=>0,'br'=>'1'); 
$desc=array('desc'=>_("* Description:"),'type'=>"text",'size'=>50,'name'=>'desc','br'=>0,'br'=>'1'); 
$groups=shn_acl_form_action_groups_id($module,false);
if($groups==false){
    echo "null";
    return;
}
 $add_button=array('value'=>_("Add"),'type'=>"button",'size'=>50,'name'=>'add','br'=>0,'br'=>'1','onClick'=>'add_types()'); 
array_push(
            $add,
            $action_name
            );
array_push(
            $add,
            $desc
            );
array_push(
		$add,
		$groups
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
   $actions=shn_acl_form_actions($module);

$rem_button=array('value'=>_("Remove"),'type'=>"button",'size'=>50,'name'=>'rem','br'=>0,'br'=>'1','onClick'=>'remove_types()'); 
array_push(
            $edit,
            $actions
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

function shn_acl_form_add_action_group($module)
{
?>
<h1 align="center">New Action Group</h1>
<div id="note">
Fields marked with * are required (entry is compulsory)
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    $header=array('name'=>'sahana','method'=>'POST','action'=>"index.php?mod=admin&act=acl_action_group_cr&sel=$module",'id'=>'formset');
shn_form_open($header,false);
_shn_action_groups_javascript("action_groups[]");
$add=array();
 $action_name=array('desc'=>_("* New Action Group : "),'type'=>"text",'size'=>50,'name'=>'action_group_name','br'=>0,'br'=>'1'); 
$desc=array('desc'=>_("* Description:"),'type'=>"text",'size'=>50,'name'=>'desc','br'=>0,'br'=>'1'); 

 $add_button=array('value'=>_("Add"),'type'=>"button",'size'=>50,'name'=>'add','br'=>0,'br'=>'1','onClick'=>'add_types()'); 
array_push(
            $add,
            $action_name
            );
array_push(
            $add,
            $desc
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
   $actions=shn_acl_form_action_groups_id($module);

$rem_button=array('value'=>_("Remove"),'type'=>"button",'size'=>50,'name'=>'rem','br'=>0,'br'=>'1','onClick'=>'remove_types()'); 
array_push(
            $edit,
            $actions
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


?>
