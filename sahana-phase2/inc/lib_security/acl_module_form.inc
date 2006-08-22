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
 global $global;
 include_once($global['approot'].'/inc/lib_form.inc');
 
 function shn_acl_module_status($module_list)
 {
 	global $global;
 	global $conf;
 	include_once($global['approot'].'/inc/lib_security/acl_api.inc');
    $db=$global['db'];
    ?>
<div id="note">
Rows are Modules ,Intersection shows whether the Module has ACL entries installed and whether ACL is enabled or not
</div>
<div id="formcontainer">
<?php
    shn_form_fopen("acl_module_cr",null, array('req_message'=>false));
    if($error==true)
        display_errors();
	shn_acl_system_module_status();
    shn_acl_generic_module_status($module_list);
//create the submit button
    shn_form_submit(_("Save"));
?>
</center>
<br />
<?php
    //close the form
    shn_form_fclose();
	
}
 
 function shn_acl_system_module_status($module_list=NULL)
 {
 	global $global;
 	global $conf;
 	include_once($global['approot'].'/inc/lib_security/acl_api.inc');
    $db=$global['db'];
    if ($module_list==NULL){
    	$module_list=array();
    	array_push($module_list,"admin");
    	array_push($module_list,"home");
    }
    ?>
<h3 align="center"> System Modules </h3>
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
 			$chkbox_opts['disabled']=true;
 		}
 ?>
 	</td>
 	<td>
 <?php
  	if(shn_acl_get_state($i)==1){
  		$text_opts="checked='true'";
  	}
  	//echo $chkbox_opts['value'];
	shn_form_checkbox('',$i,$text_opts,$chkbox_opts);
 ?>
 	</td>
 </tr>
 <?php		
 	}	
 ?>
 </tbody>
 </table>
 <br />
<?php	
}

function shn_acl_generic_module_status($module_list=NULL)
 {
 	global $global;
 	global $conf;
 	include_once($global['approot'].'/inc/lib_security/acl_api.inc');
    $db=$global['db'];
    if ($module_list==NULL){
    	$module_list=array();
    	array_push($module_list,"or");
    	array_push($module_list,"mpr");
    	array_push($module_list,"rms");
    	array_push($module_list,"cr");
    }
    ?>
<h3 align="center"> Other Modules </h3>
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
 			$chkbox_opts['disabled']=false;
 			echo "<b><font color=#2E8B57>". _("ACL Installed") ."</font></b>";
 		}else{
 			echo "<b><font color=#FF0000>". _("ACL NOT Installed") ."</font></b>";
 			$chkbox_opts['disabled']=true;
 		}
 ?>
 	</td>
 	<td>
 <?php
  	if(shn_acl_get_state($i)==1){
  		$text_opts="checked='true'";
  	}else{
  		$text_opts="";
  	}
  	
	shn_form_checkbox('',$i,$text_opts,$chkbox_opts);
 ?>
 	</td>
 </tr>
 <?php		
 	}	
 ?>
 </tbody>
 </table>
 <br />
<?php	
}


 ?>