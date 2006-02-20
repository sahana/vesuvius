<?php
/**
 * This library generates forms regarding modules in security library.
 * 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage security
 * @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */
 
 include_once($global['approot'].'/inc/lib_form.inc');
 
 function shn_acl_module_status($module_list)
 {
 	global $global;
 	global $conf;
    $db=$global['db'];
    ?>
<div id="note">
Rows are Modules ,Intersection shows whether the Module has ACL entries installed and whether ACL is enabled or not
</div>
<div id="formcontainer">
<?php
    shn_form_fopen("adm_acl_mod_status_cr");
    if($error==true)
        display_errors();
?>
<div id ="result">
    <table>
        <thead>
        	<td>
        		Module
        	</td>
        	<td>
        		Installation
        	</td
        	<td>
        		Enabled
        	</td>
        </thead>
        <tbody>
<?php

 	foreach ($module_list as $i) {
 ?>
 <tr>
 	<td>
 <?php
    $module_name=$conf['mod_'.$i.'_name'];
    $module_name = ( null == $module_name )? $i : $module_name ;
 	echo $module_name;
 ?>
 	</td>
 	<td>
 <?php
 		if(shn_acl_is_module_installed($i)){
 			echo "<b><font color=#2E8B57>". _("ACL Installed") ."</font></b>";
 		}else{
 			echo "<b><font color=#FF0000>". _("ACL NOT Installed") ."</font></b>";
 		}
 ?>
 	</td>
 	<td>
 <?php
  // $chkbox_opts['value']=shn_acl_get_state($i);
	shn_form_checkbox('','chk_'.$i,null,$chkbox_opts);
 ?>
 	</td>
 </tr>
 <?php		
 	}	
 ?>
 </tbody>
 </table>
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
	
}
 
 ?>