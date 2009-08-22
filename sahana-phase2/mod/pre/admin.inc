<?php

include_once($global['approot'].'/inc/lib_form.inc');

function _shn_pre_adm_sub_menu()
{
	global $conf;
?>
<h2>
<?php
	echo _t($conf['mod_pre_name']).' Administration<br>';
?>
</h2> 
<div id="submenu_v">
<a href="index.php?mod=pre&act=adm_effects"><?php echo _t("Disaster Eeffects");?></a>
</div>
<?php
}

function shn_pre_adm_default()
{
	global $conf;
?>

<?php
	_shn_pre_adm_sub_menu();  
	echo "Select a link from above menu";
}
?>

<?php



function _shn_pre_adm_effects_add(){
	$effect = $_POST['effect'];
	$code = 'ode_'.$_POST['effect_code'];
	if ($effect != NUll && $code != NUll){
		global $global;
		$sql = "INSERT INTO field_options VALUES('opt_disaster_effect', '$code', '$effect')";
		$res = $global['db']->Execute($sql);
		if ($res === false){
			add_error($global['db']->ErrorMsg());
		}
		else{
			add_confirmation($effect." is successfully added as a effect");
		}
	}
	else{
		add_error('Please fill all the two text boxes');
		_shn_pre_adm_threat_form();
	}
}

function _shn_pre_adm_effects_form(){
	global $global;
	$sql = "SELECT option_description FROM field_options WHERE field_name = 'opt_disaster_effect'";
	$res = $global['db']->Execute($sql);
	$effects_arr = $res->GetArray();
	$effects = array();
	foreach($effects_arr as $e){
		array_push($effects, $e['option_description']);
	}
	if ($res->RecordCount() <= 0){
		add_warning('No effect has been added currently');
	}
	else{
		shn_form_fopen();
		shn_form_fsopen('Currently added effects');
		shn_form_select($effects,'Effects');
		shn_form_fsclose();
		shn_form_fclose();
	}
	shn_form_fopen('adm_effects',null, array('req_message'=>false));
	shn_form_fsopen(_('Add a effect of disasters'));
	shn_form_hidden(array('seq'=>'add'));
	shn_form_text(_('Effect : '),'effect','size="25"',array('req'=>true));
	shn_form_text(_('Effect Code : '),'effect_code','size="3"',array('req'=>true));
    shn_form_submit(_('Submit'));
    shn_form_fsclose();
    shn_form_fclose();
}

function shn_pre_adm_effects(){
	_shn_pre_adm_sub_menu();
	switch ($_REQUEST['seq']){
		case '':
		    _shn_pre_adm_effects_form();
		    break;
		case 'add':
		    _shn_pre_adm_effects_add();
		    break;
		default:
		    break;
	}
}


