<?php
/** This file is to add,edit,delete field options through the admin interface
 *
 * PHP version 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana - http://sahana.sourceforge.net
 * @author     Kethees <ks@respere.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 */

include_once $global['approot'] . '/inc/lib_form.inc';
include_once $global['approot'] . '/inc/lib_errors.inc';

function _shn_admin_field_option_config(){	
	shn_xajax_registerFunction('admin_get_field_options');
	$error_flag = true;
    if(isset($_POST['add'])){
		if($_POST['field_name'] == null){
			add_error(_t('Please select a field name'));
			$error_flag=false;			
		}
		else if($_POST['opt_des'] == null){
			add_error(_t('Please enter option description'));
			$error_flag=false;			
		}
		else{
			$res = _shn_admin_field_add($_POST['opt_des'],$_POST['field_name']);
			if($res){
				add_confirmation(_t('Information successfully saved'));
				$_POST['opt_des'] = null;
			}
			else{
				add_error(_t('Can not add user information to the db! Please contact your Administrator.'));
			}	
		}	
    }	
    if(isset($_POST['remove'])){
		if($_POST['field_name'] == null){
			add_error(_t('Please select a field name'));
			$error_flag=false;			
		}
		else if($_POST['opt_data'] == null){
			add_error(_t('Please select option description'));
			$error_flag=false;			
		}
		else{
			$res = _shn_admin_field_remove($_POST['opt_data'],$_POST['field_name']);
			if($res){
				add_confirmation(_t('Information successfully deleted'));				
			}
			else{
				add_error(_t('Can not add user information to the db! Please contact your Administrator.'));
			}
		}
    }

    echo '<h2>'._t('Field Option Configuration').'</h2>';
	$field_name = $_POST['field_name'];
    shn_form_fopen("field_option_config",null,array('req_message'=>false));
    shn_form_fsopen(_t('Select a Field Name'));
    echo "<label> Field Name(s)</label>";
	shn_admin_field_name('field_name','admin_get_field_options(this.value);',$_POST['field_name']);
	echo "<br/>";
    shn_form_fsclose();	

    shn_form_fsopen(_t("Add Option Description"));
    shn_form_text(_t('Option Description'),'opt_des',null,null);	
    shn_form_submit(_t('Add'), "name='add'");
    shn_form_fsclose();

    shn_form_fsopen(_t("Remove Option Description"));	
		
	$options = shn_admin_field_options($_POST['field_name']);

	shn_form_select($options, _t('Existing Field Option(s)'),'opt_data' , " multiple='true' ",null);	
    shn_form_submit(_t('Remove'), "name='remove'");
    shn_form_fsclose();
}


function _shn_admin_field_remove($codes,$field_name){
    global $global;
    if(is_array($codes))
        foreach($codes as $code){
            $sql = "DELETE FROM field_options WHERE option_code = '$code' AND field_name='$field_name'";
           $res =  $global['db']->Execute($sql);
        }
    else{
        $sql = "DELETE FROM field_options WHERE option_code = '$codes' AND field_name='$field_name'";
        $res = $global['db']->Execute($sql);
    }
	return $res;
}


function _shn_admin_field_add($description,$field_name){
    global $global;
    $code = substr($description , 0 , 4);
    $code = str_replace(' ' , '_' ,$code);
    
    include_once $global['approot'] . '/inc/lib_uuid.inc';
    $n = _shn_gen_id('opt');
    $code =  strtolower($code) . $n;
	$description = strtoupper(substr($description,0,1)) . strtolower(substr($description,1,strlen($field_name)));
	
	$sql = "INSERT INTO field_options VALUES('$field_name','$code','$description')";
    $res = $global['db']->Execute($sql);
	
	return $res;
		
}

function shn_admin_field_options_xajax($field_name){
		global $global;
		$sql = "SELECT DISTINCT option_code,option_description FROM field_options 
				WHERE field_name = '$field_name' ORDER BY option_code";
		$res = $global['db']->GetAll($sql);
    	return  $res;
}

function shn_admin_field_name($name, $onchange,$opt_data){
	global $global;
		$q="SELECT distinct field_name, substring(field_name,5) as 'des' FROM field_options 			
			ORDER BY field_name ";
	
	$res = $global['db']->Execute($q);
	echo "<select name='$name' multiple='true' onchange ='$onchange'>";
	
	foreach($res as $rs){		
		$field_data = ereg_replace('_',' ',strtoupper(substr($rs[1],0,1)) . strtolower(substr($rs[1],1,strlen($rs[1]))));
	if ($opt_data == $rs[0]){
	?>	
	<option selected="<?php echo $opt_data; ?>" value="<?php echo $rs[0]?>"><?php echo _lc($field_data)?></option>	 
	<?php
	}
	else {
	?>	
	<option value="<?php echo $rs[0]?>"><?php echo _lc($field_data)?></option>	
	<?php
	}
	
	}
	echo "</select>";
}

function shn_admin_field_options($field_name){
	global $global;

	$q="SELECT DISTINCT option_code,option_description FROM field_options 
		WHERE field_name = '$field_name' ORDER BY option_code";
	$res = $global['db']->Execute($q);
	$options=array();
	foreach($res as $option){
		$options[$option['option_code']]=$option['option_description'];
	}
	
	return $options;
}
