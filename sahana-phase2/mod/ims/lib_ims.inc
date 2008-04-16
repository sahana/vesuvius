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
*             Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage ims
*/

global $global;
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_location.inc";
include_once $global['approot'].'/mod/or/lib_or.inc';
include_once $global['approot'].'/3rd/phplot/phplot_ims.php';


function shn_ims_org_list(){
        global $global;
        $db=$global['db'];
        $q = "SELECT inv_uuid,inventory_name,parent_id FROM  ims_inventory_records ORDER BY inventory_name";
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
    $q="SELECT value FROM config WHERE module_id='or' AND confkey='loc_start'";
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
    $q="SELECT value FROM config WHERE module_id='or' AND confkey='loc_range_start'";
    $res=$db->Execute($q);
    if($res->fields[0]==NULL){
           $loc["start"]=$conf['mod_or_ims_loc_level_start'];
    }else {
        $loc["start"]=$res->fields[0];
    }
    $q="SELECT value FROM config WHERE module_id='or' AND confkey='loc_range_end'";
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
    $q="SELECT search_id,name,location.location_id FROM location_details,location WHERE poc_uuid='{$child}' AND location_details.location_id=location.location_id";
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
        $q="SELECT name,location_id FROM location WHERE search_id='$cur'";
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
    $label=($label==NULL)?_t("Gender:"):$label;
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
        $q = "SELECT address FROM location_details WHERE poc_uuid='{$po_uuid}'";
        $res_addr=$db->Execute($q); 
        $contact_address=$res_addr->fields[0];
        $q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$po_uuid}' AND opt_contact_type='curr'";
        $res_phone=$db->Execute($q);
        $contact_phone=$res_phone->fields[0];
        $q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$po_uuid}' AND opt_contact_type='pmob'";
        $res_mobile=$db->Execute($q);
        $contact_mobile=$res_mobile->fields[0];
        if($org){
            $q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$po_uuid}' AND opt_contact_type='name'";
            $res_name=$db->Execute($q);
            $contact_name=$res_name->fields[0];
        }
        $q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$po_uuid}' AND opt_contact_type='fax'";
        $res_fax=$db->Execute($q);
        $contact_fax=$res_fax->fields[0];
        $q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$po_uuid}' AND opt_contact_type='email'";
        $res_email=$db->Execute($q);
        $contact_email=$res_email->fields[0];
        $q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$po_uuid}' AND opt_contact_type='web'";
        $res_web=$db->Execute($q);
        $contact_web=$res_web->fields[0];
    }
    if($org){
        $extra_opts['value']=$contact_name;
        shn_form_text(_t("Name : "),'contact_name','size="50"',$extra_opts); 
    }
    $extra_opts['value']=$contact_address;
    shn_form_text(_t("Address : "),'contact_add','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_phone;
    shn_form_text(_t("Phone : "),'contact_phone','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_mobile;
    shn_form_text(_t("Mobile No : "),'contact_mobile','size="50"',$extra_opts);
    $extra_opts['value']=$contact_fax;
    shn_form_text(_t("Fax : "),'contact_fax','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_email;
    shn_form_text(_t("Email : "),'contact_mail','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_web;
    shn_form_text(_t("Website : "),'contact_web','size="50"',$extra_opts);
}

function _shn_ims_display_org_facilities($error=false,$org_id=false)
{
    if(!shn_is_null($org_id)){
        global $global;
       $db=$global['db'];
        $q = "SELECT man_power,equipment,resources,space FROM  ims_inventory_records WHERE inv_uuid='{$org_id}'";
        $res_org=$db->Execute($q);
        if(!$res_org==NULL && !$res_org->EOF){
            $man_power=$res_org->fields[0];
            $equipment=$res_org->fields[1]; 
            $resources=$res_org->fields[2]; 
        $space=$res_org->fields[3];
        }
    }
    $extra_opts['value']=$man_power;
    shn_form_text(_t("Man Power : "),'man_power','size="50"',$extra_opts);
    $extra_opts['value']=$equipment;
    shn_form_text(_t("Equipment : "),'equipment','size="50"',$extra_opts);
    $extra_opts['value']=$resources;
    shn_form_text(_t("Other relevant resources : "),'resources','size="50"',$extra_opts);
    $extra_opts['value']=$space;
    shn_form_text(_t("Inventory Space : "),'space','size="50"',$extra_opts);
  
}

function _shn_ims_display_logininfo($error=false)
{
// for get login info
    $login_info = array(
                       array('desc'=>_t("Account Name : "),'type'=>"text",'size'=>20,'name'=>'account_name','br'=>1),
                    array('desc'=>_t("* User Name for Login: "),'type'=>"text",'size'=>20,'name'=>'user_name','br'=>1),
                    array('desc'=>_t("* Password for Login: "),'type'=>"password",'size'=>20,'name'=>'password','br'=>1),
                    array('desc'=>_t("* Confirm Password: "),'type'=>"password",'size'=>20,'name'=>'re_password','br'=>1)
    ); // end of getting logging info
    return $login_info;
}

function _shn_ims_display_extra($error=false)
{
    shn_form_checkbox(_t("Add Operation<br> (Your Organization might be having branches or carrying out relief operations in this disaster. Then information of those operations is useful : )"),'chk_branch',null,$chkbox_opts);
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

function _shn_ims_gis_inv($inv_id)
{
    global $global;
    $db=$global['db'];
    
    $map_array=array();
    $url="mod=ims&act=view_inv&id=$inv_id";

    if($inv_id==NULL)
    {
		
		//$db = $global['db'];
		
		$sql1="SELECT * FROM ims_inventory_records;";
		$ims1=$db->Execute($sql1);
		

		while(!$ims1==NULL && !$ims1->EOF)
		{
			$inv_id=$ims1->fields['inv_uuid'];
			$url="mod=ims&act=view_inv&id=$inv_id";
			$sql2="SELECT * FROM gis_location WHERE poc_uuid='$inv_id';";
			$ims2=$db->Execute($sql2);

			array_push($map_array,array("lat"=>$ims2->fields['map_northing'],"lon"=>$ims2->fields['map_easting'],"name"=>$ims1->fields['inventory_name'],"id"=>$ims2->fields['poc_uuid'],"url"=>$url));
			$ims1->MoveNext();	
		}
    }
    else
    {
	$sql1="SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
	$ims1=$db->Execute($sql1);
	
	$sql2="SELECT * FROM gis_location WHERE poc_uuid='$inv_id';";
			$ims2=$db->Execute($sql2);

			array_push($map_array,array("lat"=>$ims2->fields['map_northing'],"lon"=>$ims2->fields['map_easting'],"name"=>$ims1->fields['inventory_name'],"id"=>$ims2->fields['poc_uuid'],"url"=>$url));
    }

	return $map_array;
}

function _shn_ims_get_location($inv_id)
{
	global $global;
	$db=$global['db'];

	$sql1="SELECT * FROM location_details WHERE poc_uuid='$inv_id';";
	$ims1=$db->Execute($sql1);
	
	$location_id=$ims1->fields['location_id'];

	//$parent_id="test";
	$string_array=array();
	$i=0;

	while($location_id!=NULL)
	{
		$sql2="SELECT * FROM location WHERE loc_uuid='$location_id';";
		$ims2=$db->Execute($sql2);
		$parent_id=$ims2->fields['parent_id'];
		$name=$ims2->fields['name'];
		//array_push($string_array,$location_id=>$name);
		$string_array[$i]=$name;
		$i=$i+1;

		$location_id=$parent_id;
	}

	for($j=$i-2;$j>=0;$j--)
	{
		
		$string=$string_array[$j];
		if($j==$i-2)
		{
			$location=$string;
		}
		else
		{
			$location=$location."->".$string;
		}
		
	}
	
   	return $location;
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
        /*$timestamp_start = strtotime($start);
        $timestamp_end = strtotime($end);
        if( $timestamp_start >= $timestamp_end ) return 0;
        $start_year = date("Y",$timestamp_start);
        $end_year = date("Y", $timestamp_end);*/
        //$num_days_end = date("z",strtotime($start));
        //$num_days_end = date("z", strtotime($end));
        if($end<$start){
        	return -1;
        }
        else{
        	return 1;
        }
        /*$num_days = 0;
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
         return 0;*/
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
	
	for($i=$date_diff;$i>=0;$i-=$time_period)	
	//while(_shn_ims_count_days($date_inv,$current_date)<1 && _shn_ims_count_days($date_inv,$current_date)>0 )
	{
		$date_inv_temp=$date_inv;
		//$sql2="SELECT * FROM ims_item_records WHERE inv_id='$inv_id' AND catalog_id='$catalog_id' AND (TO_DAYS(inserted_date) - TO_DAYS($date_inv_temp))<7;";
		$sql2="SELECT * FROM ims_item_records WHERE inv_id='$inv_id' AND catalog_id='$catalog_id' AND state!='$item_state_destroyed';";
		$ims2=$db->Execute($sql2);
		
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
		
		$week=$week+1;
		$temp=$week+1;
		$alpha=2/$temp;
		
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
		
		$sql3="INSERT INTO ims_optimization (catalog_id,inv_id,week,actual_value,forecasted_value,unit) VALUES ('$catalog_id','$inv_id','$week','$sum_amount_temp','$forecasted_value','$base_unit');"; 
		$ims3=$db->Execute($sql3);
		
		list($year,$month,$day) = split("-",$date_inv);
		$date_inv=_shn_ims_timeafter($year, $month, $day,$time_period);
		
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
	
	for($i=$date_diff;$i>=0;$i-=$time_period)	
	//while(_shn_ims_count_days($date_inv,$current_date)<1 && _shn_ims_count_days($date_inv,$current_date)>0 )
	{
		$date_inv_temp=$date_inv;
		//$sql2="SELECT * FROM ims_item_records WHERE inv_id='$inv_id' AND catalog_id='$catalog_id' AND (TO_DAYS(inserted_date) - TO_DAYS($date_inv_temp))<7;";
		$sql2="SELECT * FROM ims_transfer_item WHERE inv_id_from='$inv_id' AND catalog_id='$catalog_id';";
		$ims2=$db->Execute($sql2);
		
		$sum_amount=0;
		$sum_amount_temp=0;
		$amount=0;
		$converted_amount=0;
		while(!$ims2==NULL && !$ims2->EOF)
		{
			$amount=$ims2->fields['amount_send'];
			
			$unit=$ims2->fields['unit'];
			$inserted_date=$ims2->fields['date_send'];

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
		
		$week=$week+1;
		$temp=$week+1;
		$alpha=2/$temp;
		
		
		if($week==1)
		{
			$forecasted_value=0;
			
			$forecasted_value_temp=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
		}
		else
		{
			
			$forecasted_value=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
			
		}
		
		$sql3="INSERT INTO ims_optimization (catalog_id,inv_id,week,actual_value,forecasted_value,unit) VALUES ('$catalog_id','$inv_id','$week','$sum_amount_temp','$forecasted_value','$base_unit');"; 
		$ims3=$db->Execute($sql3);
		$sum_amount_temp=0;
		
		list($year,$month,$day) = split("-",$date_inv);
		$date_inv=_shn_ims_timeafter($year, $month, $day,$time_period);
		
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
	
	for($i=$date_diff;$i>=0;$i-=$time_period)	
	//while(_shn_ims_count_days($date_inv,$current_date)<1 && _shn_ims_count_days($date_inv,$current_date)>0 )
	{
		$date_inv_temp=$date_inv;
		
		$sql2="SELECT * FROM ims_transfer_item WHERE inv_id_to='$inv_id' AND catalog_id='$catalog_id' AND received_item_id!='$received_item_id';";
		$ims2=$db->Execute($sql2);
		$sum_amount=0;
		$sum_amount_temp=0;
		while(!$ims2==NULL && !$ims2->EOF)
		{
			$amount=$ims2->fields['amount_received'];
			
			$unit=$ims2->fields['unit'];
			$inserted_date=$ims2->fields['date_received'];

			
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
		
		$week=$week+1;
		$temp=$week+1;
		$alpha=2/$temp;
		
		
		if($week==1)
		{
			$forecasted_value=0;
			
			$forecasted_value_temp=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
		}
		else
		{
			
			$forecasted_value=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
			
		}
		
		$sql3="INSERT INTO ims_optimization (catalog_id,inv_id,week,actual_value,forecasted_value,unit) VALUES ('$catalog_id','$inv_id','$week','$sum_amount_temp','$forecasted_value','$base_unit');"; 
		$ims3=$db->Execute($sql3);
		
		$sum_amount=0;
		
		list($year,$month,$day) = split("-",$date_inv);
		$date_inv=_shn_ims_timeafter($year, $month, $day,$time_period);
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
	
	for($i=$date_diff;$i>=0;$i-=$time_period)	
	//while(_shn_ims_count_days($date_inv,$current_date)<1 && _shn_ims_count_days($date_inv,$current_date)>0 )
	{
		$date_inv_temp=$date_inv;
		
		$sql2="SELECT * FROM ims_transfer_item WHERE inv_id_to='$inv_id' AND catalog_id='$catalog_id' AND received_item_id!='$received_item_id';";
		$ims2=$db->Execute($sql2);
		
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
		
		$week=$week+1;
		$temp=$week+1;
		$alpha=2/$temp;
		
		$forecasted_value=_shn_ims_smoothing($forecasted_value,$actual_value,$alpha);
		
		$sql3="INSERT INTO ims_optimization (catalog_id,inv_id,week,actual_value,forecasted_value,unit) VALUES ('$catalog_id','$inv_id','$week','$sum_amount_temp','$forecasted_value','$base_unit');"; 
		$ims3=$db->Execute($sql3);
		
		$sum_amount=0;
		
		list($year,$month,$day) = split("-",$date_inv);
		$date_inv=_shn_ims_timeafter($year, $month, $day,$time_period);
		
	}

}



function _shn_ims_get_alternate_item_amount($catalog_id,$inv_id)
{
	$item_state="destroyed";
	$sql3="SELECT * FROM ims_alternate WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
	$ims3=$db->Execute($sql3);
	
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
            		
            		$sum_amount=$sum_amount + $converted_amount;
	    		$alternate_sum_amount=$alternate_sum_amount + $converted_amount;
            		
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


$graph->SetDataValues($data);
 $graph->SetFileFormat("png"); 

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

/**
********************************************************************************
******************************************** Expired Items Report ************** ********************************************************************************
**/

function _shn_ims_expired_item_report()
{
    global $global;
    $db=$global['db'];
    $state="expired";

    
    $table_data = array();
    $row_count = 0;

    $sql="SELECT item_id,inv_id,suplier_id,item_name,amount,unit,manufactured_date,expire_date FROM ims_item_records WHERE state='$state';";
    //$ims = $db->Execute($sql1);
    $ims = $db->Execute($sql);

     $suplier_array=array();

    while (!$ims==NULL && !$ims->EOF)
    {
	$table_row = "row".$row_coount++;
        $table_row = array();

	$item_id=$ims->fields["item_id"];
        $inv_id=$ims->fields["inv_id"];
        $suplier_id=$ims->fields["suplier_id"];

        $suplier_array=_shn_or_get_suplier_name($suplier_id);
        $suplier_name=$suplier_array[$suplier_id];
        
        //$category=$ims->fields["category"];

	$table_row ["name"]= $ims->fields["item_name"];
	$table_row ["amount"]= $ims->fields["amount"];
        $unit=$ims->fields["unit"];
        $unit_name=get_unit_name($unit);
	$table_row ["unit"]= $unit_name;
	$table_row ["manu_date"]= $ims->fields["manufactured_date"];
	$table_row ["exp_date"]= $ims->fields["expire_date"];

        $sql3="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
        $ims3=$db->Execute($sql3);

	$table_row ["inventory"]=  $ims3->fields['inventory_name'];
	//$ims3->fields['suplier']=$suplier_name;
	//echo $suplier_name;
	
	$table_row ["suplier"]=$suplier_name;

	array_push($table_data,$table_row);

        $ims->MoveNext();

    }

    return $table_data;
}

/**
*************************************** Destryed Item Report ********************************************************************************
**/

function _shn_ims_destroyed_item_report()
{
    global $global;
    $db=$global['db'];
    $state="destroyed";

    
    $table_data = array();
    $row_count = 0;

    $sql1="SELECT inv_id,suplier_id,item_name,amount,unit,manufactured_date,expire_date FROM ims_item_records WHERE state='$state';";
    $ims1=$db->Execute($sql1);

    $suplier_array=array();

    while (!$ims1==NULL && !$ims1->EOF)
    {
	$table_row = "row".$row_coount++;
        $table_row = array();

	$inv_id=$ims1->fields['inv_id'];
        $suplier_id=$ims1->fields['suplier_id'];
        $suplier_array=_shn_or_get_suplier_name($suplier_id);
        $suplier_name=$suplier_array[$suplier_id];
        $item_name=$ims1->fields['item_name'];
        $amount=$ims1->fields['amount'];
        $unit=$ims1->fields['unit'];
        $unit_name=get_unit_name($unit);
        $manufactured_date=$ims1->fields['manufactured_date'];
        $expire_date=$ims1->fields['expire_date'];

        $sql2="SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id';";
        $ims2=$db->Execute($sql2);
            
        $inventory_name=$ims2->fields['inventory_name'];

	$table_row['name']=$item_name;
	$table_row['amount']=$amount;
	$table_row['unit']=$unit_name;
	$table_row['manu_date']=$manufactured_date;
	$table_row['exp_date']=$expire_date;
	$table_row['inventory']=$inventory_name;
	$table_row['suplier']=$suplier_name;

	array_push($table_data,$table_row);

	$ims1->MoveNext();
    }

    return $table_data;
}

/**
************************************************ Re-Order Level Report ********************************************************************
**/

function _shn_ims_reorder_level_report()
{
    global $global;
    $db=$global["db"];
    
    $table_data = array();
    $row_count = 0;
        
    $sql1="SELECT catalog_id,inv_id,minimum_quantity,unit FROM ims_reorder_level;";
    $ims1=$db->Execute($sql1);
    
    $state = "destroyed";
        
    $sum_amount=0;
        
        
     while (!$ims1==NULL && !$ims1->EOF)
        {
	    $table_row = "row".$row_coount++;
            $table_row = array();

            $catalog_id_min=$ims1->fields['catalog_id'];
            
            $inv_id_min=$ims1->fields['inv_id'];
           
            $minimum_quantity=$ims1->fields['minimum_quantity'];
            
            
            $unit=$ims1->fields['unit'];
            
            $unit_name=get_unit_name($unit);

            $sql2 = "SELECT unit,amount FROM ims_item_records WHERE catalog_id='$catalog_id_min' AND inv_id='$inv_id_min'AND state!='$state';";
            $ims2 =$db->Execute($sql2);
            
            while(!$ims2==NULL && !$ims2->EOF)
            {
          
            $current_unit=$ims2->fields['unit'];
            $current_amount=$ims2->fields['amount'];
                        
            
    $multiplier=unit_converter($unit,$current_unit);
    
    
    $current_amount_convert=$current_amount*$multiplier;
    
    $sum_amount=$sum_amount+$current_amount_convert;
    
    
    
            $ims2->MoveNext();
            }
    

        if($sum_amount<$minimum_quantity)
            {
                $total_amount=$sum_amount;
                $sum_amount=0;
                $sql3 = "SELECT item_id,item_name,unit FROM ims_item_records WHERE catalog_id='$catalog_id_min' AND inv_id='$inv_id_min';";
                $ims3 = $db->Execute($sql3);
    
            
             

                $sql4 = "SELECT inventory_name FROM ims_inventory_records WHERE inv_uuid='$inv_id_min';";
                $ims4 = $db->Execute($sql4);
                $inventory_name=$ims4->fields['inventory_name'];
               

                $item_id=$ims3->fields["item_id"];

            if($item_id!=null)
            {
                   
               
                $item_name=$ims3->fields["item_name"];
               
                $unit=$ims3->fields["unit"];
                

		$table_row['name']=$item_name;
		$table_row['amount']=$total_amount;
		$table_row['unit']=$unit_name;
		$table_row['inventory']=$inventory_name;
		
    	    }
    }
    else if($sum_amount>=$minimum_quantity)
    {
        $sum_amount=0;
    }
	array_push($table_data,$table_row);
        $ims1->MoveNext();
    }

    return $table_data; 
}

function _shn_ims_validate_sub_cat_form()
{
$error_flag=false;
clean_errors();

$itemid=null;
$max_depth = get_max_depth();
    for($i=0;$i<$max_depth;$i++)
    {
    $itemid = trim($_POST[$i]);
        if($itemid!=null)
        {
        break;
        }
    }

    if($itemid==null || $itemid=='none')
    {
   //add_error(_t(SHN_IMS_CATALOGUE_MISSING));
    $error_flag=true;
    }    

return $error_flag;
}

function _shn_ims_location_string($loc)
{
	global $global;
	$db=$global["db"];
	$loc_arr=array();
   	shn_get_parents($loc,&$loc_arr);
   	if($loc_arr[0]=='unknown'){
   		shn_form_label(_t("Organization Location"),"Unknown");
   	}else{
   		
   		$max=count($loc_arr)-1;
   		array_pop($loc_arr);
   		for($count=0;$count<$max;$count++){
   			$x=array_pop($loc_arr);
   			$q="SELECT name FROM location WHERE loc_uuid='{$x}'";
    			$res=$db->Execute($q);
    			if($count==0 ){
    				$location=$location.$res->Fields("name");
    			}else{
   				$location=$location." -->".$res->Fields("name");
    			}
    			
   		}
   	}
   	return $location;
}

function _shn_ims_get_locid($range_end){
//	if($_SESSION['ims_5']!=null)
//		return $_SESSION['ims_5'];
//	else if($_SESSION['ims_4']!=null)
//		return $_SESSION['ims_4'];
//	else if($_SESSION['ims_3']!=null)
//		return $_SESSION['ims_3'];
//	else if($_SESSION['ims_2']!=null)
//		return $_SESSION['ims_2'];
//	else 
//		return $_SESSION['ims_1'];
	
	for($range_end; $range_end>0; $range_end--) {
		$var='rms_'.$range_end;
	    if($_SESSION[$var]!=null && $_SESSION[$var]!="0")
		    return $_SESSION[$var];
	}
}


function _shn_ims_get_parent_locations($location_id)
{
    global $global;
    $db=$global['db'];

    $flag=false;
    $i=1;

    $locatiion_array=array();
    $location_array[0]=$location_id;

    $sql="SELECT * FROM location;";
    $ims=$db->Execute($sql);

    while(!$ims==NULL && !$ims->EOF)
    {
        $parent_id=$ims->fields['parent_id'];
	$loc_uuid=$ims->fields['loc_uuid'];


	if($parent_id==$location_id)
	{
	    $flag=true;

	}

	if($flag==true)
	{
	    $location_array[$i]=$loc_uuid;
	    $i=$i+1;

	}

	$ims->MoveNext();
    }

    return $location_array;
}

function _shn_ims_get_shelter_name()
{
    global $global;
    $db=$global['db'];
    $shelter_array=array();
    $sql="SELECT * FROM camp_general;";
    $ims=$db->Execute($sql);
    $shelter_array['']='';
    while(!$ims==NULL && !$ims->EOF)
    {
	$shelter_array[$ims->fields['c_uuid']]=$ims->fields['name'];
	$ims->MoveNext();
    }
    return $shelter_array;
}

function _shn_ims_get_organization_name()
{
    global $global;
    $db=$global['db'];
    $org_array=array();
    $sql="SELECT * FROM org_main;";
    $ims=$db->Execute($sql);
    $org_array['']='';
    while(!$ims==NULL && !$ims->EOF)
    {
	$org_array[$ims->fields['o_uuid']]=$ims->fields['name'];
	$ims->MoveNext();
    }
    return $org_array;
}

function _shn_ims_get_victim()
{
    global $global;
    $db=$global['db'];
    $victim_array=array();
    $sql="SELECT pg.g_uuid as g_uuid,pu.p_uuid as p_uuid,pg.opt_group_type as group_name,pu.full_name as full_name,pu.family_name as family_name,pu.l10n_name as l10n_name,pu.custom_name as custom_name FROM pgroup pg,person_to_pgroup ptg,person_uuid pu WHERE pg.g_uuid=ptg.g_uuid and ptg.p_uuid=pu.p_uuid;";
    $ims=$db->Execute($sql);
    
    $victim_array['']='';
    while(!$ims==NULL && !$ims->EOF)
    {
	
	$victim_array[$ims->fields['g_uuid']]=$ims->fields['full_name']." ".$ims->fields['family_name'];
	$ims->MoveNext();
    }
    return $victim_array;
}

?>
