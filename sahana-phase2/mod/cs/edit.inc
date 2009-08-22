<?php
/**
 * View & Edit  
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author       Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage cs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */


/**
 * This function shows a form to select the category.Submit the result to shn_cs_edit_form_submit() in main.inc.
 * @access public
 * @return void
 */
function shn_cs_edit_form()
{	
  /*  ?>
	<div id="submenu_v">
	<a href="index.php?mod=cs&act=edit_form_submit&view_type=item">catalogs and Items</a> 
	<a href="index.php?mod=cs&act=edit_form_submit&view_type=unit_types">Unit Types</a> 
	<a href="index.php?mod=cs&act=edit_form_submit&view_type=unit">Units</a> 
	</div>
    <?php*/
}


/**
 * This function shows the catalog/Item table. Submit the result to shn_cs_edit_cat_select_submit() in main.inc.
 * @access private
 * @return void
 */
function show_item_cat_table()
{
    ?>
	<div id="submenu_v">
	<a class = "selected" href="index.php?mod=cs&amp;act=edit_form_submit&amp;view_type=item"><?php echo _t("Catalogs and Items")?></a> 
	<a href="index.php?mod=cs&amp;act=edit_form_submit&amp;view_type=unit_types"><?php echo _t("Unit Types")?></a> 
	<a href="index.php?mod=cs&amp;act=edit_form_submit&amp;view_type=unit"><?php echo _t("Units")?></a> 
	</div>
    <?php

    require_once('lib_cs.inc');
    global $global;
    $db = $global["db"];


    //------new development
    $query1 = "SELECT ct_uuid,name FROM ct_catalogue WHERE parentid = '0' ";
    $res1 = $db->Execute($query1);
    # start filling main_catalog array
    $main_cat_arr = array('all' => _t('All'));
    
    while (!$res1 == NULL && !$res1->EOF) {
        $main_cat_arr[$res1->fields["ct_uuid"]] = $res1->fields["name"];
        $res1->MoveNext();
    }// end of filling catalog array

    // start filling levels array
    $cat_item_level_arr = array();
    $cat_item_level_arr['all'] = 'All';

    for ($i = 1; $i <= get_max_depth(); $i++) {
		$cat_item_level_arr['l' . $i] = 'Level' . $i;
	}
    // end of filling levels array

    $count_query = "SELECT count(ct_uuid) FROM ct_catalogue";
    $count_res = $db->Execute($count_query);

    $num_of_rec['all'] = 'All';
	for ($i = 1; $i <= round(($count_res->fields[0]) / 10); $i++) {
		$num_of_rec[$i . '0'] = $i . '0';
	}

    $cat_item_arr = array('all' => _t('All'),'sub_cat' => _t('Sub Catalogs'), 'item' => _t('Items'));

/*
	print "<br /><br />";
    	shn_form_fopen('edit_filter',null,$form_opts);
   	?>
    <div id="result">
    <table>

	<tr>
        <td><?php print _t("Filter by : Main catalogue"); ?></td>
        <td><?php print _t("Filter by : Cataolg/Item"); ?></td>
        <td><?php print "Filter by : Level"; ?></td>
	<td><?php print _t("Filter by : Number of Records"); ?></td>
	<td><?php print ""; ?></td>
	</tr>

	<tr>

		<?php $extra_opts['value'] = isset($_POST['filter_main_cat'])  ? $_POST['filter_main_cat'] : 'all' ;?>

        <td><?php shn_form_select($main_cat_arr,'','filter_main_cat','',$extra_opts); ?></td>

		<?php $extra_opts['value'] = isset($_POST['filter_item_cat'])  ? $_POST['filter_item_cat'] : 'all' ;?>

        <td><?php shn_form_select($cat_item_arr,'','filter_item_cat','',$extra_opts); ?></td>

		<?php $extra_opts['value'] = isset($_POST['filter_levels'])  ? $_POST['filter_levels'] : 'all' ;?>
	
        <td><?php shn_form_select($cat_item_level_arr,'','filter_levels',"",$extra_opts); ?></td>

		<?php $extra_opts['value'] = isset($_POST['filter_num_rec'])  ? $_POST['filter_num_rec'] : 'all' ;?>

	<td><?php shn_form_select($num_of_rec,'','filter_num_rec',$select_opts,$extra_opts); ?></td>

	<td><?php shn_form_submit(_t("Filter")); ?></td>
	</tr>
	</table>
	</div>	
		<?php
	shn_form_fclose();*/
//-----------------------------------------------------------------------------------------------------------------------

    $query = "SELECT option_code FROM field_options WHERE field_name = 'opt_cs_page_record'";
    $res = $db->Execute($query);
    $num_of_rec_per_page = intval($res->fields["option_code"]);
	
	if (isset($_REQUEST['page'])) {	
		$start_rec = ($_REQUEST['page'] - 1) * $num_of_rec_per_page;
		$end_rec = $_REQUEST['page'] * $num_of_rec_per_page;
		
	} else {
		$start_rec = 0;
		$end_rec = $num_of_rec_per_page;
	}
	
    if (isset($_POST['filter_main_cat']) && $_POST['filter_main_cat'] != 'all') {
    	$filter_main_cat = $_POST['filter_main_cat'];
		$query1 = "SELECT serial FROM ct_catalogue WHERE ct_uuid = '$filter_main_cat' ";
    	$res1 = $db->Execute($query1);

	    while (!$res1 == NULL && !$res1->EOF) {
		    $filter_main_cat_serial = $res1->fields["serial"];
		    $res1->MoveNext();
	    }

	    if (isset($_POST['filter_item_cat']) && $_POST['filter_item_cat'] != 'all') {
		    $filter_item_cat = $_POST['filter_item_cat'];

		    if ($filter_item_cat == 'sub_cat') {
			    $final_flag = '0';
		    } else {
		    	$final_flag = '1';
		    }
				
		    $query = "SELECT * FROM ct_catalogue WHERE serial LIKE '$filter_main_cat_serial%' and final_flag='$final_flag' and parentid != '0' ORDER BY serial LIMIT " . $start_rec . "," . $end_rec;
		    $res = $db->Execute($query);
		
		    $queryx = "SELECT * FROM ct_catalogue WHERE serial LIKE '$filter_main_cat_serial%' and final_flag='$final_flag' and parentid != '0' ORDER BY serial";
    	    $resx = $db->Execute($queryx);
	    } else {
		    $query = "SELECT * FROM ct_catalogue WHERE serial LIKE '$filter_main_cat_serial%' ORDER BY serial LIMIT " . $start_rec . "," . $end_rec;
		    $res = $db->Execute($query);
			
		    $queryx = "SELECT * FROM ct_catalogue WHERE serial LIKE '$filter_main_cat_serial%' ORDER BY serial";
    	    $resx = $db->Execute($queryx);
		}
    } else {
    	$query = "SELECT * FROM ct_catalogue ORDER BY serial LIMIT " . $start_rec . "," . $end_rec;
    	$res = $db->Execute($query);
    	
    	$queryx = "SELECT COUNT(*) FROM ct_catalogue ORDER BY serial";
    	$resx = $db->Execute($queryx);
    }
    
    ?>
    <br />
    <?php
    
    $all_recs = $resx->fields["COUNT(*)"];
    
    if ($all_recs > $num_of_rec_per_page) {
    	$num_of_pages = ceil($all_recs / $num_of_rec_per_page);
    } else {
    	$num_of_pages = 1;
    }
    
    print "Page : ";
    
    for ($i = 1; $i <= $num_of_pages; $i++) {
    ?>
    &nbsp;<a href="index.php?mod=cs&amp;act=edit_form_submit&amp;view_type=item&amp;page=<?php echo $i ?>"><?php print $i;?></a>
    <?php
    }

?>
<br /><br />
<div id="result">
<table>
    <thead>
        <td><strong><?php echo _t("Name")?></strong></td>
        <td><strong><?php echo _t("Item/catalog")?></strong></td>
	<td><strong><?php echo _t("Keyword")?></strong></td>
    </thead>
    <TBODY>
    <?php


    $num_of_rec_counter = 0;

    while (!$res == NULL && !$res->EOF) {
	    $name = $res->fields["name"];
	    $description = $res->fields["description"];
	    $cat_id = $res->fields["ct_uuid"];
	    $final_flag = $res->fields["final_flag"];
	    $keyword = $res->fields["keyword"];
	    $parent_ID = $res->fields["parentid"];

	    ?>
	    <tr>
	        <td><?php _shn_cs_add_spaces_to_table($cat_id); ?><a href="index.php?mod=cs&amp;act=edit_cat_select_submit&amp;id=<?php echo $cat_id ?>"><?php print $name;?></a></td>
	        <?php if ($final_flag == '0' && $parent_ID == '0') { ?>
	            <td><?php print _t("Main catalog"); ?></td>
	        <?php } elseif ($final_flag == '0' && $parent_ID != '0') { ?>
		    <td>&nbsp;&nbsp;<?php print _t("Sub catalog"); ?></td>
	        <?php } else { ?>
	            <td>&nbsp;&nbsp;&nbsp;&nbsp;<?php print _t("Item"); ?></td>
	        <?php } ?>
	           <td>&nbsp;&nbsp;&nbsp;&nbsp;<?php print $keyword;?></td>
	    </tr>
	    <?php  
	    $res->MoveNext();
	    	
		$num_of_rec_counter++;
	
	    if (isset($_POST['filter_num_rec']) && $_POST['filter_num_rec'] != 'all' && ($num_of_rec_counter == $_POST['filter_num_rec'])) {
			break;
		}

    }//end of while loop
    ?>
    </TBODY>    
</table>
</div>
<?php
}

/**
 * This function adds spaces to the item catalog table according to the level it exists
 * @access private
 * @return void
 */
function _shn_cs_add_spaces_to_table($cat_id)
{
    require_once('lib_cs.inc');
    $level = shn_cs_get_level_count($cat_id);
	for ($i = 0; $i < $level; $i++) {
	    $space_string .= '&nbsp;&nbsp;&nbsp;&nbsp;';
	}
	
    print $space_string;
}

/**
 * This function shows the edit form for catalog/ Item. Submit the result to shn_cs_edit_cat_form_submit() in main.inc.
 * Called by shn_cs_edit_cat_select_submit() in main.inc
 * process POST data submited by show_item_cat_table() in edit.inc
 * @access private
 * @return void
 */

function _shn_cs_edit_cat_select_submit_result()
{
    ?>
    <p><?php echo  "<b>" . _t("Using Delete, you will lose all the records of the particular catalogs, Items, Unit or Unit Types. </b>By deleting a catalog You will lose all the entries under the particular catalog."); ?></p>
    <?php
    global $global;
    $db = $global["db"];

    $id = trim($_REQUEST['id']);

    $query = "SELECT name,description FROM ct_catalogue WHERE ct_uuid = '$id' ";
    $res = $db->Execute($query);

    $name = $res->fields["name"];
    $description = $res->fields["description"];

    $form_opts['name'] = "edit_form";
    $extra_opts['req'] = true;
    shn_form_fopen('edit_cat_form_submit',null,$form_opts);
    shn_form_fsopen(_t('Details Of the catalog/Item'));
    $extra_opts['value'] = $name;
    shn_form_text(_t("Catalog / Item Name   : "),'item_cat_name','size="50"',$extra_opts);
    $extra_opts['req'] = false;
    $extra_opts['value'] = $description;
    shn_form_text(_t("Description   : "),'description','size="50"',$extra_opts);
    shn_form_fsclose();

    shn_form_hidden(array('id' => $id));

    ?>
    <br />
    <center>
    <?php
    $extra_opts['br'] = false;
    $extra_opts['req'] = false;
    
    shn_form_button(_t("Close"),"onClick = 'shn_cs_edit_cat_select_submit_result_js(\"close\")'",$extra_opts);
    shn_form_button(_t("Save"),"onClick = 'shn_cs_edit_cat_select_submit_result_js(\"edit\")'",$extra_opts);
    shn_form_button(_t("Delete"),"onClick = 'shn_cs_edit_cat_select_submit_result_js(\"del\")'",$extra_opts);

    shn_form_hidden(array('action'=>'0'));
    ?>
    </center>
    <br />
    <?php
    shn_form_fclose();

    shn_cs_edit_cat_select_submit_result_js();
}


/**
 * This function does the action specified by the button.
 * Called by shn_cs_edit_cat_form_submit() in main.inc
 * process POST data submited by _shn_cs_edit_cat_select_submit_result() in edit.inc
 * @access private
 * @return void
 */
function _shn_cs_edit_cat_form_submit_result()
{
    global $global;
    $db = $global["db"];

    $action = trim($_POST['action']);

    if ($action == 'close') {
        show_item_cat_table();
    } else if ($action == 'edit') {
		$name = trim($_POST['item_cat_name']);
        $description = trim($_POST['description']);
        $id = trim($_POST['id']);
    
        $query = "UPDATE ct_catalogue SET name = '$name' , description = '$description' WHERE ct_uuid = '$id' ";
        $res = $db->Execute($query);    
	
		add_confirmation($name . _t(" was successfully saved in the database"));
        show_item_cat_table();
    } else if ($action == 'del') {
    	$id = trim($_POST['id']);
    	$inuse_flag_return = item_cat_inuse($id);
    	
        if ($inuse_flag_return == true) {
			add_warning(_t("Operation failed. You can not Delete this Catalog/ Item. Because there are sub catalogs/Items under this catalog OR it has been used by the INVENTORY MANAGEMENT SYSTEM."));
			show_item_cat_table();
        } else {
        	$query = "DELETE FROM ct_catalogue WHERE ct_uuid = '$id' ";
        	$res = $db->Execute($query);

        	$query2 = "DELETE FROM ct_cat_unit WHERE ct_uuid = '$id' ";
        	$res2 = $db->Execute($query2);

			add_confirmation(_t("Item/Catalog was deleted"));
        	show_item_cat_table();
        }
    }

}

function item_cat_inuse($item_cat_id)
{    
    global $global;
    $db = $global["db"];
    $inuse_flag = false;
    
        $query = "SELECT * FROM ct_catalogue WHERE parentid='$item_cat_id' ";
        $res = $db->Execute($query);
        if (!$res == NULL && !$res->EOF) {
            $inuse_flag = true;
        }
        
        if (_shn_ims_find_catalogid($item_cat_id)) {
            $inuse_flag = true;
        }
        
	return $inuse_flag;
}



/**
 * This function shows the Unit table. Submit the result to shn_cs_edit_cat_select_submit() in main.inc.
 * @access private
 * @return void
 */
function show_unit_table()
{
    ?>
	<div id="submenu_v">
	<a href="index.php?mod=cs&amp;act=edit_form_submit&amp;view_type=item"><?php echo _t("Catalogs and Items")?></a> 
	<a href="index.php?mod=cs&amp;act=edit_form_submit&amp;view_type=unit_types"><?php echo _t("Unit Types")?></a> 
	<a class = "selected" href="index.php?mod=cs&amp;act=edit_form_submit&amp;view_type=unit"><?php echo _t("Units")?></a> 
	</div>
    <?php

    global $global;
    $db = $global["db"];

	?>
	<br />
	<div id="result">
	<table>
	<thead>
        <td><strong><?php echo _t("Name")?></strong></td>
        <td><strong><?php echo _t("Multiplier")?></strong></td>
    </thead>
    <TBODY>
    <?php

    $query = "SELECT * FROM ct_unit";
    $res = $db->Execute($query);


    while (!$res == NULL && !$res->EOF) {
	    $name = $res->fields["name"];
	    $multiplier = $res->fields["multiplier"];
	    $unit_id = $res->fields["unit_uuid"];
	    ?>
	    <tr>
	        <td><a href="index.php?mod=cs&amp;act=edit_unit_select_submit&amp;id=<?php echo $unit_id ?>"><?php print $name;?></a></td>
	        <td><?php print $multiplier;?></td>
	    </tr>
	    <?php  
	    $res->MoveNext();
    }//end of while loop
    ?>

    </TBODY>
    
</table>
</div>
<?php
}

function _shn_cs_edit_unit_select_submit_result()
{
    global $global;
    $db = $global["db"];

    $id = trim($_REQUEST['id']);

    $query = "SELECT * FROM ct_unit WHERE unit_uuid = '$id' ";
    $res = $db->Execute($query);

    $name = $res->fields["name"];
    $multiplier = $res->fields["multiplier"];
    $base_flag = $res->fields["base_flag"];

    $form_opts['name'] = "edit_form";
    $extra_opts['req'] = true;
    shn_form_fopen('edit_unit_form_submit',null,$form_opts);
    shn_form_fsopen(_t('Details Of the Unit'));
    $extra_opts['value'] = $name;
    shn_form_text(_t("Unit Name   : "),'unit_name','size="50"',$extra_opts);
    //$extra_opts['value'] = $multiplier;
    if ($base_flag == '1') {
        shn_form_text(_t("Multiplier   : "),'multiplier','size="50" readonly=true',array('req'=>'true','value'=>$multiplier,'help'=>_t('Specify the multiplier of the particular unit to the base unit of the unit type')));
    } else {
        shn_form_text(_t("Multiplier   : "),'multiplier','size="50"',array('req'=>'true','value'=>$multiplier,'help'=>_t('Specify the multiplier of the particular unit to the base unit of the unit type')));
    }
    shn_form_fsclose();
    
    $parent_id_array = array('id' => $id);
    shn_form_hidden($parent_id_array);

    ?>
    <br />
    <center>
    <?php
    $extra_opts['br'] = false;
    $extra_opts['req'] = false;

    shn_form_button(_t("Close"),"onClick='shn_cs_edit_unit_select_submit_result_js(\"close\")'",$extra_opts);
    shn_form_button(_t("Save"),"onClick='shn_cs_edit_unit_select_submit_result_js(\"edit\")'",$extra_opts);
    shn_form_button(_t("Delete"),"onClick='shn_cs_edit_unit_select_submit_result_js(\"del\")'",$extra_opts);

    shn_form_hidden(array('action' => '0'));
    ?>
    </center>
    <br />
    <?php

    shn_form_fclose();
    shn_cs_edit_unit_select_submit_result_js();
}

function _shn_cs_edit_unit_form_submit_result()
{
    global $global;
    $db = $global["db"];

    $action = trim($_POST['action']);

    if ($action == 'close') {
    	show_unit_table();
    } else if ($action == 'edit') {
        $name = trim($_POST['unit_name']);
        $multiplier = trim($_POST['multiplier']);
        $id = trim($_POST['id']);
    
        $query = "UPDATE ct_unit SET name = '$name' , multiplier = $multiplier WHERE unit_uuid = '$id' ";
        $res = $db->Execute($query);    

		add_confirmation($name . _t(" was successfully saved in the database"));
        show_unit_table();
    } else if ($action == 'del') {
        $id = trim($_POST['id']);
    	$inuse_flag_return = unit_inuse($id);
        if ($inuse_flag_return == true) {
			add_warning(_t("Operation failed. You can not Delete this Unit. Because it has been used in INVENTORY MANAGEMENT SYSTEM."));
			show_unit_table();
        } else {
        	$query = "DELETE FROM ct_unit WHERE unit_uuid = '$id' ";
        	$res = $db->Execute($query);
			add_confirmation(_t("Unit was Deleted"));
			show_unit_table();
        }
    }//end of else if
}

function unit_inuse($unit_id_input)
{
    $inuse_flag = false;
    if (_shn_ims_find_unitid($unit_id_input)) {
        $inuse_flag = true;
    }
	
	return $inuse_flag;
}

function show_unit_type_table()
{
    ?>
	<div id="submenu_v">
	<a href="index.php?mod=cs&amp;act=edit_form_submit&amp;view_type=item"><?php echo _t("Catalogs and Items"); ?></a> 
	<a class = "selected" href="index.php?mod=cs&amp;act=edit_form_submit&amp;view_type=unit_types"><?php echo _t("Unit Types"); ?></a> 
	<a href="index.php?mod=cs&amp;act=edit_form_submit&amp;view_type=unit"><?php echo _t("Units"); ?></a> 
	</div>
    <?php


    global $global;
    $db = $global["db"];

?>
<br />
<div id="result">
<table>
    <thead>
        <td><strong><?php echo _t("Name")?></strong></td>
        <td><strong><?php echo _t("Description")?></strong></td>
    </thead>
    <TBODY>
    <?php

    $query = "SELECT * FROM ct_unit_type";
    $res = $db->Execute($query);

    while (!$res == NULL && !$res->EOF) {
        $name = $res->fields["name"];
        $description = $res->fields["description"];
        $unit_type_id = $res->fields["unit_type_uuid"];
    ?>
    <tr>
        <td><a href="index.php?mod=cs&amp;act=edit_unittype_select_submit&amp;id=<?php echo $unit_type_id; ?>"><?php print $name; ?></a></td>
        <td><?php print $description; ?></td>
    </tr>
    <?php  
        $res->MoveNext();
    }//end of while loop
    ?>

    </TBODY>
    
</table>
</div>
<?php
}


function _shn_cs_edit_unittype_select_submit_result()
{
    global $global;
    $db = $global["db"];

    $id = trim($_REQUEST['id']);

    $query = "SELECT name,description FROM ct_unit_type WHERE unit_type_uuid = '$id' ";
    $res = $db->Execute($query);

    $name = $res->fields["name"];
    $description = $res->fields["description"];

    $form_opts['name'] = "edit_form";
    $extra_opts['req'] = true;
    shn_form_fopen('edit_unit_type_form_submit',null,$form_opts);
    shn_form_fsopen(_t('Details Of the Unit Type'));
    $extra_opts['value'] = $name;
    shn_form_text(_t("Unit Type Name   : "),'unit_type_name','size="50"',$extra_opts);
    $extra_opts['req'] = false;
    $extra_opts['value'] = $description;
    shn_form_text(_t("Description   : "),'description','size="50"',$extra_opts);
    shn_form_fsclose();
    
    $parent_id_array = array('id' => $id);
    shn_form_hidden($parent_id_array);

    ?>
    <br />
    <center>
    <?php
    $extra_opts['br'] = false;
    $extra_opts['req'] = false;
    shn_form_button(_t("Close"),"onClick='shn_cs_edit_unit_type_form_submit_result_js(\"close\")'",$extra_opts);
    shn_form_button(_t("Save"),"onClick='shn_cs_edit_unit_type_form_submit_result_js(\"edit\")'",$extra_opts);
    shn_form_button(_t("Delete"),"onClick='shn_cs_edit_unit_type_form_submit_result_js(\"del\")'");

    shn_form_hidden(array('action'=>'0'));
    ?>
    </center>
    <br />
    <?php

    shn_form_fclose();
    shn_cs_edit_unit_type_form_submit_result_js();
}

function _shn_cs_edit_unit_type_form_submit_result()
{
    global $global;
    $db = $global["db"];

    $action = trim($_POST['action']);

    if ($action == 'close') {
		show_unit_type_table();
    } else if ($action == 'edit') {
        $name = trim($_POST['unit_type_name']);
        $description = trim($_POST['description']);
        $id = trim($_POST['id']);
    
        $query = "UPDATE ct_unit_type SET name = '$name' , description = '$description' WHERE unit_type_uuid = '$id' ";
        $res = $db->Execute($query);    

		add_confirmation($name . _t(" was successfully saved in the database"));
		show_unit_type_table();
    } else if ($action == 'del') {
        $id = trim($_POST['id']);
    	$inuse_flag_return = _is_units_under_this_type($id);
        if ($inuse_flag_return == true) {
			add_warning(_t("Operation failed. You can not Delete this Unit type. There are units added under this unit type."));
			show_unit_type_table();
        } else {
        	$query = "DELETE FROM ct_unit_type WHERE unit_type_uuid = '$id' ";
        	$res = $db->Execute($query);
			add_confirmation(_t("Unit type was deleted"));
			show_unit_type_table();
        }
    }//end of else if

}

function _is_units_under_this_type($unit_type_id_in)
{
    global $global;
    $db = $global["db"];
    $inuse_flag = false;
    
        $query = "SELECT * FROM ct_unit WHERE unit_type_uuid = '$unit_type_id_in' ";
        $res = $db->Execute($query);
        if (!$res == NULL && !$res->EOF) {
            $inuse_flag = true;
        }

	return $inuse_flag;
}
