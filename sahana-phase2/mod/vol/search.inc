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
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

global $global;
include_once $global['approot']."/inc/lib_location.inc";
include_once $global['approot']."/inc/lib_errors.inc";

function _shn_vol_form_search()
{
    global $global;
    global $conf;
    $db=$global["db"];
?>
<h2><?php echo  _t("Search for Volunteers by Service and Location")?></h2>
    <div id="formcontainer">
<?php
    shn_form_fopen("search_cr");
    _shn_vol_update_loc();
     shn_form_fsopen(_t("Volunteer Service"));
    _shn_vol_display_sector($error,'dummy');
    shn_form_fsclose();
    shn_form_fsopen(_t("Selected Location"));
    $extra_options['value']="All Locations";
    shn_form_text(_t("location"),'loc',NULL,$extra_options);
    shn_form_label(_t("Select location and then select the level(province,district,ect)"),NULL);
    $select_opts="onClick='update_loc(this.options[this.selectedIndex].value,this.options[this.selectedIndex].text)'";
    shn_form_hidden(array('loc_sel'=>'0'));
    shn_form_fsclose();
 // base location
    shn_form_fsopen(" Location");
   	$parent=_shn_vol_get_start_loc();
   	$range= shn_vol_get_loc_range();
   	if($parent==$conf['mod_vol_start_loc']){
  		$location_inf = shn_location($range); 
    }else {
        $location_inf = shn_location_parent($parent,$range); 
    }
    shn_form_fsclose();
    ?><fieldset><?php
    shn_form_opt_select('opt_location_type','Location Level',$select_opts,null,null);
    ?></fieldset><?php
?>
</br>
    <center>
<?php
//create the submit button
    shn_form_submit(_t("Search"));
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

function _shn_vol_update_loc(){
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

