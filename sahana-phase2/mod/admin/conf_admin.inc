<?php
/* $Id: conf_admin.inc,v 1.13 2008-01-03 04:40:00 isurunishan Exp $ */
/**
 *
 * Sahana HTML form library
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage admin
 * @author     Chamindra de Silva (chamindra@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */


function shn_admin_conf_list()
{
	global $conf,$global;
	$is_ie = stripos($_SERVER['HTTP_USER_AGENT'],'MSIE')>0;
	/*
	 if (isset($_POST['conf_key'])) {
		shn_config_database_update($_POST['conf_key'],$_POST['conf_value']);
		add_confirmation($_POST['conf_key']." has been updated with value ".
		$_POST['conf_value']);
		}
		*/

	include_once($global['approot'].'/inc/lib_config.inc');
	include_once($global['approot'].'/inc/lib_form.inc');

	require_once($global['approot']."/3rd/xajax/xajax.inc.php");
	require_once($global['approot'].'/3rd/xajax/xajaxResponse.inc.php');

	$xajax = new xajax($conf['base_url'].'index.php?mod=admin&act=conf_list&stream=text');//$conf['base_url'].'index.php?mod=admin&act=conf_list'
	$xajax->registerFunction("_shn_admin_conf_ajax_update");
	$xajax->printJavascript("res/js/");
	?>
<script type="text/javascript" language="javascript">
		var current_edit_box = null;
<?php
	if($is_ie){
?>		
		// For Internet Explorer
		function show_edit_box(id)
		{
			// if any edit box is visible.
			if(current_edit_box!=null) {
				current_edit_box.style.visibility="hidden";
				current_edit_box=null;
			}
	
			current_edit_box=document.getElementById("edit_tr_"+id);
			current_edit_box.style.visibility="visible";
			document.getElementById("edit_txt_"+id).focus();
			
			
		}

		function hide_edit_box(id)
		{
			current_edit_box.style.visibility="hidden";
			var newValTarget = document.getElementById("target_"+id);

			if(newValTarget!=null) {
				if(newValTarget.childNodes[0]!=null) {
					newValTarget.removeChild(newValTarget.childNodes[0]);
				}
				newValTarget.appendChild(document.createTextNode("Updating..."));
			}
		
			current_edit_box=null;
			var editTextBox = document.getElementById("edit_txt_"+id);
			xajax__shn_admin_conf_ajax_update(id,(editTextBox!=null && editTextBox.value!=null)?editTextBox.value:"");
		}
<?php		
	}else{
?>
		// For CSS 2.1 compatible browsers.
		function show_edit_box(id)
		{
			// if any edit box is visible.
			if(current_edit_box!=null) {
				current_edit_box.style.display="none";
				current_edit_box=null;
			}
	
			current_edit_box=document.getElementById("edit_tr_"+id);
			current_edit_box.style.display="table-row";
			document.getElementById("edit_txt_"+id).focus();
		}

		function hide_edit_box(id)
		{
			current_edit_box.style.display="none";
			var newValTarget = document.getElementById("target_"+id);

			if(newValTarget!=null) {
				if(newValTarget.childNodes[0]!=null) {
					newValTarget.removeChild(newValTarget.childNodes[0]);
				}
				newValTarget.appendChild(document.createTextNode("Updating..."));
			}
		
			current_edit_box=null;
			var editTextBox = document.getElementById("edit_txt_"+id);
			xajax__shn_admin_conf_ajax_update(id,(editTextBox!=null && editTextBox.value!=null)?editTextBox.value:"");
		}
		<?php
		}
		?>
	
		// called by xajax to update the value asynchronously on the UI.
/*		function async_update(id,value)
		{
			var newValTarget = document.getElementById("target_"+id);
			newValTarget.removeChild(newValTarget.childNodes[0]);
			newValTarget.appendChild(document.createTextNode(value));
		}*/
</script>
		<?php
		ksort($conf);
		shn_config_database_fetch(&$dconf,'all');
		?>
<div id="result">
<table>
	<thead>
	<?php
	shn_form_table_row(array(_('Config Variable'),_('Current Value'),_('Modified Value'),_('Action')));
	?>
	</thead>
	<?php

	foreach($conf as $key => $value) {

		//$edit ='<a href="?mod=admin&act=conf_var&key='.$key.'">(edit)</a>';
		$edit ='<a href="#" onclick="show_edit_box(\''.$key.'\')">(edit)</a>';

		// truncate the strings if they are too long
		$str_value = shn_html_bool2str(shn_html_truncate($value,25));
		//$str_dconf = shn_html_bool2str(shn_html_truncate($dconf[$key],25));
		$str_dconf = shn_html_bool2str(shn_html_truncate($dconf[$key],25));
		//shn_form_table_row(array($key,$str_value,'<span id="target_'.$key.'">'.$str_dconf.'</span>',$edit));


		?>
	<tr onclick="show_edit_box('<?php echo $key; ?>')"
		style="cursor: pointer;")>
		<td><?php echo $key; ?></td>
		<td><?php echo $str_value; ?></td>
		<td><?php echo '<div id="target_'.$key.'">'.$str_dconf.'</div>'; ?></td>
		<td><?php echo $edit; ?></td>
	</tr>

	<!-- In place editing -->
	<tr id="edit_tr_<?php echo $key; ?>" <?php
	if($is_ie){
		?>
		style="visibility: hidden">
		<?php
}else{
	?>
		style="display: none">
		<?php
}
?>
		<td colspan="4">
		<div align="center" style="padding: 10px;">
		<fieldset><label for="edit_txt_<?php echo $key; ?>">New Value</label>
		<input name="edit_txt_<?php echo $key; ?>"
			id="edit_txt_<?php echo $key; ?>"
			value="<?php echo htmlspecialchars_decode((($dconf[$key]!=null)?$dconf[$key]:$value),ENT_QUOTES); ?>"
			type="text" /> <input type="button" value="Change"
			onclick="hide_edit_box('<?php echo $key; ?>')" /></fieldset>
		</div>
		</td>
	</tr>
	<?php
}

?>
</table>
</div>
<?php
}

function shn_html_bool2str($boolean)
{
	if(is_bool($boolean)) {
		$boolean = ($boolean == true)? "true":"false";
	}
	return $boolean;
}

function shn_html_truncate($string, $max_length)
{
	if(is_string($string) && strlen($string) > $max_length) {
		$string = substr($string, 0,($max_length/2)-1).
               "<a href=\"#\" title=\"$string\">...</a>".
		substr($string, -($max_length/2)+1);
	}
	return $string;
}


function shn_admin_conf_var()
{
	global $conf;

	shn_form_fopen('conf_list');
	shn_form_fsopen(_('Change Config Value'));
	shn_form_hidden(array('conf_key'=>$_GET['key']));

	if(is_bool($conf[$_GET['key']])) {
		shn_form_select(array('true'=>'true','false'=>'false'),$_GET['key'],'conf_value',null,
		array('value'=> shn_html_bool2str($conf[$_GET['key']])));
	}else {
		shn_form_text($_GET['key'],'conf_value','size="60"',array('value'=>$conf[$_GET['key']]));
	}

	shn_form_fsclose();
	shn_form_submit(_('Change value'));
	shn_form_fclose();
}

function _shn_admin_conf_ajax_update($key,$value)
{
	shn_config_database_update($key,$value);

	// truncate the new value before display.
	$new_value = htmlspecialchars_decode(shn_html_truncate($value,25));

	// create async response
	$xajax_response = new xajaxResponse();
	$xajax_response->addAssign("target_$key","innerHTML",$new_value);;
	return $xajax_response;
}

function shn_text_admin_conf_list()
{
	global $conf,$global;

	require_once($global['approot']."/3rd/xajax/xajax.inc.php");
	require_once($global['approot'].'/3rd/xajax/xajaxResponse.inc.php');

	$xajax = new xajax($conf['base_url'].'index.php?mod=admin&act=conf_list&stream=text');//$conf['base_url'].'index.php?mod=admin&act=conf_list'
	$xajax->registerFunction("_shn_admin_conf_ajax_update");
	$xajax->processRequests();
}
?>
