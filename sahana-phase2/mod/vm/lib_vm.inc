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
include_once $global['approot']."/inc/handler_form.inc";

/*
function _shn_vm_get_start_loc()
{
    global $global;
    $db=$global['db'];
    $q="select value from config where module_id='or' and confkey='loc_start'";
    $res=$db->Execute($q);
    return $res->fields[0];
}
*/

function _shn_vm_action_change_javascript($change)
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

function _shn_vm_display_skill_types($error=false,$multi=false,$value=NULL)
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
    $extra_opts['help']=_("Select skills you wish to remove");
    if($multi){
    		shn_form_opt_multi_select('opt_skill_type','','multiple="true"',$extra_opts);
    }else{
    shn_form_opt_select('opt_skill_type','',$select_opts,$extra_opts);
    }
}

function _shn_vm_admin_javascript($name)
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

function _shn_form_select_gender($error=false,$value=NULL,$label=NULL)
{
	$select_opts = array();//BUG FIX 2006-7-20
	$extra_opts = array();//BUG FIX 2006-7-20
    if($value!=NULL){
	    $extra_opts['value']=$value;
	    //$extra_opts['req']=false;
    }else{
	    //$extra_opts['req']=true;
    }
    $label=($label==NULL)?_("Gender:"):$label;
    shn_form_opt_select('opt_gender',$label,$select_opts,$extra_opts);
}

function _shn_form_select_idtype($error=false,$value=NULL,$label=NULL)
{
	$extra_opts = array();//BUG FIX 2006-7-20
	$select_opts = array();//BUG FIX 2006-7-20
    if($value!=NULL){
	    $extra_opts['value']=$value;
	    //$extra_opts['req']=false;
    }else{
	    //$extra_opts['req']=true;
    }
    $label=($label==NULL)?_("Type of Identification:"):$label;
    shn_form_opt_select('opt_id_type',$label,$select_opts,$extra_opts);
}

function _shn_form_date($label, $name = 'date', $initdate = null, $required=false, $format='YYYY-MM-DD') 
{
?>
    <label><?=$label?></label>
<?php
	if($initdate==null){
	?>
	<script>DateInput('<?=$name?>', '<?=$required?>', '<?=$format?>')</script><br>
	<?php
	}else{
	?>
	<script>DateInput('<?=$name?>', '<?=$required?>', '<?=$format?>', '<?=$initdate?>')</script><br> 
	<?php
	}
    

}


function _shn_form_select_task($error=false,$value_selected=NULL, $label=NULL, $select_opts=NULL, $extra_opts=NULL)  {
  if($value_selected!=NULL){
    $extra_opts['value']=$value_selected;
  }
  global $global;
  $result = $global['db']->Execute("select option_code, option_description from field_options where field_name = 'opt_skill_type'");
  $options = array();
  while(!$result==NULL && !$result->EOF) {
    $options[$result->fields[0]] = $result->fields[1];  // [value=opt_code,description=opt_name]
    $result->MoveNext();
  }
  $label=($label==NULL)?_("Assigned Task :"):$label;
  shn_form_select($options, $label,'task', $select_opts, $extra_opts);
}

function _shn_form_select_volunteer_skills($person_id, $post_id,$error=false,$value_selected=NULL, $label=NULL, $select_opts=NULL, $extra_opts=NULL)  {
  if($value_selected!=NULL){
    $extra_opts['value']=$value_selected;
  }
  global $global;
  $skill_opts_list = $global['db']->Execute("select opt_skill_code from vm_vol_skills where p_uuid = '{$person_id}'");
  $options = array();
  while(!$skill_opts_list==NULL && !$skill_opts_list->EOF) {
    $q = "select option_code, option_description from field_options where option_code='{$skill_opts_list->fields[0]}'";
    $skill_descriptions=$global['db']->Execute($q);
    $options[$skill_descriptions->fields[0]] = $skill_descriptions->fields[1];  // [value=opt_code,description=opt_name]
    $skill_opts_list->MoveNext();
  }
  shn_form_select($options, $label,$post_id, $select_opts = NULL, $extra_opts);
}

/*
 * _shn_form_select_organization() sets up the parameters needed to construct
 *  a <select> form element.  The key piece of data is an array, $options,
 *  which consists of [value,description] pairs used to create the <option> tags. 
 *  For example,
 *  <option value="value">description</option>
 */
function _shn_form_select_organization($error=false, $value_selected=NULL, $label=NULL, $select_opts=NULL, $extra_opts=NULL)  {
  if($value_selected!=NULL)
    $extra_opts['value']=$value_selected;
  global $global;
  $result = $global['db']->Execute("select o_uuid, name from org_main"); // Get the options from the DB.
  $options = array();                                           // Construct the <option> elements
  if($extra_opts['all_org']){
	$options[-1]="All Organizations";
  }
  while(!$result==NULL && !$result->EOF) {
    $options[$result->fields[0]] = $result->fields[1];           // [value=org_id,description=org_name]
    $result->MoveNext();
  }
  shn_form_select($options, $label, 'organization', NULL, $extra_opts);
} // _shn_form_select_organization()


/*
 * _shn_form_select_project() sets up the parameters needed to construct
 *  a <select> form element.  The key piece of data is an array, $options,
 *  which consists of [value,description] pairs used to create the <option> tags. 
 *  For example,
 *  <option value="value">description</option>
 */
function _shn_form_select_project($error=false, $value_selected=NULL, $label=NULL, $select_opts=NULL, $extra_opts=NULL)  {
  if($value_selected!=NULL)
    $extra_opts['value']=$value_selected;
  global $global;
  $result = $global['db']->Execute("select proj_id, name from vm_projects"); // Get the options from the DB.
  $options = array();                                            // Construct the <option> elements
  while(!$result==NULL && !$result->EOF) {
    $options[$result->fields[0]] = $result->fields[1];           // [value=proj_id, description=project_name]
    $result->MoveNext();
  }
  shn_form_select($options, $label, 'project', NULL, $extra_opts);
} // _shn_form_select_project()

function _shn_form_select_specialities($error=false,$value=NULL) {
    if($value!=NULL){
        $extra_opts['value']=$value;
        $extra_opts['req']=false;
    }else{
        $extra_opts['req']=true;
    }
    shn_form_opt_multi_select('opt_skill_type','Specialties : <br>(Hold the CTRL-Key to choose more than one skill)','multiple="true"',$extra_opts);
}

function _shn_location_form_volunteer($from,$to,$value=NULL){
  shn_location_jscript($to);
  if($value!=NULL){
    $location_inf = _shn_location_form_value($from,$to,$value);  
  }else {
    $location_inf = _shn_location_form($from,$to);  
  }
  shn_form_fsopen('Address');
  shn_form_add_component_list($location_inf,$section=false,$legend='',$return=false,$default_val_req=$error);
  shn_form_text(_("Street Address : "),'address','size="50"',$extra_opts); 
  shn_form_fsclose();
}

function _shn_form_get_contact_info($error=false,$org=true,$po_uuid=null)
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
	    $extra_opts['value']=$contact_address;
	    shn_form_text(_("Address : "),'contact_add','size="50"',$extra_opts); 
    }
    $extra_opts['value']=$contact_phone;
    $extra_opts['req']=false;
    
    shn_form_text(_("Phone : "),'contact_phone','size="20"',$extra_opts); 
    $extra_opts['value']=$contact_fax;
    
    shn_form_text(_("Fax : "),'contact_fax','size="20"',$extra_opts); 
    $extra_opts['value']=$contact_email;
    shn_form_text(_("Email : "),'contact_email','size="50"',$extra_opts); 
}

/*
function _shn_vm_display_org_type($error=false,$multi=false,$value=NULL)
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
*/
?>
