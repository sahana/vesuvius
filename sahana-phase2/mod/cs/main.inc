<?php
/**
 * Main Controller of the catalog System. 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage cs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot'] . "/inc/lib_menu.inc";
include_once $global['approot'] . "/inc/lib_form.inc";
include_once $global['approot'] . "/inc/lib_errors.inc";
include_once $global['approot'] . "/inc/lib_uuid.inc";
include_once $global['approot'] . "/inc/lib_paging.inc";

//reporting libraries
include_once $global['approot'] . "/inc/reporting/lib_reporting.inc";
include_once $global['approot'] . "/inc/reporting/lib_chart.inc";
//other module APIs.
include_once $global['approot'] . '/mod/ims/lib_ims.inc';
include_once $global['approot'] . '/mod/or/api.inc';
//catalog system libraries
include_once $global['approot'] . '/mod/cs/lib_cs_js.inc';
include_once $global['approot'] . '/mod/cs/lib_cs_ajax.inc';
include_once $global['approot'] . '/mod/cs/lib_cs_validate.inc';

/**
 * Create the module menu
 * @access public
 * @return void
 */
function shn_cs_mainmenu() 
{
    global $global;
    $module = $global['module'];

    // The  module menu
	shn_mod_menuopen(_t("Aid Catalog"));
	shn_mod_menuitem("default",_t("Home"));
	shn_mod_menuitem("viewedit",_t("View Aid Catalog"));
	shn_mod_menuitem("drill_down",_t("Drill Down Catalog"));
	shn_mod_menuitem("search",_t("Search Item Types"));
	shn_sub_mod_menuopen(_t("Modify Catalog"));
	shn_mod_menuitem("addmain",_t("Add New Catalog"));
	shn_mod_menuitem("addsub",_t("Add Aid Category"));
	shn_mod_menuitem("additem",_t("Add Aid Item Type"));
	//shn_mod_menuitem("addunittype",_t("Add Measurement Unit Type")); // relocate to admin section
	//shn_mod_menuitem("addunit",_t("Add Measurement Unit")); // relocate to admin section
	shn_sub_mod_menuclose();
	
	//shn_mod_menuitem("supplier_report",_t("Supplier Report")); // Supplier report should be in Inventory
	shn_mod_menuclose();
   
    // include the main menu
    include $global['approot'] . "/inc/handler_mainmenu.inc";
} 

/**
 * View the home page of the module
 * @access public
 * @return void
 */
function shn_cs_default()
{	
    include_once ('home.inc');
}

/**
 * This function calls to shn_cs_search_cat() in search.inc which enables search for a catalog,item, Units or unit types
 * @access public
 * @return void
 */
function shn_cs_search()
{
    ?>
    <h1><?php echo  (_t("Search")) ?></h1>
    <p><?php echo  _t('Select the Search Type in the select box that you need to search. By selecting catalog/Item, you are able to Search for a Item or a catalog and by selecting Unit, you are able to search for Units.'); ?></p> 
    <?php
    require_once('search.inc');
    shn_cs_search_cat();
}

/**
 * This function recieves submited result from the shn_cs_search_cat() in search.inc.
 * @access private
 * @return void
 */
function shn_cs_select_type_submit()
{
    ?>
    <h1><?php echo  (_t("Search")) ?></h1>
    <?php
    require_once('search.inc');
    $selected = trim($_POST['search_type']);

    if ($selected == 'none') {
        shn_cs_search_cat();
    } else if ($selected == 'Item') {
        shn_cs_search_cat();
        _shn_cs_cat_form();
    } else if ($selected == 'Unit') {
        shn_cs_search_cat();
        _shn_cs_unit_form();
    } else if ($selected == 'Unit_type') {
        shn_cs_search_cat();
        _shn_cs_unit_type_form();
    }
}

function shn_cs_search_item_submit()
{
    ?>
    <h1><?php echo  (_t("Search catalog/item")) ?></h1>
    <?php
    require_once('search.inc');
    
    if (_shn_cs_validate_cat_form()) {
        display_errors();
        shn_cs_search_cat();
        _shn_cs_cat_form();
    } else {
        shn_cs_search_cat();
        _shn_cs_cat_form();
        _shn_cs_search_item_cat_submit_result();
    }
}

function shn_cs_search_unit_submit()
{
    ?>
    <h1><?php echo  (_t("Search units")) ?></h1>
    <?php
    require_once('search.inc');

    shn_cs_search_cat();
    _shn_cs_unit_form();
    _shn_cs_search_unit_submit_result();
	
}

function shn_cs_search_unit_type_submit()
{
    ?>
    <h1><?php echo  (_t("Search unit types")) ?></h1>
    <?php
    require_once('search.inc');

    if (_shn_cs_validate_search_unit_type_form()) {
        display_errors();
        shn_cs_search_cat();
        _shn_cs_unit_type_form();
    } else {
        shn_cs_search_cat();
        _shn_cs_unit_type_form();
        _shn_cs_search_unit_type_submit_result();
    }
}


function shn_cs_addmain()
{
    ?>
    <h1><?php echo  (_t("Add New Aid Catalog")) ?></h1>
    <p><?php echo  _t('Please add the details of the New Aid Catalog below'); ?></p>
    <?php

    require_once('add.inc');
    shn_cs_addmain_form();
}

function shn_cs_addsub()
{
    ?>
    <h1><?php echo  (_t("Add A New Category")) ?></h1>
    <p><?php echo  _t('The Aid Catolog can be divided in to categories or classified by the type of item. You can create a hierachy of categories. First select the parent category that you wish to place this new category under:'); ?></p>
    <?php
    require_once('add.inc');
    shn_cs_addsub_form1();
}


function shn_cs_addmain_form_submit()
{
    require_once('add.inc');
    
    if (_shn_cs_validate_addmainform()) {
        display_errors();
        shn_cs_addmain_form();
    } else {
        _shn_cs_addmain_form_result();
    }
}

function shn_cs_addsub_form1_submit()
{
    ?>
    <h1><?php echo  (_t('Add New Category')) ?></h1>	
    <?php
    require_once('add.inc');
    require_once('lib_cs.inc');
    
    if (_shn_cs_validate_sub_cat_form()) {
        display_errors();
        shn_cs_addsub_form1();
    } else {
        _shn_cs_addsub_form1_result();
    }
	
}

function shn_cs_addsub_form2_submit()
{
    require_once('add.inc');
    
    if (_shn_cs_validate_subcatform()) {
        display_errors();
        _shn_cs_addsub_form1_result();
    } else {
        _shn_cs_addsub_form2_result();
    }
}


function shn_cs_addunit()
{
    ?>
    <h1><?php echo  (_t("Add Measurement Unit")) ?></h1>
    <p><?php echo  _t(' This feature allows to add measurement unit/units. Before adding a sub category you have to add the measurement unit/units that is  used by the particular category.'); ?></p>
    <?php
    require_once('add.inc');
    shn_cs_addunit_form();
}

function shn_cs_addunit_select_utype_submit()
{
    ?>
    <h1><?php echo  (_t("Add Measurement Unit")) ?></h1>
    <?php
    require_once('add.inc');
    shn_cs_addunit_form();
    _shn_cs_utype_select_submit_result();
}


function shn_cs_addunit_form_submit()
{
    require_once('add.inc');
	
    if (_shn_cs_validate_unitform()) {
        display_errors();
        shn_cs_addunit_form();
        _shn_cs_utype_select_submit_result();
    } else {
        _shn_cs_addunit_form_result();
    }
}


function shn_cs_additem()
{
	?>
	<h1><?php echo  (_t("Add Item Type: Select Category")) ?></h1>
	<p><?php echo  _t('First select the parent category, before proceeding to add the Item Type details'); ?></p>
	<?php

	require_once('add.inc');
	shn_cs_additem_form1();
}


function shn_cs_additem_form1_submit()
{
    ?>
    <h1><?php echo  (_t("Add Item")) ?></h1>
    <?php

    require_once('add.inc');
    require_once('lib_cs.inc');

    if (_shn_cs_validate_sub_cat_form()) {
        display_errors();
        shn_cs_additem_form1();
    } else {
        shn_cs_additem_form1_result();
    }
	
}

function shn_cs_additem_form2_submit()
{
    require_once('add.inc');
    //shn_cs_additem_form2_result();
    if (_shn_cs_validate_additem_form()) {
    	display_errors();
        shn_cs_additem_form1_result();
    } else {
        shn_cs_additem_form2_result();
    }
}


function shn_cs_viewedit()
{
    ?>
        <h1><?php echo  (_t("View And Edit")) ?></h1>
        <p><?php echo  _t("Here you are able to view, edit and Delete all the catalogues, Items, Units and Unit Types which are handled by the catalogue system. ") . "<b>" . _t("Using Delete, you will lose all the records of the particular catalogues, Items, Unit or Unit Types.") . "</b>"; ?></p>
    <?php

    require_once('edit.inc');
    //shn_cs_edit_form();
    show_item_cat_table();
}

function shn_cs_edit_form_submit()
{
    require_once('edit.inc');

    //$selected = trim($_POST['edit_type']);
    $selected = $_REQUEST['view_type'];

    if (!isset($selected)) {
        //shn_cs_edit_form();
        show_item_cat_table();
    } else if ($selected == 'item') {
        //shn_cs_edit_form();
        show_item_cat_table();
    } else if ($selected == 'unit') {
        //shn_cs_edit_form();
        show_unit_table();
    } else if ($selected == 'unit_types') {
        //shn_cs_edit_form();
        show_unit_type_table();
    }
}

function shn_cs_edit_cat_select_submit()
{
    ?>
    <h1><?php echo  (_t("Edit catalog / item")) ?></h1>
    <?php
    require_once('edit.inc');
    _shn_cs_edit_cat_select_submit_result();
}

function shn_cs_edit_cat_form_submit()
{
    require_once('edit.inc');
    _shn_cs_edit_cat_form_submit_result();
}

function shn_cs_edit_unit_select_submit()
{
    ?>
    <h1><?php echo  (_t("Edit Unit")) ?></h1>
    <?php
    require_once('edit.inc');
    _shn_cs_edit_unit_select_submit_result();
}

function shn_cs_edit_unit_form_submit()
{
    require_once('edit.inc');
    _shn_cs_edit_unit_form_submit_result();
}

function shn_cs_edit_unittype_select_submit()
{
    ?>
    <h1><?php echo  (_t("Edit Unit Type")) ?></h1>
    <?php
    require_once('edit.inc');
    _shn_cs_edit_unittype_select_submit_result();
}

function shn_cs_edit_unit_type_form_submit()
{
    require_once('edit.inc');
    _shn_cs_edit_unit_type_form_submit_result();
}

function shn_cs_edit_filter()
{
    require_once('edit.inc');
    shn_cs_edit_form();
    show_item_cat_table();
}


function shn_cs_addunittype()
{
    ?>
    <h1><?php echo  (_t("Add Unit Type")) ?></h1>
    <?php
    require_once('add.inc');
    
    ?>
    <p><?php echo  _t('Here you are able to add Unit type. For every Unit type you have to add a base unit. Eg. If you add volume as the unit type, Litre can be specified as the base unit.'); ?></p>
    <?php
    
    shn_cs_add_unit_type_form();
}

function shn_cs_addunitform_submit()
{
    require_once('add.inc');

    if (_shn_cs_validate_unit_type_form()) {
        display_errors();
        shn_cs_add_unit_type_form();
    } else {
        _shn_cs_add_unit_type_form_result();
    }
}

function shn_cs_keyword_search()
{
    require_once('add.inc');
    _shn_cs_search_keyword_result();
}

function shn_cs_search_keyword_select_submit()
{
    require_once('add.inc');
    $id = trim($_REQUEST['id']);
    $type = trim($_REQUEST['type']);

    if ($type == 'item') {
        shn_cs_additem_form1_result(true);
    } else if ($type == 'sub_catalogue') {
        _shn_cs_addsub_form1_result(true);
    }
}

function shn_cs_supplier_report()
{
    require_once('supplier_report.inc');
    shn_cs_show_supplier_report();
}

function shn_cs_drill_down()
{
	require_once('drill_down.inc');
}
