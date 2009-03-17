<?php
/**
* This library helps uses phpgacl library to manage ACL
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra De Silva
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/
/**
 * @todo TO BE REMOVED
 * @deprecated by Ravith Botejue.
 * Commenting out the following. Couldn't find a possible use of this file.
 * Can be safely removed if nothing breaks.
 */
/*global $global;
include_once $global['approot']."/inc/handler_form.inc";
include_once $global['approot']."/inc/lib_location.inc";

function shn_admin_location_form()
{
?>
	<h1 align="center"><?php echo _t("Add Locations")?></h1>
	<div id="note">
	<?php echo _t("Fields marked with * are required (entry is compulsory)")?>
	</div>
<?php
    if($error==true)
        display_errors();
?>
	<div id="formcontainer">
<?php
    shn_form_fopen("add_loc_cr");
    _shn_admin_location_form();
?>
	</center>
	<br />
	<center>
<?php
 	shn_form_submit("Submit");
?>
	</center>
	<br />
<?php
    //close the form
    shn_form_fclose(false);
?>
	</div>
<?php
    // end of form

}


function _shn_admin_location_form()
{
    global $global;
    $db=$global["db"];
    shn_form_fsopen(_t("New Location Details)"));
    $extra_opts['req']=true;
    shn_form_text(_t("Location Name : "),'loc_name','size="50"',$extra_opts);
    $extra_opts['req']=false;
    shn_form_text(_t("Description : "),'desc','size="50"',$extra_opts);
    shn_form_text(_t("ISO code : "),'iso','size="50"',$extra_opts);
    shn_form_fsclose();
    shn_form_fsopen(_t("Location Type (level)"));
    shn_form_opt_select('opt_location_type','',$select_opts,array('req'=>true));
    shn_form_fsclose();
    shn_form_fsopen(_t("Now Select the parent Location"));
    $range= shn_get_range();
    shn_location($range,null,null);
    shn_form_fsclose();
}*/
