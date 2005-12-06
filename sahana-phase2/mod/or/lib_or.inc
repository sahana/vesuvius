<?php
/*
*
* Sahana HTML form handler
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra <ravindra@opensource.lk>
* @author     Pradeeper <pradeeper@opensource.lk>
* @author     Chathra <chathra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/
function _shn_or_display_gender($error=false){
    global $global;
    $db=$global['db'];
    $q = "select option_code,option_description from field_options where field_name='opt_gender'";
    $res=$db->Execute($q);
    $gender=array();
        
    while(!$res->EOF){
        array_push(
            $gender,
            array(  'drop_desc'=>$res->fields[1],
                    'value'=>$res->fields[0]
            )       
        );
        
        $res->MoveNext();
    }
   return array('desc'=>_("Gender :"),'type'=>'dropdown','name'=>'sex','br'=>1,'options'=>$gender);
   				
}
function _shn_or_display_org_type($error=false)
{
    global $global;
    $db=$global['db'];
    
    $q = "select option_code,option_description from field_options where field_name='opt_org_type'";
    $res=$db->Execute($q);
    $or_type_options=array();
        
    while(!$res==NULL && !$res->EOF){
        array_push(
            $or_type_options,
            array(  'drop_desc'=>$res->fields[1],
                    'value'=>$res->fields[0]
            )       
        );
        
        $res->MoveNext();
    }
$or_type=array('desc'=>_("* Organization Type:"),'type'=>"dropdown",'name'=>'org_type','options'=>$or_type_options,'br'=>'1');    
   return $or_type;

}
    

function _shn_or_display_sector($error=false)
{
    global $global;
    $db=$global['db'];

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

return (array('desc'=>_("* Services Provided : "),'type'=>"multiselect",'size'=>4,'name'=>"sector[]",'options'=>$or_sector_type_options,
                        'br'=>'1'
                    ));

}


function _shn_or_display_contact_person($error=false,$org=true,$po_uuid=null){
$contact=array();
if(shn_is_null($po_uuid)){
    if($org){		
        $name=array('desc'=>_("Name : "),'type'=>"text",'size'=>50,'name'=>'contact_name','br'=>1);
    }
        $addr= array('desc'=>_("Address : "),'type'=>"textarea",'rows'=>10,'cols'=>60,'name'=>'contact_add','br'=>1);
        $phone=array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact_phone','br'=>1);
        $fax=array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact_fax','br'=>1);
        $email= array('desc'=>_("Email : "),'type'=>"text",'size'=>20,'name'=>'contact_mail','br'=>1);
    
                        
}else {
    global $global;
    $db=$global['db'];
    $q = "select address from location_details where poc_uuid={$po_uuid}";
    $res_addr=$db->Execute($q); 
    $contact_address=$res_addr->fields[0];
    $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='curr'";
    $res_phone=$db->Execute($q);
    $contact_phone=$res_phone->fields[0];
    if($org){
        $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='name'";
        $res_name=$db->Execute($q);
        $contact_name=$res_name->fields[0];
    }
    $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='fax'";
    $res_fax=$db->Execute($q);
    $contact_fax=$res_fax->fields[0];
    $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='email'";
    $res_email=$db->Execute($q);
    $contact_email=$res_email->fields[0];
   
    if($org){
        $name=array('desc'=>_("Name : "),'type'=>"text",'size'=>50,'name'=>'contact_name','br'=>1,'value'=>$contact_name);
    }
    $addr=array('desc'=>_("Address : "),'type'=>"textarea",'rows'=>10,'cols'=>60,'name'=>'contact_add','br'=>1,'value'=>$contact_address);
    $phone=array('desc'=>_("Phone : "),'type'=>"text",'size'=>10,'name'=>'contact_phone','br'=>1,'value'=>$contact_phone);
    $fax=array('desc'=>_("Fax : "),'type'=>"text",'size'=>10,'name'=>'contact_fax','br'=>1,'value'=>$contact_fax);
    $email=array('desc'=>_("email : "),'type'=>"text",'size'=>20,'name'=>'contact_mail','br'=>1,'value'=>$contact_email);
}
if($org){
    array_push(
            $contact,
            $name
            );
}
array_push(
            $contact,
            $addr
            );
array_push(
            $contact,
            $phone
            );
array_push(
            $contact,
            $fax
            );
array_push(
            $contact,
            $email
            );
return $contact;
}

function _shn_or_display_org_facilities($error=false,$org_id=false){
if(shn_is_null($org_id)){
// for comments
    $facilities = array(
		// get man power of the OR
                array('desc'=>_("Man Power (No):"),'type'=>"text",'size'=>4,'name'=>'man_power','br'=>1),
                array('type'=>"textarea",'desc'=>("Other Relevant Resources:"),'name'=>"resources",'rows'=>10,'cols'=>60,'br'=>1)
    ); // end of comments
}else {
    global $global;
    $db=$global['db'];
    $q = "select man_power,resources from org_main where o_uuid='{$org_id}'";
    
    $res_org=$db->Execute($q);
    if(!$res_org==NULL && !$res_org->EOF){
        
    
    $man_power=$res_org->fields[0]; 
    $resources=$res_org->fields[1]; 
// for comments
    $facilities = array(
		// get man power of the OR
                array('desc'=>_("Man Power (No):"),'type'=>"text",'size'=>4,'name'=>'man_power','br'=>1,'value'=>$man_power),
                array('type'=>"textarea",'desc'=>("Other relevant resources:"),'name'=>"resources",'rows'=>10,'cols'=>60,'br'=>1,'value'=>$resources)
    ); // 
	}
}
return $facilities;
}

function _shn_or_display_logininfo($error=false){
// for get login info
    $login_info = array(
    		       	array('desc'=>_("Account Name : "),'type'=>"text",'size'=>20,'name'=>'account_name','br'=>1),
                    array('desc'=>_("* User Name for Login: "),'type'=>"text",'size'=>20,'name'=>'user_name','br'=>1),
                    array('desc'=>_("* Password for Login: "),'type'=>"password",'size'=>20,'name'=>'password','br'=>1),
                    array('desc'=>_("* Confirm Password: "),'type'=>"password",'size'=>20,'name'=>'re_password','br'=>1)
    ); // end of getting logging info
return $login_info;
}

function _shn_or_display_extra($error=false){

$extra = array(
 
                    array('desc'=>_("Add Operation<br> (Your Organization might be having branches or carrying out relief operations in this disaster. Then information of those operations is usefull.) "),'type'=>'checkbox','name'=>'chk_branch','value'=>'add','algin'=>'right','select'=>1,'br'=>4)
                    
            );

return $extra;
}

function shn_or_district_villages($bsd_district){
global $global;
$db=$global["db"];

	$q="select location_id,name from location where parent_id={$bsd_district}";
        $res_tmp=$db->Execute($q);
        $k=0;
    
        while ((!$res_tmp==NULL)&&(!$res_tmp->EOF)){
	        $loc=$loc."{$res_tmp->fields[0]}";
            $res_tmp->MoveNext();
            if(!$res_tmp->EOF)
                $loc=$loc.",";
	}

return $loc;

}


function shn_or_province_villages($bsd_province){
global $global;
$db=$global["db"];

	$q="select location_id,name from location where parent_id={$bsd_province}";
        $res_tmp=$db->Execute($q);
        $k=0;
       
        while ((!$res_tmp==NULL)&&(!$res_tmp->EOF)){
	        $loc=$loc.shn_or_district_villages($res_tmp->fields[0]);
            $res_tmp->MoveNext();

	}

return $loc;

}
