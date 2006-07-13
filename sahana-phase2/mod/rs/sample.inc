<?php
/**
 * Sample Report
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

function shn_rs_search_cs_data()
{
    $option_array=array('none' => '-----Select -----','Item' => 'Item/Catalogue','Unit' => 'Unit','Unit_types'=>'Unit Types');
    $form_opts['name']="select_type_form";
    shn_form_fopen('select_type_submit',null,$form_opts);
    shn_form_fsopen(_('Select Category'));
    $select_opts='onChange="changeform()"';
    shn_form_select($option_array,'','search_type',$select_opts,null);
    shn_form_fsclose();
    shn_form_fclose();
}

function show_cat_search_form()
{

}

function show_unit_search_form()
{

}

function show_unit_type_search_form()
{

}

?>
<script type="text/javascript">
    function changeform()
    {
    var x=document.select_type_form.search_type.options[document.select_type_form.search_type.selectedIndex].value;
    if(x!='none')
        {
        document.select_type_form.submit();
        }
    }
</script>
<?php

?>