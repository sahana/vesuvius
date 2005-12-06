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
include_once $global['approot']."/inc/handler_form.inc";
include_once $global['approot']."/inc/lib_errors.inc";


function shn_or_form_search()
{
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
$loc=array('desc'=>_("Search Based on"),'type'=>"dropdown",'name'=>'loc_option','options'=>$options,'br'=>'1');   
$loc_options=array();
array_push(
$loc_options,
$loc
);
$or_sector=_shn_or_display_sector($error);
$sector=array();
array_push(
$sector,
$or_sector
);
 
?>
<h1 align="center">Search for Organizations by Service and Location</h1>
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=or&act=search_cr','id'=>'formset');
	shn_form_open($header,false);
      

   shn_form_add_component_list($sector,$section=true,$legend='Services',$return=false,$default_val_req=true);
    // base location
                         
shn_form_add_component_list($loc_options,$section=true,$legend='Select Location Type',$return=false,$default_val_req=true);
    $location_inf = shn_location_form('1','4'); 
    

?>
</br>
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Search');
	shn_form_add_component($submit,false,false);
?>
</center>
</br>
<?php
        //close the form
     	shn_form_close(false);
?>				     
</div>
<?php
}
