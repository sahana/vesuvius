<?php
/**
 * validate Library of catalogue system  
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
 * This function validates the values entered in add main form.
 *This function is called by shn_cs_addmain_form_submit() in main.inc
 * @access private
 * @return boolean
 */
function _shn_cs_validate_addmainform()
{
    $error_flag = false;
    clean_errors();
    
    //this checks whether name entered in the add main form
    if (trim($_POST['main_cat_name']) == null) {
    	add_error(_t("Please enter the catalog name"));
    	$error_flag = true;
    }

    return $error_flag;
}

/**
 * This function validates the values entered in add unit form.
 *This function is called by shn_cs_addunit_form_submit() in main.inc
 * @access private
 * @return boolean
 */
function _shn_cs_validate_unitform()
{
    $error_flag = false;
    clean_errors();
    
    //this checks whether name entered in the add unit form
    if (trim($_POST['unit_name']) == null) {
    	add_error(_t("Please enter the unit name"));
    	$error_flag = true;
    }    

    if (trim($_POST['multiplier']) == null) {
    	add_error(_t("Please enter the multiplier"));
    	$error_flag = true;
    }

    if (trim($_POST['multiplier']) != strval(floatval(trim($_POST['multiplier']))) && trim($_POST['multiplier']) != null) {
    	add_error(_t("Entered multiplier is not a valid number"));
    	$error_flag = true;
    }

    return $error_flag;
}

/**
 * This function validates the add sub catagory form.
 * This function is called by shn_cs_addsub_form2_submit() in main.inc
 * @access private
 * @return boolean
 */
function _shn_cs_validate_subcatform()
{
    $error_flag = false;
    clean_errors();
    //this checks whether name entered in the add sub category form
    if (trim($_POST['sub_cat_name']) == null) {
    	add_error(_t("Please enter the sub category name"));
    	$error_flag = true;
    }    

    return $error_flag;
}

/**
 * This function validates the add item form.
 * This function is called by shn_cs_additem_form2_submit() in main.inc
 * @access private
 * @return boolean
 */
function _shn_cs_validate_additem_form()
{
    $error_flag = false;
    clean_errors();

    //this checks whether name entered in the add Item form
    if (trim($_POST['itemname']) == null) {
    	add_error(_t("Please enter the item name"));
    	$error_flag = true;
    }    

    if (trim($_POST['measurement_type']) == null || trim($_POST['measurement_type']) == 'none') {
    	add_error(_t("Please select the unit type"));
    	$error_flag = true;
    }

    if (trim($_POST['unit_select']) == null) {
    	add_error(_t("Please select unit/units"));
    	$error_flag = true;
    }

    return $error_flag;
}

/**
 * This function validates the add unit type form.
 * This function is called by shn_cs_addunitform_submit() in main.inc
 * @access private
 * @return boolean
 */
function _shn_cs_validate_unit_type_form()
{
    $error_flag = false;
    clean_errors();

    //this checks whether name entered in the add Item form
    if (trim($_POST['unit_type_name']) == null) {
    	add_error(_t("Please enter the unit type name"));
    	$error_flag = true;
    }    

    if (trim($_POST['base_unit_name']) == null) {
    	add_error(_t("Please enter the base unit name"));
    	$error_flag = true;
    }

    return $error_flag;
}

/**
 * This function validates the search catalog/item form.
 * This function is called by shn_cs_search_item_submit() in main.inc
 * @access private
 * @return boolean
 */
function _shn_cs_validate_cat_form()
{
    $error_flag = false;
    clean_errors();

    if (trim($_POST['cat_item_name']) == null) {
    	add_error(_t("Please Enter the Item/catalog name to be searched"));
    	$error_flag = true;
    }    
    
    if (trim($_POST['item_cat_radio']) == null) {
    	add_error(_t("Please Select either Item or catalog radio button to search"));
    	$error_flag = true;
    }

    return $error_flag;
}


/**
 * This function validates the search unit type form.
 * This function is called by shn_cs_search_unit_type_submit() in main.inc
 * @access private
 * @return boolean 
 */
function _shn_cs_validate_search_unit_type_form()
{
    $error_flag = false;
    clean_errors();

    if (trim($_POST['unit_type_name']) == null || trim($_POST['unit_type_name']) == '') {
    	add_error(_t("Please enter the unit type name to be searched"));
    	$error_flag = true;
    }

    return $error_flag;
}
