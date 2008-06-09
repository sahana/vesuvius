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
<a href="index.php?mod=pre&act=adm_threat"><?php echo _t("Threat Levels");?></a>
<a href="index.php?mod=pre&act=adm_effects"><?php echo _t("Disaster Eeffects");?></a>
<a href="index.php?mod=pre&act=adm_term"><?php echo _t("Terms of Recoverying methods");?></a>
<a href="index.php?mod=pre&act=adm_facility"><?php echo _t("Facilities of areas under threat");?></a>
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

function _shn_pre_adm_threat_form(){
	global $global;
	$sql = "SELECT option_description FROM field_options WHERE field_name = 'opt_threat_level'";
	$res = $global['db']->Execute($sql);
	$effects_arr = $res->GetArray();
	$effects = array();
	foreach($effects_arr as $e){
		array_push($effects, $e['option_description']);
	}
	if ($res->RecordCount() <= 0){
		add_warning('No threat level has been added currently');
	}
	else{
		shn_form_fopen();
		shn_form_fsopen('Currently added threat levels');
		shn_form_select($effects,'threat levels');
		shn_form_fsclose();
		shn_form_fclose();
	}
	shn_form_fopen('adm_threat',null, array('req_message'=>false));
	shn_form_fsopen(_('Add a threat'));
	shn_form_hidden(array('seq'=>'add'));
	shn_form_text(_('Threat : '),'threat','size="25"',array('req'=>true));
	shn_form_text(_('Threat Code : '),'threat_code','size="3"',array('req'=>true));
    shn_form_submit(_('Submit'));
    shn_form_fsclose();
    shn_form_fclose();
    
    shn_form_fopen('adm_threat',null, array('req_message'=>false));
	shn_form_fsopen(_('Remove a threat'));
	shn_form_hidden(array('seq'=>'remove'));
	global $global;
	$sql = "SELECT field_name, option_description FROM field_options WHERE field_name = 'opt_threat_level'";
	$res = $global['db']->Execute($sql);
	$result = $res->GetArray();
	//$arry
	foreach ($result as $r){
		
	}
    shn_form_submit(_('Submit'));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_pre_adm_threat_add(){
	$threat = $_POST['threat'];
	$code = $_POST['threat_code'];
	$code = 'otl_'.$code;
	if ($threat != NUll && $code != NUll){
		global $global;
		$sql = "INSERT INTO field_options VALUES('opt_threat_level', '$code', '$threat')";
		$res = $global['db']->Execute($sql);
		if ($res === false){
			add_error($global['db']->ErrorMsg());
		}
		else{
			add_confirmation($threat." successfully added as a threat level");
		}
	}
	else{
		add_error('Please fill all the two text boxes');
		_shn_pre_adm_threat_form();
	}
}

function shn_pre_adm_threat(){
	_shn_pre_adm_sub_menu();
	switch ($_REQUEST['seq']){
		case '':
		    _shn_pre_adm_threat_form();
		    break;
		case 'add':
		    _shn_pre_adm_threat_add();
		    break;
		default:
		    break;
	}
}

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

function _shn_pre_adm_term_form(){
	global $global;
	$sql = "SELECT option_description FROM field_options WHERE field_name = 'opt_recovering_term'";
	$res = $global['db']->Execute($sql);
	$effects_arr = $res->GetArray();
	$effects = array();
	foreach($effects_arr as $e){
		array_push($effects, $e['option_description']);
	}
	if ($res->RecordCount() <= 0){
		add_warning('No recoverying has been added currently');
	}
	else{
		shn_form_fopen();
		shn_form_fsopen('Currently added recovering terms');
		shn_form_select($effects,'Terms');
		shn_form_fsclose();
		shn_form_fclose();
	}
	shn_form_fopen('adm_term',null, array('req_message'=>false));
	shn_form_fsopen(_('Add a term of a recoverying method'));
	shn_form_hidden(array('seq'=>'add'));
	shn_form_text(_('Term : '),'term','size="25"',array('req'=>true));
	shn_form_text(_('Term Code : '),'term_code','size="3"',array('req'=>true));
    shn_form_submit(_('Submit'));
    shn_form_fsclose();
    shn_form_fclose();
	
}

function _shn_pre_adm_term_add(){
	$effect = $_POST['term'];
	$code = 'ort_'.$_POST['term_code'];
	if ($effect != NUll && $code != NUll){
		global $global;
		$sql = "INSERT INTO field_options VALUES('opt_recovering_term', '$code', '$effect')";
		$res = $global['db']->Execute($sql);
		if ($res === false){
			add_error($global['db']->ErrorMsg());
		}
		else{
			add_confirmation($effect." is successfully added as a term of recoverying method");
		}
	}
	else{
		add_error('Please fill all the two text boxes');
		_shn_pre_adm_threat_form();
	}
}

function shn_pre_adm_term(){
	_shn_pre_adm_sub_menu();
	switch ($_REQUEST['seq']){
		case '':
			_shn_pre_adm_term_form();
			break;
		case 'add':
			_shn_pre_adm_term_add();
			break;
		default:
			break;
	}
	
}

function _shn_pre_adm_facility_form(){
	global $global;
	$sql = "SELECT option_description FROM field_options WHERE field_name = 'opt_area_facility'";
	$res = $global['db']->Execute($sql);
	$facility_arr = $res->GetArray();
	$facility = array();
	foreach($facility_arr as $f){
		array_push($facility, $f['option_description']);
	}
	if ($res->RecordCount() <= 0){
		add_warning('No facility has been added currently');
	}
	else{
		shn_form_fopen();
		shn_form_fsopen('Currently added facilities of areas under threat');
		shn_form_select($facility,'facility');
		shn_form_fsclose();
		shn_form_fclose();
	}
	shn_form_fopen('adm_facility',null, array('req_message'=>false));
	shn_form_fsopen(_('Add a facility of area under threat'));
	shn_form_hidden(array('seq'=>'add'));
	shn_form_text(_('Facility : '),'facility','size="25"',array('req'=>true));
	shn_form_text(_('Facility Code : '),'facility_code','size="3"',array('req'=>true));
    shn_form_submit(_('Submit'));
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_pre_adm_facility_add(){
	$facility = $_POST['facility'];
	$code = 'oaf_'.$_POST['facility_code'];
	if ($facility != NUll && $code != NUll){
		global $global;
		$sql = "INSERT INTO field_options VALUES('opt_area_facility', '$code', '$facility')";
		$res = $global['db']->Execute($sql);
		if ($res === false){
			add_error($global['db']->ErrorMsg());
		}
		else{
			add_confirmation($facility." is successfully added as a facility of a area under threat");
		}
	}
	else{
		add_error('Please fill all the two text boxes');
		_shn_pre_adm_facility_form();
	}
}

function shn_pre_adm_facility(){
	_shn_pre_adm_sub_menu();
	switch ($_REQUEST['seq']){
		case '':
			_shn_pre_adm_facility_form();
			break;
		case 'add':
			_shn_pre_adm_facility_add();
			break;
		default:
			break;
	}
}

?>