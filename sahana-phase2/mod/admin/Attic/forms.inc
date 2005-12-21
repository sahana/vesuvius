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
<h1 align="center">Add Locations</h1>
<div id="note">
Fields marked with * are required (entry is compulsory)
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    $header=array('name'=>'sahana','method'=>'POST','action'=>'index.php?mod=admin&act=add_loc_cr','id'=>'formset');
shn_form_open($header,false);
	
	_shn_admin_location_form();  
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

function _shn_admin_location_form(){   

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
           
 $loc_name=array('desc'=>_("* Location Name : "),'type'=>"text",'size'=>50,'name'=>'loc_name','br'=>0,'br'=>'1'); 
$desc=array('desc'=>_("Description : "),'type'=>"text",'size'=>50,'name'=>'desc','br'=>0,'br'=>'1');
$iso=array('desc'=>_("ISO code : "),'type'=>"text",'size'=>50,'name'=>'iso','br'=>0,'br'=>'1');
$add=array();

array_push(
            $add,
            $loc_name
            );
array_push(
            $add,
            $desc
            );
array_push(
            $add,
            $iso
            );  
 
shn_form_add_component_list($add,$section=true,$legend='New Location Information',$return=false,$default_val_req=true);  

shn_form_add_component_list($loc_options,$section=true,$legend='Select Location Type',$return=false,$default_val_req=true);
$location_inf=shn_location('1','4');
shn_form_add_component_list($location_inf,$section=true,$legend='Parent Location',$return=false,$default_val_req=$error);
  
}
