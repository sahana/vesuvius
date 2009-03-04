<?php

/**
 * DSM xajex.inc
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @author     G.W.R. Sandaruwan <sandaruwan[at]opensource[dot]lk> <rekasandaruwan[at]gmail[dot]com
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage dsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

//register the function name as a ajax function
array_push($global['xajax_functions'],'dsm_show_form');
//array_push($global['xajax_functions'],'dsm_save_definition');
array_push($global['xajax_functions'],'dsm_add_field_value');
array_push($global['xajax_functions'],'dsm_add_field_param');
array_push($global['xajax_functions'],'dsm_set_field_type');
array_push($global['xajax_functions'],'dsm_delete_value');
array_push($global['xajax_functions'],'dsm_delete_param');
array_push($global['xajax_functions'],'dsm_put_value_in_session');
array_push($global['xajax_functions'],'dsm_add_validation_rule');
array_push($global['xajax_functions'],'dsm_clear_validation_rules');

/*
 *  function dsm_save_definition($text,$type,$name,$validation,$last_val_params,$dis_id){
 global $global;
 shn_session_start();
 $errors = array();

 if(isset($_SESSION['dsm'])==false){
 $_SESSION['dsm']=array();
 }
 if(isset($_SESSION['dsm'][$dis_id])==false){
 $_SESSION['dsm'][$dis_id] = array();
 }
 if(isset($_SESSION['dsm'][$dis_id]['field_values'])==false){
 $_SESSION['dsm'][$dis_id]['field_values'] = array();
 }
 if(isset($_SESSION['dsm'][$dis_id]['field_value_texts'])==false){
 $_SESSION['dsm'][$dis_id]['field_value_texts'] = array();
 }
 if(isset($_SESSION['dsm'][$dis_id]['field_param_keys'])==false){
 $_SESSION['dsm'][$dis_id]['field_param_keys'] = array();
 }
 if(isset($_SESSION['dsm'][$dis_id]['field_param_values'])==false){
 $_SESSION['dsm'][$dis_id]['field_param_values'] = array();
 }
 // insert the last value text, value, param key and param value to the session.
 if(strlen(trim($last_val_params['last_val']))>0){
 array_push(&$_SESSION['dsm'][$dis_id]['field_values'],$last_val_params['last_val']);
 }
 if(strlen(trim($last_val_params['last_val_text']))>0){
 array_push(&$_SESSION['dsm'][$dis_id]['field_value_texts'],$last_val_params['last_val_text']);
 }
 if(strlen(trim($last_val_params['last_param_key']))>0){
 array_push(&$_SESSION['dsm'][$dis_id]['field_param_keys'],$last_val_params['last_param_key']);
 }
 if(strlen(trim($last_val_params['last_param_value']))>0){
 array_push(&$_SESSION['dsm'][$dis_id]['field_param_values'],$last_val_params['last_param_value']);
 }

 $field_response = new xajaxResponse();

 //Save the data in to database------------------------------------------------------------------------
 if($text==null || strlen(trim($text))==0){
 $errors[] = _t('Please enter a "Field text".');
 //$field_response->addAssign("field_text_error","class","show");
 }

 if($name==null || strlen(trim($name))==0){
 $errors[] = _t('Please enter a "Field Name".');
 }

 if($type==null || strlen(trim($type))==0){
 $errors[] = _t('Please select a "Field Type".');
 }

 // do value validation
 if($type=='dropdown'){
 if(count($values)==0){
 $errors[] = _t('Drop down field requires at least one value.');
 }
 }else if($type=='check'){
 if(count($values)==0){
 $errors[] = _t('Checkbox field requires at least one value.');
 }
 }
 else if($type=='radio'){
 if(count($values)==0){
 $errors[] = _t('Radio button field requires at least one value.');
 }
 }

 //Create response------------------------------------------------------------------------

 if(count($errors)==0){

 $db = $global['db'];
 $db->StartTrans();
 //$db->debug = true; //debug code
 $query1 = "INSERT INTO dsm_fields(text,type,name) VALUES('$text','$type','$name')";
 $res1 = $db->Execute($query1);

 //-------------------------------------------------------------------------------------------------

 $field_id_query = "SELECT MAX(field_id) as next_fid FROM dsm_fields";
 $res2 = $db->Execute($field_id_query);
 $field_id = $res2->fields[0];

 // set the fieldid as the index too
 $query1 = "UPDATE dsm_fields SET indx=? WHERE field_id=?";
 $db->Execute($query1,array($field_id,$field_id));

 $query2 = $db->Prepare('INSERT INTO dsm_field_values(vals_text,value,field_id,indx) VALUES (?,?,?,?)');
 $values = $_SESSION['dsm'][$dis_id]['field_values'];
 $value_texts = $_SESSION['dsm'][$dis_id]['field_value_texts'];

 $array_keys = array_keys($values);
 foreach ($array_keys as $k){
 $db->Execute($query2,array($value_texts[$k],$values[$k],$field_id,$k));
 }

 //---------------------------------------------------------------------------------------------------

 $param_keys = $_SESSION['dsm'][$dis_id]['field_param_keys'];
 $param_vals = $_SESSION['dsm'][$dis_id]['field_param_values'];
 $query3 = $db->Prepare('INSERT INTO dsm_field_params(param_key,param,field_id) VALUES (?,?,?)');

 $array_keys = array_keys($param_keys);
 foreach ($array_keys as $k){
 $db->Execute($query3,array($param_keys[$k],$param_vals[$k],$field_id));
 }

 //----------------------------------------------------------------------------------------------------

 //$query = "INSERT INTO dsm_field_validation(field_id,field_validation) VALUES('$field_id','$validation')";
 //$res2 = $db->Execute($query);

 // link with disease.
 $query5 = $db->Prepare('INSERT INTO dsm_definitions(dis_id,field_id) VALUES(?,?)');
 $db->Execute($query5,array($dis_id,$field_id));

 $failed = $db->HasFailedTrans();
 $db->CompleteTrans();

 ob_start();
 if($failed==false){
 shn_form_button(_t("Create Field"),' onclick="add_field(\'field_list_div\')" ');
 echo "<hr />";
 echo "<div style='background-color: green;border:1px solid black;color:white;font-weight:bold;padding:2px;'> Field Saved </div>
 <div><table width='100%'><tr>";
 echo "<th>"._t('Field Name').'</th>';
 echo "<th>"._t('Field Type').'</th>';

 echo "<th>&nbsp;</th></tr>";

 // clear the session data placeholder
 if(isset($_SESSION['dsm'])){
 unset($_SESSION['dsm']);
 }

 //create edit and delete field--------------------------------------------------------------
 $field_id_query = "SELECT * FROM dsm_fields df JOIN dsm_definitions dd ON dd.field_id=df.field_id WHERE dd.dis_id=? ORDER BY df.field_id";
 $res5 = $db->Execute($field_id_query,array($dis_id));
 if($res5)
 while($row=$res5->FetchRow()){
 echo "<tr>";
 echo "<td >".$row['text']."</td>";
 echo "<td >".$row['type']."</td>";
 echo "<td ><a href=index.php?mod=dsm&act=edit_definition&field_id=".$row['field_id']."&disease_id=".$dis_id.">"._t("Edit")."</a>";
 echo "&nbsp &nbsp<a href=index.php?mod=dsm&act=delete_fields_confirm&field_id=".$row['field_id']."&disease_id=".$dis_id.">"._t("Delete")."</a></td>";
 echo "</tr>";
 }
 echo "</table></div>";
 }else{
 // error.
 echo "<div class=\"error\"><ul>";
 echo "<li>"._t("An unknown error occured while saving field.")."</li>";
 echo "</ul></div>";
 }
 $html_txt = ob_get_clean();
 $field_response->addAssign("field_list_div","innerHTML",$html_txt);

 }else{

 // show the errors
 $error_html = "<div class=\"error\"><ul>";
 foreach($errors as $e){
 $error_html .= "<li>".$e."</li>";
 }
 $error_html .= "</ul></div>";

 shn_session_start();
 if(isset($_SESSION['dsm'])==false){
 $_SESSION['dsm']=array();
 }
 if(isset($_SESSION['dsm'][$dis_id])==false){
 $_SESSION['dsm'][$dis_id] = array();
 }
 // set the default feild type
 $_SESSION['dsm'][$dis_id]['current_field_type'] = 'text';

 ob_start();
 ?>
 <div id="field_form"><?php
 echo $error_html;
 shn_form_fopen("reg_dsm_create_form");
 shn_form_fsopen(_t("Field Type"));
 $extra_opts = array();
 ?>
 <div class="info"><?= _t("These are the basic details of create a custom field.");?></div>
 <?php
 $extra_opts['req']=true;
 $extra_opts['value']='';
 //$extra_opts['help']=_t("Give the text for field to dsplay");
 echo '<div id="field_text_error" class="hide"></div>';
 shn_form_text(_t("Field Text : "),'dsm_field_text','size="40"',$extra_opts);

 //$extra_opts['help']=_t("Text Field, Text Area, Option Button, Check Box, Select Single, Select Multiple ");
 $options = array('text'=>_t('Text Box'),'textarea'=>_t('Text Area'),'dropdown'=>_t('Dropdown Box'),'radio'=>_t('Radio Button'),'check'=>_t('Check Box'),'date'=>_t('Date Field'));
 shn_form_select($options,_t("Field Type"),'dsm_field_type',' onchange="dsm_set_field_type(this.options[this.selectedIndex].value,\''.$dis_id.'\')"',array('req'=>true,'value'=>'text'));

 //$extra_opts['help']=_t("give the unique name");
 shn_form_text(_t("Field Name : "),'dsm_field_name','size="20"',$extra_opts);
 shn_form_fsclose();

 shn_form_fsopen(_t("Values for Field"));
 ?>
 <div class="info"><?= _t("Enter the at least one value for the fied.");?></div>

 <div id="value_div">
 <table>
 <tr>
 <th><?php echo _t("Text")?></th>
 <th><?php echo _t("Value")?></th>
 </tr>
 <tr>
 <td><?php shn_form_text(_t(""),'dsm_field_value_text_1',null,array('br'=>false,'no_label'=>true,'value'=>''));?></td>
 <td><?php shn_form_text(_t(""),'dsm_field_value_1','size="20"',array('br'=>false,'no_label'=>true,'value'=>'')); ?></td>
 </tr>
 <tr>
 <td colspan="2"><?php shn_form_button(_t('Add New Value'),' onclick="add_field_value(1)" ');?></td>
 </tr>
 </table>
 </div>
 <script type="text/javascript">
 field_form = MochiKit.DOM.getElement('field_form');
 </script> <?php
 shn_form_fsclose();

 shn_form_fsopen(_t("Parameter for Field"));
 ?>
 <div class="info"><?= _t("Enter the at least one param for the field.");?></div>


 <div id="param_div">
 <table>
 <tr>
 <th><?php echo _t('Key')?></th>
 <th><?php echo _t('Value')?></th>
 </tr>
 <tr>
 <td><?php shn_form_text(_t(""),'dsm_field_param_key_1',null,array('br'=>false,'no_label'=>true,'value'=>''));?></td>
 <td><?php shn_form_text(_t(""),'dsm_field_param_value_1','size="20"',array('br'=>false,'no_label'=>true,'value'=>'')); ?></td>
 </tr>
 <tr>
 <td colspan="2"><?php shn_form_button(_t('Add New param'),' onclick="add_field_param(1)" ');?></td>
 </tr>
 </table>
 </div>

 <?php
 shn_form_fsclose();

 shn_form_fsopen(_t("Validation for Field"));
 ?>
 <div class="info"><?= _t("Enter the Validation Critearia for the fied.");?></div>

 <?php
 $extra_opts['req']=false;
 //$extra_opts['help']=_t("Enter the Validation Critearia using <, >, ||, &  for the fied");
 shn_form_text(_t("Validation Critearia"),'dsm_field_validation','size="50"',$extra_opts);
 shn_form_fsclose();

 shn_form_button(_t("Create Field"),'onclick="save_definition()"');

 shn_form_fclose();
 //Form close
 ?></div>
 <?php

 $content = ob_get_clean();
 $field_response->addAssign('field_list_div','innerHTML',$content);
 return $field_response;

 }


 return $field_response;
 }*/

/**
 * Add New Field
 *
 * @param unknown_type $text
 * @param unknown_type $value
 * @param unknown_type $number
 * @param unknown_type $dis_id
 * @return unknown
 */

function dsm_add_field_value($number,$dis_id){
	global $global;
	shn_session_start();
	$response = new xajaxResponse();
	$text = '';
	$value = '';

	// initialize the session data holders the first time
	if(isset($_SESSION['dsm'])==false){
		$_SESSION['dsm'] = array();
	}

	if(isset($_SESSION['dsm'][$dis_id])==false){
		$_SESSION['dsm'][$dis_id] = array();
		$_SESSION['dsm'][$dis_id]['val_text'] = array();
		$_SESSION['dsm'][$dis_id]['val_value'] = array();
		/*$_SESSION['dsm'][$dis_id]['field_value_texts'] = array();
		 $_SESSION['dsm'][$dis_id]['field_values'] = array();*/
	}else{
		$text = $_SESSION['dsm'][$dis_id]['val_text'][$number];
		$value = $_SESSION['dsm'][$dis_id]['val_value'][$number];
	}

	//$response->addScript('console.debug("text='.$text.'")');
	//$response->addScript('console.debug("value='.$value.'")');
	// save values to session for recreation
	/*if(strlen(trim($text))>0){
	$_SESSION['dsm'][$dis_id]['field_value_texts'][$number] = $text;
	}
	if(strlen(trim($value))>0){
	$_SESSION['dsm'][$dis_id]['field_values'][$number] = $value;
	}*/
	// do error checking
	$errors = array();
	if(strlen(trim($text))==0){
		$errors[] = _t('Please enter a valid text.');
	}
	if(strlen(trim($value))==0){
		$errors[] = _t('Please enter a valid value');
	}

	ob_start();

	// print any errors
	if(count($errors)>0){
		echo "<div class='error message'>";
		echo "<ul>";
		foreach ($errors as $e){
			echo "<li>".$e."</li>";
		}
		echo "</ul></div>";
	}

	// append table and header
	$val_texts_in_session = $_SESSION['dsm'][$dis_id]['val_text'];
	$val_values_in_session = $_SESSION['dsm'][$dis_id]['val_value'];
	echo '<table><tr><th>'._t("Text").'</th><th>'. _t("Value").'</th></tr>';

	// append rows only if no errors in previous submission
	/*for($i=1;$i<=(count($errors)>0?$number:($number+1));$i++){*/
	$i = 0;
	foreach($val_texts_in_session as $i=>$v){
		echo '<tr><td>';
		shn_form_text(_t(""),'dsm_field_value_text_'.$i,'onblur="put_value_in_session(\'val_text\','.$i.',this.value,\''.$dis_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>(isset($val_texts_in_session[$i])?$val_texts_in_session[$i]:'')));
		echo '</td><td>';
		shn_form_text(_t(""),'dsm_field_value_'.$i,'onblur="put_value_in_session(\'val_value\','.$i.',this.value,\''.$dis_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>(isset($val_values_in_session[$i])?$val_values_in_session[$i]:'')));
		echo "</td><td>";
		shn_form_button(_t('Delete'),' onclick="delete_value('.($i).')" ',array('br'=>false));
		echo '</td></tr>';
	}
	// blank fields for next item
	$i++;
	echo '<tr><td>';
	shn_form_text(_t(""),'dsm_field_value_text_'.$i,'onblur="put_value_in_session(\'val_text\','.$i.',this.value,\''.$dis_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>''));
	echo '</td><td>';
	shn_form_text(_t(""),'dsm_field_value_'.$i,'onblur="put_value_in_session(\'val_value\','.$i.',this.value,\''.$dis_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>''));
	echo "</td><td>&nbsp;</td></tr>";


	// append bottom row and add new button
	echo '<tr><td colspan="3">';
	shn_form_button(_t('Add New Value'),' onclick="add_field_value('.($number+1).')" ');
	echo '</td></tr></table>';
	$html_content = ob_get_clean();

	$response->addAssign('value_div','innerHTML',$html_content);
	$response->addScript('setValueIndex('.($number+1).')');
	return $response;
}

/**
 * Delet Field Value
 *
 * @param unknown_type $text
 * @param unknown_type $value
 * @param unknown_type $number
 * @param unknown_type $dis_id
 * @return unknown
 */

function dsm_delete_value($number,$dis_id){
	global $global;
	shn_session_start();
	//shn_session_unset();
	$response = new xajaxResponse();
	//echo $number."<br/>";
	//var_dump($_SESSION['dsm'][$dis_id]['field_value_texts']);
	if(isset($_SESSION['dsm'][$dis_id])){
		unset($_SESSION['dsm'][$dis_id]['val_text'][$number] );
		unset($_SESSION['dsm'][$dis_id]['val_value'][$number]);
	}

	ob_start();
	// append table and header
	echo '<table><tr><th>'._t("Text").'</th><th>'. _t("Value").'</th></tr>';

	$i = 0;

	// append rows only if no errors in previous submission
	foreach($_SESSION['dsm'][$dis_id]['val_text'] as $i=>$v){
		echo '<tr><td>';
		shn_form_text(_t(""),'dsm_field_value_text_'.$i,'onblur="put_value_in_session(\'val_text\','.$i.',this.value,\''.$dis_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>(isset($_SESSION['dsm'][$dis_id]['val_text'][$i])?$_SESSION['dsm'][$dis_id]['val_text'][$i]:'')));
		echo '</td><td>';
		shn_form_text(_t(""),'dsm_field_value_'.$i,'onblur="put_value_in_session(\'val_value\','.$i.',this.value,\''.$dis_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>(isset($_SESSION['dsm'][$dis_id]['val_value'][$i])?$_SESSION['dsm'][$dis_id]['val_value'][$i]:'')));
		echo "</td><td>";
		shn_form_button(_t('Delete'),' onclick="delete_value('.($i).')" ',array('br'=>false));
		echo '</td></tr>';
	}
	// append bottom row and add new button
	echo '<tr><td colspan="3">';
	shn_form_button(_t('Add New Value'),' onclick="add_field_value('.($i).')" ');
	echo '</td></tr></table>';
	$html_content = ob_get_clean();

	$response->addAssign('value_div','innerHTML',$html_content);
	$response->addScript('setValueIndex('.($i).')');
	return $response;
}


function dsm_delete_param($number,$dis_id){
	global $global;
	shn_session_start();
	//shn_session_unset();
	$response = new xajaxResponse();
	//echo $number."<br/>";
	//var_dump($_SESSION['dsm'][$dis_id]['field_value_texts']);
	if(isset($_SESSION['dsm'][$dis_id])){
		unset($_SESSION['dsm'][$dis_id]['param_key'][$number] );
		unset($_SESSION['dsm'][$dis_id]['param_value'][$number]);
	}

	ob_start();
	// append table and header
	echo '<table><tr><th>'._t("Key").'</th><th>'. _t("Value").'</th></tr>';

	$i = 0;

	// append rows only if no errors in previous submission
	foreach($_SESSION['dsm'][$dis_id]['param_key'] as $i=>$v){
		echo '<tr><td>';
		shn_form_text(_t(""),'dsm_field_param_key_'.$i,'onblur="put_value_in_session(\'param_key\','.$i.',this.value,\''.$dis_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>(isset($_SESSION['dsm'][$dis_id]['param_key'][$i])?$_SESSION['dsm'][$dis_id]['param_key'][$i]:'')));
		echo '</td><td>';
		shn_form_text(_t(""),'dsm_field_param_value_'.$i,'onblur="put_value_in_session(\'param_value\','.$i.',this.value,\''.$dis_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>(isset($_SESSION['dsm'][$dis_id]['param_value'][$i])?$_SESSION['dsm'][$dis_id]['param_value'][$i]:'')));
		echo "</td><td>";
		shn_form_button(_t('Delete'),' onclick="delete_param('.($i).')" ',array('br'=>false));
		echo '</td></tr>';
	}
	// append bottom row and add new button
	echo '<tr><td colspan="3">';
	shn_form_button(_t('Add New Parameter'),' onclick="add_field_param('.($i).')" ');
	echo '</td></tr></table>';
	$html_content = ob_get_clean();

	$response->addAssign('param_div','innerHTML',$html_content);
	$response->addScript('setValueIndex('.($i).')');
	return $response;
}
/**
 * Add New field
 *
 * @param unknown_type $key
 * @param unknown_type $value
 * @param unknown_type $number
 * @param unknown_type $dis_id
 * @return unknown
 */
function dsm_add_field_param($number,$dis_id){
	global $global;
	//shn_session_start();
	$response = new xajaxResponse();
	$key = '';
	$value = '';
	// initialize the session data holders the first time
	if(isset($_SESSION['dsm'])==false){
		$_SESSION['dsm'] = array();
	}
	if(isset($_SESSION['dsm'][$dis_id])==false){
		$_SESSION['dsm'][$dis_id] = array();
		$_SESSION['dsm'][$dis_id]['param_key'] = array();
		$_SESSION['dsm'][$dis_id]['param_value'] = array();
	}else{
		$key = $_SESSION['dsm'][$dis_id]['param_key'];
		$value = $_SESSION['dsm'][$dis_id]['param_value'];
	}

	// do error checking
	$errors = array();
	if(strlen(trim($key))==0){
		$errors[] = _t('Please enter a valid key.');
	}
	if(strlen(trim($value))==0){
		$errors[] = _t('Please enter a valid value');
	}

	ob_start();

	// print any errors
	if(count($errors)>0){
		echo "<div class='error message'>";
		echo "<ul>";
		foreach ($errors as $e){
			echo "<li>".$e."</li>";
		}
		echo "</ul></div>";
	}

	// append table and header
	echo '<table><tr><th>'._t("Key").'</th><th>'. _t("Value").'</th></tr>';

	$param_keys_in_session = $_SESSION['dsm'][$dis_id]['param_key'];
	$param_values_in_session = $_SESSION['dsm'][$dis_id]['param_value'];
	// append rows only if no errrors in previous submission
	foreach($param_keys_in_session as $i=>$v){
		echo '<tr><td>';
		shn_form_text(_t(""),'dsm_field_param_key_'.$i,'onblur="put_value_in_session(\'param_key\','.$i.',this.value,\''.$dis_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>(isset($param_keys_in_session[$i])?$param_keys_in_session[$i]:'')));
		echo '</td><td>';
		shn_form_text(_t(""),'dsm_field_param_value_'.$i,'onblur="put_value_in_session(\'param_value\','.$i.',this.value,\''.$dis_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>(isset($param_values_in_session[$i])?$param_values_in_session[$i]:'')));
		echo "</td><td>";
		shn_form_button(_t('Delete'),' onclick="delete_param('.($i).')" ',array('br'=>false));
		echo '</td></tr>';
	}
	// add a blank field for the next value
	$i++;
	echo '<tr><td>';
	shn_form_text(_t(""),'dsm_field_param_key_'.$i,'onblur="put_value_in_session(\'param_key\','.$i.',this.value,\''.$dis_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>''));
	echo '</td><td>';
	shn_form_text(_t(""),'dsm_field_param_value_'.$i,'onblur="put_value_in_session(\'param_value\','.$i.',this.value,\''.$dis_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>''));
	echo "</td><td>&nbsp;</td></tr>";

	// append bottom row and add new button
	echo '<tr><td colspan="3">';
	shn_form_button(_t('Add New Parameter'),' onclick="add_field_param('.(count($errors)>0?$number:($number+1)).')" ');
	echo '</td></tr></table>';
	$html_content = ob_get_clean();

	$response->addAssign('param_div','innerHTML',$html_content);
	$response->addScript('setParamIndex('.($number+1).')');
	return $response;
}

/*function dsm_show_form($dis_id){

global $global;
shn_session_start();
if(isset($_SESSION['dsm'])==false){
$_SESSION['dsm']=array();
}
if(isset($_SESSION['dsm'][$dis_id])==false){
$_SESSION['dsm'][$dis_id] = array();
}
// set the default feild type
$_SESSION['dsm'][$dis_id]['current_field_type'] = 'text';

$response = new xajaxResponse();
ob_start();
?>
<div id="field_form"><?php
shn_form_fopen("save_definition",'dsm');
shn_form_fsopen(_t("Field Type"));
$extra_opts = array();
?>
<div class="info"><?= _t("These are the basic details of create a custom field.");?></div>
<?php
$extra_opts['req']=true;
$extra_opts['value']='';
//$extra_opts['help']=_t("Give the text for field to dsplay");
echo '<div id="field_text_error" class="hide"></div>';
shn_form_text(_t("Field Text : "),'dsm_field_text','size="40" onblur="autoset_field_name(this.value,\'dsm_field_name\')"',$extra_opts);

shn_form_opt_select("dsm_field_data_type",_('Filed Data Type'));

//$extra_opts['help']=_t("Text Field, Text Area, Option Button, Check Box, Select Single, Select Multiple ");
$options = array('text'=>_t('Text Box'),'textarea'=>_t('Text Area'),'dropdown'=>_t('Dropdown Box'),'radio'=>_t('Radio Button'),'check'=>_t('Check Box'),'date'=>_t('Date Field'),);
shn_form_select($options,_t("Field Type"),'dsm_field_type',' onchange="dsm_set_field_type(this.options[this.selectedIndex].value,\''.$dis_id.'\')"',array('req'=>true,'value'=>'text'));

//$extra_opts['help']=_t("give the unique name");
shn_form_text(_t("Field Name : "),'dsm_field_name','size="20"',$extra_opts);

shn_form_fsclose();

shn_form_fsopen(_t("Values for Field"));
?>
<div class="info"><?= _t("Enter the at least one value for the field.");?></div>

<div id="value_div">
<table>
<tr>
<th><?php echo _t("Text")?></th>
<th><?php echo _t("Value")?></th>
</tr>
<tr>
<td><?php shn_form_text(_t(""),'dsm_field_value_text_1','onblur="put_value_in_session(\'val_text\',this.value,\''.$dis_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>''));?></td>
<td><?php shn_form_text(_t(""),'dsm_field_value_1','size="20" onblur="put_value_in_session(\'val_value\',this.value,\''.$dis_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>''));?></td>
</tr>
<tr>
<td colspan="2"><?php shn_form_button(_t('Add New Value'),' onclick="add_field_value(1)" ');?></td>
</tr>
</table>
</div>
<script type="text/javascript">
field_form = MochiKit.DOM.getElement('field_form');

</script> <?php
shn_form_fsclose();

shn_form_fsopen(_t("Parameter for Field"));
?>
<div id="param_div">
<table>
<tr>
<th><?php echo _t('Key')?></th>
<th><?php echo _t('Value')?></th>
</tr>
<tr>
<td><?php shn_form_text(_t(""),'dsm_field_param_key_1',null,array('br'=>false,'no_label'=>true,'value'=>''));?></td>
<td><?php shn_form_text(_t(""),'dsm_field_param_value_1','size="20"',array('br'=>false,'no_label'=>true,'value'=>'')); ?></td>
</tr>
<tr>
<td colspan="2"><?php shn_form_button(_t('Add New param'),' onclick="add_field_param(1)" ');?></td>
</tr>
</table>
</div>

<?php
shn_form_fsclose();

shn_form_fsopen(_t("Validation for Field"));
?>
<div class="info"><?= _t("Enter the Validation Critearia for the fied.");?></div>

<?php
$extra_opts['req']=false;
//$extra_opts['help']=_t("Enter the Validation Critearia using <, >, ||, &  for the fied");
shn_form_text(_t("Validation Critearia"),'dsm_field_validation','size="50"',$extra_opts);
shn_form_fsclose();

shn_form_submit(_t("Save"),'name="save"');

shn_form_fclose();
//Form close
?></div>
<?php

$content = ob_get_clean();
$response->addAssign('field_list_div','innerHTML',$content); return
$response;
}*/

function dsm_set_field_type($type,$dis_id){
	global $global;
	shn_session_start();
	if(isset($_SESSION['dsm'])==false){
		$_SESSION['dsm']=array();
	}
	if(isset($_SESSION['dsm'][$dis_id])==false){
		$_SESSION['dsm'][$dis_id] = array();
	}
	$_SESSION['dsm'][$dis_id]['current_field_type'] = $type;
	return new xajaxResponse();
}

/*function dsm_set_data_type($data_type,$dis_id){
 global $global;
 shn_session_start();
 if(isset($_SESSION['dsm'])==false){
 $_SESSION['dsm']=array();
 }
 if(isset($_SESSION['dsm'][$dis_id])==false){
 $_SESSION['dsm'][$dis_id] = array();
 }
 $_SESSION['dsm'][$dis_id]['current_data_field_type'] = $data_type;
 return new xajaxResponse();
 }*/

function dsm_put_value_in_session($type,$indx,$value,$dis_id){
	global $global;
	shn_session_start();
	if(isset($_SESSION['dsm'])==false){
		$_SESSION['dsm']=array();
	}
	if(isset($_SESSION['dsm'][$dis_id])==false){
		$_SESSION['dsm'][$dis_id] = array();
	}
	if(isset($_SESSION['dsm'][$dis_id][$type])==false){
		$_SESSION['dsm'][$dis_id][$type] = array();
	}
	$_SESSION['dsm'][$dis_id][$type][$indx] = $value;
	$resp = new xajaxResponse();
	//$resp->addScript('console.debug("'.$indx.'")');
	return $resp;
}

function dsm_add_validation_rule($rule,$rule_text){
	global $global;
	$resp = new xajaxResponse();
	include_once 'lib_dsm_validation.inc';
	shn_session_start();
	if(isset($_SESSION['dsm'])==false){
		$_SESSION['dsm']=array();
	}
	if(isset($_SESSION['dsm'][$dis_id])==false){
		$_SESSION['dsm'][$dis_id] = array();
	}
	if(isset($_SESSION['dsm'][$dis_id]['validation_rules'])==false){
		$_SESSION['dsm'][$dis_id]['validation_rules'] = array();
	}
	$_SESSION['dsm'][$dis_id]['validation_rules'][] = $rule;
	ob_start();
	//var_dump($_SESSION['dsm'][$dis_id]['validation_rules']);
	$hidden = array();
	if(count($_SESSION['dsm'][$dis_id]['validation_rules'])>0){
		echo "<ol>";
		foreach($_SESSION['dsm'][$dis_id]['validation_rules'] as $i=>$r){
			$hidden['dsm_validation_rule_'.$i] = $r;				
			echo "<li>".dsm_validation_get_rule_text($r)."<div class=\"info\">".dsm_validation_get_rule_information($r,$i)."</div></li>";
		}
		echo "</ol>";
		shn_form_hidden($hidden);
	}
	$content = ob_get_clean();
	$resp->addAssign('validation_rule_div','innerHTML',$content);
	return $resp;
}

function dsm_clear_validation_rules(){
	global $global;
	$resp = new xajaxResponse();
	shn_session_start();
	if(isset($_SESSION['dsm'][$dis_id]['validation_rules'])){
		unset($_SESSION['dsm'][$dis_id]['validation_rules']);
	}
	$resp->addAssign('validation_rule_div','innerHTML','&nbsp;');
	return $resp;
}
?>
