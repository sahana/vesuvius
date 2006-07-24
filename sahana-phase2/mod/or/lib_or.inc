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
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

global $global;
include_once $global['approot']."/inc/lib_form.inc";

function _shn_org_get_incidents($org_id)
{
	global $global;
	$db=$global["db"];
	$q = "select i.incident_id,name from incident as i,resource_to_incident as r where i.incident_id=r.incident_id and r.x_uuid='{$org_id}'";
    $res_incident=$db->Execute($q);   
    $or_incident_arr=array();
    	while(!$res_incident->EOF){
    		    $temp=array($res_incident->fields["incident_id"],$res_incident->fields["name"]);
            array_push(
                $or_incident_arr,
               // $res_incident->fields["incident_id"]
               $temp
            );       
            $res_incident->MoveNext();
    }  
    return $or_incident_arr;
}

function _shn_org_get_incident_string($org_id)
{
	 $arr=_shn_org_get_incidents($org_id);
	 $max=count($arr);
   	 array_pop($arr);
   		for($count=0;$count<$max;$count++){
   			$x=array_pop($arr);
   			$q="select name from incident where incident_id='{$x}'";
    			$res=$db->Execute($q);
    			//if($count==0 ){
    				$str=$str.$res->Fields("name");
    		//	}else{
   			//	$location=$location."-->".$res->Fields("name");
    			//}
    			
   		}
    return $str;
	
}

function _shn_org_location_string($loc)
{
	global $global;
	$db=$global["db"];
	$loc_arr=array();
   	shn_get_parents($loc,&$loc_arr);
   	if($loc_arr[0]=='unknown'){
   		shn_form_label(_("Organization Location"),"Unknown");
   	}else{
   		
   		$max=count($loc_arr)-1;
   		array_pop($loc_arr);
   		for($count=0;$count<$max;$count++){
   			$x=array_pop($loc_arr);
   			$q="select name from location where loc_uuid='{$x}'";
    			$res=$db->Execute($q);
    			if($count==0 ){
    				$location=$location.$res->Fields("name");
    			}else{
   				$location=$location."-->".$res->Fields("name");
    			}
    			
   		}
   	}
   	return $location;
}

function _shn_org_position($org_id,$incidents=null,$rootsonly=false){
	$org_list=shn_or_org_list($incidents,$rootsonly);
	$i=0;
	foreach($org_list as $key=>$name){
		$i=$i+1;
		if($org_id==$key){
			return $i;
		}
		
	}
}
function _shn_or_is_root($org_id){
	global $global;
	$db=$global["db"];
	$q="select o_uuid from org_main where o_uuid='{$org_id}' and parent_id is NULL ";
	$res=$db->Execute($q);
	if(($res==NULL) || ($res->EOF)){
		return false;
	}else{
		return true;
	}
}

function shn_or_create_database_IN_array($arr){
	
        if($arr!=null){
        $list="(";
        $j=0;
        foreach ($arr as $i){
        		$val="'$i'";
        		if($j==0){
        			$list=$list.$val;	
        		}else{
        			$list=$list.",".$val;	
        		}
        		$j++;
        }
        $list=$list.")";
        }
	return $list;
}

function shn_or_org_list($incidents=null,$rootsonly=false){
	    global $global;
        $db=$global['db'];
        if($incidents!=null){
        $list="(";
        $j=0;
        foreach ($incidents as $i){
        		if($j==0){
        			$list=$list.$i;	
        		}else{
        			$list=$list.",".$i;	
        		}
        		$j++;
        }
        $list=$list.")";
        }
        if($rootsonly==true){
        		$root=" and parent_id is NULL ";
        }else{
        		$root="";
        }
        
        if($incidents==null)
			$q = "select o_uuid,name from org_main where privacy=false".$root." order by o_uuid";
		else
			$q = "select o_uuid,name from org_main,resource_to_incident where privacy=false ".$root."and resource_to_incident.x_uuid=org_main.o_uuid and incident_id IN $list order by o_uuid";
        $res_org=$db->Execute($q);
        $org_list=array();
        while(!$res_org==NULL && !$res_org->EOF){
        		$org_list[$res_org->fields["o_uuid"]]=$res_org->fields["name"];
        		$res_org->MoveNext();
        }
        return $org_list;
}

function shn_or_org_incident_list($incidents=null,$rootsonly=false){
	    global $global;
        $db=$global['db'];
		$list=shn_or_create_database_IN_array($incidents);
        if($rootsonly==true){
        	$root=" and parent_id is NULL ";
        }else{
        	$root="";
        }
        if($incidents==null)
			$q = "select distinct o_uuid from org_main where privacy=false".$root;
		else
			$q = "select distinct o_uuid  from org_main,resource_to_incident where privacy=false  ".$root." and parent_id is NULL and resource_to_incident.x_uuid=org_main.o_uuid and incident_id IN $list";
		$res_org=$db->Execute($q);
		$orgs=array();
    		while(!$res_org==NULL && !$res_org->EOF){
    			array_push(
    				$orgs,
    				$res_org->fields["o_uuid"]
    			);
        		$res_org->MoveNext();
    		}
        return  $orgs;
}


function shn_or_org_loc_sector_incident_list($loc,$sector,$incidents=null,$rootsonly=false){
	    global $global;
        $db=$global['db'];
		$list=shn_or_create_database_IN_array($incidents);
        if($rootsonly==true){
        		$root=" and org_main.parent_id is NULL ";
        }else{
        		$root="";
        }
        if($incidents==null)
			$q = "select distinct o_uuid from org_main,location,location_details where privacy=false and loc_uuid='{$loc}' and loc_uuid=location_id and org_main.o_uuid=poc_uuid".$root;
		else
			$q = "select distinct o_uuid  from org_main,resource_to_incident,location,location_details where privacy=false  ".$root." and org_main.parent_id is NULL and resource_to_incident.x_uuid=org_main.o_uuid and incident_id IN $list and loc_uuid='{$loc}' and loc_uuid=location_id and org_main.o_uuid=poc_uuid";
		echo $q;
		$res_org=$db->Execute($q);
		$orgs=array();
    		while(!$res_org==NULL && !$res_org->EOF){
    			array_push(
    				$orgs,
    				$res_org->fields["o_uuid"]
    			);
        		$res_org->MoveNext();
    		}
        return  $orgs;
}

function _shn_or_get_start_loc()
{
    global $global;
    global $conf;
    $db=$global['db'];
    $q="select value from config where module_id='or' and confkey='loc_start'";
    $res=$db->Execute($q);
 //   if($res->fields[0]==NULL){
   //    	return $conf['mod_or_start_loc'];
    //}else {
    	if($res==NULL){
    		return NULL;
    }else{
    		return $res->fields["value"];
    }
}

function shn_or_get_loc_range()
{
    global $global;
    global $conf;
    $db=$global['db'];
    $loc=array();
    $q="select value from config where module_id='or' and confkey='loc_range_start'";
    $res=$db->Execute($q);
    if($res->fields[0]==NULL){
       	$loc["start"]=$conf['mod_or_loc_level_start'];
    }else {
    	$loc["start"]=$res->fields[0];
    }
    $q="select value from config where module_id='or' and confkey='loc_range_end'";
    $res=$db->Execute($q);
    if($res->fields[0]==NULL){
       	$loc["end"]=$conf['mod_or_loc_level_end'];
    }else {
    	$loc["end"]=$res->fields[0];
    }
    return $loc;
}

function _shn_or_action_change_javascript($form,$change)
{
?>
<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName("<?php echo $change?>");
         x[0].value=action;
         document.<?php echo $form?>.submit();
         return;
    }
</script>
<?php
}

function _shn_or_admin_javascript($name)
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
function _shn_or_get_org_loc_parents($child)
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



function _shn_or_display_gender($error=false,$value=NULL,$label=NULL)
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
function _shn_or_display_org_type($error=false,$multi=false,$value=NULL)
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
    $extra_opts['help']=_("please select whether you are a government organization,multinational ect");
    if($multi){
    		shn_form_opt_multi_select('opt_org_type','','multiple="true"',$extra_opts);
    }else{
    shn_form_opt_select('opt_org_type','',$select_opts,$extra_opts);
    }
}

function _shn_or_display_org_sub_type($error=false,$multi=false,$value=NULL)
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
    $extra_opts['help']=_("please select whether you are Department,Branch,ect of the parent organization");

    shn_form_opt_select('opt_org_sub_type','',$select_opts,$extra_opts);
     
}



function _shn_or_display_sector($error=false,$value=NULL)
{
    if($value!=NULL){
        $extra_opts['value']=$value;
       // $extra_opts['req']=false;
    }else{
       // $extra_opts['req']=true;
    }
    $extra_opts['req']=true;
    $extra_opts['help']=_("select the services your provide ,i.e what you do as an organization. e.g.if you are a supplier select it");
    shn_form_opt_multi_select('opt_sector_type','','multiple="true"',$extra_opts);
}

function _shn_or_display_contact_person($error=false,$confirm=false,$po_uuid=null)
{
    if($confirm==true){
    		shn_form_label(_("Name"),$_SESSION['org']['contact_name']);
    		shn_form_label(_("Address"),$_SESSION['org']['contact_address']);
    		shn_form_label(_("Phone"),$_SESSION['org']['contact_phone']);
    		shn_form_label(_("Mobile"),$_SESSION['org']['contact_mobile']);
    		shn_form_label(_("Fax"),$_SESSION['org']['contact_fax']);
    		shn_form_label(_("Website"),$_SESSION['org']['contact_web']);
    		return;
    }
   if($error==true){
   		$contact_address=$_SESSION['org']['contact_address'];
        $contact_phone=$_SESSION['org']['contact_phone'];
        $contact_mobile=$_SESSION['org']['contact_mobile'];
        $contact_name=$_SESSION['org']['contact_name'];
        $contact_fax=$_SESSION['org']['contact_fax'];
        $contact_email=$_SESSION['org']['contact_mail'];
        $contact_web=$_SESSION['org']['contact_web'];
    }
    if(!shn_is_null($po_uuid)){
        global $global;
        $db=$global['db'];
        $q = "select address from location_details where poc_uuid='{$po_uuid}'";
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
    $extra_opts['value']=$contact_name;
    $extra_opts['help']=_("Name of the person to be contacted in a disaster");
    shn_form_text(_("Name : "),'contact_name','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_address;
      $extra_opts['help']=_("Address to be contacted in a disaster");
    shn_form_text(_("Address : "),'contact_add','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_phone;
      $extra_opts['help']=_("Land line number to be contacted in a disaster");
    shn_form_text(_("Phone : "),'contact_phone','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_mobile;
      $extra_opts['help']=_("Mobile Phone number to be contacted in a disaster");
    shn_form_text(_("Mobile No : "),'contact_mobile','size="50"',$extra_opts);
    $extra_opts['value']=$contact_fax;
      $extra_opts['help']=_("Fax number to be contacted in a disaster");
    shn_form_text(_("Fax : "),'contact_fax','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_email;
      $extra_opts['help']=_("Email address to be contacted in a disaster");
    shn_form_text(_("Email : "),'contact_mail','size="50"',$extra_opts); 
    $extra_opts['value']=$contact_web;
      $extra_opts['help']=_("Website of the Organization");
    shn_form_text(_("Website : "),'contact_web','size="50"',$extra_opts);
}

function _shn_or_display_org_facilities($error=false,$confirm=false,$org_id=false)
{
    if($confirm==true){
    		shn_form_label(_("Man Power"),$_SESSION['org']['man_power']);
    		shn_form_label(_("Equipment"),$_SESSION['org']['equipment']);
    		shn_form_label(_("Resources"),$_SESSION['org']['resources']);
    		return;
    }
    if($error==true){
        $man_power=$_SESSION['org']['man_power'];
        $equipment=$_SESSION['org']['equipment']; 
        $resources=$_SESSION['org']['resources'];	
    }
    if(!shn_is_null($org_id)){
        global $global;
       $db=$global['db'];
        $q = "select man_power,equipment,resources from org_main where o_uuid='{$org_id}'";
        $res_org=$db->Execute($q);
        if(!$res_org==NULL && !$res_org->EOF){
            $man_power=$res_org->fields[0];
            $equipment=$res_org->fields[1]; 
            $resources=$res_org->fields[2]; 
        }
    }
    $extra_opts['value']=$man_power;
    $extra_opts['help']=_("Specify the workforce(Men/Women) in your organization. This amount would" .
    		"be useful in identifying the potential number of volunteers in the event of a disaster");
    shn_form_text(_("Man Power : "),'man_power','size="50"',$extra_opts);
    $extra_opts['value']=$equipment;
    $extra_opts['help']=_("Specify the kind of equipment you have,that will be useful in Disaster Relief" .
    		" Operations");
    shn_form_text(_("Equipment : "),'equipment','size="50"',$extra_opts);
    $extra_opts['value']=$resources;
    $extra_opts['help']=_("Specify any other resource that you think might be useful in Disaster Relief" .
    	" Operations");
    shn_form_text(_("Other relevant resources : "),'resources','size="50"',$extra_opts);
}

function _shn_or_display_logininfo($error=false)
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
function _shn_or_display_orgs($error=false,$multi=false,$value=NULL)
{
    global $global;
    $db=$global["db"];
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
    $options=shn_or_org_list();
    $extra_opts['help']=_("select the parent entity");
    shn_form_select($options,'','parent',$select_opts,$extra_opts);
}

function _shn_or_display_incident_form($error=false,$act)
{
    global $global;
    global $conf;
    $db=$global['db'];
?>
<h2><?=_("Select the Disaster/event/incident")?> </h2>
<div id="note">
<?=_("Since there are multiple incidents you required to select relevant incidents ");?>
</div>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
    shn_form_fopen($act);
    shn_form_fsopen('Choose related incidents:The Default Incident is Highlighted');
    _shn_or_display_incident(false,true);
    shn_form_fsclose();
    shn_form_hidden(array('incident'=>"true"));
    ?>
<br />
<center>
<?php
//create the submit button
   shn_form_submit(_("Next"));
?>
</center>
<br />
<?php
        //close the form
    shn_form_fclose();
?>				     
</div>
<?php
    // end of form
} 

function _shn_or_display_incident($error=false,$multi=false,$value=NULL)
{
    global $global;
    $db=$global["db"];
    if($value==NULL){
    		$q="select value from user_preference where module_id='ims' and pref_key='incident_id'";
    		$res=$db->Execute($q);
    		if(!$res==NULL && !$res->EOF){
    			$value=array();
    			array_push(
    				$value,
    				$res->fields["value"]
    			);
    			
    		}
   }
    $extra_opts['req']=true;
    if($multi){
        $select_opts="multiple='true'";
    }else{
        //$select_opts="multiple='false'";;
    }
    $q = "select incident_id,name from incident";
    
    $res_options=$db->Execute($q) ; 
    //$options['-1']="ALL incidents";
    while(!$res_options->EOF){
    		$options[$res_options->fields["incident_id"]]=$res_options->fields["name"];
         //add all the locations e.g $options['sl'=>'sri lanka']
        $res_options->MoveNext();
    }
    
    if(!empty($value)){
    		$extra_opts['value']=$value;	
    }
    $extra_opts['help']=_("select related incidents");
    shn_form_multi_select('incidents',$options,'',$select_opts,$extra_opts);
}

function _shn_or_display_extra($error=false)
{
    shn_form_checkbox(_("Add Operation<br> (Your Organization might be having branches or carrying out relief operations in this disaster. Then information of those operations is usefull : )"),'chk_branch',null,$chkbox_opts);
}

function _shn_or_get_suplier_name($suplier_id)
{
	global $global;
        $db=$global['db'];
	$org_id=0;
	$suplier_array=array();	
	$sql="SELECT name FROM org_main WHERE o_uuid='$suplier_id';";
	$or=$db->Execute($sql);
	$suplier_array[$suplier_id]=$or->fields['name'];

	$sql1="SELECT o_uuid,name FROM org_main WHERE o_uuid!='$suplier_id' AND o_uuid!='$org_id';";
	$or1=$db->Execute($sql1);
	
	while($or1!=NULL && !$or1->EOF)
	{
	$suplier_array[$or1->fields['o_uuid']]=$or1->fields['name'];
	$or1->MoveNext();
	}
	return $suplier_array;

//$inventory_array[$inv_id]=$ims0->fields['inventory_name'];

}

function _shn_or_check_org_reg_info_complete()
{

    include_once "errors.inc";
    global $global;
	include_once $global['approot']."/inc/lib_validate.inc";
	$error=false;
    $VARCHAR=100; 
	list($error,$_SESSION['org']['name'])=(shn_validate_field($_POST{"org_name"},"Organization Name",$VARCHAR,true))?array($error,$_POST{"org_name"}):array(true,NULL);
    list($error,$_SESSION['org']['type'])=(shn_validate_opt_field('opt_org_type',$_POST{"opt_org_type"},"Organization Type",$VARCHAR,false))?array($error,$_POST{"opt_org_type"}):array(true,NULL);
    list($error,$_SESSION['org']['sector'])=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Organization Sector",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
    $loc=shn_location_get_form_submit_loc();
    if ($loc==-1){
        $error=true;
        add_error(SHN_ERR_OR_LOCATION_INCOMPLETE);
    }else{
    		$_SESSION['org']['loc']=$loc;
    }
    
    if (trim(strlen($_POST{"reg_no"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $_SESSION['org']['reg_no']=$_POST{"reg_no"};
    }
    if (trim(strlen($_POST{"contact_name"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $_SESSION['org']['contact_name']=$_POST{"contact_name"};
    }
    $_SESSION['org']['contact_address']=$_POST{"contact_add"};
    if (trim(strlen($_POST{"contact_phone"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $_SESSION['org']['contact_phone']=$_POST{"contact_phone"};
    }
     if (trim(strlen($_POST{"contact_mobile"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $_SESSION['org']['contact_mobile']=$_POST{"contact_mobile"};
    }
    if (trim(strlen($_POST{"contact_fax"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
         $_SESSION['org']['contact_fax']=$_POST{"contact_fax"};
    }
    if (trim(strlen($_POST{"contact_mail"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        
        if(!shn_valid_email($contact_mail)){
            add_error(SHN_ERR_OR_EMAIL);
            $error=true;
        }else{
        		$_SESSION['org']['contact_mail']=$_POST{"contact_mail"};
        }
    }
     if (trim(strlen($_POST{"contact_web"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $_SESSION['org']['contact_web']=$_POST{"contact_web"};
    }
    if (trim(strlen($_POST{"man_power"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $_SESSION['org']['man_power']=$_POST{"man_power"};
    }
    if (trim(strlen($_POST{"equipment"})) > $VARCHAR){
        add_error(SHN_ERR_OR_REG_MAX);
        $error=true;
    }else {
        $_SESSION['org']['equipment']=$_POST{"equipment"};
    }
    $_SESSION['org']['resources']=$_POST{"resources"};
    return $error;
}

function array_copy($src,&$dest,$start,$end)
{
	for($i=$start;$i<$end;$i++){
		$dest[$i-$start]=$src[$i];
	}
	
	
}
?>
