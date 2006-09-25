<?php
/**Internal Library of the Inventory Management system 
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
* @subpackage ims
*/

global $global;
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_location.inc";
//include_once '';
include_once $global['approot'].'/mod/or/lib_or.inc';
include_once $global['approot'].'/3rd//phplot/phplot_ims.php';


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

    if($error_flag1==true)
    {
	add_error(SHN_ERR_IMS_INVALID_DATE);
        return $error_flag1;
    }
    else
    {
        return $error_flag1;
    }
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

//*******************************************************SOC*******************************************************
function _shn_ims_date_conversion($date)
{
	list($year,$month,$day) = split("-",$date);
	$convert_date=$month."-".$day."-".$year;
	return $convert_date;
}
function _shn_ims_count_days($start, $end)
{
    if( $start != '0000-00-00' and $end != '0000-00-00' )
    {
        $timestamp_start = strtotime($start);
        $timestamp_end = strtotime($end);
        if( $timestamp_start >= $timestamp_end ) return 0;
        $start_year = date("Y",$timestamp_start);
        $end_year = date("Y", $timestamp_end);
        $num_days_start = date("z",strtotime($start));
        $num_days_end = date("z", strtotime($end));
        $num_days = 0;
        $i = 0;
        if( $end_year > $start_year )
        {
           while( $i < ( $end_year - $start_year ) )
           {
              $num_days = $num_days + date("z", strtotime(($start_year + $i)."-12-31"));
              $i++;
           }
         }
         return ( $num_days_end + $num_days ) - $num_days_start;
    }
    else
    {
         return 0;
     }
}

function _shn_ims_smoothing($forcasted_value,$actual_value,$alpha)
{
	 //ft+1=(1-?)ft+?*at
		
	//$alpha=0.3;
	$forcast_value=((1-$alpha)*$forcasted_value)+($alpha*$actual_value);
	return $forcast_value;
	
}

function _shn_ims_datediff($dformat, $endDate, $beginDate)
{
$date_parts1=explode($dformat, $beginDate);
$date_parts2=explode($dformat, $endDate);
$start_date=gregoriantojd($date_parts1[0], $date_parts1[1], $date_parts1[2]);
$end_date=gregoriantojd($date_parts2[0], $date_parts2[1], $date_parts2[2]);
return $end_date - $start_date;

}

function _shn_ims_total_amount($catalog_id,$inv_id)
{
	global $global;
	$db=$global["db"];

	//if(!$inv_id==NULL)
	//{
		$sql1="SELECT * FROM ims_item_records WHERE inv_id='$inv_id' AND catalog_id='$catalog_id';";
		$ims1=$db->Execute($sql1);
		$sum_amount=0;
		while(!$ims1==NULL && !$ims1->EOF)
		{
			$amount=$ims2->fields['amount'];
			$unit=$ims2->fields['unit'];
			
			$base_unit=convert_to_base_unit($unit);
			$converted_amount=$amount*unit_converter($base_unit,$unit);
            
                	$sum_amount=$sum_amount + $converted_amount;
			$ims1->MoveNext();			
		}
		
	//}

	return $sum_amount;

	
}

function _shn_ims_sum_amount($catalog_id,$inv_id)
{
	global $global;
	$db=$global["db"];
	if($inv_id=="all")
	{
		$sql1="SELECT * FROM ims_item_records WHERE catalog_id='$catalog_id';";
		$ims1=$db->Execute($sql1);
	}
	else
	{
		$sql1="SELECT * FROM ims_item_records WHERE inv_id='$inv_id' AND catalog_id='$catalog_id';";
		$ims1=$db->Execute($sql1);
	}
	$sum_amount=0;
	while(!$ims1==NULL && !$ims1->EOF)
	{
		$amount=$ims1->fields['amount'];
		$unit=$ims1->fields['unit'];
			
		$base_unit=convert_to_base_unit($unit);
		$converted_amount=$amount*unit_converter($base_unit,$unit);
            
                $sum_amount=$sum_amount + $converted_amount;
		$ims1->MoveNext();			
	}
	return $sum_amount;
}

function _shn_ims_first_data($inv_id,$catalog_id)
{
	global $global;
	$db=$global["db"];
	$sql1="SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
	$ims1=$db->Execute($sql1);
	$date_inv=$ims1->fields['added_date'];
	$date_inv_convert=_shn_ims_date_conversion($date_inv);
//has to be commented	
	$date_inv_convert="01-08-2006";
	
	$current_date=date("m-d-Y");
	$number_of_days=_shn_ims_datediff('-',$current_date,$date_inv_convert);
	$temp=$number_of_days-7;
	if($temp>0)
	{
		$days_after_inv_date=date("Y-m-d",time() - ($temp*24*60*60));
	}
	if($temp<0)
	{
		$days_after_inv_date=date("Y-m-d",time() -($number_of_days*24*60*60));
		
	}

	$sql2="SELECT * FROM ims_item_records WHERE catalog_id='$catalog_id' AND inv_id='$inv_id' AND (TO_DAYS(inserted_date) - TO_DAYS($date_inv))<7;";
	$ims2=$db->Execute($sql2);
	$sum_amount=0;
	while(!$ims2==NULL && !$ims2->EOF)
	{
		$amount=$ims1->fields['amount'];
		$unit=$ims1->fields['unit'];
			
		$base_unit=convert_to_base_unit($unit);
		$converted_amount=$amount*unit_converter($base_unit,$unit);
            
                $sum_amount=$sum_amount + $converted_amount;
		$ims2->MoveNext();		
	}
	//return $sum_amount;
	//$week=date("d-m-Y",time() + 604800);
	//$date_amount_inv=date("Y-m-d",time() - 604800);
	//$date_inv_week=_shn_ims_datediff('-',$date_inv_week,$date);
	
}

function _shn_ims_smoothing_constant($catalog_id,$inv_id)
{
	global $global;
	$db=$global["db"];

	$sql1="SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' AND inv_id='$inv_id' ORDER BY week DESC;";
	$ims1=$db->Execute($sql1);
	
	$week=$ims1->fields['week'];
	
	$temp=$week+1;
	$alpha=2/$temp;

	return $alpha;
	
} 

function _shn_ims_weekafter($fyear, $fmonth, $fday)
{
	return date ("Y-m-d", mktime (0,0,0,$fmonth,$fday+7,$fyear));
}

function _shn_ims_timeafter($fyear, $fmonth, $fday,$time_period)
{
	return date ("Y-m-d", mktime (0,0,0,$fmonth,$fday+$time_period,$fyear));
}

function _shn_ims_insert_data_to_predict($catalog_id,$inv_id,$time_period)
{
	global $global;
	$db=$global["db"];

	$sql1="SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
	$ims1=$db->Execute($sql1);
	$date_inv=$ims1->fields['added_date'];
	$date_inv_convert=_shn_ims_date_conversion($date_inv);
	$current_date=date("Y-m-d");

	$week=0;
	$date_diff=_shn_ims_count_days($date_inv,$current_date);

	$item_state_destroyed="destroyed";
	//print $date_diff;
	//print ("M");
	//$sum_amount=0;
	for($i=$date_diff;$i>=0;$i-=$time_period)	
	//while(_shn_ims_count_days($date_inv,$current_date)<1 && _shn_ims_count_days($date_inv,$current_date)>0 )
	{
		$date_inv_temp=$date_inv;
		//$sql2="SELECT * FROM ims_item_records WHERE inv_id='$inv_id' AND catalog_id='$catalog_id' AND (TO_DAYS(inserted_date) - TO_DAYS($date_inv_temp))<7;";
		$sql2="SELECT * FROM ims_item_records WHERE inv_id='$inv_id' AND catalog_id='$catalog_id' AND state!='$item_state_destroyed';";
		$ims2=$db->Execute($sql2);
		//print $sql2;
		$sum_amount=0;
		$sum_amount_temp=0;
		while(!$ims2==NULL && !$ims2->EOF)
		{
			$amount=$ims2->fields['amount'];
			
			$unit=$ims2->fields['unit'];
			$inserted_date=$ims2->fields['inserted_date'];

			if(_shn_ims_count_days($date_inv_temp,$current_date)<_shn_ims_count_days($inserted_date,$current_date)||_shn_ims_count_days($date_inv_temp,$current_date)==_shn_ims_count_days($inserted_date,$current_date))
			{
			
			$base_unit=convert_to_base_unit($unit);
			$converted_amount=$amount*unit_converter($base_unit,$unit);
            
                	$sum_amount=$sum_amount + $converted_amount;
			$sum_amount_temp=$sum_amount;
			}
			else
			{
				$sum_amount_temp=$sum_amount;
			}
			$ims2->MoveNext();
		}
		$actual_value=$sum_amount_temp;
		//print $actua_value;
		//print ("kkk");
		$week=$week+1;
		$temp=$week+1;
		$alpha=2/$temp;
		
		//print $alpha;
		//print "<br>";
		//print $week;
		if($week==1)
		{
			$forecasted_value=0;
			
			$forecasted_value_temp=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
		}
		else
		{
			
			//$alpha_smoothing=1-$alpha;
			$forecasted_value=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
			//$actual_value_smoothing=$alpha*$actual_value;
			//$forecasted_value_smoothing=$alpha_smoothing*$forcasted_value;
			//$forecasted_value=$forecasted_value_smoothing + $actual_value_smoothing;
		}
		//print $forecasted_value.",";
		$sql3="INSERT INTO ims_optimization (catalog_id,inv_id,week,actual_value,forecasted_value,unit) VALUES ('$catalog_id','$inv_id','$week','$sum_amount_temp','$forecasted_value','$base_unit');"; 
		$ims3=$db->Execute($sql3);
		//print $sql3;
		list($year,$month,$day) = split("-",$date_inv);
		$date_inv=_shn_ims_timeafter($year, $month, $day,$time_period);
		//print $date_inv;
		if($week==1)
		{
			$forecasted_value=$forecasted_value_temp;
		}
		else
		{
			;
		}
	}

	//$sql4="SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' AND inv_id='$inv_id' ORDER BY week DESC;";
	//$ims4=$db->Execute($sql4);
	//print $sql4;
	//$week=$ims4->fields['week'];
	//print $week;
	
}

function _shn_ims_predict_sending_items($catalog_id,$inv_id,$time_period)
{
	global $global;
	$db=$global["db"];

	$sql1="SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
	$ims1=$db->Execute($sql1);
	$date_inv=$ims1->fields['added_date'];
	$date_inv_convert=_shn_ims_date_conversion($date_inv);
	$current_date=date("Y-m-d");

	$week=0;
	$date_diff=_shn_ims_count_days($date_inv,$current_date);

	$item_state_destroyed="destroyed";
	//print $date_diff;
	//print ("M");
	//$sum_amount=0;
	for($i=$date_diff;$i>=0;$i-=$time_period)	
	//while(_shn_ims_count_days($date_inv,$current_date)<1 && _shn_ims_count_days($date_inv,$current_date)>0 )
	{
		$date_inv_temp=$date_inv;
		//$sql2="SELECT * FROM ims_item_records WHERE inv_id='$inv_id' AND catalog_id='$catalog_id' AND (TO_DAYS(inserted_date) - TO_DAYS($date_inv_temp))<7;";
		$sql2="SELECT * FROM ims_transfer_item WHERE inv_id_from='$inv_id' AND catalog_id='$catalog_id';";
		$ims2=$db->Execute($sql2);
		//print $sql2;
		$sum_amount=0;
		$sum_amount_temp=0;
		$amount=0;
		$converted_amount=0;
		while(!$ims2==NULL && !$ims2->EOF)
		{
			$amount=$ims2->fields['amount_send'];
			//print $amount;
			$unit=$ims2->fields['unit'];
			$inserted_date=$ims2->fields['date_send'];

			//if(_shn_ims_count_days($date_inv_temp,$current_date)<_shn_ims_count_days($inserted_date,$current_date)||_shn_ims_count_days($date_inv_temp,$current_date)==_shn_ims_count_days($inserted_date,$current_date))
			if(_shn_ims_count_days($date_inv_temp,$current_date)==_shn_ims_count_days($inserted_date,$current_date))
			{
			
			$base_unit=convert_to_base_unit($unit);
			$converted_amount=$amount*unit_converter($base_unit,$unit);
            
                	$sum_amount=$sum_amount + $converted_amount;
			$sum_amount_temp=$sum_amount;
			}
			else
			{
				$sum_amount_temp=$sum_amount;
			}
			$ims2->MoveNext();
		}
		$actual_value=$sum_amount_temp;
		//print $actua_value;
		//print ("kkk");
		$week=$week+1;
		$temp=$week+1;
		$alpha=2/$temp;
		
		//print $alpha;
		//print "\n";
		//print $week;
		if($week==1)
		{
			$forecasted_value=0;
			
			$forecasted_value_temp=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
		}
		else
		{
			/*print $actual_value;
			print "<br>";
			print $forecasted_value;
			print "<br>";
			print $alpha;
			print "<br>";*/
			$forecasted_value=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
			
		}
		//print $forecasted_value.",";
		$sql3="INSERT INTO ims_optimization (catalog_id,inv_id,week,actual_value,forecasted_value,unit) VALUES ('$catalog_id','$inv_id','$week','$sum_amount_temp','$forecasted_value','$base_unit');"; 
		$ims3=$db->Execute($sql3);
		$sum_amount_temp=0;
		//print $sql3;
		list($year,$month,$day) = split("-",$date_inv);
		$date_inv=_shn_ims_timeafter($year, $month, $day,$time_period);
		//print $date_inv;
		if($week==1)
		{
			$forecasted_value=$forecasted_value_temp;
		}
		else
		{
			;
		}
	}

}

function _shn_ims_predict_receiving_items($catalog_id,$inv_id,$time_period)
{

	global $global;
	$db=$global["db"];

	$sql1="SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
	$ims1=$db->Execute($sql1);
	$date_inv=$ims1->fields['added_date'];
	$date_inv_convert=_shn_ims_date_conversion($date_inv);
	$current_date=date("Y-m-d");

	$week=0;
	$date_diff=_shn_ims_count_days($date_inv,$current_date);

	$received_item_id=-1;

	$item_state_destroyed="destroyed";
	//print $date_diff;
	//print ("M");
	//$sum_amount=0;
	for($i=$date_diff;$i>=0;$i-=$time_period)	
	//while(_shn_ims_count_days($date_inv,$current_date)<1 && _shn_ims_count_days($date_inv,$current_date)>0 )
	{
		$date_inv_temp=$date_inv;
		//$sql2="SELECT * FROM ims_item_records WHERE inv_id='$inv_id' AND catalog_id='$catalog_id' AND (TO_DAYS(inserted_date) - TO_DAYS($date_inv_temp))<7;";
		$sql2="SELECT * FROM ims_transfer_item WHERE inv_id_to='$inv_id' AND catalog_id='$catalog_id' AND received_item_id!='$received_item_id';";
		$ims2=$db->Execute($sql2);
		//print $sql2;
		$sum_amount=0;
		$sum_amount_temp=0;
		while(!$ims2==NULL && !$ims2->EOF)
		{
			$amount=$ims2->fields['amount_received'];
			
			$unit=$ims2->fields['unit'];
			$inserted_date=$ims2->fields['date_received'];

			//if(_shn_ims_count_days($date_inv_temp,$current_date)<_shn_ims_count_days($inserted_date,$current_date)||_shn_ims_count_days($date_inv_temp,$current_date)==_shn_ims_count_days($inserted_date,$current_date))
			if(_shn_ims_count_days($date_inv_temp,$current_date)==_shn_ims_count_days($inserted_date,$current_date))
			{
			
			$base_unit=convert_to_base_unit($unit);
			$converted_amount=$amount*unit_converter($base_unit,$unit);
            
                	$sum_amount=$sum_amount + $converted_amount;
			$sum_amount_temp=$sum_amount;
			}
			else
			{
				$sum_amount_temp=$sum_amount;
			}
			$ims2->MoveNext();
		}
		$actual_value=$sum_amount_temp;
		//print $actua_value;
		//print ("kkk");
		$week=$week+1;
		$temp=$week+1;
		$alpha=2/$temp;
		
		//print $alpha;
		//print "\n";
		//print $week;
		if($week==1)
		{
			$forecasted_value=0;
			
			$forecasted_value_temp=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
		}
		else
		{
			/*print $actual_value;
			print "<br>";
			print $forecasted_value;
			print "<br>";
			print $alpha;
			print "<br>";*/
			$forecasted_value=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
			
		}
		//print $forecasted_value.",";
		$sql3="INSERT INTO ims_optimization (catalog_id,inv_id,week,actual_value,forecasted_value,unit) VALUES ('$catalog_id','$inv_id','$week','$sum_amount_temp','$forecasted_value','$base_unit');"; 
		$ims3=$db->Execute($sql3);
		//print $sql3;

		$sum_amount=0;
		
		list($year,$month,$day) = split("-",$date_inv);
		$date_inv=_shn_ims_timeafter($year, $month, $day,$time_period);
		//print $date_inv;
		if($week==1)
		{
			$forecasted_value=$forecasted_value_temp;
		}
		else
		{
			;
		}
	}

}



function _shn_ims_predict_both_items($catalog_id,$inv_id,$time_period)
{

	global $global;
	$db=$global["db"];

	$sql1="SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
	$ims1=$db->Execute($sql1);
	$date_inv=$ims1->fields['added_date'];
	$date_inv_convert=_shn_ims_date_conversion($date_inv);
	$current_date=date("Y-m-d");

	$week=0;
	$date_diff=_shn_ims_count_days($date_inv,$current_date);

	$received_item_id=-1;

	$item_state_destroyed="destroyed";
	//print $date_diff;
	//print ("M");
	//$sum_amount=0;
	for($i=$date_diff;$i>=0;$i-=$time_period)	
	//while(_shn_ims_count_days($date_inv,$current_date)<1 && _shn_ims_count_days($date_inv,$current_date)>0 )
	{
		$date_inv_temp=$date_inv;
		//$sql2="SELECT * FROM ims_item_records WHERE inv_id='$inv_id' AND catalog_id='$catalog_id' AND (TO_DAYS(inserted_date) - TO_DAYS($date_inv_temp))<7;";
		$sql2="SELECT * FROM ims_transfer_item WHERE inv_id_to='$inv_id' AND catalog_id='$catalog_id' AND received_item_id!='$received_item_id';";
		$ims2=$db->Execute($sql2);
		//print $sql2;
		$sum_amount=0;
		$sum_amount_temp=0;
		while(!$ims2==NULL && !$ims2->EOF)
		{
			$amount=$ims2->fields['amount_received'];
			
			$unit=$ims2->fields['unit'];
			$inserted_date=$ims2->fields['date_received'];

			if(_shn_ims_count_days($date_inv_temp,$current_date)<_shn_ims_count_days($inserted_date,$current_date)||_shn_ims_count_days($date_inv_temp,$current_date)==_shn_ims_count_days($inserted_date,$current_date))
			{
			
			$base_unit=convert_to_base_unit($unit);
			$converted_amount=$amount*unit_converter($base_unit,$unit);
            
                	$sum_amount=$sum_amount + $converted_amount;
			$sum_amount_temp=$sum_amount;
			}
			else
			{
				$sum_amount_temp=$sum_amount;
			}
			$ims2->MoveNext();
		}
		$actual_value=$sum_amount_temp;
		//print $actua_value;
		//print ("kkk");
		$week=$week+1;
		$temp=$week+1;
		$alpha=2/$temp;
		
		//print $alpha;
		//print "\n";
		//print $week;
		/*if($week==1)
		{
			$forecasted_value=0;
			
			$forecasted_value_temp=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
		}
		else
		{
			print $actual_value;
			print "<br>";
			print $forecasted_value;
			print "<br>";
			print $alpha;
			print "<br>";
			$forecasted_value=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
			
		}*/
		$forecasted_value=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
		//print $forecasted_value.",";
		$sql3="INSERT INTO ims_optimization (catalog_id,inv_id,week,actual_value,forecasted_value,unit) VALUES ('$catalog_id','$inv_id','$week','$sum_amount_temp','$forecasted_value','$base_unit');"; 
		$ims3=$db->Execute($sql3);
		//print $sql3;

		$sum_amount=0;
		
		list($year,$month,$day) = split("-",$date_inv);
		$date_inv=_shn_ims_timeafter($year, $month, $day,$time_period);
		//print $date_inv;
		/*if($week==1)
		{
			$forecasted_value=$forecasted_value_temp;
		}
		else
		{
			;
		}*/
	}

}



function _shn_ims_get_alternate_item_amount($catalog_id,$inv_id)
{
	$item_state="destroyed";
	$sql3="SELECT * FROM ims_alternate WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
	$ims3=$db->Execute($sql3);
	//print $sql3;
	while(!$ims3==NULL && !$ims3->EOF)
	{
		$alternate=$ims3->fields['alternate'];
		
		if($inv_id==0)
		{
			$sql4="SELECT * FROM ims_item_records WHERE catalog_id='$alternate' AND state!='$item_state';";
		}
		else
		{
			$sql4="SELECT * FROM ims_item_records WHERE catalog_id='$alternate' AND inv_id='$inv_id' AND state!='$item_state';";
		}
		$ims4=$db->Execute($sql4);
		//print $sql4;
		while(!$ims4==NULL && !$ims4->EOF)
		{
			$item_id=$ims4->fields["item_id"];
            		$suplier_id=$ims4->fields["suplier_id"];
            		$suplier_name_array=_shn_or_get_suplier_name($suplier_id);
            		$suplier_name=$suplier_name_array[$suplier_id];
	    		$item_name=$ims4->fields['item_name'];

	    		$inventory_id=$ims4->fields['inv_id'];
            
            
            		$amount=$ims4->fields["amount"];
            
            
            		$unit=$ims4->fields["unit"];
            		$base_unit=convert_to_base_unit($unit);
            
            		$converted_amount=$amount*unit_converter($base_unit,$unit);
            		//print $converted_amount;
            		$sum_amount=$sum_amount + $converted_amount;
	    		$alternate_sum_amount=$alternate_sum_amount + $converted_amount;
            		//print $sum_amount;
            		$unit_name=get_unit_name($unit);
            		$base_unit_name=get_unit_name($base_unit);
            		$state=$ims->fields['state'];
         
	
			$sql5="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inventory_id';";
        		$ims5=$db->Execute($sql5);
               		$inventory_name=$ims5->fields['inventory_name'];

			$ims4->MoveNext();
		}

		$ims3->MoveNext();
	}

}




function _shn_ims_bar_chart_inventory($data,$catalog_array,$i,$y)
{
//include ( "../3rd/phplot1/phplot.php");
$graph = new PHPlot(700,500);

//$graph->SetDataType( "linear-linear"); //text-data
$graph->SetDataType("text-data");  //Must be called before SetDataValues

// Specify some data
/*$data = array(
    array(  "a", 2000,1500, 0, 100, 600,200),
    array(  "b", 2010,1000, 100, 150,200,300),
    array(  "c", 2015,500, 700, 179, 400,500),
    array(  "dd",2020,200,1000,979, 1000,600),
    array(  "e", 2025,100,1200,78,150,700),
    array(  "f", 2030,50, 1450,343, 1300,800)
);*/
//$data = array($temp);
$graph->SetDataValues($data);
 $graph->SetFileFormat("png"); // parameters = "png" or "jpg" or "gif"

//Specify plotting area details
$graph->SetImageArea(700,500);
/*commented types are ok with the data*/
//$graph->SetPlotType( "lines");
//$graph->SetPlotType( "linepoints");
//$graph->SetPlotType( "points");
//$graph->SetPlotType( "area");
//$graph->SetPlotType( "thinbarline");
//$graph->SetPlotType( "squared");
//$graph->SetPlotType( "pie");
$graph->SetPlotType( "bars");
//$graph->SetPlotType( "stackedbars");

$graph->SetTitleFontSize( "5"); // the max value of font size is 5
$graph->SetTitle( "Forecasting by Inventory");

$graph->SetLegend($catalog_array);
//$graph->SetPlotAreaWorld(2000,0,2050,2500); // parameters = ($starting_val_of_x_axis, $s_val_of_y, $ending_val_of_x, $e_val_of_y)
$graph->SetPlotBgColor( "red");
$graph->SetPlotBorderType( "left");
$graph->SetBackgroundColor( "orange"); // set the chart background

//you can set the x title by one line or as commented three lines
$graph->SetXTitle("Item", "both"); // para = ($title, $position); $postion= plotup or plotdown or both or none
$graph->SetYTitle('Amount',"both"); // plotright or plotleft or both or both

//Define the X axis
/*$graph->SetXLabel( "Year");
$graph->SetHorizTickIncrement( "5");
$graph->SetXGridLabelType( "title");*/

//Define the Y axis
$graph->SetVertTickIncrement( "500"); //the gap between two values in the Y axis
$graph->SetPrecisionY( "0"); // determine how many decimal points should be there in Y axis values
$graph->SetYGridLabelType( "data");
$graph->SetLightGridColor( "blue");
$graph->SetOutputFile("barChart.png");

$y=$y+2000;
//$graph->SetNewPlotAreaPixels(70,120,375,220);
$graph->SetPlotAreaWorld(0,0,$i,$y);
$graph->DrawGraph();
}






function _shn_ims_bar_chart($data,$j,$max)
{
//include ( "../3rd/phplot1/phplot.php");
$graph = new PHPlot(700,500);

//$graph->SetDataType( "linear-linear"); //text-data
$graph->SetDataType("text-data");  //Must be called before SetDataValues

// Specify some data
/*$data = array(
    array(  "a", 2000,1500, 0, 100, 600,200),
    array(  "b", 2010,1000, 100, 150,200,300),
    array(  "c", 2015,500, 700, 179, 400,500),
    array(  "dd",2020,200,1000,979, 1000,600),
    array(  "e", 2025,100,1200,78,150,700),
    array(  "f", 2030,50, 1450,343, 1300,800)
);*/
$graph->SetDataValues($data);
 $graph->SetFileFormat("png"); // parameters = "png" or "jpg" or "gif"

//Specify plotting area details
$graph->SetImageArea(700,500);
/*commented types are ok with the data*/
//$graph->SetPlotType( "lines");
//$graph->SetPlotType( "linepoints");
//$graph->SetPlotType( "points");
//$graph->SetPlotType( "area");
//$graph->SetPlotType( "thinbarline");
//$graph->SetPlotType( "squared");
//$graph->SetPlotType( "pie");
$graph->SetPlotType( "bars");
//$graph->SetPlotType( "stackedbars");

$graph->SetTitleFontSize( "5"); // the max value of font size is 5
$graph->SetTitle( "Forecasting by item");

$graph->SetLegend(array("actual value","forecasted value"));
//$graph->SetPlotAreaWorld(2000,0,2050,2500); // parameters = ($starting_val_of_x_axis, $s_val_of_y, $ending_val_of_x, $e_val_of_y)
$graph->SetPlotBgColor( "red");
$graph->SetPlotBorderType( "left");
$graph->SetBackgroundColor( "orange"); // set the chart background

//you can set the x title by one line or as commented three lines
$graph->SetXTitle("Time Period", "both"); // para = ($title, $position); $postion= plotup or plotdown or both or none
$graph->SetYTitle('Amount',"both"); // plotright or plotleft or both or both

//Define the X axis
/*$graph->SetXLabel( "Year");
$graph->SetHorizTickIncrement( "5");
$graph->SetXGridLabelType( "title");*/

//Define the Y axis
$graph->SetVertTickIncrement( "500"); //the gap between two values in the Y axis
$graph->SetPrecisionY( "0"); // determine how many decimal points should be there in Y axis values
$graph->SetYGridLabelType( "data");
$graph->SetLightGridColor( "blue");
$graph->SetOutputFile("barChart.png");

$max=$max+2000;


//$graph->SetNewPlotAreaPixels(70,120,375,220);
$graph->SetPlotAreaWorld(0,0,$j,$max);
$graph->DrawGraph();
}

function _shn_ims_line_chart($data,$x,$y)
{
	$graph = new PHPlot(700,500);

//$graph->SetDataType( "linear-linear"); //text-data
$graph->SetDataType("text-data");  //Must be called before SetDataValues

// Specify some data
/*$data = array(
    array(  "a", 2000,1500, 0, 100, 600,200),
    array(  "b", 2010,1000, 100, 150,200,300),
    array(  "c", 2015,500, 700, 179, 400,500),
    array(  "dd",2020,200,1000,979, 1000,600),
    array(  "e", 2025,100,1200,78,150,700),
    array(  "f", 2030,50, 1450,343, 1300,800)
);*/

/*$data = array(
	array("a",2000,1000),
	array("b",2000,1000)
);*/

$graph->SetDataValues($data);
 $graph->SetFileFormat("png"); // parameters = "png" or "jpg" or "gif"

//Specify plotting area details
$graph->SetImageArea(700,500);
/*commented types are ok with the data*/
$graph->SetPlotType( "lines");
//$graph->SetPlotType( "linepoints");
//$graph->SetPlotType( "points");
//$graph->SetPlotType( "area");
//$graph->SetPlotType( "thinbarline");
//$graph->SetPlotType( "squared");
//$graph->SetPlotType( "pie");
//$graph->SetPlotType( "bars");
//$graph->SetPlotType( "stackedbars");

$graph->SetTitleFontSize( "5"); // the max value of font size is 5
$graph->SetTitle( "Forecasting by Item");

$graph->SetLegend(array("Re-Order level","forecasted value"));
//$graph->SetPlotAreaWorld(2000,0,2050,2500); // parameters = ($starting_val_of_x_axis, $s_val_of_y, $ending_val_of_x, $e_val_of_y)
$graph->SetPlotBgColor( "red");
$graph->SetPlotBorderType( "left");
$graph->SetBackgroundColor( "orange"); // set the chart background

//you can set the x title by one line or as commented three lines
$graph->SetXTitle("time", "both"); // para = ($title, $position); $postion= plotup or plotdown or both or none
$graph->SetYTitle('amount',"both"); // plotright or plotleft or both or both

//Define the X axis
/*$graph->SetXLabel( "Year");
$graph->SetHorizTickIncrement( "5");
$graph->SetXGridLabelType( "title");*/

//Define the Y axis
$graph->SetVertTickIncrement( "500"); //the gap between two values in the Y axis
$graph->SetPrecisionY( "0"); // determine how many decimal points should be there in Y axis values
$graph->SetYGridLabelType( "data");
$graph->SetLightGridColor( "blue");
$graph->SetOutputFile("lineChart.png");

$y=$y+2000;

//$graph->SetNewPlotAreaPixels(70,120,375,220);
$graph->SetPlotAreaWorld(0,0,$x,$y);
$graph->DrawGraph();
}

function _shn_ims_pie_chart($data,$catalog_array)
{
	$graph = new PHPlot(700,500);

//$graph->SetDataType( "linear-linear"); //text-data
$graph->SetDataType("text-data");  //Must be called before SetDataValues

$data2 = array($data);

// Specify some data
/*$data1 = array(
    array(  "a", 2000,1500, 0, 100, 600,200),
    array(  "b", 2010,1000, 100, 150,200,300),
    array(  "c", 2015,500, 700, 179, 400,500),
    array(  "dd",2020,200,1000,979, 1000,600),
    array(  "e", 2025,100,1200,78,150,700),
    array(  "f", 2030,50, 1450,343, 1300,800)
);*/
//print ("<br>");
//print ("Mahesh");
//print_r($data2);
$graph->SetDataValues($data);
 $graph->SetFileFormat("png"); // parameters = "png" or "jpg" or "gif"

//Specify plotting area details
$graph->SetImageArea(700,500);
/*commented types are ok with the data*/
//$graph->SetPlotType( "lines");
//$graph->SetPlotType( "linepoints");
//$graph->SetPlotType( "points");
//$graph->SetPlotType( "area");
//$graph->SetPlotType( "thinbarline");
//$graph->SetPlotType( "squared");
$graph->SetPlotType( "pie");
//$graph->SetPlotType( "bars");
//$graph->SetPlotType( "stackedbars");

$graph->SetTitleFontSize( "5"); // the max value of font size is 5
$graph->SetTitle( "Forecasting by Inventory");

//$graph->SetLegend(array("2000","2001","2002","2003", "2004", "2005", "2006", "2007"));
$graph->SetLegend($catalog_array);
//$graph->SetPlotAreaWorld(2000,0,2050,2500); // parameters = ($starting_val_of_x_axis, $s_val_of_y, $ending_val_of_x, $e_val_of_y)
$graph->SetPlotBgColor( "red");
$graph->SetPlotBorderType( "left");
$graph->SetBackgroundColor( "orange"); // set the chart background

//you can set the x title by one line or as commented three lines
//$graph->SetXTitle("SD X title", "both"); // para = ($title, $position); $postion= plotup or plotdown or both or none
//$graph->SetYTitle('SD Y title',"both"); // plotright or plotleft or both or both

//Define the X axis
/*$graph->SetXLabel( "Year");
$graph->SetHorizTickIncrement( "5");
$graph->SetXGridLabelType( "title");*/

//Define the Y axis
$graph->SetVertTickIncrement( "500"); //the gap between two values in the Y axis
$graph->SetPrecisionY( "0"); // determine how many decimal points should be there in Y axis values
$graph->SetYGridLabelType( "data");
$graph->SetLightGridColor( "blue");
$graph->SetOutputFile("pieChart.png");


//$graph->SetNewPlotAreaPixels(70,120,375,220);
$graph->SetPlotAreaWorld(0,0,7,2000);
$graph->DrawGraph();
}



function _shn_ims_chart_test()
{
$graph = new PHPlot(700,500);

//$graph->SetDataType( "linear-linear"); //text-data
$graph->SetDataType("text-data");  //Must be called before SetDataValues

$data = array(
    array(  "a", 2000,1500),
    array(  "b", 2010,1000),
    array(  "c", 2015,500),
    array(  "dd",2020,2000),
    array(  "e", 2025,100),
    //array(  "f", 2030,50),
   // array(  "f", 2030,50),
    //array(  "f", 2030,50)
);

// Specify some data
$data123 = array(
    array(  "a", 2000,1500, 0, 100, 600,200),
    array(  "b", 2010,1000, 100, 150,200,300),
    array(  "c", 2015,500, 700, 179, 400,500),
    array(  "d",2020,200,1000,979, 1000,600),
    array(  "e", 2025,100,1200,78,150,700),
    array(  "f", 2030,50, 1450,343, 1300,800)
   // array(  "g", 2030,50, 1450,343, 1300,800),
    //array(  "h", 2030,50, 1450,343, 1300,800)
);
$graph->SetDataValues($data);
 $graph->SetFileFormat("png"); // parameters = "png" or "jpg" or "gif"

//Specify plotting area details
$graph->SetImageArea(700,500);
/*commented types are ok with the data*/
//$graph->SetPlotType( "lines");
//$graph->SetPlotType( "linepoints");
//$graph->SetPlotType( "points");
//$graph->SetPlotType( "area");
//$graph->SetPlotType( "thinbarline");
//$graph->SetPlotType( "squared");
//$graph->SetPlotType( "pie");
$graph->SetPlotType( "bars");
//$graph->SetPlotType( "stackedbars");

$graph->SetTitleFontSize( "5"); // the max value of font size is 5
$graph->SetTitle( "This is SD test chart");

$graph->SetLegend(array("2000","2001","2002","2003", "2004", "2005", "2006", "2007"));
//$graph->SetPlotAreaWorld(2000,0,2050,2500); // parameters = ($starting_val_of_x_axis, $s_val_of_y, $ending_val_of_x, $e_val_of_y)
$graph->SetPlotBgColor( "red");
$graph->SetPlotBorderType( "left");
$graph->SetBackgroundColor( "orange"); // set the chart background

//you can set the x title by one line or as commented three lines
$graph->SetXTitle("SD X title", "both"); // para = ($title, $position); $postion= plotup or plotdown or both or none
$graph->SetYTitle('SD Y title',"both"); // plotright or plotleft or both or both

//Define the X axis
/*$graph->SetXLabel( "Year");
$graph->SetHorizTickIncrement( "5");
$graph->SetXGridLabelType( "title");*/

//Define the Y axis
$graph->SetVertTickIncrement( "500"); //the gap between two values in the Y axis
$graph->SetPrecisionY( "0"); // determine how many decimal points should be there in Y axis values
$graph->SetYGridLabelType( "data");
$graph->SetLightGridColor( "blue");
$graph->SetOutputFile("barChart.png");


//$graph->SetNewPlotAreaPixels(70,120,375,220);
$graph->SetPlotAreaWorld(0,0,6,2000);
$graph->DrawGraph();
}


function _shn_ims_double_smoothing($catalog_id,$inv_id,$time_period)
{
	global $global;
	$db=$global["db"];

	$sql1="SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
	$ims1=$db->Execute($sql1);
	while(!$ims1==NULL && !$ims1->EOF)
	{
		$week=$ims1->fields['week'];
		$forecasted_value=$ims1->fields['forecasted_value'];

		$beta=2/($week+1);

		if($week==1)
		{
			$double_forecasted_value=0;
			//continue;
		}
		else
		{
			$double_forecasted_value=($beta*($forecasted_value-$temp)) + ((1-$beta)*$double_forecasted_value_temp);
			
		}

	$sql2="UPDATE ims_optimization SET double_forecasted_value='{$double_forecasted_value}' WHERE catalog_id='$catalog_id' AND inv_id='$inv_id' AND week='$week';";
	$ims2=$db->Execute($sql2);



		$double_forecasted_value_temp=$double_forecasted_value;
		$temp=$forecasted_value;
		$ims1->MoveNext();
	}

	//return $double_forecasted_value_temp;
}

function _shn_ims_double_smoothing_forecast($catalog_id,$inv_id,$week)
{
	global $global;
	$db=$global["db"];

	$week=$week-1;

	$query1="SELECT * FROM ims_optimization WHERE catalog_id='$catalog_id' AND inv_id='$inv_id' AND week>='$week';";
	$ims_query1=$db->Execute($query1);
	//print $query1;
	while(!$ims_query1==NULL && !$ims_query1->EOF)
	{
		$forecasted_value=$ims_query1->fields['forecasted_value'];
		$double_forecasted_value=$ims_query1->fields['double_forecasted_value'];
		$time=$ims_query1->fields['week'];
		$beta=2/($time+1);

		if($time==$week)
		{
			$forecasted_temp=$forecasted_value;
			$double_forecasted_temp=$double_forecasted_value;
		}
		else
		{
			;
		}

		$ims_query1->MoveNext();
	}

	$double_forecast=($beta*($forecasted_value-$forecasted_temp)) + ((1-$beta)*$double_forecasted_temp);
	
	return $double_forecast;
	
} 


?>
