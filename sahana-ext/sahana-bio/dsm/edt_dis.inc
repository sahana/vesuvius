<?php
function _shn_dsm_edit_disease()
{
	global $global;
	shn_form_fopen("edit_disease",'dsm',null,array('req'=>false));
	//shn_form_hidden(array('seq'=>'edit_dis'));
    $sql = "SELECT dis_id,dis_name FROM diseases";
	$res = _shn_dsm_execute($sql);//print $res;
	//return $res;
?>
<table width=100%>
<thead>
<tr>
<td> <?= _t('Disease Name'); ?></td>
<td> <?= _t('Edit'); ?></td>
<td> <?php print _t('Delete'); ?></td>
</tr>
</thead>

<?php 
if($res) { 
    while (!$res -> EOF) {
?> 
<tr>
<td><?php print $res->fields['dis_name'];?></td>
<td><?php echo '<br /><a href="index.php?mod='.$global['module'].'&act=edit_disease&dis_uuid='.$res->fields['dis_id'].'">'.'Edit'.'</a><br />'; ?></td>
<td><?php echo '<br /><a href="index.php?mod='.$global['module'].'&act=delete_disease&dis_uuid='.$res->fields['dis_id'].'">'.'Delete'.'</a><br />'; ?></td>
</tr>
<?php
        $res->MoveNext();
    }
}
 ?>
</table>
<?php
shn_form_fclose();
}

function _shn_edit_tab_menu()
{
	shn_adm_menuopen(_t("Disease Surviellance Module"));
 
	shn_adm_menuitem("edit_disease", _t("General Details"));
	shn_adm_menuitem("edit_disease&seq=factors", _t("Causative Factors"));
	shn_adm_menuitem("edit_disease&seq=symptoms", _t("Symptoms"));
	//shn_adm_menuitem("edit_disease&seq=risk", _t("Risk Analysis"));
	//shn_adm_menuitem("edit_disease&seq=cost", _t("Cost Estimation"));
	
	shn_adm_menuclose();
}

function _shn_dsm_disease_details($dis_uuid)
{
	$details = _shn_general_data_from_table($_SESSION['disease_id']);
	shn_form_fopen('edit_disease','dsm',array('req'=>false));
	shn_form_hidden(array ('seq' => 'edit_dis'));
	
	shn_form_fsopen(_('General Details'));
	
	$extra_opts['value'] = $details['name'];
	shn_form_text(_t('Name'),'name',null,$extra_opts);
	
	shn_form_fsclose();
	
	shn_form_submit(_t('Save'));
	
	shn_form_fclose();
	
}

function _shn_dsm_disease_symptoms()
{
	$details = array();
	$details = _shn_dsm_get_disease_sym($_SESSION['disease_id']);//var_dump($details);
	shn_form_fopen('edit_disease','dsm',array('req'=>false));
	//shn_form_hidden(array ('seq' => 'page3'));
	
	shn_form_fsopen(_('Primary Symptoms'));
	foreach ($details as $det) {
		shn_form_label($det);
	}
    echo '<p> Select ' . $sym_priority . ' Symptom from the list below.</p>';
    $stored_symptoms = _shn_dsm_get_stored_sym();
    shn_form_multi_select('symptomdb', $stored_symptoms,'','length=100%');
    shn_form_submit(_t('Save'), "name='button'");
    
    shn_form_fsclose();
    
    shn_form_fsopen(_('Minor Symptoms'));
	
    echo '<p> Select ' . $sym_priority . ' Symptom from the list below.</p>';
    //$stored_symptoms = _shn_dsm_get_stored_sym();
    shn_form_multi_select('symptomdb', $stored_symptoms,'','length=100%');
    shn_form_submit(_t('Save'), "name='button'");
    
    shn_form_fsclose();
    
//    shn_form_fsopen(_('Add New Symptom'));
//    echo '<p> If you want to add new symptom, use the textbox below.</p>';
//    $extra_opt['value'] = '';//shn_form_text(_t('General Name'),'symptom');
//    shn_form_text('', 'symptom','size=100% maxlength=200');
//    ?> <center> <?php
//    shn_form_submit(_t('Add'), "name='button'");
//    ?> </center> <?php
//    
//	shn_form_fsclose();
	
	shn_form_fclose();
}

function _shn_update_disease_symptoms()
{
	$sql = "";
	$ok = _shn_dsm_execute($sql);
    if ($ok) {
		print 'success';
	}
}

function _shn_dsm_disease_factors()
{
	$details = _shn_dsm_get_disease_factors($_SESSION['disease_id']);
	shn_form_fopen('edit_disease','dsm',array('req'=>false));
	//shn_form_hidden(array ('seq' => 'page3'));
	
	shn_form_fsopen(_('Causative Factors'));
	var_dump($details);
	shn_form_fsclose();
	
	shn_form_fclose();
}

function _shn_update_disease_factors()
{
    $sql = "UPDATE ";
	$ok = _shn_dsm_execute($sql);
    if ($ok) {
		print 'success';
	}  
}

function _shn_update_disease_details()
{
	$sql = "UPDATE diseases SET dis_name='{$_POST['name']}' WHERE dis_id='{$_SESSION['disease_id']}'";
	$ok = _shn_dsm_execute($sql);
	if ($ok) {
		print 'success';
	}
}
?>