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
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

global $global;
include_once $global['approot']."/inc/lib_form.inc";

function _shn_or_get_start_loc(){
    global $global;
    $db=$global['db'];
    $q="select value from config where module_id='or' and confkey='loc_start'";
    $res=$db->Execute($q);
    return $res->fields[0];
}







function _shn_or_action_change_javascript($change){
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

function _shn_or_admin_javascript($name){
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
function _shn_or_get_org_loc_parents($child){
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



function _shn_or_display_gender($error=false,$value=NULL,$label=NULL){
/* 
  if($value!=NULL){
	$extra_opts['value']=$value;
	$extra_opts['req']=false;
   }else{
	$extra_opts['req']=true;
}*/
    $label=($label==NULL)?"Gender:":$label;
shn_form_opt_select('opt_gender',$label,$select_opts,$extra_opts);
 
   				
}
function _shn_or_display_org_type($error=false,$multi=false,$value=NULL)
{
if($value!=NULL){
$extra_opts['value']=$value;
$extra_opts['req']=false;
}else{
$extra_opts['req']=true;
}
  if($multi){
$select_opts="multiple='true'";
}else{
//$select_opts="multiple='false'";;

}  
shn_form_opt_select('opt_org_type','',$select_opts,$extra_opts);
 
}
//function search_array($arr,    

function _shn_or_display_sector($error=false,$value=NULL)
{
if($value!=NULL){
    $extra_opts['value']=$value;
    $extra_opts['req']=false;
}else{
    $extra_opts['req']=true;
}
shn_form_opt_multi_select('opt_sector_type','','multiple="true"',$extra_opts);
//shn_form_opt_multi_select('opt_sector_type','');
}


function _shn_or_display_contact_person($error=false,$org=true,$po_uuid=null){
if(!shn_is_null($po_uuid)){
 
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
   
    
}
 if($org){
$extra_opts['value']=$contact_name;
shn_form_text(_("Name : "),'contact_name','size="50"',$extra_opts); 
}
$extra_opts['value']=$contact_address;
shn_form_text(_("Address : "),'contact_add','size="50"',$extra_opts); 
$extra_opts['value']=$contact_phone;
shn_form_text(_("Phone : "),'contact_phone','size="50"',$extra_opts); 
$extra_opts['value']=$contact_fax;
shn_form_text(_("Fax : "),'contact_fax','size="50"',$extra_opts); 
$extra_opts['value']=$contact_email;
shn_form_text(_("Email : "),'contact_mail','size="50"',$extra_opts); 
    

}

function _shn_or_display_org_facilities($error=false,$org_id=false){
if(!shn_is_null($org_id)){

    global $global;
    $db=$global['db'];
    $q = "select man_power,resources from org_main where o_uuid='{$org_id}'";
    
    $res_org=$db->Execute($q);
    if(!$res_org==NULL && !$res_org->EOF){
        
    
    $man_power=$res_org->fields[0]; 
    $resources=$res_org->fields[1]; 
}
}
$extra_opts['value']=$man_power;
shn_form_text(_("Man Power : "),'man_power','size="50"',$extra_opts);
$extra_opts['value']=$resources;
shn_form_text(_("Other relevant resources : "),'resources','size="50"',$extra_opts);
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

//$chkbox_opts['value']=true;
shn_form_checkbox(_("Add Operation<br> (Your Organization might be having branches or carrying out relief operations in this disaster. Then information of those operations is usefull : "),'chk_branch',null,$chkbox_opts);
}

function _shn_or_district_villages($bsd_district){
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

function _shn_or_province_villages($bsd_province){
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
