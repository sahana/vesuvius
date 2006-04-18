<?php
/** search form for the Organization Registry 
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
include_once $global['approot']."/inc/lib_location.inc";
include_once $global['approot']."/inc/lib_errors.inc";

/**
** Function for searching items
**/



function _shn_ims_search_item()
{

?>

<h1 align="center"><?php print _("Search an inventory item"); ?></h1>
<div id="search">

</div>

<?php
	$extra_opts['req']=true;

	shn_form_fopen("search_database");
	shn_form_fsopen(_('Search items '));
	shn_form_text(_("Search by Item name   : "),'item_name_search','size="50"',$extra_opts);

	$category_array=array();
	$category_array["bla"]=_("Blankets and Shelter");
	$category_array["med"]=_("Medical Drugs");
	$category_array["food"]=_("Food and Nutrition");
	$category_array["other"]=_("Other");
	shn_form_select($category_array,_("Category"),'itemcat','size="1"',$extra_opts);

	$item_state_array=array();
	$item_state_array["available"]=_("Items available");
	$item_state_array["tobe_detroyed"]=_("Items to be destroyed");
	$item_state_array["already_destroyed"]=_("Items already destroyed");
	shn_form_select($item_state_array,_("  State  : "),'item_state','size="1"',$extra_opts);

	shn_form_fsclose();

	
	shn_form_submit(_("Submit"));
	
	
	

	//shn_form_fsopen();	
	//$extra_opts['req']=false;
?>

		
</div>
	
<?php
	//shn_form_fsclose();
	shn_form_fclose();
}

/**
** Function for searching inventories
**/


function _shn_ims_form_search()
{
    global $global;
    global $conf;
    $db=$global["db"];
?>
<h2><?= _("Search for Inventories by Location")?></h2>
    <div id="formcontainer">
<?php
    shn_form_fopen("search_cr");
    _shn_ims_update_loc();
    shn_form_fsopen(_("Selected Location"));
    $extra_options['value']="All Locations";
    shn_form_text(_("location"),'loc',NULL,$extra_options);
    shn_form_label(_("Select location and then select the level(province,district,ect)"),NULL);
    $select_opts="onClick='update_loc(this.options[this.selectedIndex].value,this.options[this.selectedIndex].text)'";
    shn_form_hidden(array('loc_sel'=>'0'));
    shn_form_fsclose();
 // base location
    shn_form_fsopen(" Location");
   	$parent=_shn_ims_get_start_loc();
   	$range= shn_ims_get_loc_range();
  	shn_location($range,null,$parent); 
    shn_form_fsclose();
    ?><fieldset><?
    shn_form_opt_select('opt_location_type','Location Level',$select_opts,null,null);
    ?></fieldset><?
?>
</br>
    <center>
<?php
//create the submit button
    shn_form_submit(_("Search"));
?>
</center>
    </br>
<?php
        //close the form
    shn_form_fclose();
?>				     
</div>
<?php
}

function _shn_ims_update_loc(){
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
?>
