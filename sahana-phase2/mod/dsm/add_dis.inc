<?php
/**
 * DSM add_dis.inc
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @author     G.W.R. Sandaruwan <sandaruwan[at]opensource[dot]lk> <rekasandaruwan[at]gmail[dot]com
 * @author     Viraj Edirisinghe
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage dsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot'] . '/inc/handler_form.inc';
include_once $global['approot'] . '/inc/lib_uuid.inc';
//include_once $global['approot'] . '/inc/lib_form.inc';
/*?>
<div id="home">
<h2><?php print (_t('New Disease Details')); ?></h2>
</div>
<?php*/

//shn_form_open();

//=======================================================================================================

function _shn_dsm_get_data($errors=false)
{
	if ($errors) {
		display_errors();
	}
    ?>
    <h2><center><?php print (_t('New Disease Details')); ?></center></h2>
    <?php
	shn_form_fopen('add_dis','dsm');
    shn_form_hidden(array ('seq' => 'page2'));

    shn_form_fsopen(_('General Details'));

    shn_form_text(_t('General Name'),'name','',array('req'=>true));
    shn_form_text(_t('Medical Name'),'med_name');
    shn_form_text(_t('Cause'),'cause');
    shn_form_text(_t('Carrier'),'carrier');   
    $extra_opts['select'] = true; 
    shn_form_opt_select('age_groups',_t('Vulnerable age groups'),'eff_age',$extra_opts);
    	
	shn_form_fsclose();

    shn_form_fsopen(_('Special Risks'));
    
    
    unset($extra_opts['help']);
    //$extra_opts['select'] = true;
    shn_form_select(array('Not Relevant','male'=>'Male','female'=>'Female'), _t('Gender'),"eff_gender", '',$extra_opts);
    shn_form_opt_select('dri_water',_t('Drinking Water Supply'),'drink_water',$extra_opts);
    shn_form_opt_select('nutrition_level',_t('Nutrition Level'),'nutrition',$extra_opts);
    shn_form_opt_select('sanitary',_t('Sanitary Facilitity'),'sanitary',$extra_opts);
    shn_form_opt_select('seasons',_t('Seasonal Factors'),'seasons',$extra_opts);
    //shn_form_text(_t(''),'');
    //shn_form_text(_t('Family_jaa..na'),'');
    //shn_form_text(_t(''),'');

    shn_form_fsclose();
    
    shn_form_submit(_t('Next'),"name='next'");
    shn_form_fclose();
}

function _shn_dsm_validate()
{
	clean_errors();
	$error_flag = false;
	$dis_name = $_POST['name'];
	if ($dis_name == null) {
		add_error(_t('Please enter a disease name.'));
		$error_flag = true;
	}
	
	return $error_flag;
}

function _shn_dsm_set_datails()
{
	$_SESSION['dis_name'] = $_POST['name'];
	$_SESSION['med_name'] = $_POST['med_name'];
	$_SESSION['carrier'] = $_POST['carrier'];
	$_SESSION['cause'] = $_POST['cause'];
	$_SESSION['eff_age'] = $_POST['age_groups'];
	
	$_SESSION['eff_gender'] = $_POST['eff_gender'];
	$_SESSION['drink_water'] = $_POST['dri_water'];
	$_SESSION['nutrition'] = $_POST['nutrition_level'];
	$_SESSION['sanitary'] = $_POST['sanitary'];
	$_SESSION['seasons'] = $_POST['seasons'];
}


function _shn_dsm_add_symptoms($sym_priority=null)
{
	?>
    <h2><center><?php print (_t($sym_priority . ' Symptom of the Disease')); ?></center></h2>
    <?php
	shn_form_fopen('add_dis','dsm',array('req'=>false, 'enctype' => 'enctype="multipart/form-data"'));
    shn_form_hidden(array ('seq' => 'page3'));
    //= $_SESSION['priority'];
//    shn_form_fsopen(_('Symptoms'));
//    echo '<p> Symptoms that you have added for ' . $_SESSION['dis_name'] . ' are listed below.</p>';
    if (!$_SESSION[$sym_priority]['symptoms']) {
    	$_SESSION[$sym_priority]['symptoms'] = array();
    }
    if (!$_SESSION[$sym_priority]['symptoms_id']) {
    	$_SESSION[$sym_priority]['symptoms_id'] = array();
    }
    if ($_POST['symptom'] != null | $_POST['symptom'] != '') {
       array_push($_SESSION[$sym_priority]['symptoms'], $_POST['symptom']);$_POST['symptom']=null;
    }
    if ($_POST['symptomdb'] != null) {
        foreach ($_POST['symptomdb'] as $uuid) {
        	array_push($_SESSION[$sym_priority]['symptoms_id'], $uuid);
            $a = _shn_dsm_get_stored_sym($uuid);
            array_push($_SESSION[$sym_priority]['symptoms'], $a);
        }
    }
    if (count($_SESSION[$sym_priority]['symptoms']) > 0) {
    shn_form_fsopen(_($sym_priority . ' Symptoms'));
    echo '<p>' . $sym_priority . ' Symptoms that you have added for <strong>' . $_SESSION['dis_name'] . '</strong> are listed below.</p>';
        foreach ($_SESSION[$sym_priority]['symptoms'] as $symptom) {
           //shn_form_text('', '', 'READONLY size=100%',array('value'=>$symptom));
           shn_form_label('',$symptom);
           
        }
       /* if($_SESSION['priority'] == 'Primary'){
        	
            unset($_SESSION['Primary']);	
        }	
        else if($_SESSION['priority'] == 'Minor'){
        	
        	unset($_SESSION['Minor']);
        }	
        shn_form_submit(_t('Remove'), "name='remove'");*/
        //shn_form_fsclose();
    }
    shn_form_fsclose();
    
    shn_form_fsopen(_('Select Symptoms'));
    echo '<p> Select ' . $sym_priority . ' Symptom from the list below.</p>';
    $stored_symptoms = _shn_dsm_get_stored_sym();
    shn_form_multi_select('symptomdb', $stored_symptoms,'','length=100%');
    shn_form_submit(_t('Add to Disease'), "name='button'");
    
    shn_form_fsclose();
    
    shn_form_fsopen(_('Add New Symptom'));
    echo '<p> If you want to add new symptom, use the textbox below.</p>';
    $extra_opt['value'] = '';//shn_form_text(_t('General Name'),'symptom');
    shn_form_text('', 'symptom','size=100% maxlength=200');
    ?> <center> <?php
    shn_form_submit(_t('Add New '), "name='button'");
    ?> </center> <?php
    //shn_form_button('sffsfs');
    
    shn_form_fsclose();
    
    shn_form_submit(_t('Next'), "name='button'");
    
    shn_form_fclose();
}

function _shn_symtoms_todb($opt = 'one')
{
	$sym_priority = $_SESSION['priority'];
	if ($opt == 'one') {
		$sym = $_POST['symptom'];
		$id = shn_create_uuid('symptom');
		$ul_id = '0';
        $sql = "INSERT INTO dsm_symptoms(sym_id,description,upperlevel_id) VALUES ('$id','$sym','$ul_id')";
        $ok = _shn_dsm_execute($sql);
        if ($ok) {
        	array_push($_SESSION[$sym_priority]['symptoms_id'], $id);
        }
	} elseif ($opt == 'all') {
	    foreach ($_SESSION[$sym_priority]['symptoms'] as $sym) {
		    $id = shn_create_uuid('symptom');
		    $ul_id = '0';
            $sql = "INSERT INTO dsm_symptoms(sym_id,description,upperlevel_id) VALUES ('$id','$sym','$ul_id')";
            $ok = _shn_dsm_execute($sql);
	    }  
    }
}


function _shn_dsm_confirm()
{
	?>
    <h2><center><?php print (_t('Confirm Details of ' . $_SESSION['dis_name'] .'.')); ?></center></h2>
    <?php
	shn_form_fopen('add_dis','dsm',array('req'=>false));
    shn_form_hidden(array ('seq' => 'finish'));

    shn_form_fsopen(_t('Genral Details'));

    shn_form_label(_t('General Name'),$_SESSION['dis_name']);
    shn_form_label('Medical Name',$_SESSION['med_name']);
    shn_form_label('Carrier',$_SESSION['carrier']);
    shn_form_label('Cause',$_SESSION['cause']);
    
    shn_form_fsclose();
    
    shn_form_fsopen(_t('Primary Symptoms'));

    foreach ($_SESSION['Primary']['symptoms'] as $sym) {
        shn_form_label('',$sym);
    }
//    foreach ($_SESSION['Primary']['symptoms_id'] as $sym) {
//        shn_form_label('',$sym);
//    }
    shn_form_fsclose();
    shn_form_fsopen(_t('Minor Symptoms'));
    foreach ($_SESSION['Minor']['symptoms'] as $sym) {
        shn_form_label('',$sym);
    }
//    foreach ($_SESSION['Minor']['symptoms_id'] as $sym) {
//        shn_form_label('',$sym);
//    }
    
    shn_form_fsclose();
    
    shn_form_fsopen(_t('Factors'));

    foreach ($_SESSION['factors'] as $fac) {
        shn_form_label('',$fac);
    }
    foreach ($_SESSION['symptoms_id'] as $ses) {
        shn_form_label('',$ses);
    }
    
    shn_form_label('Vulnarable Age group',$_SESSION['eff_age']);
    shn_form_label('Vulnarable Gender',$_SESSION['eff_gender']);
    shn_form_label('Drinking water',$_SESSION['drink_water']);
    shn_form_label('Nutrition Level',$_SESSION['nutrition']);
    shn_form_label('Sanitary Facilities',$_SESSION['sanitary']);
    shn_form_label('Seasonal Factors',$_SESSION['seasons']); 
       
    shn_form_fsclose();
   ?> <center> <?php
    shn_form_submit('Save');
   ?> </center> <?php
    
    shn_form_fclose();
}

function _shn_dsm_write_to_db()
{
	$disease = shn_create_uuid('disease'); //print $disease;
	global $global;
	$db = $global['db'];
	$sql = "INSERT INTO dsm_diseases(dis_id,dis_name,age_group,med_name,cause,carrier) VALUES ('$disease','{$_SESSION['dis_name']}','{$_SESSION['eff_age']}','{$_SESSION['med_name']}','{$_SESSION['cause']}','{$_SESSION['carrier']}')";
	$sql_ok = _shn_dsm_execute($sql);
	if ($sql_ok) {
	    add_confirmation(_t($_SESSION['dis_name'] . ' is successfully added.'));
	}
	add_symptoms('Primary', $disease);
	add_symptoms('Minor', $disease);
	
	global $global;
    $db = $global['db'];
    $module = $global['module'];
       
    $sql = "INSERT INTO dsm_diseases_risks(dis_id,eff_gender,dri_water,nutrition_level,sanitary,seasons) VALUES (?,?,?,?,?,?)";
    $res = $db->Execute($sql,array($disease,$_SESSION['eff_gender'],$_SESSION['drink_water'],$_SESSION['nutrition'],$_SESSION['sanitary'],$_SESSION['seasons']));
    
   // $sql = "INSERT INTO disease_cau_factors(dis_id,fac_id,priority) VALUES ('$disease','{$_SESSION[]}','{$_SESSION['']}')";
	//$sql_ok = _shn_dsm_execute($sql);
	if ($sql_ok) {
	    //add_confirmation(_t($_SESSION['dis_name'] . ' is successfully added.'));
	}
	
}

function add_symptoms($priority, $disease)
{
    foreach ($_SESSION[$priority]['symptoms_id'] as $sym) {
    $sql = "INSERT INTO dsm_disease_symptoms(dis_id,sym_id,code,priority) VALUES ('$disease','$sym','sym','$priority')";
	$sql_ok = _shn_dsm_execute($sql);
	    if ($sql_ok) {
	        //add_confirmation(_t('sym' . ' is successfully added.'));
	    }
	}
}

