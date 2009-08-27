<?php
/* $Id: edit_disease.inc,v 1.3 2009-08-27 22:26:48 pradeeper Exp $ */

/**
 * Edit a disease
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author      Nuwan Waidyanatha <waidyanatha@lirne.net>
 * @copyright   Lanka Software Foundation - http://www.opensource.lk
 * @package     mod
 * @subpackage  bsm
 * @license     http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
/**
 * @name    Generate Tabbs
 * @param string $selected
 * @access public
 * @return void
 * @todo code this
 */
function shn_generate_tabs($selected=''){

	global $conf;
	$tabs = $conf['mod_bsm']['edit']['tabs'];
	?>
<div id="form_tabs">
<ul>
<?php
foreach($tabs as $tab){
	?>
	<li><a href="#"><?= $tab; ?></a></li>
	<?php
}
?>
</ul>
</div>
<?php
}
/**
* @name Load information on the disease
* @param string $disease
* @access public
* @return void
*/
function shn_bsm_edit_load($disease){
    global $global;
    global $conf;

    $sql =  "SELECT disease AS disease, dis_enum AS d_enum, dis_type AS d_type, dis_priority AS d_priority, icd_code AS icd_code, ";
    $sql .=  "icd_desc AS icd_desc, notes AS notes FROM bsm_disease WHERE deactivate_dt IS NULL AND disease = '$disease' ";
    
    $rs = $global['db']->Execute($sql);
	
    $_SESSION['bsm']['edit']['disease'] = $rs->fields['disease'];
    $_SESSION['bsm']['edit']['d_enum'] = $rs->fields['d_enum'];
    $_SESSION['bsm']['edit']['type'] = $rs->fields['d_type'];
    $_SESSION['bsm']['edit']['priority'] = $rs->fields['d_priority'];
    $_SESSION['bsm']['edit']['icd_code'] = $rs->fields['icd_code'];
    $_SESSION['bsm']['edit']['icd_desc'] = $rs->fields['icd_desc'];
    $_SESSION['bsm']['edit']['notes'] = $rs->fields['notes'];
}
/**
 * Edit Form
 *
 * @param mixed $errors
 * @access public
 * @return void
 */
function shn_bsm_edit_entry($errors=false){
    global $global;
    global $conf;
    
    shn_form_fopen("edit&entity=disease",null,array('req_message'=>true));
    shn_form_hidden(array('seq'=>'entry'));
    shn_form_fsopen(_('Details for Disease: '.$_SESSION['bsm']['edit']['disease'].'  {'.$_SESSION['bsm']['edit']['d_enum'].'}'));

    $sql = "SELECT DISTINCT dis_type AS d_type FROM bsm_dis_type WHERE deactivate_dt IS NULL ";
    $rsql = $global['db']->Execute($sql);
    $arropt = array();
    foreach ($rsql AS $r => $rv)
    {
        array_push($arropt,$rv[0]);
    }
    $arropt = array_combine($arropt,$arropt);
    shn_form_select($arropt,_('Type'), 'type',null,array('value'=>$_SESSION['bsm']['edit']['type'],'help' => _('Select a disease type.'), 'req'=>false));
    shn_form_opt_select('opt_dis_priority',_('Priority'), null, array('value'=>$_SESSION['bsm']['edit']['priority'],'help' => _('Select the disease priority.'), 'req'=>false));
    shn_form_text(_('ICD 10 Code'),'icd_code','size="30"',array('value'=>$_SESSION['bsm']['edit']['icd_code'],'help' => _('Enter full or part of the ICD 10 code.'), 'req'=>false));
    shn_form_textarea(_('ICD 10 descritpion'),'icd_desc',null,array('value'=>$_SESSION['bsm']['edit']['icd_desc'],'help' => _('Enter full or part of the ICD 10 description.'), 'req'=>false));
    shn_form_textarea(_('Other Notes'),'notes',null,array('value'=>$_SESSION['bsm']['edit']['notes'],'help' => _('Enter full or part of the ICD 10 description.'), 'req'=>false));

    shn_form_submit(_('Save'));
    shn_form_fsclose();

    shn_bsm_symp_vw();
}
/**
 * @name    view symptom information in relation to disease
 * @return  void
 * @global <type> $global
 * @global <type> $conf
 */
function shn_bsm_symp_vw(){

    global $global;
    global $conf;
    
    //retieve disease symptoms
    $sql = "SELECT s.symptom, s.symp_code FROM bsm_symptom s INNER JOIN bsm_dis_symp ds ON ds.symptom = s.symptom ";
    $sql .= "INNER JOIN bsm_disease d ON d.disease = ds.disease WHERE ds.deactivate_dt IS NULL AND ds.disease = '".$_SESSION['bsm']['edit']['disease']."'";
    $arrsymp = $global['db']->Execute($sql);
    
    //retieve disease signs
    $sql = "SELECT s.sign, s.sign_code FROM bsm_sign s INNER JOIN bsm_dis_sign ds ON ds.sign = s.sign ";
    $sql .= "INNER JOIN bsm_disease d ON d.disease = ds.disease WHERE ds.deactivate_dt IS NULL AND ds.disease = '".$_SESSION['bsm']['edit']['disease']."'";
    $arrsign = $global['db']->Execute($sql);

    //retieve disease causality factors
    $sql = "SELECT cf.caus_fact, cf.caus_fact_code FROM bsm_caus_fact cf INNER JOIN bsm_dis_caus_fact dsf ON dsf.caus_fact = dsf.caus_fact ";
    $sql .= "INNER JOIN bsm_disease d ON d.disease = dsf.disease WHERE dsf.deactivate_dt IS NULL AND dsf.disease = '".$_SESSION['bsm']['edit']['disease']."'";
    $arrcf = $global['db']->Execute($sql);

    if($_GET['act']!='edit')
        $select = true;
    shn_form_fsopen(_('Symptoms, Signs, and Causality Factors (to edit or further details clik on the record)'));
    ?>
    <TABLE>
    <div id = "symptom_table">
    <TD>
    <?php echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].
                '&act=search&entity=symptom&seq=lukup&rtnfrm=disease&rtnid='
                .$_SESSION['bsm']['edit']['disease'].'">'."ADD".'</a><br>'; ?>
    <TABLE>
    <THEAD>
        <TD><?= _('Symptom');?></TD>
        <TD><?= _('Code');?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <?php
    if($arrsymp!=null)
    {
        foreach($arrsymp as $symp)
        {
    ?><TR>
        <TD> <?php   echo $symp['symptom'] ? $symp['symptom'].'<br>' : ''; ?> </TD>
        <TD> <?php   echo $symp['symp_code'] ? $symp['symp_code'].'<br>' : ''; ?> </TD>
    </TR><?php
        }
    }
    ?></TABLE>
    </TD>
    </div>

    <TD>
    <?php echo "     "; ?>
    </TD>

    <div id = "sign_table">
    <TD>
        <?php echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].
                '&act=search&entity=sign&seq=lukup&rtnfrm=disease&rtnid='
                .$_SESSION['bsm']['edit']['disease'].'">'."ADD".'</a><br>'; ?>
    <TABLE>
    <THEAD>
        <TD><?= _('Sign');?></TD>
        <TD><?= _('Code');?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <?php
    if($arrsign!=null)
    {
        foreach($arrsign as $sign)
        {
        ?><TR>
            <TD> <?php echo $sign['sign'] ? $sign['sign'].'<br>' : ''; ?> </TD>
            <TD> <?php echo $sign['sign_code'] ? $sign['sign_code'].'<br>' : ''; ?> </TD>
        </TR><?php
        }
    }
    ?></TABLE>
    </TD></div>

    <div id = "causality_factor_table">
    <TD>
    <?php echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].
                '&act=search&entity=caus_factor&seq=lukup&rtnfrm=disease&rtnid='
                .$_SESSION['bsm']['edit']['disease'].'">'."ADD".'</a><br>'; ?>
    <TABLE>
    <THEAD>
        <TD><?= _('Causality');?></TD>
        <TD><?= _('Code');?></TD>
        <?=($select?'<TD>'._('Select').'</TD>':''); ?>
    </THEAD>
    <?php
    if($arrcf!=null)
    {
        foreach($arrcf as $causfact)
        {
        ?><TR>
            <TD> <?php echo $causfact['caus_fact'] ? $causfact['caus_fact'].'<br>' : ''; ?> </TD>
            <TD> <?php echo $causfact['caus_fact_code'] ? $causfact['caus_fact_code'].'<br>' : ''; ?> </TD>
        </TR><?php
        }
    }
    ?></TABLE>
    </TD></div>

    </TABLE><?php

    shn_form_fsclose();
}
/**
 * Validation of the Edit Form
 *
 * @access public
 * @return void
 */
function shn_bsm_edit_validate(){
	global $global;
	global $conf;

	$error_flag=false;

	//trim them all
	foreach($_POST as $k => $v){
		$v = trim($v);
		if($v != '')
		$local_post[$k] = $v;
	}

	$local_post['disease'] = $_SESSION['bsm']['edit']['disease'];
	//clean
	$_SESSION['bsm']['edit']=null;
	$_SESSION['bsm']['edit']=$local_post;

	if(!isset($local_post['disease'])){
		add_error(_("Please enter a disease name; null values not allowed"));
		$error_flag=true;
	}
	if(!isset($local_post['type'])){
		add_error(_("Please select a type; null values not allowed"));
		$error_flag=true;
	}

	if($error_flag)
	return false;
	else{return true;}
}
/**
 * @name    Confirmation page
 * @access public
 * @return void
 */
function shn_bsm_edit_confirm(){
    global $global;
    global $conf;

    $_SESSION['bsm']['edit']['type'] = isset($_POST['type']) ? trim($_POST['type']) : null;
    $_SESSION['bsm']['edit']['icd_code'] = isset($_POST['icd_code']) ? trim($_POST['icd_code']) : null;
    $_SESSION['bsm']['edit']['icd_desc'] = isset($_POST['icd_desc']) ? trim($_POST['icd_desc']) : null;
    $_SESSION['bsm']['edit']['priority'] = isset($_POST['priority']) ? trim($_POST['priority']) : null;
    $_SESSION['bsm']['edit']['notes'] = isset($_POST['notes']) ? trim($_POST['notes']) : null;

    shn_form_hidden(array('seq'=>'commit'));
}
/**
 * @name    Commits the changes to the database
 * @access public
 * @return void
 */
function shn_bsm_edit_commit(){
	// $update_array[<field_name>] = value
	global $global;
	global $conf;

	//$update_array['loc_id'] = $_SESSION['bsm']['edit']['location_uuid'];
        //if ($conf['debug']){print ('loc id = '.$_SESSION['bsm']['edit']['location_uuid'].'<hr><br>');}

	if(isset($_SESSION['bsm']['edit']['type'])){$update_array['dis_type'] = $_SESSION['bsm']['edit']['type'];}
	if(isset($_SESSION['bsm']['edit']['priority'])){$update_array['dis_priority'] = $_SESSION['bsm']['edit']['priority'];}
	if(isset($_SESSION['bsm']['edit']['icd_code'])){$update_array['icd_code'] = $_SESSION['bsm']['edit']['icd_code'];}
	if(isset($_SESSION['bsm']['edit']['icd_desc'])){$update_array['icd_desc'] = $_SESSION['bsm']['edit']['icd_desc'];}
	if(isset($_SESSION['bsm']['edit']['notes'])){$update_array['notes'] = $_SESSION['bsm']['edit']['notes'];}
	
	shn_db_update($update_array,'bsm_disease'," WHERE disease = '".$_SESSION['bsm']['edit']['disease']."'");
	$_GET['rtnid'] = $_SESSION['bsm']['edit']['disease'];
}
/**
 * @name    Commits loouk up value of parent location
 * @access  public
 * @return  void
 */
function shn_bsm_edit_commit_lukup($pk_uuid=null,$fk_uuid=null,$fk_name=null, $disease=null){

    global $global;
    global $conf;

    if ($pk_uuid==null || $fk_uuid==null){
    	add_error(_("Your lookup selection is invalid, failed to return the values!"));
    } else {
        
    	switch ($_GET['entity'])
        {
            case 'symptom':
                $sql = "SELECT 1 FROM bsm_dis_symp WHERE deactivate_dt IS NULL AND disease = '".$pk_uuid."' AND symptom = '".$fk_uuid."'";
                $rsql = $global['db']->Execute($sql);
                if($rsql->RecordCount()>0){add_error(_("A record with same disease and symptom exisits"));}
                else{
                    $insert_array['disease'] = $disease;
                    $insert_array['symptom'] = $fk_uuid;
                    shn_db_insert($insert_array,'bsm_dis_symp',null,$disease);
                }
                break;
            case 'sign':
                $sql = "SELECT 1 FROM bsm_dis_sign WHERE deactivate_dt IS NULL AND disease = '".$pk_uuid."' AND sign = '".$fk_uuid."'";
                $rsql = $global['db']->Execute($sql);
                if($rsql->RecordCount()>0){add_error(_("A record with same disease and sign exisits"));}
                else{
                    $insert_array['disease'] = $disease;
                    $insert_array['sign'] = $fk_uuid;
                    shn_db_insert($insert_array,'bsm_dis_sign',null,$pk_uuid);
                }
                break;
            default:
            case 'caus_factor':
                $sql = "SELECT 1 FROM bsm_dis_caus_fact WHERE deactivate_dt IS NULL AND disease = '".$pk_uuid."' AND caus_fact = '".$fk_uuid."'";
                $rsql = $global['db']->Execute($sql);
                if($rsql->RecordCount()>0){add_error(_("A record with same disease and causality factor exisits"));}
                else{
                    $insert_array['disease'] = $pk_uuid;
                    $insert_array['caus_fact'] = $fk_uuid;
                    shn_db_insert($insert_array,'bsm_dis_caus_fact',null,$pk_uuid);
                }
                break;
            default:
                break;
        }
    }
}
?>