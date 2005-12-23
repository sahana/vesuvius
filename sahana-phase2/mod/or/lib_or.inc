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
function _shn_or_del_org(){
 global $global;
$db=$global['db'];
$org_id=$_POST{"org_id"};
$q="delete from org_main where o_uuid=$org_id";
            $res=$db->Execute($q);
            $q="delete from sector where pgoc_uuid=$org_id";
            $res=$db->Execute($q);
 $q="delete from location_details where poc_uuid=$org_id";
            $res=$db->Execute($q);
            $q="delete from contact where pgoc_uuid=$org_id";
            $res=$db->Execute($q);
}

function _shn_or_edit_org(){
    global $global;
    $error=false;
    $VARCHAR=100;
    $org_id=$_POST{"org_id"};
    list($error,$org_name)=(shn_validate_field($_POST{"org_name"},"Organization Name",$VARCHAR,true))?array($error,$_POST{"org_name"}):array(true,NULL);
        
    list($error,$org_type)=(shn_validate_opt_field('opt_org_type',$_POST{"org_type"},"Organization Type",$VARCHAR,false))?array($error,$_POST{"org_type"}):array(true,NULL);
   
    list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"sector"},"Organization Sector",$VARCHAR,true))?array($error,$_POST{"sector"}):array(true,NULL);

    if (is_null($_POST{"4"})){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else {    
        $bsd_village=trim($_POST{"4"});
    }

    if (trim(strlen($_POST{"reg_no"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $reg_no=$_POST{"reg_no"};
    }
    if (trim(strlen($_POST{"contact_name"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_name=$_POST{"contact_name"};
    }
/*
    if (trim(strlen($_POST{"contact_add"})) > $CONTACT_ADDRESS){
        add_error(SHN_ERR_OR_REG_MAX);
    }else {
       $contact_address=$_POST{"contact_add"};
    }
*/
    $contact_address=$_POST{"contact_add"};
    if (trim(strlen($_POST{"contact_phone"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_phone=$_POST{"contact_phone"};
    }
    if (trim(strlen($_POST{"contact_fax"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
         $contact_fax=$_POST{"contact_fax"};
    }
    if (trim(strlen($_POST{"contact_mail"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $contact_mail=$_POST{"contact_mail"};
    }
    if (trim(strlen($_POST{"man_power"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $man_power=$_POST{"man_power"};
    }
    $resources=$_POST{"resources"};
    
    $db=$global['db'];
           //no validation done on other fields as they are not unique
            $q="update org_main set name='{$org_name}',opt_org_type='{$org_type}',reg_no='{$reg_no}',man_power='{$man_power}',resources='{$resources}' where o_uuid=$org_id";
            $res=$db->Execute($q);
            $q="delete from sector where pgoc_uuid=$org_id";
            $res=$db->Execute($q);
            $i=0;
            while($i<count($sector)){
                $q="insert into sector(pgoc_uuid,opt_sector) values($org_id,'{$sector[$i]}')";
                $res=$db->Execute($q);
                $i=$i+1;
            }
            $q="update location_details set location_id='{$bsd_village}',address='{$contact_address}' where poc_uuid=$org_id";
            $res=$db->Execute($q);
            $q="update contact set contact_name='{$contact_name}' where pgoc_uuid=$org_id and opt_contact_type='name'";
            $res=$db->Execute($q);
            $q="update contact set contact_value='{$contact_phone}' where pgoc_uuid=$org_id and opt_contact_type='curr'";
            $res=$db->Execute($q);
            $q="update contact set contact_value='{$contact_fax}' where pgoc_uuid=$org_id and opt_contact_type='fax'";
            $res=$db->Execute($q);
           $q="update contact set contact_value='{$contact_mail}' where pgoc_uuid=$org_id and opt_contact_type='email'";
            $res=$db->Execute($q);
  ?>
    <div id="result_msg">
       <?php echo $org_name?> Organization was succesfully Updated
    </div>
    </br>
<?php
       
}

function shn_or_action_change_javascript($change){
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

function shn_or_admin_javascript($name){
?>
<script type="text/javascript">

 // sort function - ascending (case-insensitive)
        function sortFuncAsc(record1, record2) {
            var value1 = record1.optText.toLowerCase();
            var value2 = record2.optText.toLowerCase();
            if (value1 > value2) return(1);
            if (value1 < value2) return(-1);
            return(0);
        }

        // sort function - descending (case-insensitive)
        function sortFuncDesc(record1, record2) {
            var value1 = record1.optText.toLowerCase();
            var value2 = record2.optText.toLowerCase();
            if (value1 > value2) return(-1);
            if (value1 < value2) return(1);
            return(0);
        }

        function sortSelect(selectToSort, ascendingOrder) {
            if (arguments.length == 1) ascendingOrder = true;    // default to ascending sort

            // copy options into an array
            var myOptions = [];
            for (var loop=0; loop<selectToSort.options.length; loop++) {
                myOptions[loop] = { optText:selectToSort.options[loop].text, optValue:selectToSort.options[loop].value };
            }

            // sort array
            if (ascendingOrder) {
                myOptions.sort(sortFuncAsc);
            } else {
                myOptions.sort(sortFuncDesc);
            }

            // copy sorted options from array back to select box
            selectToSort.options.length = 0;
            for (var loop=0; loop<myOptions.length; loop++) {
                var optObj = document.createElement('option');
                optObj.text = myOptions[loop].optText;
                optObj.value = myOptions[loop].optValue;
                selectToSort.options.add(optObj);
            }
        }

        function add_types(){
            var y=document.getElementsByName("type");
            var z=document.getElementsByName("type_abbr");
            var add=document.getElementsByName("added");
            var remove=document.getElementsByName("removed");
            var exist=search(add[0].value,z[0].value,true,y[0].value);
            if(exist){
                alert("The Type Exists,you just added it");
                return;
            }
            var x=document.getElementsByName("<?php echo $name?>");
            exist=search_select_box(x[0],z[0].value,true,y[0].value);
            if(exist){
                alert("The Type Exists in the DataBase");
                return;
            }
            exist=search(remove[0].value,z[0].value,true,y[0].value);
            if(exist){
                remove[0]=del(remove[0].value,z[0].value);
                return;
            }
            opt = document.createElement("option") ;
            opt.text = y[0].value ;
            opt.value = z[0].value ;
            x[0].appendChild(opt) ;
            sortSelect(x[0], true) ;
            add[0].value= add[0].value+":"+z[0].value+"|"+y[0].value;
            y[0].value=null;
            z[0].value=null
        }

        function remove_types(){
            var x=document.getElementsByName("<?php echo $name?>");
            removeSelectedOptions(x[0]);
            sortSelect(x[0], true) ;
        }

        function hasOptions(obj) {
    	    if (obj!=null && obj.options!=null) { return true; }
	            return false;
	    }
	
        function removeSelectedOptions(from) { 
	        if (!hasOptions(from)) { return; }
	        if (from.type=="select-one") {
		        from.options[from.selectedIndex] = null;
		    }
	        else {
		        var add=document.getElementsByName("added");
                var remove=document.getElementsByName("removed");
                for (var i=(from.options.length-1); i>=0; i--) { 
        			var o=from.options[i]; 
			        if (o.selected) { 
					    var exist=search(add[0].value,o.value,false);
            			if(exist){
					        add[0].value=del(add[0].value,o.value);
                        }else{
                         	remove[0].value= remove[0].value+":"+o.value+"|"+o.text;
					    }
				        from.options[i] = null; 
				    }
            	}
            }
             	from.selectedIndex = -1; 
	    } 

        function search(arr,value,both,desc){
            if (window.RegExp) {
                var re = new RegExp(value);
                var temp = new Array(); 
                temp = arr.split(':');
                if (temp.length==1){
                    return false;
                }
                for (var i=0; i<temp.length; i++) {
                    var options = new Array(); 
                    options= temp[i].split('|');
                    var re = new RegExp(value);
                    if (re.test(options[0])) {
                        return true;
                    }
				    if(both){
		                re = new RegExp(desc);
                        if (re.test(options[1])) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        function search_select_box(obj,value,both,desc) {
	        if (window.RegExp) {
        		if (!hasOptions(obj)) { return false; }
		        for (var i=0; i<obj.options.length; i++) {
		            var re = new RegExp(value);
                    if (re.test(obj.options[i].value)) {
                        return true;
                    }
				    if(both){
		                re = new RegExp(desc);
                        if (re.test(obj.options[i].text)) {
                            return true;
                        }
		            }
                }
	        }
            return false;
        }
        function del(from,what){
            var temp = new Array();
            temp = from.split(':');
            from=null;
            if (temp.length==1){
                return false;
            }
            for (var i=1; i<temp.length; i++) {
                var options = new Array(); 
                options= temp[i].split('|');
                if(options[0]!=what){
                    
                    from= from+":"+options[0]+"|"+options[1];
                }
            }
            
            return from;
        }
	
</script>
<?php
}
function shn_or_get_org_loc_parents($child){
    global $global;
    $db=$global['db'];
    $q="select search_id,name,location.location_id from location_details,location where poc_uuid='{$child}' and location_details.location_id=location.location_id";
    $res_temp=$db->Execute($q);
    $final=array();
    $final[0]=$res_temp->fields[0];
    $final[1]=$res_temp->fields[1];
    $final[2]=$res_temp->fields[2];

    $bsd_village=$res_temp->fields[0];
    $loc=split("\.", $bsd_village);
    $loc_return=array();
    for($k=0;$k<count($loc)-1;$k++){
        $cur=$cur.$loc[$k];
        $temp=array();
        $temp[0]=$cur;     
        $q="select name,location_id from location where search_id='$cur'";
        $res_loc=$db->Execute($q);
        $temp[1]=$res_loc->fields[0];
        $temp[2]=$res_loc->fields[1];
        array_push(
            $loc_return,
            $temp
            );
        if($k!=count($loc)-1){
            $cur=$cur.".";
        }
	}
        array_push(
            $loc_return,
            $final
            );
       

     return $loc_return;
}
function shn_or_get_parents($child){

    global $global;
    $db=$global['db'];
    $q="select search_id,name,location_id from location where location_id=$child";
    $res_temp=$db->Execute($q);
    $final=array();
    $final[0]=$res_temp->fields[0];
    $final[1]=$res_temp->fields[1];
    $final[2]=$res_temp->fields[2];

    $bsd_village=$res_temp->fields[0];
    $loc=split("\.", $bsd_village);
    $loc_return=array();
    for($k=0;$k<count($loc)-1;$k++){
        $cur=$cur.$loc[$k];
        $temp=array();
        $temp[0]=$cur;     
        $q="select name,location_id from location where search_id='$cur'";
        $res_loc=$db->Execute($q);
        $temp[1]=$res_loc->fields[0];
        $temp[2]=$res_loc->fields[1];
        array_push(
            $loc_return,
            $temp
            );
        if($k!=count($loc)-1){
            $cur=$cur.".";
        }
	}
        array_push(
            $loc_return,
            $final
            );
       

     return $loc_return;
}



function _shn_or_display_gender($error=false,$value=NULL){
    global $global;
    $db=$global['db'];
    $q = "select option_code,option_description from field_options where field_name='opt_gender'";
    $res=$db->Execute($q);
    $gender=array();
    $selected=($value==$res->fields[0])?true:false;
    while(!$res->EOF){
        array_push(
            $gender,
            array(  'drop_desc'=>$res->fields[1],
                    'value'=>$res->fields[0],
 		     'selected'=>$selected
            )       
        );
        
        $res->MoveNext();
    }
   return array('desc'=>_("Gender :"),'type'=>'dropdown','name'=>'sex','br'=>1,'options'=>$gender);
   				
}
function _shn_or_display_org_type($error=false,$multi=false,$value=NULL)
{
    global $global;
    $db=$global['db'];
    $q = "select option_code,option_description from field_options where field_name='opt_org_type' order by option_description";
    $res=$db->Execute($q);
    $options=array();
    
    while(!$res==NULL && !$res->EOF){
	$selected=(trim($value)==trim($res->fields[0]))?true:false;
       array_push(
                    $options,
                    array(  'drop_desc'=>$res->fields[1],
                        'value'=>$res->fields[0],
                        'selected'=>$selected
                     )       
                );
        
        $res->MoveNext();
    }

$type=$multi?array('desc'=>_("* Organization Type:"),'type'=>"multiselect",'size'=>4,'name'=>'org_type[]','options'=>$options,'br'=>'1'):array('desc'=>_("* Organization Type:"),'type'=>"dropdown",'name'=>'org_type','options'=>$options,'br'=>'1');  
return $type;

}
//function search_array($arr,    

function _shn_or_display_sector($error=false,$values=NULL)
{
    global $global;
    $db=$global['db'];

$q = "select option_code,option_description from field_options where field_name='opt_sector_type' order by option_description";
    $res=$db->Execute($q);
    $or_sector_type_options=array();
    while(!$res->EOF){
    
        $selected=false;
        if($values!=NULL){
            if ((array_search($res->fields[0],$values)==true) || (array_search($res->fields[0],$values)===0)){
                $selected=true; 
            }
        }
        array_push(
            $or_sector_type_options,
            array(  'drop_desc'=>$res->fields[1],
                    'value'=>$res->fields[0],
                        'selected'=>$selected
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
