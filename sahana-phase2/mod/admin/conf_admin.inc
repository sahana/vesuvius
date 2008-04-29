<?php

/* $Id: conf_admin.inc,v 1.20 2008-04-29 17:26:40 franboon Exp $ */

/* $Id: conf_admin.inc,v 1.20 2008-04-29 17:26:40 franboon Exp $ */
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
include_once($global['approot'].'inc/lib_config.inc');

function shn_admin_conf_list()
{
	global $conf,$global;
	/*
	 * Special types are declared here as an associative array with
	 * the key.
	 * Each key corresponds to an array , whoose first element will identify
	 * the special type of control. Any other elements will be extra_opts
	 *
	 * Ravith.
	 */

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
			if(document.getElementById("edit_txt_"+id)){
			    document.getElementById("edit_txt_"+id).focus();
			}else if(document.getElementById("edit_txt_"+id+"_t")){
			    // for boolean values
			    document.getElementById("edit_txt_"+id+"_t").focus();
			}


		}

		function hide_edit_box(id)
		{
			var newValTarget = document.getElementById("target_"+id);

			if(newValTarget!=null) {
				if(newValTarget.childNodes[0]!=null) {
					newValTarget.removeChild(newValTarget.childNodes[0]);
				}
				newValTarget.appendChild(document.createTextNode("Updating..."));
			}

			current_edit_box=null;
			var editTextBox = null;
			if(document.getElementById("edit_txt_"+id)){
			    editTextBox = document.getElementById("edit_txt_"+id);
			}else{
                editTextBox = "";
            }
			xajax__shn_admin_conf_ajax_update(id,(editTextBox!=null && editTextBox.value!=null)?editTextBox.value:"");
		}
		
		// called by xajax to hide.
		function _hide(){
		    current_edit_box.style.visibility="hidden";
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
			if(document.getElementById("edit_txt_"+id)){
                document.getElementById("edit_txt_"+id).focus();
            }else if(document.getElementById("edit_txt_"+id+"_1")){
                // for boolean values
                document.getElementById("edit_txt_"+id+"_1").focus();
            }
		}

		function hide_edit_box(id)
		{
			var newValTarget = document.getElementById("target_"+id);

			if(newValTarget!=null) {
				if(newValTarget.childNodes[0]!=null) {
					newValTarget.removeChild(newValTarget.childNodes[0]);
				}
				newValTarget.appendChild(document.createTextNode("Updating..."));
			}

			current_edit_box=null;
			var editTextBox = null;
            if(document.getElementById("edit_txt_"+id)){
                editTextBox = document.getElementById("edit_txt_"+id);
            }else{
                editTextBox = "";
            }
			xajax__shn_admin_conf_ajax_update(id,(editTextBox!=null && editTextBox.value!=null)?editTextBox.value:"");
		}
		
		// called by xajax to hide.
		function _hide(id){
		    current_edit_box=document.getElementById("edit_tr_"+id);
		    current_edit_box.style.display="none";
		    current_edit_box = null;
		}
		<?php
	}
		?>
    /**
    Used to change the value of boolean types using ajax calls.
    */
    function change_bool(fieldId,fieldObj){
        var target = document.getElementById(fieldId);
        target.value = fieldObj.value;
    }
	
</script>
		<?php
		ksort($conf);
		shn_config_database_fetch($dconf,'all');
		?>
<div id="result">
<table>
	<thead>
	<?php
	shn_form_table_row(array(_t('Config Variable'),_t('Current Value'),_t('Modified Value'),_t('Action')));
	?>
	</thead>
	<?php

	foreach($conf as $key => $value) {

		//$edit ='<a href="?mod=admin&act=conf_var&key='.$key.'">(edit)</a>';
		$edit ='<a href="#_'.$key.'" onclick="show_edit_box(\''.$key.'\')">(edit)</a>';

		// truncate the strings if they are too long
		$str_value = shn_html_bool2str(shn_html_truncate($value,25));
		//$str_dconf = shn_html_bool2str(shn_html_truncate($dconf[$key],25));
		$str_dconf = shn_html_bool2str(shn_html_truncate($dconf[$key],25));
		//shn_form_table_row(array($key,$str_value,'<span id="target_'.$key.'">'.$str_dconf.'</span>',$edit));

		$field_metadata = shn_config_get_metadata($key);
		?>
	<tr onclick="show_edit_box('<?php echo $key; ?>')"
		style="cursor: pointer;")>
		<td><!--uncomment the link if page scrolls up when clicked on edit --><!-- <a id="_<?php echo $key ?>"></a> --><?php echo $key; ?></td>
		<td><?php
		// Column 1
		if(isset($field_metadata)){
			// =========== Password ===============
			$sp_type = $field_metadata['type'];
			if(strtolower($sp_type)=='password'){
				echo "**********";
			}// any other special types should be handled here
			// ============= Boolean ================
			else if(strtolower($sp_type)=='boolean'){
				echo ($str_value == true)?'True':'False';
			}
			// ============= Integer ================
			// ============= Double =================
			// ============= URL ====================
			// ============= EMAIL ==================
			// ============= String =================
			else{
				echo $str_value;
			}
		} else{
			echo $str_value;
		}
		?></td>
		<td><?php
		// Column 2
		if(isset($field_metadata) && is_array($field_metadata)){
			$sp_type = $field_metadata['type'];
			// =========== Password ===============
			if(strtolower($sp_type)=='password'){
				echo '<div id="target_'.$key.'">**********</div>';
			}// any other special types should be handled here
			// ============= Boolean ================
			else if(strtolower($sp_type)=='boolean'){
				echo '<div id="target_'.$key.'">'.(($str_value == true)?'True':'False').'</div>';
			}// any other special types should be handled here
			// ============= Integer ================
    		// ============= Double =================
			// ============= URL ====================
			// ============= EMAIL ==================
            // ============= String =================			
			else{
				echo '<div id="target_'.$key.'">'.$str_dconf.'</div>';
			}
		}  else{
			echo '<div id="target_'.$key.'">('.$str_dconf.') raw </div>';
		}
		?></td>
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
		<div class="message error hide" id="target_<?php echo $key; ?>_error"></div>
		<div align="center" style="padding: 10px;">
		<fieldset><label for="edit_txt_<?php echo $key; ?>">New Value</label>
		<?php

		if(isset($field_metadata) && is_array($field_metadata)){
			$sp_type = $field_metadata['type'];

			// =========== Password ===============

			if(strtolower($sp_type)=='password'){
				?> <input name="edit_txt_<?php echo $key; ?>"
			     id="edit_txt_<?php echo $key; ?>" value="" type="password" /> <input
			     type="button" value="Change"
			     onclick="hide_edit_box('<?php echo $key; ?>')" /> <?php
			/*echo htmlspecialchars_decode((($dconf[$key]!=null)?$dconf[$key]:$value),ENT_QUOTES); */
             }// any other special types should be handled here

			// ============= Boolean ================
			
			else if(strtolower($sp_type)=='boolean'){
				$val= trim(htmlspecialchars_decode((($dconf[$key]!=null)?$dconf[$key]:$value),ENT_QUOTES));
				$checked_t = ($val==true || $val=='1')?"checked='checked'":"";
				$checked_f = ($val==false || $val=='0')?"checked='checked'":"";
				?> <input type="hidden" name="edit_txt_<?php echo $key; ?>"
						id="edit_txt_<?php echo $key; ?>" value="<?php echo $val ?>"> <input
						name="_edit_txt_<?php echo $key; ?>"
						id="_edit_txt_<?php echo $key; ?>_t" type="radio" value="true"
						<?php echo $checked_t; ?>
						onchange="change_bool('edit_txt_<?php echo $key; ?>',this)" /> <label
						for="_edit_txt_<?php echo $key; ?>_t"><?php echo _t("True") ?></label>
					&nbsp;&nbsp; <input name="_edit_txt_<?php echo $key; ?>"
						id="_edit_txt_<?php echo $key; ?>_f" type="radio" value="false"
						<?php echo $checked_f; ?>
						onchange="change_bool('edit_txt_<?php echo $key; ?>',this)" /> <label
						for="_edit_txt_<?php echo $key; ?>_f"><?php echo _t("False") ?></label>
					&nbsp;&nbsp; <input type="button" value="Change"
						onclick="hide_edit_box('<?php echo $key; ?>')" /> <?php
			}// any other special types should be handled here
			// ============= Integer ================
			// ============= Double =================
			// ============= URL ====================
			// ============= EMAIL ==================
            // ============= String =================			
			else{
				if(isset($field_metadata['use_textarea']) && $field_metadata['use_textarea']==true){
					?>
                <textarea name="edit_txt_<?php echo $key; ?>"
                        id="edit_txt_<?php echo $key; ?>"
                        type="text" ><?php echo htmlspecialchars_decode((($dconf[$key]!=null)?$dconf[$key]:$value),ENT_QUOTES); ?></textarea> <input type="button" value="Change"
                        onclick="hide_edit_box('<?php echo $key; ?>')" /> <?php
				}else{
			?>
			    <input name="edit_txt_<?php echo $key; ?>"
			            id="edit_txt_<?php echo $key; ?>"
			            value="<?php echo htmlspecialchars_decode((($dconf[$key]!=null)?$dconf[$key]:$value),ENT_QUOTES); ?>"
			            type="text" /> <input type="button" value="Change"
			            onclick="hide_edit_box('<?php echo $key; ?>')" /> <?php
			     }
            }
        } else{
	       ?> <input name="edit_txt_<?php echo $key; ?>"
			id="edit_txt_<?php echo $key; ?>"
			value="<?php echo htmlspecialchars_decode((($dconf[$key]!=null)?$dconf[$key]:$value),ENT_QUOTES); ?>"
			type="text" /> <input type="button" value="Change"
			onclick="hide_edit_box('<?php echo $key; ?>')" /> <?php
        }
?></fieldset>
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
		$boolean = ($boolean == true)? "True":"False";
	}else if("true" == strtolower(trim($boolean))){
		$boolean = "True";
	}else if("false" == strtolower(trim($boolean))){
		$boolean = "False";
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
	shn_form_fsopen(_t('Change Config Value'));
	shn_form_hidden(array('conf_key'=>$_GET['key']));

	if(is_bool($conf[$_GET['key']])) {
		shn_form_select(array('true'=>'true','false'=>'false'),$_GET['key'],'conf_value',null,
		array('value'=> shn_html_bool2str($conf[$_GET['key']])));
	}else {
		shn_form_text($_GET['key'],'conf_value','size="60"',array('value'=>$conf[$_GET['key']]));
	}

	shn_form_fsclose();
	shn_form_submit(_t('Change value'));
	shn_form_fclose();
}

function _shn_admin_conf_ajax_update($key,$value)
{
	$error = false;
    $error = shn_config_validate_value($key,$value);
    
	if($error===false){
		// no errors.
		shn_config_database_update($key,$value);
		// truncate the new value before display.
		$new_value = htmlspecialchars_decode(shn_html_truncate($value,25));
		$new_value = shn_html_bool2str($new_value);
		$new_value = shn_html_truncate($new_value,25);

		// create async response
		$xajax_response = new xajaxResponse();
		$xajax_response->addAssign("target_$key","innerHTML",$new_value);;
		// hide error if visible
		$xajax_response->addAssign("target_".$key."_error","className","feedback_content_error hide");;
		// hide row.
		$xajax_response->addScript("_hide('$key')");
		return $xajax_response;
	}else{
		$xajax_response = new xajaxResponse();
		$xajax_response->addAssign("target_".$key."_error","innerHTML",$error);;
		$xajax_response->addAssign("target_".$key."_error","className","feedback_content_error show");;
		//echo $xajax_response;
		//file_put_contents("/tmp/errors.txt","helo");
		return $xajax_response;
	}
}

function shn_text_admin_conf_list()
{
	global $conf,$global;

	require_once($global['approot']."/3rd/xajax/xajax.inc.php");
	require_once($global['approot'].'/3rd/xajax/xajaxResponse.inc.php');


	$xajax = new xajax($conf['base_url'].'index.php?mod=admin&act=conf_list&stream=text');//$conf['base_url'].'index.php?mod=admin&act=conf_list'
	$xajax->exitAllowedOff();
	$xajax->registerFunction("_shn_admin_conf_ajax_update");
	$xajax->processRequests();



}

/**
 * Display errors callback function. called by the sream error
 * handler.
 *
 */
function _shn_text_admin_conf_list__display_errors(){
	/*global $global;
	 $xajax_response = new xajaxResponse();
	 $msg = "Oops.. there were a few errors...<br/><ul>";
	 foreach($global['submit_errors'] as $error){
		$msg.="<li>".$error."</li>";
		}
		$msg.="</ul>";
		*/
}
?>
