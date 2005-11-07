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
$q = "select option_code,option_description from field_options where field_name='opt_sector_type'";
    $res=$db->Execute($q);
    $or_sector_type_options=array();

    while(!$res->EOF){
        array_push(
            $or_sector_type_options,
            array(  'drop_desc'=>$res->fields[1],
                    'value'=>$res->fields[0]
            )       
        );
        
        $res->MoveNext();
 }
  
  
$q = "select location.name,location.location_id from location where location.opt_location_type='1'";
    $res=$db->Execute($q);
    $or_countries=array();
        
    while(!$res->EOF){
        array_push(
            $or_countries,
            array(  'drop_desc'=>$res->fields[0],
                    'value'=>$res->fields[1]
            )       
        );
        
        $res->MoveNext();
    }

    $q = "select location.name,location.location_id from location where location.opt_location_type='2'";
    $res=$db->Execute($q);
    $or_provinces=array();
        
    while(!$res->EOF){
        array_push(
            $or_provinces,
            array(  'drop_desc'=>$res->fields[0],
                    'value'=>$res->fields[1]
            )       
        );
        
        $res->MoveNext();
    }
    $q = "select location.name,location.location_id from location where location.opt_location_type='3'";
 
    $res=$db->Execute($q);
    $or_districts=array();
        
    while(!$res->EOF){
        array_push(
            $or_districts,
            array(  'drop_desc'=>$res->fields[0],
                    'value'=>$res->fields[1]
            )       
        );
        
        $res->MoveNext();
    }
    $q = "select location.name,location.location_id from location where location.opt_location_type='4'";
 

    $res=$db->Execute($q);
    $or_villages=array();
        
    while(!$res->EOF){
        array_push(
            $or_villages,
            array(  'drop_desc'=>$res->fields[0],
                    'value'=>$res->fields[1]
            )       
        );
        
        $res->MoveNext();
    }
?>
<h2>Search for Organizations by Service and Location</h2>
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=or&act=search_cr','id'=>'formset');
	shn_form_open($header,false);
      
 $sector = array(
                        array('desc'=>_("Services Provided : "),'type'=>"multiselect",'size'=>4,'name'=>"sector[]",'options'=>$or_sector_type_options,
                        'br'=>'1'
                        ) // end of list form
                     );
   shn_form_add_component_list($sector,$section=true,$legend='',$return=false,$default_val_req=true);
    // base location
    $location_inf = array(
                  //      array('desc'=>_("* Country of Origin:"),'type'=>'dropdown','name'=>'bsd_country','options'=>$or_countries,'br'=>'1'                             ),                         
                        array ('br'=>2, 'type'=>'radio','desc'=>'Select Location Type ','name'=>'loc_option', 'align'=>'right','options'=> 
                             array ( 
                                    array ('br'=>0, 'drop_desc' => 'Province', 'value' => 'province'),
                                    array ('br'=>0, 'drop_desc' => 'District', 'value' => 'district'),
                                    array ('br'=>2, 'drop_desc' => 'Village', 'value' => 'village')
                            )
                        ),                      

                        array('desc'=>_("Province :"),'type'=>'dropdown','name'=>'bsd_province',
                            'options'=>$or_provinces,'br'=>'1'
                        ),// end of option
array('desc'=>_("OR"),'type'=>'label','br'=>'2'
                        ),// 
                        array('desc'=>_("District :"),'type'=>'dropdown','name'=>'bsd_district',
                            'options'=>$or_districts,'br'=>'1'
                        ),// end of option
array('desc'=>_("OR"),'type'=>'label','br'=>'2'
                        ),// 
                        array('desc'=>_("Village :"),'type'=>'dropdown','name'=>'bsd_village',
                            'options'=>$or_villages,'br'=>'1'
                        )
                    );// end of option
                             
    // OR infomation
    shn_form_add_component_list($location_inf,$section=true,$legend='Base Location Information',$return=false,$default_val_req=true);

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
