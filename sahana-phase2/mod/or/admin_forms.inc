<?php
/**Admin forms of the Organization Registry 
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

include_once($global['approot'].'/inc/lib_form.inc');
include_once $global['approot']."/inc/handler_form.inc";
include_once "lib_or.inc";

function shn_or_adm_location_form()
{
    global $global;
    $db=$global["db"];
?>
<h2><?=_("Set the Starting Location")?></h2>
<div id="note">
<?=_("When a Disaster happens,typically organizations located in a certain region get involved. Therefore when you select a location its a waste of time to always start from country. If you know the country ,give it in this form,and you can start with sub-divisions of that country. Furthermore ,if the Disaster is confined to a much smaller geographical area, select the appropriate location to start with.")?>
</div>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    shn_form_fopen("adm_location_cr");
    shn_form_fsopen(_("I want all the Locations ,so don't set a starting point"));
    shn_form_checkbox('','chk_start',null,$chkbox_opts);
    shn_form_fsclose();
    shn_form_fsopen(_("Select the Location Level you want fix"));
    shn_form_opt_select('opt_location_type','',$select_opts,null,null);
    shn_form_fsclose();
    $location_inf=shn_location_all();
    shn_form_add_component_list($location_inf,$section=true,$legend='Now Select the Location',$return=false,$default_val_req=$error);
 ?>
<br />
<center>
<?php
//create the submit button
    shn_form_submit(_("Save"));
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose();
?>				     
</div>
<?php
    // end of form
	
}

function shn_or_adm_or_type_form()
{
?>
<h2><?=_("Organization Types")?></h2>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    shn_form_fopen("adm_type_cr");
    _shn_or_admin_javascript("opt_org_type");
    shn_form_fsopen("Add New Type Information");
    shn_form_text(_("Organization Type : "),'type','size="50"',null); 
    shn_form_text(_("Abbrevation [3 letter unique abbr. to store in the database] : "),'type_abbr','size="50"',null); 
    shn_form_hidden(array("added"=>'0'));
    shn_form_hidden(array("removed"=>'0'));
    shn_form_button(_("Add"),"onClick='add_types()'");
    shn_form_fsclose();
 ?>
</center>
<?php
    shn_form_fsopen("Remove Types");
    _shn_or_display_org_type($error,true);
     shn_form_button(_("Remove"),"onClick='remove_types()'");
    shn_form_fsclose();
 ?>
</center>
<br />
<center>
<?php
    shn_form_hidden('added');
    shn_form_hidden('removed');
    shn_form_add_component($added,$return=false,$default_val_req=false);
    shn_form_submit(_("Save"))
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose();
?>				     
</div>
<?php
    // end of form
} 

function shn_or_adm_or_sector_form()
{
?>
<h2><?=_("Organization Sectors")?></h1>
<?php
    if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    shn_form_fopen("adm_sector_cr");
    _shn_or_admin_javascript("opt_sector_type[]");
    shn_form_fsopen("Add New Sector Information");
    shn_form_text(_("Organization Sector : "),'type','size="50"',null); 
    shn_form_text(_("Abbrevation [3 letter unique abbr. to store in the database] : "),'type_abbr','size="50"',null); 
    shn_form_hidden(array("added"=>'0'));
    shn_form_hidden(array("removed"=>'0'));
    shn_form_button(_("Add"),"onClick='add_types()'");
    shn_form_fsclose();
 ?>
</center>
<?php
    shn_form_fsopen("Remove Types");
    _shn_or_display_sector($error,true);
    shn_form_button(_("Remove"),"onClick='remove_types()'");
    shn_form_fsclose();
 ?>
</center>
<br />
<center>
<?php
    shn_form_hidden('added');
    shn_form_hidden('removed');
    shn_form_add_component($added,$return=false,$default_val_req=false);
    shn_form_submit(_("Save"))
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose();
?>				     
</div>
<?php
    // end of form
} 
