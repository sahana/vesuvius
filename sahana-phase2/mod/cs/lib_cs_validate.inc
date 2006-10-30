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
    $error_flag=false;
    clean_errors();
    
    //this checks whether name entered in the add main form
    if(trim($_POST['main_cat_name'])==null)
    {
    add_error(_("Please Enter the Catalogue Name"));
    $error_flag=true;
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
    $error_flag=false;
    clean_errors();
    
    //this checks whether name entered in the add unit form
    if(trim($_POST['unit_name'])==null)
    {
    add_error(_("Please Enter the Unit Name"));
    $error_flag=true;
    }    

    if(trim($_POST['multiplier'])==null)
    {
    add_error(_("Please Enter the Multiplier"));
    $error_flag=true;
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
    $error_flag=false;
    clean_errors();
    //this checks whether name entered in the add sub category form
    if(trim($_POST['sub_cat_name'])==null)
    {
    add_error(_("Please Enter the Sub Category Name"));
    $error_flag=true;
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
    $error_flag=false;
    clean_errors();

    //this checks whether name entered in the add Item form
    if(trim($_POST['itemname'])==null)
    {
    add_error(_("Please Enter the Item Name"));
    $error_flag=true;
    }    

    if(trim($_POST['measurement_type'])==null || trim($_POST['measurement_type'])=='none')
    {
    add_error(_("Please Select the Unit Type"));
    $error_flag=true;
    }

    if(trim($_POST['unit_select'])==null)
    {
    add_error(_("Please Select Unit/Units"));
    $error_flag=true;
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
    $error_flag=false;
    clean_errors();

    //this checks whether name entered in the add Item form
    if(trim($_POST['unit_type_name'])==null)
    {
    add_error(_("Please Enter the Unit Type Name"));
    $error_flag=true;
    }    

    if(trim($_POST['base_unit_name'])==null)
    {
    add_error(_("Please Enter the Base Unit Name"));
    $error_flag=true;
    }

    return $error_flag;
}

/**
 * This function validates the search catalogue/item form.
 * This function is called by shn_cs_search_item_submit() in main.inc
 * @access private
 * @return boolean
 */
function _shn_cs_validate_cat_form()
{
    $error_flag=false;
    clean_errors();

    if(trim($_POST['cat_item_name'])==null)
    {
    add_error(_("Please Enter the Item/Catalogue Name to be searched"));
    $error_flag=true;
    }    
    if(trim($_POST['item_cat_radio'])==null)    
    {
    add_error(_("Please Select either Item or Catalogue radio button to search"));
    $error_flag=true;
    }

    return $error_flag;
}

/**
 * This function validates the search unit form.
 * This function is called by shn_cs_search_unit_submit() in main.inc
 * @access private
 * @return boolean 
 */
function _shn_cs_validate_unit_form()
{
    $error_flag=false;
    clean_errors();

    if(trim($_POST['measurement_type'])==null || trim($_POST['measurement_type'])=='none' && trim($_POST['unit_name'])!='all' )
    {
    add_error(_("Please Select the Measurement Unit Type"));
    $error_flag=true;
    }

    if(trim($_POST['unit_name'])==null)
    {
    add_error(_("Please Enter the Unit Name to be searched"));
    $error_flag=true;
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
    $error_flag=false;
    clean_errors();

    if(trim($_POST['unit_type_name'])==null || trim($_POST['unit_type_name'])== '')
    {
    add_error(_("Please Enter the Unit type Name to be searched"));
    $error_flag=true;
    }

    return $error_flag;
}

?>