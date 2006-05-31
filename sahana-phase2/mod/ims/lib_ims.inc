<?php
/**Internal Library of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
	      Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

global $global;
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_location.inc";
//include_once '';

function shn_ims_org_list(){
	    global $global;
        $db=$global['db'];
		$q = "select inv_uuid,inventory_name,parent_id from  ims_inventory_records order by inventory_name";
        $res_org=$db->Execute($q);
        $org_list=array();
        while(!$res_org==NULL && !$res_org->EOF){
        		$org_list[$res_org->fields[0]]=$res_org->fields[1];
        		$res_org->MoveNext();
        }
        return $org_list;
}
function _shn_ims_get_start_loc()
{
    global $global;
    global $conf;
    $db=$global['db'];
    $q="select value from config where module_id='or' and confkey='loc_start'";
    $res=$db->Execute($q);
    if($res->fields[0]==NULL){
       	return $conf['mod_or_ims_start_loc'];
    }else {
    	return $res->fields[0];
    }
}

function shn_ims_get_loc_range()
{
    global $global;
    global $conf;
    $db=$global['db'];
    $loc=array();
    $q="select value from config where module_id='or' and confkey='loc_range_start'";
    $res=$db->Execute($q);
    if($res->fields[0]==NULL){
       	$loc["start"]=$conf['mod_or_ims_loc_level_start'];
    }else {
    	$loc["start"]=$res->fields[0];
    }
    $q="select value from config where module_id='or' and confkey='loc_range_end'";
    $res=$db->Execute($q);
    if($res->fields[0]==NULL){
       	$loc["end"]=$conf['mod_or_ims_loc_level_end'];
    }else {
    	$loc["end"]=$res->fields[0];
    }
    return $loc;

	

	
}

function _shn_ims_action_change_javascript($change)
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

function _shn_ims_admin_javascript($name)
{
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
            var k=x[0].options.length;
            x[0].options[k]=opt;
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
function _shn_ims_get_org_loc_parents($child)
{
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



function _shn_ims_display_gender($error=false,$value=NULL,$label=NULL)
{
    if($value!=NULL){
	    $extra_opts['value']=$value;
	    //$extra_opts['req']=false;
    }else{
	    //$extra_opts['req']=true;
    }
    $label=($label==NULL)?_("Gender:"):$label;
    shn_form_opt_select('opt_gender',$label,$select_opts,$extra_opts);
}
function _shn_ims_display_org_type($error=false,$multi=false,$value=NULL)
{
    if($value!=NULL){
        $extra_opts['value']=$value;
       // $extra_opts['req']=false;
    }else{
      //  $extra_opts['req']=true;
    }
    $extra_opts['req']=true;
    if($multi){
        $select_opts="multiple='true'";
    }else{
        //$select_opts="multiple='false'";;
    }  
    shn_form_opt_select('inventory_type','',$select_opts,$extra_opts);
}

function _shn_ims_display_sector($error=false,$value=NULL)
{
    if($value!=NULL){
        $extra_opts['value']=$value;
       // $extra_opts['req']=false;
    }else{
       // $extra_opts['req']=true;
    }
    $extra_opts['req']=true;
    shn_form_opt_multi_select('opt_sector_type','','multiple="true"',$extra_opts);
}

function _shn_ims_display_contact_person($error=false,$org=true,$po_uuid=null)
{
    if(!shn_is_null($po_uuid)){
        global $global;
        $db=$global['db'];
        $q = "select address from location_details where poc_uuid={$po_uuid}";
        $res_addr=$db->Execute($q); 
        $contact_address=$res_addr->fields[0];
        $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='curr'";
        $res_phone=$db->Execute($q);
        $contact_phone=$res_phone->fields[0];
        $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='pmob'";
        $res_mobile=$db->Execute($q);
        $contact_mobile=$res_mobile->fields[0];
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
        $q = "select contact_value from contact where pgoc_uuid='{$po_uuid}' and opt_contact_type='web'";
        $res_web=$db->Execute($q);
        $contact_web=$res_web->fields[0];
    }
    if($org){
        $extra_opts['value']=$contact_name;
        shn_form_text(_("Name : "),'contact_name','size="50"',$extra_opts); 
    }
    $extra_opts['value']=$contact_address;
    shn_form_text(_("Address : "),'contact_add','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_phone;
    shn_form_text(_("Phone : "),'contact_phone','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_mobile;
    shn_form_text(_("Mobile No : "),'contact_mobile','size="50"',$extra_opts);
    $extra_opts['value']=$contact_fax;
    shn_form_text(_("Fax : "),'contact_fax','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_email;
    shn_form_text(_("Email : "),'contact_mail','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_web;
    shn_form_text(_("Website : "),'contact_web','size="50"',$extra_opts);
}

function _shn_ims_display_org_facilities($error=false,$org_id=false)
{
    if(!shn_is_null($org_id)){
        global $global;
       $db=$global['db'];
        $q = "select man_power,equipment,resources,space from  ims_inventory_records where inv_uuid='{$org_id}'";
        $res_org=$db->Execute($q);
        if(!$res_org==NULL && !$res_org->EOF){
            $man_power=$res_org->fields[0];
            $equipment=$res_org->fields[1]; 
            $resources=$res_org->fields[2]; 
	    $space=$res_org->fields[3];
        }
    }
    $extra_opts['value']=$man_power;
    shn_form_text(_("Man Power : "),'man_power','size="50"',$extra_opts);
    $extra_opts['value']=$equipment;
    shn_form_text(_("Equipment : "),'equipment','size="50"',$extra_opts);
    $extra_opts['value']=$resources;
    shn_form_text(_("Other relevant resources : "),'resources','size="50"',$extra_opts);
    $extra_opts['value']=$space;
    shn_form_text(_("Inventory Space : "),'space','size="50"',$extra_opts);
  
}

function _shn_ims_display_logininfo($error=false)
{
// for get login info
    $login_info = array(
    		       	array('desc'=>_("Account Name : "),'type'=>"text",'size'=>20,'name'=>'account_name','br'=>1),
                    array('desc'=>_("* User Name for Login: "),'type'=>"text",'size'=>20,'name'=>'user_name','br'=>1),
                    array('desc'=>_("* Password for Login: "),'type'=>"password",'size'=>20,'name'=>'password','br'=>1),
                    array('desc'=>_("* Confirm Password: "),'type'=>"password",'size'=>20,'name'=>'re_password','br'=>1)
    ); // end of getting logging info
    return $login_info;
}

function _shn_ims_display_extra($error=false)
{
    shn_form_checkbox(_("Add Operation<br> (Your Organization might be having branches or carrying out relief operations in this disaster. Then information of those operations is usefull : )"),'chk_branch',null,$chkbox_opts);
}

//-----------------------------------------------------------------------------------------------------------------
function _shn_ims_expire_date_check()
{
	global $global;
	$db=$global["db"];
	$state="expired";
	$state1="destroyed";
		
	$sql="UPDATE ims_item_records SET state='$state' WHERE ((TO_DAYS(expire_date) - TO_DAYS(CURRENT_DATE()))<0 and state!='$state1');";
	$ims=$db->Execute($sql);	
}

function _shn_ims_date_validate($date)
{
	$error_flag1=false;
	

	list($year,$month,$day)=split('[/.-]', $date);
	if($year<0 || $year>2100 )
	{
		//add_error("Year should be a value between 1900 and 2100");
		$error_flag1=true;
	}
	if($month<0 || $month>12 )
	{
		//add_error("Invalid Month");
		$error_flag1=true;
	}
	if($day<0)
	{
		//add_error("Invald Day");
		$error_flag1=true;
	}
	if(($month==1 || $month==3 || $month==5 || $month==7 || $month==8 || $month==10 || $month==12) && $day>31)
	{
		//add_error("The month doesn't have such a date ");
		$error_flag1=true;
	}
	if($month==2 && $day>29)
	{
		//add_error(SHN_ERR_IMS_INVALID_DATE);
		$error_flag=true;
	}
	if(($month==4 || $month==6 || $month==9 || $month==11) && $day>30)
	{
		//add_error("The month doesn't have such a date ");
		$error_flag1=true;
	}
	
	add_error(SHN_ERR_IMS_INVALID_DATE);
	return $error_flag1;
	
}

function _shn_ims_find_catalogid($catalog_id)
{
	global $global;
	$db=$global["db"];
	$catalog_found=false;
	$sql1="SELECT item_id FROM ims_item_records WHERE catalog_id='$catalog_id';";
	$ims1=$db->Execute($sql1);
	$item_id=$ims1->fields['item_id'];
		
					
	$sql2="SELECT inv_id FROM ims_reorder_level WHERE catalog_id='$catalog_id';";
	$ims2=$db->Execute($sql2);
	$inv_id=$ims2->fields['inv_id'];

	if($item_id!=null || $inv_id!=null)
	{
	$catalog_found=true;
	}
	else
	{
	$catalog_found=false;
	}

	return $catalog_found;
}

function _shn_ims_find_unitid($unit_id)
{
	global $global;
	$db=$global["db"];
	$unit_found=false;

	$sql1="SELECT item_id FROM ims_item_records WHERE unit='$unit_id';";
	$ims1=$db->Execute($sql1);
	$item_id=$ims1->fields['item_id'];
		
					
	$sql2="SELECT inv_id FROM ims_reorder_level WHERE unit='$unit_id';";
	$ims2=$db->Execute($sql2);
	$inv_id=$ims2->fields['inv_id'];

	$sql3="SELECT item_id FROM ims_transfer_item WHERE unit='$unit_id';";
	$ims3=$db->Execute($sql3);
	$item_id3=$ims3->fields['item_id'];

	if($item_id!=null || $inv_id!=null || $item_id3!=null)
	{
	$unit_found=true;
	}
	else
	{
	$unit_found=false;
	}

	return $unit_found;
	
}

?>
