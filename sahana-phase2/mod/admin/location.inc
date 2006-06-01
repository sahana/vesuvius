<?php
/**
* This library helps uses phpgacl library to manage ACL
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra De Silva
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $global;
include_once $global['approot']."/inc/handler_form.inc";
include_once $global['approot']."/inc/lib_location.inc";
/*
function _shn_admin_location_form(){
?>
<h1 align="center"><?=_("Add Locations")?></h1>
<div id="note">
<?=_("Fields marked with * are required (entry is compulsory)")?>
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    shn_form_fopen("add_loc_cr");
    _shn_admin_location_form();
 ?>
</center>
<br />
<center>
<?php
 	shn_form_submit("Submit");
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose(false);
?>
</div>
<?php
    // end of form

}
*/
function _shn_admin_location_view_form(){
?>
<h1 align="center"><?=_("First select the location to Edit & Delete")?></h1>
<div id="note">
<?=_("Fields marked with * are required (entry is compulsory)")?>
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php

    	shn_form_fopen("view_loc_cr");
    	_shn_or_update_loc();
    	?>
    	<div id="note">
	<?=_("Select location and then select the level(province,district,ect)," .
			"the selected location field at the end of the form will be updated")?>
	</div>
	<?


    $select_opts="onClick='update_loc(this.options[this.selectedIndex].value,this.options[this.selectedIndex].text)'";
    shn_form_hidden(array('loc_sel'=>'0'));
    shn_form_fsclose();
 // base location
    shn_form_fsopen(" Location");
	$range= shn_get_range();
    shn_location($range,null,null);; 
    shn_form_fsclose();
    ?><fieldset><?
    shn_form_opt_select('opt_location_type','Location Level',$select_opts,null,null);
    ?></fieldset><?
    
    shn_form_fsopen(_("Selected Location for Edit/Delete"));
    $extra_options['value']="All Locations";
    $extra_options['size']=60;
    shn_form_text(_("location"),'loc',"size=50",$extra_options);
    shn_form_fsclose();
 ?>
</center>
<br />
<center>
<?php
 	shn_form_submit("Submit");
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose(false);
?>
</div>
<?php
    // end of form

}

function _shn_admin_location_edit_form($loc){
	 global $global;
     $db=$global['db'];
     $q="select name,description,iso_code from location where loc_uuid='{$loc}'";
     $res=$db->Execute($q);
     
	?>
<h1 align="center"><?=_("Edit Location")?></h1>
<div id="note">
<?=_("Fields marked with * are required (entry is compulsory)")?>
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
	$form_opts['name']='view';	
    shn_form_fopen("edit_loc_cr",null,$form_opts);
    shn_form_fsopen(_("Location Details"));
    $extra_opts['req']=true;
    $extra_opts['value']=$res->fields["name"];
    shn_form_text(_("Location Name : "),'loc_name','size="50"',$extra_opts);
    $extra_opts['req']=false;
    $extra_opts['value']=$res->fields["description"];
    shn_form_text(_("Description : "),'desc','size="50"',$extra_opts);
    $extra_opts['value']=$res->fields["iso_code"];
    shn_form_text(_("ISO code : "),'iso','size="50"',$extra_opts);
    shn_form_fsclose();
    
 ?>
</center>

<?php
 	

//create the submit button
    shn_form_button(_("Close"),"onClick='change_action(\"close\")'");
	shn_form_button(_("Save"),"onClick='change_action(\"edit\")'");
    shn_form_button(_("Delete"),"onClick='change_action(\"del\")'");
    shn_form_hidden(array('action'=>'0'));
     shn_form_hidden(array('loc_id'=>$loc));
    _shn_admin_action_change_javascript("action");
    //close the form
    
?>
</center>
<br />
<?php
	shn_form_fclose(false);
?>
</div>
<?php
    // end of form
	
}

function _shn_admin_levels_form()
{
?>
<h2><?=_("Location Levels")?></h2>
<div id="note">
<?=_("The Location you add will be added after remaining ones)")?>
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
	$last=shn_get_last_level();
    shn_form_fopen("loc_lvl_cr");
    _shn_admin_loc_javascript("opt_location_type",$last[0]);
    shn_form_fsopen("Add New Level Information");
    shn_form_text(_("New Level : "),'type','size="50"',null); 
  //  shn_form_text(_("Abbrevation [3 letter unique abbr. to store in the database] : "),'type_abbr','size="50"',null); 
    shn_form_hidden(array("added"=>'0'));
    shn_form_hidden(array("removed"=>'0'));
    shn_form_button(_("Add"),"onClick='add_types()'");
    shn_form_fsclose();
 ?>
</center>
<?php
    shn_form_fsopen("Remove Levels");
    $select_opts="multiple='true'";
    shn_form_opt_select('opt_location_type','',$select_opts,$extra_opts);
  //  _shn_or_display_org_type($error,true);
     shn_form_button(_("Remove"),"onClick='remove_types()'");
    shn_form_fsclose();
 ?>
</center>
<br />
<center>
<?php
   shn_form_submit(_("Save"))
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

function _shn_adm_loc_lvl_cr()
{
    global $global;
    $db=$global['db'];
    $add = explode(":", $_POST{"added"});
    $remove = explode(":", $_POST{"removed"});
    for($i=1;$i<count($add);$i++){
        $temp = explode("|", $add[$i]);
        $q="insert into field_options(field_name,option_code,option_description) values('opt_location_type','{$temp[0]}','{$temp[1]}')";
        $res=$db->Execute($q);
    }
    for($i=1;$i<count($remove);$i++){
        $temp = explode("|", $remove[$i]);
        $q="delete from field_options where field_name='opt_location_type' and option_code='".$temp[0]."'";
        $res=$db->Execute($q);
    }
    _shn_admin_levels_form();
}

function _shn_admin_location_range_form()
{
    global $global;
    $db=$global["db"];
?>
<h2><?=_("Set the Location Range")?></h2>
<div id="note">
<?=_("In a Disaster,all the location levels might not be important ,set the range here")?>
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
	$range= shn_or_get_loc_range();
    shn_form_fopen("adm_location_range_cr",NULL,array('req_message'=>false));
    shn_location_level_range_form('start','Set Starting Level',$range["start"]);
 	shn_location_level_range_form('end','Set End Level',$range["end"]);
?>
<br />
<center>
<?php
//create the submit button
    shn_form_submit(_("Save"));
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


function _shn_admin_location_form()
{
    global $global;
    $db=$global["db"];
    ?>
    <h1 align="center"><?=_("Add Locations")?></h1>
	<div id="note">
	<?=_("Fields marked with * are required (entry is compulsory)")?>
	</div>
	<?php
    if($error==true)
        display_errors();
	?>
	<div id="formcontainer">
<?php
	
    shn_form_fopen("add_loc_cr");
    shn_form_fsopen(_("New Location Details"));
    $extra_opts['req']=true;
    shn_form_text(_("Location Name : "),'loc_name','size="50"',$extra_opts);
    $extra_opts['req']=false;
    shn_form_text(_("Description : "),'desc','size="50"',$extra_opts);
    shn_form_text(_("ISO code : "),'iso','size="50"',$extra_opts);
    shn_form_fsclose();
    shn_form_fsopen(_("Location Type (level)"));
    $extra_opts["req"]=true;
    $extra_opts["sort"]="option_code";
    shn_form_opt_select('opt_location_type','',$select_opts,$extra_opts);
    shn_form_fsclose();
    shn_form_fsopen(_("Now Select the parent Location"));
    $range= shn_get_range();
    shn_location($range,null,null);
    shn_form_fsclose();
    ?>
	</center>
	<br />
	<center>
<?php
 	shn_form_submit("Submit");
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose(false);
?>
</div>
<?php
    // end of form

}


function _shn_or_update_loc(){
?>
<script type="text/javascript">
    function update_loc(action,desc){
        var x=document.getElementsByName(action);
        var loc_val=x[0].options[x[0].selectedIndex].value;
        var loc_desc=x[0].options[x[0].selectedIndex].text;
        var x=document.getElementsByName('loc_sel');
        x[0].value=loc_val;
        loc_desc=desc+"->"+loc_desc;
        var x=document.getElementsByName('loc');
        x[0].value=loc_desc;
        return;
    }
</script>
<?php
}


function _shn_admin_action_change_javascript($change)
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

function _shn_admin_loc_javascript($name,$last)
{
?>
<script type="text/javascript">
var last=<?php echo $last?>;
 // sort function - ascending (case-insensitive)
        function sortFuncAsc(record1, record2) {
            var value1 = record1.optValue.toLowerCase();
            var value2 = record2.optValue.toLowerCase();
            if (value1 > value2) return(1);
            if (value1 < value2) return(-1);
            return(0);
        }

        // sort function - descending (case-insensitive)
        function sortFuncDesc(record1, record2) {
            var value1 = record1.optValue.toLowerCase();
            var value2 = record2.optValue.toLowerCase();
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
        		last=last+1;
            var y=document.getElementsByName("type");
          //  var z=document.getElementsByName("type_abbr");
            var add=document.getElementsByName("added");
            var remove=document.getElementsByName("removed");
            var exist=search(add[0].value,last,true,y[0].value);
            if(exist){
                alert("The Type Exists,you just added it");
                return;
            }
            var x=document.getElementsByName("<?php echo $name?>");
            exist=search_select_box(x[0],last,true,y[0].value);
            if(exist){
                alert("The Type Exists in the DataBase");
                return;
            }
            exist=search(remove[0].value,last,true,y[0].value);
            if(exist){
                remove[0]=del(remove[0].value,last);
                return;
            }
            opt = document.createElement("option") ;
            opt.text = y[0].value ;
            opt.value = last ;
            var k=x[0].options.length;
            x[0].options[k]=opt;
            sortSelect(x[0], true) ;
            add[0].value= add[0].value+":"+last+"|"+y[0].value;
            y[0].value=null;
            //z[0].value=null
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


