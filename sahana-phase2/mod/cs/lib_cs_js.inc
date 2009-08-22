<?php
/**
 * javaScript Library of catalog system  
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
 * This function prints the javascript function to submit the "edit_cat_form_submit" in edit.inc
 * called in _shn_cs_edit_cat_select_submit_result() in edit.inc
 * @access private
 * @return void
 */
function shn_cs_edit_cat_select_submit_result_js()
{
?>
<script type="text/javascript">
    function shn_cs_edit_cat_select_submit_result_js(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         var bool = true;
         if(action == 'del'){
         	bool = confirm("Are you sure you want to delete this");
         }
         if(bool)
         	document.edit_form.submit();
         return;
    }
</script>
<?php
}

/**
 * This function prints the javascript function to submit the "edit_unit_select_submit_result" in edit.inc
 * called in _shn_cs_edit_unit_select_submit_result() in edit.inc
 * @access private
 * @return void
 */
function shn_cs_edit_unit_select_submit_result_js()
{
?>
<script type="text/javascript">
    function shn_cs_edit_unit_select_submit_result_js(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.edit_form.submit();
         return;
    }
</script>
<?php
}

/**
 * This function prints the javascript function to submit the "edit_unit_select_submit_result" in edit.inc
 * called in _shn_cs_edit_unit_select_submit_result() in edit.inc
 * @access private
 * @return void
 */
function shn_cs_edit_unit_type_form_submit_result_js()
{
?>
<script type="text/javascript">
    function shn_cs_edit_unit_type_form_submit_result_js(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.edit_form.submit();
         return;
    }
</script>
<?php
}

/**
 * This function prints the javascript function to submit the "select_unit_type_form" in edit.inc
 * called in shn_cs_addunit_form() in add.inc
 * @access private
 * @return void
 */
function shn_cs_addunit_form_js()
{
?>
<script type="text/javascript">
    function select_unit_type_form_js()
    {
    //document.select_unit_type_form.submit();
    var x=document.select_unit_type_form.unit_type.options[document.select_unit_type_form.unit_type.selectedIndex].value;
    if(x!='none')
        {
        document.select_unit_type_form.submit();
        }
    }
</script>
<?php
}

/**
 * This function prints the javascript function to submit the "select_type_submit" in search.inc
 * called in shn_cs_search_cat() in search.inc
 * @access private
 * @return void
 */
function shn_cs_search_cat_js()
{
?>
<script type="text/javascript">
    function shn_cs_search_cat_js()
    {
    var x=document.select_type_form.search_type.options[document.select_type_form.search_type.selectedIndex].value;
    if(x!='none')
        {
        document.select_type_form.submit();
        }
    }
</script>
<?php
}

