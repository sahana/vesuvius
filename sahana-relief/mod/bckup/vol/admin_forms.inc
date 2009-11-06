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
include_once "lib_vol.inc";

function shn_vol_adm_skill_form()
{
	global $global;
	include_once($global['approot'].'/inc/lib_misc.inc');
	include_once("api.inc");
	?>
<h2><?php echo _t("Volunteer Skills")?></h2>
	<?php
	if($error==true)
	display_errors();
	?>
<div id="formcontainer"><?php
$type_arr=shn_vol_skill_list();
$form_opts['name']='add_type';
shn_form_fopen("adm_skill_cr",null,$form_opts);
shn_add_remove_javascript("opt_skill_type[]",$type_arr);
//  shn_form_fsopen("Add New Type Information");

shn_form_hidden(array("added"=>','));
shn_form_hidden(array("removed"=>','));

//   shn_form_fsclose();
?>
<?php
shn_form_fsopen("Add Skills");
_shn_vol_display_skills($error,true,null,false);
//  shn_form_button(_t("Remove"),"onClick='remove_types()'");
shn_form_text(_t("New Skill : "),'type','size="50"',null);
?>
<center>
<?php
shn_form_button(_t("Add"),"onClick='add_types()'");
?>
</center>
<?php
shn_form_fsclose();
?>
<br />
<center><?php
$extra_opts['br']=false;
$extra_opts['req']=false;
shn_form_button(_t("Update"),"onClick='change_action(\"save\")'",$extra_opts);
shn_form_button(_t("Undo"),"onClick='change_action(\"reset\")'",$extra_opts);
shn_form_hidden(array('action'=>'0'));
shn_reset_form_javascript("add_type","opt_skill_type[]");
?></center>
<br />
<?php
//close the form
shn_form_fclose();
?></div>
<?php
// end of form
}

function shn_or_adm_or_sector_form()
{
	?>
<h2><?php echo _t("Organization Sectors")?>
</h1>
	<?php
	if($error==true)
	display_errors();
	?>
<div id="formcontainer"><?php
shn_form_fopen("adm_sector_cr");
_shn_or_admin_javascript("opt_sector_type[]");
shn_form_fsopen("Add New Sector Information");
shn_form_text(_t("Organization Sector : "),'type','size="50"',null);
shn_form_text(_t("Abbrevation [3 letter unique abbr. to store in the database] : "),'type_abbr','size="50"',null);
shn_form_hidden(array("added"=>'0'));
shn_form_hidden(array("removed"=>'0'));
shn_form_button(_t("Add"),"onClick='add_types()'");
shn_form_fsclose();
?>
</center>
<?php
shn_form_fsopen("Remove Types");
_shn_or_display_sector($error,true);
shn_form_button(_t("Remove"),"onClick='remove_types()'");
shn_form_fsclose();
?>
</center>
<br />
<center><?php
shn_form_submit(_t("Save"))
?></center>
<br />
<?php
//close the form
shn_form_fclose();
?></div>
<?php
// end of form
}
