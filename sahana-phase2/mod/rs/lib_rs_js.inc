<?php
/**
 * Lib rs javascript
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
 * @subpackage rs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

/**
 * This function contain a javascript that submits the content of mod_select. this is called by the function _show_mod_select_form() in sample.inc
 * @access public
 * @return void
 */
function shn_sample_change_form_js()
{
?>
<script type="text/javascript">
    function changeform()
    {
    var x=document.mod_select.mod_name.options[document.mod_select.mod_name.selectedIndex].value;
    if(x!='none')
        {
        document.mod_select.submit();
        }
    }
</script>
<?php
}

/**
 * This function contain a javascript that submits the content of sample_rep_form. this is called by the function shn_rs_sample_report() in sample.inc
 * @access public
 * @return void
 */
function shn_sample_change_action_js()
{
?>
<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.sample_rep_form.submit();
         return;
    }
</script>
<?php
}

/**
 * This function contain a javascript that submits the content of sample_rep_form. this is called by the function shn_rs_search_type_select() in 	search.inc
 * @access public
 * @return void
 */
function shn_rs_search_cat_js()
{
?>
<script type="text/javascript">
    function changeform()
    {
 var x=document.rep_search.search_rep_chart.options[document.rep_search.search_rep_chart.selectedIndex].value;
	
  if(x!='none')
        {
        document.rep_search.submit();
        }
    }
</script>
<?php
}
?>