<?php
/*
*
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra <ravindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

global $global;
include_once $global['approot']."/inc/lib_location.inc";
include_once $global['approot']."/inc/lib_errors.inc";

function _shn_or_form_search()
{
    global $global;
    $db=$global["db"];
?>
<h2><?= _("Search for Organizations by Service and Location")?></h2>
    <div id="formcontainer">
<?php
    shn_form_fopen("search_cr");
    _shn_or_update_loc();
    shn_form_fsopen(_("Organization Type"));
    _shn_or_display_org_type($error,false,'dummy');
    shn_form_fsclose();
    shn_form_fsopen(_("Organization Sector"));
    _shn_or_display_sector($error,'dummy');
    shn_form_fsclose();
    shn_form_fsopen(_("Based Location"));
    $extra_options['value']="All Locations";
    shn_form_text(_("location"),'loc',NULL,$extra_options);
    shn_form_label(_("Select location and then select the level(province,district,ect)"),NULL);
    $select_opts="onClick='update_loc(this.options[this.selectedIndex].value,this.options[this.selectedIndex].text)'";
    shn_form_hidden(array('loc_sel'=>'0'));
    shn_form_fsclose();                      
    $location_inf = shn_location_form('1','4'); 
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

function _shn_or_update_loc(){
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
