<?php 
/**
 * Add Category  
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
 * This function shows a form to add main category and submit values to a function in the main.inc
 * @access public
 * @return void
 */
function shn_cs_addmain_form()
{
    shn_form_fopen('addmain_form_submit');
    shn_form_fsopen(_t('Details of the catalog'));
    unset($_POST);

    shn_form_text(_t("Name   : "),'main_cat_name','size="30"', array('req'=>true,'note'=>'e.g. Medical Catalog'));
    shn_form_text(_t("Description   : "),'description','size="40"');
    shn_form_fsclose();
    shn_form_fsopen(_t('Keyword'));

    shn_form_text(_t(" "),'keyword','size="50"', array(
            'note' => _t('e.g. medical, drugs, health'),
            'help'=>_t('Enter a keyword which will help you to search particular catalog/item easily, when you add sub catalogs or items under this main catalog.')));

    shn_form_fsclose();
    shn_form_submit(_t("Add Catalog"));
    shn_form_fclose();

}

/**
 * This function shows the result after processing the POST values from shn_cs_addmain_form().
 *This function is called by shn_cs_addmain_form_submit() in main.inc
 * @access private
 * @return void
 */
function _shn_cs_addmain_form_result()
{
    require_once("lib_cs.inc");
    global $global;
    $db = $global["db"];
    $parentid = '0';
    $name = trim($_POST['main_cat_name']);
    $description = trim($_POST['description']);
    $keyword = trim($_POST['keyword']);
    
    
    $query1 = "SELECT ct_uuid FROM ct_catalogue WHERE name = '$name' and parentid = '0'";
    $res1 = $db->Execute($query1);
    
    if (isset($res1->fields["ct_uuid"])) {
    	add_warning(_t("Operation failed. Catalog name called ") . $name . _t(" already exists. Please use another name for the catalog."));
    	shn_cs_addmain_form();
    } else {
        $id = shn_create_uuid("catalogue");
    	$serial = shn_cs_generate_maincat_serial();

    	$q = "INSERT INTO ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) VALUES($parentid,'$id','$name','$description','$keyword','$serial')";
    	$res = $db->Execute($q);

		if ($res == true) {
			add_confirmation($name . _t(" was successfully saved in the database"));
			shn_cs_addmain_form();
		} else {
			add_warning(_t("Operation failed. ct_catalogue table not found in the database. Please contact system administrator."));
		}	
    }
}


/**
 * This function shows a form to add a sub category. It calls to a function in lib_cs.inc and submit the result to addsub_form1_submit.
 * @access public
 * @return void
 */

function shn_cs_addsub_form1()
{
    require_once("lib_cs.inc");
    $form_opts['name'] = 'subcat';
     
    shn_form_fopen("addsub_form1_submit",null,$form_opts);
    $max_depth = get_max_depth();
    shn_sub_cat($max_depth,'subcat','',true);
    shn_form_fclose();

    print "<br /><b>" . _t("Do a keyword search to find the parent category.") . "</b>";
    shn_form_fopen("keyword_search",null,array('req_message'=>false));
    shn_form_fsopen(_t('Keyword Search'));

    shn_form_text(_t(" "),'search_keyword','size="50"', array(
            'note' => _t('e.g. medical, drugs, health'),
            'help'=> _t('Search for the catalog using a keyword and then add catalogs/Items under it.'))
            );

    shn_form_hidden(array('type' => 'sub_catalogue'));
    shn_form_submit(_t("Search"));
    shn_form_fsclose();
    shn_form_fclose();
}


/**
 * This function shows a form to add a sub category.Submit the result to addsub_form2_submit() in main.inc.
 * @access private
 * @return void
 */
function _shn_cs_addsub_form1_result($is_keyword_search = false)
{
    global $global;
    $db = $global["db"];

    require_once("lib_cs.inc");
    if ($is_keyword_search == false) {
        $parent_id = get_itemid();
    } else {
        $parent_id = trim($_REQUEST['id']);
    }

    $extra_opts['req'] = true;
    shn_form_fopen("addsub_form2_submit");
    shn_form_fsopen(_t('New Category Details'));
    shn_form_text(_t("Name   : "),'sub_cat_name','size="50"',$extra_opts);
    shn_form_text(_t("Description   : "),'sub_description','size="50"',null);
    shn_form_fsclose();
    shn_form_fsopen(_t('Keyword'));
    shn_form_text(" ",'sub_keyword','size="50"', array('help'=>_t('Enter a keyword which will help you to search particular catalog/item easily, when you add sub catalogs or items under this sub catalog.')));
    shn_form_fsclose();
    
    //the parent ID is submitted as a hidden variable
    $parent_id_array = array('0' => $parent_id);
    shn_form_hidden($parent_id_array);

    shn_form_submit(_t("Add"));
    shn_form_fclose();
}

/**
 * This function shows the result after processing the POST values from _shn_cs_addsub_form1_result().
 *This function is called by shn_cs_addsub_form2_submit() in main.inc
 * @access private
 * @return void
 */

function _shn_cs_addsub_form2_result()
{
    global $global;
    $db = $global["db"];

    require_once("lib_cs.inc");
    $parent_id = get_itemid();

    $serial = shn_cs_generate_subcat_item_serial($parent_id);

    $sub_cat_name = trim($_POST['sub_cat_name']);
    $sub_description = trim($_POST['sub_description']);
    $sub_keyword = trim($_POST['sub_keyword']);
    $id = shn_create_uuid("catalogue");
    $q = "INSERT INTO ct_catalogue (parentid,ct_uuid,name,description,keyword,serial) VALUES('$parent_id','$id','$sub_cat_name','$sub_description','$sub_keyword','$serial')";
    $res = $db->Execute($q);

	if ($res == true) {
	    add_confirmation($sub_cat_name . _t(" was successfully saved in the database"));

	    ?>
	    <p><b><?php echo  _t("Add another sub catalog"); ?></b></p>
	    <?php

	    shn_cs_addsub_form1();
	} else {
	    add_warning(_t("Operation failed. ct_catalogue table not found in the database. Please contact system Administrator."));
	}
}

/**
 * This function shows a form to add Measurement Unit
 * @access public
 * @return void
 */
function shn_cs_addunit_form()
{
    global $global;
    $db = $global["db"];
    
    $option_array = array();

    $query = "SELECT unit_type_uuid,name FROM ct_unit_type ";
    $res = $db->Execute($query);
    $option_array['none'] = _t('----Select Unit type----');
    while (!$res == NULL && !$res->EOF) {
        $option_array[$res->fields['unit_type_uuid']] = $res->fields['name'];
        $res->MoveNext();
    }
    
    if ($option_array == null) {
        shn_form_fopen(null);
        shn_form_fsopen(_t("Information"));
        ?>
        <p><?php echo  _t('There is no any Measurement Unit category found. '); ?><a href="index.php?mod=cs&amp;act=addunittype"><?php echo _t("Add Unit category")?></a><?php echo  _t(' First'); ?></p>
    
        <?php
        shn_form_fsclose();
        shn_form_fclose();
    } else {
        $extra_opts['req'] = true;
        $form_opts['name'] = "select_unit_type_form";
        shn_form_fopen("addunit_select_utype_submit",null,$form_opts);
        shn_form_fsopen(_t("Select Measurement Unit Type"));
        $select_opts = 'onChange="select_unit_type_form_js()"';
        shn_form_select($option_array,'','unit_type',$select_opts,null);
        shn_form_fsclose();
        shn_form_fclose();
    }

    shn_cs_addunit_form_js();
}

function _shn_cs_utype_select_submit_result()
{
    global $global;
    $db = $global["db"];
    
    $unit_type_id = trim($_POST['unit_type']);
    
    $query = "SELECT name FROM ct_unit WHERE unit_type_uuid ='$unit_type_id' AND base_flag ='1'";
    $res = $db->Execute($query);
    
    $base_unit_name = $res->fields['name'];

    shn_form_fopen("addunit_form_submit");
    shn_form_fsopen(_t('Measurement Unit'));
    $extra_opts['req'] = true;
    shn_form_text(_t("Unit : "),'unit_name','size="50"',$extra_opts);
    $extra_opts['value'] = $base_unit_name;
    $extra_opts['req'] = false;
    shn_form_text(_t("Base Unit : "),'base_unit','size="5" readonly=true',$extra_opts);

    shn_form_text(_t("Multiplier : "),'multiplier','size="50"',array('req'=>'true','help'=>_t('Enter the Multiplier of the entered Unit to the base unit of the Unit Type. Eg: Unit = g, Base unit=kg, Multiplier=0.001 (g=kg*0.001)')));
    shn_form_fsclose();

    $unit_id_array = array('unit_type_id' => $unit_type_id);
    shn_form_hidden($unit_id_array);

    shn_form_submit(_t("Save"));

    shn_form_fclose();    

}


/**
 * This function shows the result after processing the POST values from shn_cs_addunit_form().
 *This function is called by shn_cs_addunit_form_submit() in main.inc
 * @access private
 * @return void
 */

function _shn_cs_addunit_form_result()
{
    global $global;
    $db = $global["db"];
        
    $unit_name = trim($_POST['unit_name']);
    $multiplier = trim($_POST['multiplier']);
    $unit_type_id = trim($_POST['unit_type_id']);
    
    $unit_id = shn_create_uuid("unit");
    $query = "INSERT INTO ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) VALUES('$unit_type_id','$unit_id','$unit_name','0',$multiplier)";
    $res = $db->Execute($query);

	if ($res == true) {
	    add_confirmation($unit_name . _t(" was successfully saved in the database"));
	    ?>
	    <p><b><?php echo  _t("Add another Unit"); ?></b></p>
	    <?php
	    shn_cs_addunit_form();
	} else {
	    add_warning(_t("Operation failed. ct_unit table not found in the database. Please contact system Administrator."));
	}
}


function shn_cs_additem_form1()
{
    global $global;
    $db = $global["db"];
    require_once("lib_cs.inc");
    $form_opts['name'] = 'subcat';
 
    shn_form_fopen("additem_form1_submit",null,$form_opts);
    $max_depth = get_max_depth();
    shn_sub_cat($max_depth,'subcat','',true);
    shn_form_fclose();

    $query = "SELECT name,ct_uuid FROM ct_catalogue WHERE parentid='0' ";
    $res = $db->Execute($query);
    if ($res == true) {
        print "<br /><b>" . _t("Do a keyword search to find the catalogue.") . "</b>";
        shn_form_fopen("keyword_search");
        shn_form_fsopen(_t('Keyword Search'));
        shn_form_text(" ",'search_keyword','size="50"', array('help'=>_t('Search for the catalog using a keyword and then add catalogs/Items under it.')));
        shn_form_hidden(array('type' => 'item'));
        shn_form_submit(_t("Search"));
        shn_form_fsclose();
        shn_form_fclose();
    }
}


function shn_cs_additem_form1_result($is_keyword_search = false)
{
    global $global;
    $db = $global["db"];
    require_once("lib_cs.inc");
    if ($is_keyword_search == false) {
        $parent_id = get_itemid();
    } else {
        $parent_id = trim($_REQUEST['id']);
    }
    
    $option_array = array();
    $query = "SELECT unit_type_uuid,name FROM ct_unit_type ";
    $res = $db->Execute($query);
    $option_array['none'] = _t('----Select Unit type----');
    
    while (!$res == NULL && !$res->EOF) {
        $option_array[$res->fields['unit_type_uuid']] = $res->fields['name'];
        $res->MoveNext();
    }

    $form_opts['name'] = "select_unit_type_form1";
    $extra_opts['req'] = true;
    shn_form_fopen("additem_form2_submit",null,$form_opts);

    shn_form_fsopen(_t('Item Type Details'));
    shn_form_text(_t("Name   : "),'itemname','size="50"',$extra_opts);
    shn_form_text(_t("Description   : "),'item_description','size="50"',null);
    shn_form_fsclose();

    shn_form_fsopen(_t('Keyword'));
    shn_form_text(" ",'item_keyword','size="50"', array('help'=>_t('Enter a keyword which will help you to search particular item easily.')));
    shn_form_fsclose();

    $select_opts = 'onChange=change_units(this.options[this.selectedIndex].value)';
    shn_form_fsopen(_t('Measurement Type'));
    shn_form_select($option_array,_t('Measurement Type :'),'measurement_type',$select_opts,array('req'=>true));
    shn_form_fsclose();
    $myoptions = array();
    shn_form_fsopen(_t('Measurement Unit'));
    shn_form_multi_select('unit_select',$myoptions, _t("Unit :"),'size=5 multiple="multiple"',array('req'=>true));
    shn_form_fsclose();

/*
    //This functionality should be moved to Inventory management

    $suppliers=shn_or_organization_search(null,array(_t("Supplier of Goods")));
    shn_form_fsopen(_t('Suppliers'));
    shn_form_multi_select('supplier_select',$suppliers, _t("Suppliers :"),'size=5 multiple="multiple"' );
    shn_form_fsclose();*/

    $parent_id_array = array('0' => $parent_id);
    shn_form_hidden($parent_id_array);

    shn_cs_additem_form1_result_ajax();
    shn_form_submit(_t("Add"));
    shn_form_fclose();

}

function shn_cs_additem_form2_result()
{
    global $global;
    $db = $global["db"];

    $items_saved_ok = false;
    $all_units_saved_ok = false;
    $save_failed_units = array();

    require_once("lib_cs.inc");
    $parent_id = get_itemid();
    
    $serial = shn_cs_generate_subcat_item_serial($parent_id);

    $item_name = trim($_POST['itemname']);
    $description = trim($_POST['item_description']);
    $item_keyword = trim($_POST['item_keyword']);

    $id = shn_create_uuid("catalogue");
    $q = "INSERT INTO ct_catalogue (parentid,ct_uuid,name,description,keyword,final_flag,serial) VALUES('$parent_id','$id','$item_name','$description','$item_keyword','1','$serial')";
    $res = $db->Execute($q);

	if ($res == true) {	
	    $items_saved_ok = true;
	}

    $unit_selected = $_POST["unit_select"];
    $num = sizeof($unit_selected);

    for ($i = 0; $i < $num; $i++) {
        $temp = $unit_selected[$i];
        $q = "INSERT INTO ct_cat_unit (ct_uuid,unit_uuid) VALUES('$id','$temp')";
        $res = $db->Execute($q);
    		if ($res == false) {	
				array_push($save_failed_units,$temp);
			}
    }//end of for

    $suppliers_selected = $_POST["supplier_select"];

    if ($suppliers_selected != null) {
        $numOfsuppliers = count($suppliers_selected);
        $supplier_arr_keys = array_keys($suppliers_selected);
        $save_failed_suppliers = array();

		for ($i = 0; $i < $numOfsuppliers; $i++) {
		    $temp = $suppliers_selected[$supplier_arr_keys[$i]];
		    $q = "INSERT INTO ct_suppliers (ct_uuid,supplier) VALUES('$id','$temp')";
		    $res = $db->Execute($q);
		    if ($res == false) {	
				array_push($save_failed_suppliers,$temp);
			}
		}//end of for
    }


	if ($save_failed_units == null) {
		$all_units_saved_ok = true;
	} else {
		$all_units_saved_ok = false;
	}
	
	if ($items_saved_ok == true && $all_units_saved_ok == true) {
		add_confirmation($item_name . _t(" was successfully saved in the database"));
		?>
		<p><b><?php echo  _t("Add another Item"); ?></b></p>
		<?php
		shn_cs_additem_form1();
	} elseif ($items_saved_ok == true && $all_units_saved_ok == false) {	
		$del_query = "DELETE FROM ct_catalogue WHERE ct_uuid = '$id' ";
		$res = $db->Execute($del_query);

		add_warning(_t("Operation failed. ct_cat_unit table not found in the database. Please contact system Administrator."));
	} elseif ($items_saved_ok == false && $all_units_saved_ok == true) {
		$del_query = "DELETE FROM ct_cat_unit WHERE ct_uuid = '$id' ";
		$res = $db->Execute($del_query);

		add_warning(_t("Operation failed. ct_catalogue table not found in the database. Please contact system Administrator."));
	} else {
		add_warning(_t("Operation failed. ct_catalogue and ct_cat_unit tables not found in the Database. Please contact system Administrator."));		
	}
}


function shn_cs_add_unit_type_form()
{
    $extra_opts['req'] = true;
    unset($_POST);
    shn_form_fopen("addunitform_submit");
    shn_form_fsopen(_t('Unit Type Details'));
    shn_form_text(_t("Name   : "),'unit_type_name','size="50"',$extra_opts);
    shn_form_text(_t("Description   : "),'unit_type_description','size="50"',null);
    shn_form_fsclose();

    shn_form_fsopen(_t('Base Unit Details'));
    shn_form_text(_t("Name   : "),'base_unit_name','size="50"',array('req'=>'true','help'=>_t('Specify a base unit here. Eg: Unit Type - Mass, Base Unit- kg')));
    shn_form_fsclose();

    shn_form_submit(_t("Add"));
    shn_form_fclose();
}

function _shn_cs_add_unit_type_form_result()
{
    global $global;
    $db = $global["db"];

    $unit_type_saved_ok = false;
    $base_unit_saved_ok = false;

    $unit_type_name = trim($_POST['unit_type_name']);
    $description = trim($_POST['unit_type_description']);
    $base_unit_name = trim($_POST['base_unit_name']);

    $unit_type_id = shn_create_uuid("unit_type");
    $q = "INSERT INTO ct_unit_type (unit_type_uuid,name,description) VALUES('$unit_type_id','$unit_type_name','$description')";
    $res = $db->Execute($q);
	if ($res == true) {
	    $unit_type_saved_ok = true;
	}

    $unit_id = shn_create_uuid("unit");
    $query = "INSERT INTO ct_unit(unit_type_uuid,unit_uuid,name,base_flag,multiplier) VALUES('$unit_type_id','$unit_id','$base_unit_name','1',0)";
    $res = $db->Execute($query);
	if ($res == true) {
		$base_unit_saved_ok = true;
	}

    if ($unit_type_saved_ok == true && $base_unit_saved_ok == true) {
		add_confirmation($unit_type_name . _t(" was successfully saved in the database"));
		?>
		<p><b><?php echo  _t("Add another unit type"); ?></b></p>
		<?php
		shn_cs_add_unit_type_form();
	} elseif ($unit_type_saved_ok == true && $base_unit_saved_ok == false) {
		$q = "DELETE FROM ct_unit_type WHERE unit_type_uuid = '$unit_type_id'";
	        $res = $db->Execute($q);
		add_warning(_t("Operation failed. ct_unit table not found in the Database. Please contact system Administrator.")); 
	} elseif ($unit_type_saved_ok == false && $base_unit_saved_ok == true) {
		$q = "DELETE FROM ct_unit WHERE unit_type_uuid = '$unit_type_id'";
	   	$res = $db->Execute($q);
		add_warning(_t("Operation failed. ct_unit_type table not found in the Database. Please contact system Administrator."));
	} else {
		add_warning(_t("Operation failed. ct_unit_type and ct_unit tables not found in the Database. Please contact system Administrator."));
	}
	
}


function _shn_cs_search_keyword_result()
{
    global $global;
    $db = $global["db"];

    print _t("Click on the parent catalogue that you need to add sub catalogue or Item under it.") . "<br /> ";

    $search_keyword = $name = trim($_POST['search_keyword']);
    $type = trim($_POST['type']);

?>
<br />
<div id="result">
<table>
    <thead>
        <td><strong><?php echo _t("Name")?></strong></td>
        <td><strong><?php echo _t("Description")?></strong></td>
        <td><strong><?php echo _t("Item/catalog")?></strong></td>
	<td><strong><?php echo _t("Keyword")?></strong></td>
    </thead>
    <TBODY>
    <?php

    $first_3_letters = substr($search_keyword, 0, 2);
    $query = "SELECT * FROM ct_catalogue WHERE keyword like '$first_3_letters%' AND final_flag!='1' ";
    $res = $db->Execute($query);

    while (!$res == NULL && !$res->EOF) {
        $name = $res->fields["name"];
        $description = $res->fields["description"];
        $cat_id = $res->fields["ct_uuid"];
        $final_flag = $res->fields["final_flag"];
        $keyword = $res->fields["keyword"];
    ?>
    <tr>
        <td><a href="index.php?mod=cs&amp;act=search_keyword_select_submit&amp;id=<?php echo $cat_id ?>&amp;type=<?php echo $type ?>"><?php print $name;?></a></td>
        <td><?php print $description; ?></td>
        <?php if ($final_flag == '0') { ?>
            <td><?php print _t("Catalog"); ?></td>
        <?php } else { ?>
            <td><?php print _t("Item"); ?></td>
        <?php } ?>
	<td><?php print $keyword; ?></td>
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

