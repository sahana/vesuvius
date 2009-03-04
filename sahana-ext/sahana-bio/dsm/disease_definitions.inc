<?php
/**
 * DSM disease_definition.inc
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

include_once ($global['approot']."/inc/lib_form.inc");

function shn_dsm_add_fields($add_field = false,$val_vals=null,$val_texts=null,$param_keys = null, $param_vals=null,$validations=null){

	include_once 'lib_dsm_validation.inc';
	global $global;
	$db = $global['db'];
	// clear session data placeholder on refresh
	if(isset($_SESSION['dsm'])){
		unset($_SESSION['dsm']);
	}

	$disease_query = "SELECT dis_id,dis_name,med_name,serial,description FROM dsm_diseases WHERE dis_id=?";
	$disease_id = (isset($_REQUEST['disease_id'])?$_REQUEST['disease_id']:(-1));

	if($disease_id!=-1){
		$disease_res = $db->Execute($disease_query,array($disease_id));

		include_once $global['approot'].'/inc/lib_xajax.inc';
		shn_xajax_registerFunction('dsm_set_field_type');
		//shn_xajax_registerFunction('dsm_save_definition');
		shn_xajax_registerFunction('dsm_add_field_value');
		shn_xajax_registerFunction('dsm_add_field_param');
		shn_xajax_registerFunction('dsm_show_form');
		shn_xajax_registerFunction('dsm_delete_value');
		shn_xajax_registerFunction('dsm_delete_param');
		shn_xajax_registerFunction('dsm_put_value_in_session');
		shn_xajax_registerFunction('dsm_add_validation_rule');
		shn_xajax_registerFunction('dsm_clear_validation_rules');

		?>

<script type="text/javascript" src="res/js/mochikit/Base.js"> /* include the mochikit Base */ </script>
<script type="text/javascript" src="res/js/mochikit/DOM.js"> /* include the mochikit Dom */ </script>
<script type="text/javascript" src="res/js/mochikit/Iter.js"> /* include the mochikit Iter */ </script>
<script type="text/javascript" src="res/js/mochikit/Style.js"> /* include the mochikit Style */ </script>
<script type="text/javascript" src="res/js/mochikit/Signal.js"> /* include the mochikit Style */ </script>
<script type="text/javascript" src="res/js/mochikit/Color.js"> /* include the mochikit Style */ </script>
<script type="text/javascript" src="res/js/mochikit/Position.js"> /* include the mochikit Style */ </script>
<script type="text/javascript" src="res/js/mochikit/Visual.js"> /* include the mochikit Style */ </script>

<script type="text/javascript">
        var field_form = null;
                
        function add_field(){
                dsm_show_form('<?php echo $disease_id;?>'); 
        }    
        
        function add_validation_rule(){
            var validation = document.getElementById('validation_rules');
            if(validation){
                var rule = validation.options[validation.selectedIndex].value;
                var rule_text = validation.options[validation.selectedIndex].text;
                dsm_add_validation_rule(rule,rule_text);
            }
        }
        
        function autoset_field_name(value,field_id){
            var field = document.getElementById(field_id);
            if(field){
                value = value.toLowerCase();
                value = value.replace(/\s+/,'_');
                field.value = value;
            }
        }       
        
       function autoset_field_type(value,field_id,div_id,value_for_sex){
            var field = document.getElementById(field_id);
   
            if(value=='sex'){
                var indx = 0;
                for(i=0;i<field.options.length;i++){
                    if(field.options[i].value == 'radio'){
                        indx = i;
                        break;
                    }
                }
                field.selectedIndex=indx;
                
                document.getElementById("value_div").style.visibility = "hidden";
                document.getElementById("value_for_sex").innerHTML="<strong>values are automaticaly generate for Sex Data Type</strong>";
           } else{
                indx=0
                //field.options[i].value = 0;   
                field.selectedIndex=indx;
                document.getElementById("value_div").style.visibility = "visible";
                document.getElementById("value_for_sex").innerHTML="";
           }     
        }        
          
    </script>
<h2><?php echo _t("Disease Data Entry Form Definition");?></h2>
<div id="result">
<table>
	<tr>
		<td><?php echo _t("Disease ID")?></td>
		<td><?php echo $disease_res->fields[0]?></td>
	</tr>
	<tr>
		<td><?php echo _t("Disease Name")?></td>
		<td><?php echo $disease_res->fields[1]?></td>
	</tr>
	<tr>
		<td><?php echo _t("Medical Name")?></td>
		<td><?php echo $disease_res->fields[2]?></td>
	</tr>
	<tr>
		<td><?php echo _t("Serial")?></td>
		<td><?php echo $disease_res->fields[3]?></td>
	</tr>
	<tr>
		<td><?php echo _t("Description")?></td>
		<td><?php echo $disease_res->fields[4]?></td>
	</tr>
</table>
</div>

<div id="field_list_div"
	style="padding: 2px; width: 100%; height: auto;"><?php

	$field_query = $db->Prepare("SELECT df.* FROM dsm_definitions dd JOIN dsm_fields df ON dd.field_id=df.field_id WHERE dd.dis_id=? ORDER BY df.field_id");
	$res5 = $db->Execute($field_query,array($disease_id));

	if($res5 && $res5->RecordCount()>0 && isset($_REQUEST['add_field'])==false && $add_field==false){
		shn_form_fopen('add_fields','dsm');
		shn_form_hidden(array('disease_id'=>$disease_id,'add_field'=>true));
		shn_form_submit(_t("Create Field"));
		shn_form_fclose();
		?>
<hr />
		<?php
	}

	if($res5 && $res5->RecordCount()>0  && isset($_REQUEST['add_field'])==false && $add_field==false){

		echo "<table width='100%'><tr>";
		echo "<th>"._t('Field Name').'</th>';
		echo "<th>"._t('Field Type').'</th>';

		echo "<th>"._t('Action').'</th>';

		echo "<th>&nbsp;</th></tr>";

		//create edit and delete field--------------------------------------------------------------

		while($row=$res5->FetchRow()){
			echo "<tr>";
			echo "<td >".$row['text']."</td>";
			echo "<td >".$row['type']."</td>";
			echo "<td >";
			shn_acl_secure_hyperlink('dsm','edit_definition','Edit',$stream=null,$params=array('disease_id'=>$disease_id,'field_id'=>$row['field_id']),$text_opts='');
			echo  "&nbsp &nbsp";
			shn_acl_secure_hyperlink('dsm','delete_fields_confirm','Delete',$stream=null,$params=array('disease_id'=>$disease_id,'field_id'=>$row['field_id']),$text_opts='');
			
			echo "</td</tr>";
		}
		echo "</table></div>";

	}
	?>

<div id="field_form"><?php

if(($res5 && ($res5->RecordCount()==0)) || isset($_REQUEST['add_field']) || $add_field==true) {
	global $global;
	$db = $global['db'];

	shn_form_fopen('save_definition','dsm');
	shn_form_hidden(array('field_id'=>$field_id,'disease_id'=>$disease_id));

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

	shn_form_opt_select("dsm_field_data_type",_('Filed Data Type'),' onchange="autoset_field_type(options[selectedIndex].value,\'dsm_field_type\',\'value_div\',\'value_for_sex\')"');

	//$extra_opts['help']=_t("Text Field, Text Area, Option Button, Check Box, Select Single, Select Multiple ");
	$options = array('text'=>_t('Text Box'),'textarea'=>_t('Text Area'),'dropdown'=>_t('Dropdown Box'),'radio'=>_t('Radio Button'),'check'=>_t('Check Box'),'date'=>_t('Date Field'),);
	shn_form_select($options,_t("Field Type"),'dsm_field_type',array('req'=>true,'value'=>'text'));

	//$extra_opts['help']=_t("give the unique name");
	shn_form_text(_t("Field Name : "),'dsm_field_name','size="20"',$extra_opts);

	shn_form_fsclose();

	shn_form_fsopen(_t("Values for Field"));
	?>
<div id="value_for_sex"><?= _t("");?></div>
<div id="value_div">
<div class="info"><?= _t("Enter the at least one value for the field.");?></div>

<table>
	<tr>
		<th><?php echo _t("Text")?></th>
		<th><?php echo _t("Value")?></th>
	</tr>
	<?php
	if(isset($val_vals) && isset($val_texts)){
		if(count($val_texts)==0){
    ?>
    <tr>
        <td><?php shn_form_text(_t(""),'dsm_field_value_text_1','onblur="put_value_in_session(\'val_text\',1,this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>''));?></td>
        <td><?php shn_form_text(_t(""),'dsm_field_value_1','size="20" onblur="put_value_in_session(\'val_value\',1,this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>''));?></td>
    </tr>
    <?php
		}else{
			foreach ($val_texts as $i=>$v){
	?>
	<tr>
		<td><?php shn_form_text(_t(""),'dsm_field_value_text_'.$i,'onblur="put_value_in_session(\'val_text\','.$i.',this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>$v));?></td>
		<td><?php shn_form_text(_t(""),'dsm_field_value_'.$i,'size="20" onblur="put_value_in_session(\'val_value\','.$i.',this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>$v));?></td>
	</tr>
	<?php
			}
		}
	}else{
		?>
	<tr>
		<td><?php shn_form_text(_t(""),'dsm_field_value_text_1','onblur="put_value_in_session(\'val_text\',1,this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>''));?></td>
		<td><?php shn_form_text(_t(""),'dsm_field_value_1','size="20" onblur="put_value_in_session(\'val_value\',1,this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>''));?></td>
	</tr>
	<?php
	}
	?>
	<tr>
		<td colspan="2"><?php shn_form_button(_t('Add New Value'),' onclick="add_field_value(1)" ');?></td>
	</tr>
</table>
</div>
<script type="text/javascript">
    field_form = MochiKit.DOM.getElement('field_form');
    
</script> <?php
shn_form_fsclose();

shn_form_fsopen(_t("Validation for Field"));

$extra_opts['req']=false;
//$extra_opts['help']=_t("Enter the Validation Critearia using <, >, ||, &  for the fied");
$opts = dsm_validation_get_rules();
shn_form_select($opts,_t('Validation Rule'),'validation_rules','',array('br'=>false,'value'=>'not_empty'));
shn_form_button(_t('Add Rule'),' onclick="add_validation_rule()"');
echo "<h4>"._t("Current Ruleset")."</h4>";
echo "<div id='validation_rule_div'>";

// show previously entered validations
if(isset($validations) && count($validations)>0){
	$hidden = array();
	echo "<ul>";
	foreach($validations as $i=>$r){
		$hidden['dsm_validation_rule_'.$i] = $r;
		echo "<li>".dsm_validation_get_rule_text($r)."<div class=\"info\">".dsm_validation_get_rule_information($r,$i)."</div></li>";
	}
	echo "</ul>";
	shn_form_hidden($hidden);
}

echo "</div>";
shn_form_button(_t('Clear All'),'onclick="dsm_clear_validation_rules()"');
shn_form_fsclose();

shn_form_fsopen(_t("Parameters"));
?>
<div id="param_div">
<table>
	<tr>
		<th><?php echo _t('Key')?></th>
		<th><?php echo _t('Value')?></th>
	</tr>
	<?php
	if(isset($param_keys) && isset($param_vals)){
		if(count($param_keys)==0){
    ?>
    <tr>
        <td><?php shn_form_text(_t(""),'dsm_field_param_key_1','onblur="put_value_in_session(\'param_key\',1,this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>''));?></td>
        <td><?php shn_form_text(_t(""),'dsm_field_param_value_1','onblur="put_value_in_session(\'param_value\',1,this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>'')); ?></td>
    </tr>
    <?php
        }else{
		  foreach ($param_keys as $i=>$v){
			?>
	<tr>
		<td><?php shn_form_text(_t(""),'dsm_field_param_key_'.$i,'onblur="put_value_in_session(\'param_key\','.$i.',this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>$v));?></td>
		<td><?php shn_form_text(_t(""),'dsm_field_param_value_'.$i,'onblur="put_value_in_session(\'param_value\','.$i.',this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>$v)); ?></td>
	</tr>
	<?php
		  }
        }
	}else{
		?>
	<tr>
		<td><?php shn_form_text(_t(""),'dsm_field_param_key_1','onblur="put_value_in_session(\'param_key\',1,this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>''));?></td>
		<td><?php shn_form_text(_t(""),'dsm_field_param_value_1','onblur="put_value_in_session(\'param_value\',1,this.value,\''.$disease_id.'\')"',array('br'=>false,'no_label'=>true,'value'=>'')); ?></td>
	</tr>
	<?php
	}
	?>
	<tr>
		<td colspan="2"><?php shn_form_button(_t('Add New param'),' onclick="add_field_param(1)" ');?></td>
	</tr>
</table>
</div>

	<?php
	shn_form_fsclose();

	shn_form_submit(_t("Save"),'name="save"');

	shn_form_fclose();
	//Form close
	?></div>


<script type="text/javascript">

<!--
    // caller function for the xajax function   
    function add_field_value(number){
        //var text = document.getElementById('dsm_field_value_text_'+number);
        //var val = document.getElementById('dsm_field_value_'+number);
        dsm_add_field_value(number,'<?php echo $disease_id;?>');
    }
    
    //delet value
    function delete_value(number) {
        dsm_delete_value(number,'<?php echo $disease_id;?>');          

    }
    //delete parameter
    function delete_param(number) {
        dsm_delete_param(number,'<?php echo $disease_id;?>');          

    }
    
    // caller function for the xajax function
    function add_field_param(number){
        //var key = document.getElementById('dsm_field_param_key_'+number);
        //var val = document.getElementById('dsm_field_param_value_'+number);
        dsm_add_field_param(number,'<?php echo $disease_id;?>');
    }
    
    // variable indexes for values and parameters
    var value_index=1;
    var param_index=1;
 
    // setter method for value index
    // called by xajax
    function setValueIndex(v){
        //alert(v);
        value_index = v;
    }
    
    // setter method for param index
    // called by xajax
    function setParamIndex(p){
        //alert(p);
        param_index = p;
    }
    
    function put_value_in_session(type,indx,value,dis_id){
        dsm_put_value_in_session(type,indx,value,dis_id);
    }
//-->

</script> <?php
}
	}else{
		add_error(_t("Disease Not Found !"));
	}
}

function shn_dsm_view_disease_definition($disease_id = null){
	global $global;
	?>
<h2><?php echo _t("View Created Fields");?></h2>
	<?php

	$db = $global['db'];
	$module = $global['module'];
	if($disease_id==null){
		$disease_id = $_REQUEST['disease_id'];
	}

	$field_query = $db->Prepare("SELECT df.* FROM dsm_definitions dd JOIN dsm_fields df ON dd.field_id=df.field_id WHERE dd.dis_id=? ORDER BY df.indx");
	$res5 = $db->Execute($field_query,array($disease_id));

	if($res5){
		if($res5->RecordCount()>0){

			echo "<table width='100%'><tr>";
			//echo "<th>"._t('Field ID').'</th>';
			echo "<th>"._t('Field Information').'</th>';
			echo "<th>"._t('Field  Display Order').'</th>';
			echo "<th>&nbsp;</th>";
			echo "</tr>";

			//create edit and delete field
			while($row=$res5->FetchRow()){

				$field_id = $row['field_id'];
				$text = $row['text'];
				$type = $row['type'];
				$name = $row['name'];
				$data_type=$row['data_type'];
				echo "<tr>";
				//echo "<td >".$row['field_id']."</td>";
				echo "<td >";

				$query1 = "SELECT vals_text,value FROM dsm_field_values WHERE field_id=?";
				$res1 = $db->Execute($query1,array($field_id));
				//display field type
				if ($type=="text"){
					$vals_text= $res1->fields["vals_text"];
					$vals= $res1->fields["value"];

					echo _t("Field text").":".$text."<br>";
					echo _t("Field Data Type").":".$data_type."<br>";
					echo _t("Field Type").":".$type."<br>";
					echo _t("Field Name").":".$name. "<br><br>";
					echo _t("Values")." :".$vals."</br>";
				}

				//text aria
				else if ($type=="textarea"){
					$vals_text= $res1->fields["vals_text"];
					$vals= $res1->fields["value"];

					echo _t("Field text").":".$text."<br>";
					echo _t("Field Data Type").":".$data_type."<br>";
					echo _t("Field Type").":".$type."<br>";
					echo _t("Field Name").":".$name. "<br><br>";
					echo _t("Values")." :".$vals."</br>";
				}

				//drop down
				else if($type=="dropdown"){

					echo _t("Field text").":".$text."<br>";
					echo _t("Field Data Type").":".$data_type."<br>";
					echo _t("Field Type").":".$type."<br>";
					echo _t("Field Name").":".$name. "<br><br>";
					echo _t("Values")." :";

					$vals_array = array();
					foreach($res1 as $row){
						$vals_textb=$row["vals_text"];
						$vals=$row["value"];
						$vals_array[$vals]=$vals;

						echo $vals."<br>";
					}
				}

				//radio
				else if($type=="radio"){

					echo _t("Field text").":".$text."<br>";
					echo _t("Field Data Type").":".$data_type."<br>";
					echo _t("Field Type").":".$type."<br>";
					echo _t("Field Name").":".$name. "<br><br>";
					echo _t("Values")." :";

					while($row=$res1->FetchRow()){
						$vals_textb=$row["vals_text"];
						$vals=$row["value"];

						echo $vals."<br>";
					}
				}

				//check
				else if($type=="check"){

					echo _t("Field text").":".$text."<br>";
					echo _t("Field Data Type").":".$data_type."<br>";
					echo _t("Field Type").":".$type."<br>";
					echo _t("Field Name").":".$name. "<br><br>";
					echo _t("Values")." :";

					while($row=$res1->FetchRow()){
						$vals_text=$row["vals_text"];
						$vals=$row["value"];

						echo $vals."<br>";
					}
				}

				//date
				else if ($type=="date"){

					$vals_text= $res1->fields["vals_text"];
					$vals= $res1->fields["value"];

					echo _t("Field text").":".$text."<br>";
					echo _t("Field Data Type").":".$data_type."<br>";
					echo _t("Field Type").":".$type."<br>";
					echo _t("Field Name").":".$name. "<br><br>";
					echo _t("Values")." :".$vals."</br>";
				}

				echo "<td align='center' valign='middle'>";
				shn_form_fopen('move_field','dsm',array('req_message'=>false,'class'=>''));
				shn_form_hidden(array('field_id'=>$field_id,'disease_id'=>$disease_id));
				shn_form_imagebutton('up','theme/default/img/up.png');
				echo "&nbsp;&nbsp;";
				shn_form_imagebutton('down','theme/default/img/down.png');
				shn_form_fclose();
				echo "</td>";
				echo "</td>";
				echo "<td >";
				shn_acl_secure_hyperlink('dsm','edit_definition','Edit',$stream=null,array('field_id'=>$field_id,'disease_id'=>$disease_id),$text_opts='');
				echo "&nbsp &nbsp";
				shn_acl_secure_hyperlink('dsm','delete_fields_confirm','Delete',$stream=null,array('field_id'=>$field_id,'disease_id'=>$disease_id),$text_opts='');
				echo "</td>";
				echo "</tr>";
			}
			echo "</table>";

		}
	}
	shn_acl_secure_hyperlink('dsm','add_fields','Add Field',$stream=null,array('disease_id'=>$disease_id,'add_field'=>'true'),$text_opts='');
	
}

//view field befor delete
function shn_dsm_delete_fields_confirm(){

	echo "<h2>". _t("Confirm to Delete This Field")."</h2>";
	echo "<p>"._t("Are you sure you need to delete the following field?. <br/> <br/><em>Note that all values and parameter of field will be deleted!</em>")."</p><br/>";

	global $global;
	$db = $global['db'];
	$module = $global['module'];
	$field_id = $_REQUEST['field_id'];
	$disease_id = $_REQUEST['disease_id'];

	shn_form_fopen('delete_fields','dsm',$form_opts = array('req_message'=>false));
	shn_form_hidden(array('field_id'=>$field_id,'disease_id'=>$disease_id));

	$field_info_query = "SELECT text,type,name,data_type FROM dsm_fields WHERE field_id=$field_id";
	$res1 = $db->Execute($field_info_query);
	$text=$res1->fields["text"];
	$type=$res1->fields["type"];
	$name=$res1->fields["name"];
	$data_type=$res1->fields["data_type"];

	echo "<table>";
	echo "<tr>";
	//echo "<td>". _t("Field ID").":".$field_id."</td>";
	echo "<td>"._("Field Text").":".$text."</td>";
	echo "<td>"._("Field Type").":".$type."</td>";
	echo "<td>"._("Field Name").":".$name."</td>";
	echo "<td>"._("Field Data Type").":".$data_type."</td>";
	//echo "<td ><a href=index.php?mod=dsm&act=delete_fields&field_id=".$row['field_id'].">"._t("Delete")."</a></td>";
	//echo "<td><a href=\"index.php?mod=dsm&act=view_disease_definition&disease_id=".$disease_id."\">"._t("Cancel")."</a> </td>";
	echo "<td>";
	shn_form_submit(_t("Delete"),'name="delete"');
	echo "</td>";
	echo "<td>";
	shn_form_submit(_t("Cancel"),'name="cancel"');
	echo "</td>";
	echo "</tr>";
	echo "</table>";
	shn_form_fclose();
}

//function for move field
function shn_dsm_move_field(){
	global $global;
	$db = $global['db'];

	$field_id = $_REQUEST['field_id'];
	$disease_id = $_REQUEST['disease_id'];
	$direction = (isset($_REQUEST['up']) || isset($_REQUEST['up_x']))?'UP':'DOWN';

	if($direction=='UP'){
		$query1 = "SELECT indx FROM dsm_fields WHERE field_id=?";
		$res1 = $db->Execute($query1,array($field_id));
		$indx1 = $res1->fields[0];
		$query2 = "SELECT field_id,indx FROM dsm_fields WHERE indx=(SELECT MAX(indx) FROM dsm_fields WHERE indx<?)";
		$res2 = $db->Execute($query2,array($indx1));
		if($res2->RecordCount()>0){
			$field_id2 = $res2->fields[0];
			$indx2 = $res2->fields[1];
			$query3 = $db->Prepare("UPDATE dsm_fields SET indx=? WHERE field_id=?");
			// interchange indexes
			$db->Execute($query3,array($indx2,$field_id));
			$db->Execute($query3,array($indx1,$field_id2));
		}
	}else{
		$query1 = "SELECT indx FROM dsm_fields WHERE field_id=?";
		$res1 = $db->Execute($query1,array($field_id));
		$indx1 = $res1->fields[0];
		$query2 = "SELECT field_id,indx FROM dsm_fields WHERE indx=(SELECT MIN(indx) FROM dsm_fields WHERE indx>?)";
		$res2 = $db->Execute($query2,array($indx1));
		if($res2->RecordCount()>0){
			$field_id2 = $res2->fields[0];
			$indx2 = $res2->fields[1];
			$query3 = $db->Prepare("UPDATE dsm_fields SET indx=? WHERE field_id=?");
			// interchange indexes
			$db->Execute($query3,array($indx2,$field_id));
			$db->Execute($query3,array($indx1,$field_id2));
		}
	}
	shn_dsm_view_disease_definition($disease_id);
}

//diseas data entry form
function shn_dsm_disease_form(){
	include_once('lib_dsm_validation.inc');
	global $global;
	$db = $global['db'];
	$dis_id = $_REQUEST['dis_id'];
	echo "<h2>"._t("Data Entry Form")."</h2>";
	//$db->debug = true;
	$module = $global['module'];
	if(isset($_REQUEST['dis_id'])){
		if(isset($_REQUEST['seq'])==false || $_REQUEST['seq']=='show_form'){
			_show_data_entry_form();
		}else if($_REQUEST['seq']=='confirm_details'){
			// do validation.
			$errors = dsm_validation_check_validity($_REQUEST['dis_id']);
			if($errors!=false){
				_show_data_entry_form();
				return;
			}


			if(isset($_POST['back'])){
				_show_data_entry_form();
			}else if(isset($_POST['save'])){
				_save_form_data();
			}else{
				_show_confirm_data_form();
			}
		}
	}else{
		echo "<h2>"._t("New Case")."</h2>";
		echo "<p>"._t("Please select a disesase from the list below to create a new case.")."</p>";

		shn_form_fopen('disease_form','dsm',$form_opts = array('req_message'=>false));
		shn_form_fsopen(_t('Select Disease'));

		$query = "SELECT * FROM dsm_diseases ORDER BY dis_name";
		$res = $db->Execute($query);
		$opts = array();
		if($res){
			while($row=$res->FetchRow()){
				$opts[$row['dis_id']] = $row['dis_name'].((strlen(trim($row['med_name']))>0)?"  ( ".$row['med_name']." )":"");
			}
		}
		shn_form_select($opts,_t("Disease"),'dis_id','',array("req"=>true));
		shn_form_submit(_t("Next>>"));
		shn_form_fsclose();
		shn_form_fclose();
	}
}

function _show_data_entry_form(){
	global $global;
	$db=$global['db'];
	$dis_id = $_REQUEST['dis_id'];
	$form_query = 'SELECT df.* FROM dsm_fields df JOIN dsm_definitions dd ON dd.field_id=df.field_id AND dd.dis_id=? ORDER BY indx';
	$res = $db->GetAll($form_query,array($dis_id));

	shn_form_fopen('disease_form','dsm',$form_opts);
	shn_form_hidden(array('dis_id'=>$dis_id,'seq'=>'confirm_details'));
	shn_form_fsopen();
	shn_form_text(_t('Patient Identification Code'),'patient_identifier',null,array('req'=>false));

	echo "<table align=\"top\">";
	foreach ( $res as $row){
		echo "<tr>";

		$field_id = $row['field_id'];
		$text = $row['text'];
		$type = $row['type'];
		$name = $row['name'];

		$query1 = "SELECT vals_text,value FROM dsm_field_values WHERE field_id=?";
		$res1 = $db->Execute($query1,array($field_id));

		//text box
		if ($type=="text"){

			$vals_text= $res1->fields["vals_text"];
			$vals= $res1->fields["value"];

			shn_form_text(_t($text),$name);
		}

		//text aria
		else if ($type=="textarea"){

			$vals_text= $res1->fields["vals_text"];
			$vals= $res1->fields["value"];

			shn_form_textarea(_t($text),$name);
		}

		//drop down
		else if($type=="dropdown"){

			$vals_array = array();
			foreach($res1 as $row){
				$vals=$row["value"];
				$vals_array[$vals]=$vals;
			}
			//shn_form_select($vals_array,$text, $name,'');
			shn_form_select($vals_array,_t($text),$name,'',array('value'=>$value_new));
		}

		//radio
		else if($type=="radio"){
			echo"<table><tr>";
			echo "<td>".$text."</td>";

			while($row=$res1->FetchRow()){
				$vals_text=$row["vals_text"];
				$vals=$row["value"];
				echo "<tr><td>";
				shn_form_radio(array($vals=>$vals_text),'',$name);
				echo "</td></tr>";
			}
			echo"</table><br>";
		}

		//check
		else if($type=="check"){

			echo"<table><tr>";
			echo "<td>".$text."</td>";

			$query1 = $db->Prepare('SELECT vals_text,value FROM dsm_field_values WHERE field_id=?');
			$res1=$db->Execute($query1,array($field_id));
			if($res1->RecordCount()>1){
				while($row=$res1->FetchRow()){
					$val_text=$row["vals_text"];
					$val=$row["value"];
					echo "<tr><td>";
					shn_form_checkbox($val_text, $name.'[]',null,array('value'=>$val));
					echo "</td></tr>";
				}
			}else{
				$val_text=$row["vals_text"];
				$val=$row["value"];
				echo "<tr><td>";
				shn_form_checkbox($val_text, $name,null,array('value'=>$val));
				echo "</td></tr>";
			}
			echo"</tr></table><br>";
		}

		//date
		else if ($type=="date"){
			//$vals= $res1->fields["value"];
			shn_form_date($text,$name,$extra_opts ='');
		}
		echo "</tr>";
	}
	echo "</table>";

	shn_form_fsclose();

	shn_form_submit(_t("Cancel"),'name="cancel"');
	shn_form_reset(_t("Reset"));
	shn_form_submit(_t("Save"),'name="confirm"');

	shn_form_fclose();echo "</div>";
}

function _show_confirm_data_form(){
	global $global;
	$dis_id = $_REQUEST['dis_id'];
	$db=$global['db'];
	shn_form_fopen('disease_form','dsm',array('req_message'=>false));
	shn_form_hidden(array('seq'=>'confirm_details'));

	$form_query = 'SELECT df.* FROM dsm_fields df JOIN dsm_definitions dd ON dd.field_id=df.field_id AND dd.dis_id=? ORDER BY indx';
	$res = $db->GetAll($form_query,array($dis_id));
	echo "<div class='warning message'>"._t("Are you sure you need to save the follwing details?")."<br/><br><em>"._t("Please note that these details cannot be changed once saved.")."</em></div>";
	shn_form_fsopen(_t('Confirm Details'));
	echo "<table valign=\"top\">";
	echo "<tr><td>"._t("Patient Identification Code")."</td><td>".$_POST['patient_identifier']."</td></tr>";

	foreach ( $res as $row){
		echo "<tr><td>";

		$field_id = $row['field_id'];
		$type = $row['type'];
		$text = $row['text'];
		$name = $row['name'];

		$query1 = "SELECT vals_text,value FROM dsm_field_values WHERE field_id=?";
		$res1 = $db->Execute($query1,array($field_id));

		//text box
		if ($type=="text" || $type=="textarea" || $type=="date" || $type=='radio'){

			$vals_text= $res1->fields["vals_text"];
			$val= $res1->fields["value"];

			echo $text."</td><td>".$_POST[$name]."</td>";
		}
		//drop down
		else if($type=="dropdown" || $type=="check"){

			$vals_text= $res1->fields["vals_text"];
			echo $text."</td><td><ul>";

			foreach($_POST[$name] as $val){
				echo "<li>";
				echo $val;
				echo "</li>";
			}
			echo "</ul></td>";
		}
		echo "</tr>";
	}
	echo "</table>";
	// send all current post values to the next sequence in hidden fields.
	$post_params = array();
	foreach($_POST as $k=>$v){

		if($k!='seq'){
			if(is_array($v)){
				// multiple valueed params.
				$post_params[$k] = array();
				foreach($v as $val){
					$post_params[$k][] = $val;
				}
			}else{
				$post_params[$k] = $v;
			}
		}
	}
	shn_form_hidden($post_params);
	shn_form_fsclose();
	shn_form_submit(_t('<< Back'),' name="back"');
	shn_form_submit(_t("Save"),'name="save"');
	shn_form_fclose();
}

function _save_form_data(){
	global $global;
	$db = $global['db'];
	$dis_id = $_POST['dis_id'];
	//$db->debug=true;
	$form_query = 'SELECT df.* FROM dsm_fields df JOIN dsm_definitions dd ON dd.field_id=df.field_id AND dd.dis_id=? ORDER BY indx';
	$res = $db->GetAll($form_query,array($dis_id));

	if(isset($_POST['save'])){
		// get the next case id
		$date=date("Y-m-d");
		$query = "SELECT MAX(case_id) AS c FROM dsm_case_data";
		$res = $db->Execute($query);
		$case_id = 1;
		if($res && $res->RecordCount()>0){
			$case_id = ($res->fields['c']+1);
		}
		// get the next submit id
		$query = "SELECT MAX(submission_id) AS s FROM dsm_case_data";
		$res = $db->Execute($query);
		$submission_id = 1;
		if($res && $res->RecordCount()>0){
			$submission_id = ($res->fields['s']+1);
		}

		$query ='SELECT df.name AS name,df.field_id AS field_id FROM dsm_fields df JOIN dsm_definitions dd ON dd.field_id=df.field_id AND dd.dis_id=? ORDER BY indx';
		$res = $db->Execute($query,array($dis_id));

		if($res){
			$db->StartTrans();
			$query = $db->Prepare("INSERT INTO dsm_case_data (case_id,field_id,dis_id,data_id,submission_id,patient_identifier,date,value) VALUES (?,?,?,?,?,?,?,?)");
			while($row=$res->FetchRow()){
				// get each value in $_POST.
				$value = $_POST[$row['name']];
				$patient_identifier = $_POST['patient_identifier'];
				//var_dump($_POST);
				//$db->debug =true;

				/**
				 * Save values to database.
				 */
				if(is_array($value)){
					// has multiple values.
					$data_id = 1;
					foreach($value as $v){
						$db->Execute($query,array($case_id,$row['field_id'],$dis_id,$data_id,$submission_id,$patient_identifier,$date,$v));
						$data_id++;
					}
				}else{
					// only single value for field
					$db->Execute($query,array($case_id,$row['field_id'],$dis_id,1,$submission_id,$patient_identifier,$date,$value));
				}
			}
			//save data to dsm_case_count table
			$query_case_count = "INSERT INTO dsm_case_count(case_id,dis_id,date) VALUES('$case_id','$dis_id','$date')";
			$res1 = $db->Execute($query_case_count);

			$failed = $db->HasFailedTrans();
			$db->CompleteTrans();
			if($failed){
				// Transaction failed.
				add_error(_t("An unknown error occured while saving this form."));
				_show_data_entry_form();
			}else{
				add_confirmation(_t("Form data was saved successfully."));
				_show_saved_data($dis_id,$case_id);
			}
		}
	}
}

function _show_saved_data($dis_id,$case_id){
	global $global;
	$db=$global['db'];

	echo "<h3>"._t("Saved Details")."</h3>";
	$form_query = 'SELECT cd.*,df.text,df.type,df.name,dfv.vals_text FROM dsm_case_data cd JOIN dsm_fields df ON df.field_id = cd.field_id LEFT OUTER JOIN dsm_field_values dfv ON dfv.field_id=cd.field_id AND dfv.value=cd.value WHERE cd.dis_id = ? AND cd.case_id = ? ORDER BY df.indx,cd.field_id,cd.data_id';
	$res = $db->Execute($form_query,array($dis_id,$case_id));

	echo "<table valign=\"top\">";
	echo "<tr><td>"._t("Patient Identification Code")."</td><td>".$res->fields['patient_identifier']."</td></tr>";
	$_tdata_id = 0;
	$vals = array();
	while($row=$res->FetchRow()){
		$name = $row['name'];
		$type = $row['type'];
		$text = $row['text'];
		$value = $row['value'];
		$vals_text = $row['vals_text'];
		if(isset($vals[$name])==false){
			$vals[$name] = array();
			$vals[$name]['text'] = $text;
			$vals[$name]['type'] = $type;
			$vals[$name]['value'] = array($value);
			$vals[$name]['vals_text'] = array($vals_text);
		}else{
			$vals[$name]['value'][] = $value;
			$vals[$name]['vals_text'][] = $vals_text;
		}
	}

	foreach($vals as $n=>$v){
		$type = $vals[$n]['type'];
		$text = $vals[$n]['text'];
		$value = $vals[$n]['value'];
		$val_text = $vals[$n]['vals_text'];

		if ($type=="text" || $type=="textarea" || $type=="date" || $type=='radio'){
			echo "<tr><td>".$text."</td><td>".$value[0]."</td></tr>";
		}
		//drop down
		else if($type=="dropdown" || $type=="check"){
			//echo "$data_id - $_tdata_id<br/>";
			echo "<tr><td>".$text."</td><td><ul>";
			foreach($vals[$name]['vals_text'] as $value){
				echo "<li>".$value."</li>";
			}

			//close the previous
			echo "</ul></td></tr>";

		}
	}

	echo "</table>";
}

//save definition
function shn_dsm_save_definition(){
	global $global;
	include_once 'lib_dsm_validation.inc';
	$db = $global['db'];
	//$db->debug=true;

	$module = $global['module'];
	$disease_id=$_REQUEST['disease_id'];
	//var_dump($_REQUEST);

	$text=$_POST['dsm_field_text'];
	$type=$_POST['dsm_field_type'];
	$name=$_POST['dsm_field_name'];
	$data_type=$_POST['dsm_field_data_type'];

	$field_value_texts=array();
	$field_values=array();
	$field_param_keys=array();
	$field_param_values=array();
	$field_validations = array();

	//explode value and param
	foreach($_POST as $k=>$v){
		$i = 0;
		if(preg_match('/dsm_field_value_text_\d+/',$k)!=0){
			$i = explode('dsm_field_value_text_',$k);
			$i = $i[1];
			if(strlen(trim($v))>0){
				$field_value_texts[$i] = $v;
			}

		}else if(preg_match('/dsm_field_value_\d+/',$k)!=0){
			$i = explode('dsm_field_value_',$k);
			$i = $i[1];
			if(strlen(trim($v))>0){
				$field_values[$i] = $v;
			}

		}else if(preg_match('/dsm_field_param_key_\d+/',$k)!=0){
			$i = explode('dsm_field_param_key_',$k);
			$i = $i[1];
			if(strlen(trim($v))>0){
				$field_param_keys[$i] = $v;
			}

		}else if(preg_match('/dsm_field_param_value_\d+/',$k)!=0){
			$i = explode('dsm_field_param_value_',$k);
			$i = $i[1];
			if(strlen(trim($v))>0){
				$field_param_values[$i] = $v;
			}
		}else if(preg_match('/dsm_validation_rule_\d+/',$k)!=0){
			$i = explode('dsm_validation_rule_',$k);
			$i = $i[1];
			$field_validations[$i] = $v;
		}
	}

	//var_dump($field_param_keys);
	//var_dump($field_param_values);
	$errors = false;
	if($text==null || strlen(trim($text))==0){
		add_error(_t("Please fill the Field Text"));
		$errors = true;
	}

	if($name==null || strlen(trim($name))==0){
		add_error(_t("Please fill the Field Name"));
		$errors = true;
	}

	if($type==null || strlen(trim($type))==0){
		add_error(_t("Please fill the Field Type"));
		$errors = true;
	}

	if($data_type==null || strlen(trim($data_type))==0){
		add_error(_t("Please fill the Field Data Type"));
		$errors = true;
	}

	if($type=='dropdown' && (count($field_values)<1)){
		add_error(_t('Dropdown field requires at least one value.'));
		$errors = true;
	}
	if($type=='check' && (count($field_values)<1)){
		add_error(_t('Check Box field requires at least one value.'));
		$errors = true;
	}
	if($data_type!=="sex" && $type=='radio' && (count($field_values)<1)){
		add_error(_t('Radio Button field requires at least one value.'));
		$errors = true;
	}
	if($data_type=="sex" && $type=='radio' && (count($field_values)>2)){
		add_error(_t('Radio Button field requires at least one value.'));
		$errors = true;
	}
	if($type=='text' && (count($field_values)>1)){
		add_error(_t('Text Box field can not add more than one value.'));
		$errors = true;
	}
	if($type=='textarea' && (count($field_values)>1)){
		add_error(_t('Text Area field can not add more than one value.'));
		$errors = true;
	}
	if($type=='date' && (count($field_values)>1)){
		add_error(_t('Date Field field can not add more than one value.'));
		$errors = true;
	}

	if(count($field_validations)>0){
		$status = true;
		$param_array = array();
		foreach($field_param_keys as $k=>$v){
			$param_array[$v] = $field_param_values[$k];
		}
		foreach($field_validations as $i=>$r){
			$status &= dsm_validation_check_params($r,$i,$param_array);
		}

		$errors = !$status;
	}

	if($errors == true){
		shn_dsm_add_fields(true,$field_values,$field_value_texts,$field_param_keys,$field_param_values,$field_validations);
	}else{
		$db->StartTrans();
		//$db->debug = true; //debug code
		//if field_data_type==sex
		if($_POST['dsm_field_data_type']=="sex"){
			$query1 = "INSERT INTO dsm_fields(text,type,name,data_type) VALUES(?,?,?,?)";
			$res1 = $db->Execute($query1,array($text,'radio',$name,$data_type));
		}else{
			$query1 = "INSERT INTO dsm_fields(text,type,name,data_type) VALUES(?,?,?,?)";
			$res1 = $db->Execute($query1,array($text,$type,$name,$data_type));
		}

		$field_id_query = "SELECT MAX(field_id) as next_fid FROM dsm_fields";
		$res2 = $db->Execute($field_id_query);
		$field_id = $res2->fields[0];

		// set the fieldid as the index too
		$query1 = "UPDATE dsm_fields SET indx=? WHERE field_id=?";
		$db->Execute($query1,array($field_id,$field_id));

		if($_POST['dsm_field_data_type']=="sex"){

			//save field values
			$query_sex ="INSERT INTO dsm_field_values(vals_text,value,field_id,indx) VALUES ('Male','male','$field_id','1'),('Female','female','$field_id','2')";
			$res_sex = $db->Execute($query_sex);

		}
		//outher field_data_type
		else{

			//save field values
			$query2 = $db->Prepare('INSERT INTO dsm_field_values(vals_text,value,field_id,indx) VALUES (?,?,?,?)');

			$array_keys = array_keys($field_value_texts);
			foreach ($array_keys as $k){
				$db->Execute($query2,array($field_value_texts[$k],$field_values[$k],$field_id,$k));
			}

		}

		//save field param
		$query3 = $db->Prepare('INSERT INTO dsm_field_params(param_key,param,field_id) VALUES (?,?,?)');

		$array_keys = array_keys($field_param_keys);
		foreach ($array_keys as $k){
			$db->Execute($query3,array($field_param_keys[$k],$field_param_values[$k],$field_id));
		}
		
        //save field validation rule
		$query4 = $db->Prepare('INSERT INTO dsm_field_validation(field_id,rule,rule_order) VALUES (?,?,?)');
		$array_keys = array_keys($field_validations);
		foreach ($array_keys as $k){
			$db->Execute($query4,array($field_id,$field_validations[$k],$k));
		}

		//save field validation
		//$query = "INSERT INTO dsm_field_validation(field_id,field_validation) VALUES('$field_id','$validation')";
		//$res2 = $db->Execute($query);

		// link with disease.
		$query5 = $db->Prepare('INSERT INTO dsm_definitions(dis_id,field_id) VALUES(?,?)');
		$db->Execute($query5,array($disease_id,$field_id));
			
		$failed = $db->HasFailedTrans();
		$db->CompleteTrans();
		if($failed){
			add_error(_t('An unknown error occured while saving data.'));
		}else{
			// clear session;
			unset($_SESSION['dsm']);
			unset($_POST);
		}
		shn_dsm_add_fields();
	}
}
?>
