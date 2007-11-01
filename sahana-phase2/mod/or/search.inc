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

function _shn_or_form_search()
{
    global $global;
    global $conf;
    $db=$global["db"];
?>
<h2><?= _('Search for Organizations by Name,Type,Service and Location')?></h2>

	
    <div id="formcontainer">
<?php
    shn_form_fopen("search_cr");

    shn_form_fsopen(_('Primary Details'));
    $extra_opts['req']=false;
    shn_form_text(_('Organization Name : '),'org_name','size="40"',$extra_opts);
    $extra_opts['help']=_('please select whether you are a government organization,multinational ect');
    $extra_opts['all']=true;
    shn_form_opt_select('opt_org_type','Organization Type',null,$extra_opts);
    $extra_opts['help']=_('Select the services your provide ,i.e what you do as an organization. e.g.if you are a supplier select it');
    shn_form_opt_select('opt_sector_type','Organization Sector',null,$extra_opts);
    shn_form_fsclose();
    shn_form_fsopen(_("Base Location"));
 	shn_location(null,null,null,$extra_opts);
 	shn_form_text(_("Address"),'loc_txt','size="40"', NULL);
 	shn_form_fsclose();

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
