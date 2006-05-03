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
	      Mahesh Kaluarachchi <mahesh@opensource.lk>
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
	$form_opts['name']='subcat';
	shn_form_fopen("search_item_page",null,$form_opts);
	shn_sub_cat(6,'subcat');


	shn_form_fclose();
}

function _shn_ims_search_item_page()
{
$parent_id = trim($_POST['0']);
	// this 5 should be replaced by the $max that is retrieved from the DB
	for($i=1;$i<5;$i++)
	{
	$parent_id = trim($_POST[$i]);
	
		if($parent_id==null)
		{
		$parent_id = $_POST[$i-1];
		break;
		}
	}
	//print ("test");	
	echo $parent_id;
?>

<h1 align="center"><?php print _("Search an inventory item"); ?></h1>
<div id="search">

<?php
	$extra_opts['req']=true;

	shn_form_fopen("search_database");
	shn_form_fsopen(_('Search items '));
	shn_form_text(_("Search by Item name   : "),'item_name','size="50"',$extra_opts);

	$item_state_array=array();
	$item_state_array["available"]=_("Item available");
	$item_state_array["expired"]=_("Item to be destroyed");
	$item_state_array["destroyed"]=_("Item already destroyed");
	shn_form_select($item_state_array,_("  State  : "),'item_state','size="1"',$extra_opts);

	global $global;
	$db=$global["db"];
	$inventory_array=array();
	//$inventory_array['0']="None";
	$q="SELECT inv_uuid,inventory_name FROM ims_inventory_records;";
	$ims=$db->Execute($q);
	//$j=0;
	while($ims!=NULL && !$ims->EOF)
	{
		
		$inventory_array[$ims->fields['inv_uuid']]=$ims->fields['inventory_name'];//}
		$ims->MoveNext();
		//$j=$j+1;
		//print ($j);
	}	
	
	shn_form_select($inventory_array,_("Inventory : "),'inventory','size="1"',$extra_opts);
	

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
