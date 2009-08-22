<?php

/**
 * DSM edit_dis.inc
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

function _shn_dsm_edit_disease()
{
	global $global;
	shn_form_fopen("edit_disease",'dsm',null,array('req'=>false));
	//shn_form_hidden(array('seq'=>'edit_dis'));
    $sql = "SELECT dis_id,dis_name FROM dsm_diseases";
	$res = _shn_dsm_execute($sql);//print $res;
	//return $res;
?>
<h2>Alter Disease Details</h2>

<div id="result">
<table width=100%>
<thead>
<td> <?php echo  _t('Disease Name'); ?></td>
<td> <?php echo  _t('Edit'); ?></td>
<!--  <td> <?php print _t('Delete'); ?></td> -->
</thead>

<?php   
if($res) { 
    while (!$res -> EOF) {
?> 
<tr>    
<td><?php print $res->fields['dis_name'];?></td>
<td><?php echo '<br><a href="index.php?mod='.$global['module'].'&act=edit_disease&dis_uuid='.$res->fields['dis_id'].'">'.'Edit'.'</a><br>'; ?></td>
</tr>
<?php
        $res->MoveNext();
    }
}
 ?>
</table>
</div>
<?php
shn_form_fclose();
}

function _shn_edit_tab_menu()
{
	shn_adm_menuopen(_t("Disease Surviellance Module"));
    shn_adm_menuitem("edit_disease", _t("View Diseases"));
	//shn_adm_menuitem("edit_disease&sec=edit_dis", _t("General Details"));
	shn_adm_menuitem("edit_disease&seq=general", _t("Edit General Details"));
	shn_adm_menuitem("edit_disease&seq=factors", _t("Edit Causative Factors"));
	shn_adm_menuitem("edit_disease&seq=symptoms", _t("Symptoms"));
	//shn_adm_menuitem("edit_disease&seq=risk", _t("Risk Analysis"));
	//shn_adm_menuitem("edit_disease&seq=cost", _t("Cost Estimation"));
	
	shn_adm_menuclose();
}

function _shn_dsm_disease_details($dis_uuid)
{
	$details = _shn_general_data_from_table($_SESSION['disease_id']);
	$details_risks = _shn_risks_data_from_table($_SESSION['disease_id']);
	shn_form_fopen('edit_disease','dsm',array('req'=>false));
	shn_form_hidden(array ('seq' => 'edit_dis'));
	
	shn_form_fsopen(_('General Details&nbsp;:'.$details['dis_name']));
	
	$extra_opts['value'] = $details['name'];
	//shn_form_text(_t('Name'),'name',null,$extra_opts);
	print "Disease Name : ".$details['dis_name']."<br><br>";
    print "Medical Name : ".$details['med_name']."<br><br>";
    print "Carrier : ".$details['carrier']."<br><br>";
    print "Cause : ".$details['cause']."<br><br>";
    print "Age Group : ".$details['age_group']."<br><br>";        
	shn_form_fsclose();
	
	shn_form_fsopen(_('Risks'));
    
    $extra_opts['value'] = $details['name'];
    //shn_form_text(_t('Name'),'name',null,$extra_opts);
   
    print "Gender : ".$details_risks['eff_gender']."<br><br>";
    print "Drinking Water Supply : ". $details_risks['drink_water']."<br><br>";
    print "Nutrition Level : ".$details_risks['nutrition']."<br><br>";
    print "Sanitary Facilitity : ".$details_risks['sanitary']."<br><br>";
    print "Seasonal Factors : ".$details_risks['seasons'];
        
    shn_form_fsclose();
	
	//shn_form_submit(_t('Save'));
	
	shn_form_fclose();
	
}

// edit gegeral detaile
function shn_dsm_edit_general_detailsl(){
	
	$details = _shn_general_data_from_table($_SESSION['disease_id']);
    shn_form_fopen('edit_general_details_cr','dsm',array('req_messahe'=>true));
    //shn_form_hidden(array ('seq' => 'page2'));

    shn_form_fsopen(_('Edit General Details &nbsp;:'.$details['dis_name']));

    shn_form_text(_t('General Name'),'name','',array('req'=>true));
    shn_form_text(_t('Medical Name'),'med_name');
    shn_form_text(_t('Cause'),'cause');
    shn_form_text(_t('Carrier'),'carrier');  
    $extra_opts['select'] = true;
    shn_form_opt_select('age_groups',_t('Vulnerable age groups'),'eff_age',$extra_opts);  
           
    shn_form_fsclose();
    
    shn_form_submit(_t('Save'),"name='save_general'");
    shn_form_fclose();
	// shn_dsm_edit_general_details_cr function is in main.inc
}

//edit risk factors
function shn_dsm_edit_factors(){
	$details = _shn_general_data_from_table($_SESSION['disease_id']);
    shn_form_fopen('edit_factors_cr','dsm',array('req_messahe'=>true));
    //shn_form_hidden(array ('seq' => 'page2'));

    shn_form_fsopen(_('Edit General Details &nbsp;:'.$details['dis_name']));

    unset($extra_opts['help']);
    $extra_opts['select'] = true;
    shn_form_select(array('Not Relevant','male'=>'Male','female'=>'Female'), _t('Gender'),"eff_gender", '',$extra_opts);
    shn_form_opt_select('dri_water',_t('Drinking Water Supply'),'drink_water',$extra_opts);
    shn_form_opt_select('nutrition_level',_t('Nutrition Level'),'nutrition',$extra_opts);
    shn_form_opt_select('sanitary',_t('Sanitary Facilitity'),'sanitary',$extra_opts);
    shn_form_opt_select('seasons',_t('Seasonal Factors'),'seasons',$extra_opts);  
           
    shn_form_fsclose();
    
    shn_form_submit(_t('Save'),"name='save_factors'");
    shn_form_fclose();
    // shn_dsm_edit_factors_cr function is in main.inc
	
}
//modifyed function for edit disease synptoms
function _shn_dsm_edit_disease_symptoms(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    //$db->debug=true;
    $dis_id = $_SESSION['disease_id'];
   
    $query_dis_name = "SELECT dis_name,med_name FROM dsm_diseases WHERE dis_id =?";
    $res_name = $db->Execute($query_dis_name,array($dis_id));
    $dis_name=$res_name->fields["dis_name"];
    $med_name=$res_name->fields["med_name"];
    
    shn_form_fopen('add_disease_symptoms_cr','dsm',array('req_massege'=>false));
    shn_form_hidden(array('sym_id'=>$sym_id,'dis_id'=>$dis_id));
    shn_form_fsopen(_t("Availble Symptoms of Disease &nbsp;".$dis_name."&nbsp;(".$med_name.")"));
    
    echo "</ul>";
   
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(dis_id) AS c FROM dsm_disease_symptoms WHERE dis_id =?";
    $rs = $db->Execute($q,array($dis_id));
    $count=$rs->fields['c'];
    $rpp=10;

    $note_query = "SELECT ds.description,ds.sym_id, dds.priority FROM dsm_disease_symptoms dds JOIN dsm_symptoms ds ON ds.sym_id=dds.sym_id AND dds.dis_id=?";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp,array($dis_id));
    echo "<table>";
    echo "<th> Description</th> <th>Priority</th> <th> </th>";
    while($row=$rs->FetchRow()){
        echo "<tr>";
        echo "<td>".$row['description']."</td>";
        echo "<td>".$row['priority']."</td>";
        echo "<td>";
        echo '<a href="index.php?mod='.$global['module'].'&act=delete_disease_symptom_confirm&sym_id='.$row['sym_id'].'">'._t('Delete Symptom').'</a>'; 
        echo "</td>";
        echo "</tr>";
    }
    echo "</table>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        echo '<a href="index.php?mod='.$global['module'].'&act=edit_disease&seq=symptoms&dis_id='.$dis_id.'&page=0">'._t('First').'</a>'; 
        echo "&nbsp";
        echo '<a href="index.php?mod='.$global['module'].'&act=edit_disease&seq=symptoms&dis_id='.$dis_id.'&page='.($page-1).'"> &lt </a>'; 
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        echo '<a href="index.php?mod='.$global['module'].'&act=edit_disease&seq=symptoms&dis_id='.$dis_id.'&page='.($i).'">'.($i+1).'</a>'; 
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        echo '<a href="index.php?mod='.$global['module'].'&act=edit_disease&seq=symptoms&dis_id='.$dis_id.'&page='.($page+1).'"> &gt </a>'; 
        echo "&nbsp";
        echo '<a href="index.php?mod='.$global['module'].'&act=edit_disease&seq=symptoms&dis_id='.$dis_id.'&page='.($page_count-1).'">'._t('Last').'</a>'; 
    }
    shn_form_fsclose();
    
    shn_form_fsopen(_t("Add Symptoms to Disease" ));
    
    shn_form_fsopen(_('Primary Symptoms'));
    
    foreach ($details as $det) {
        shn_form_label($det);
    }
    echo '<p> Select ' . $sym_priority . ' Symptom from the list below.</p>';
    $stored_symptoms = _shn_dsm_get_stored_sym();
    shn_form_multi_select('primary', $stored_symptoms,'','length=100%');
    shn_form_submit(_t('Save'), "name='primary_symptom'");
    
    shn_form_fsclose();
    
    shn_form_fsopen(_('Minor Symptoms'));
    
    echo '<p> Select ' . $sym_priority . ' Symptom from the list below.</p>';
    //$stored_symptoms = _shn_dsm_get_stored_sym();
    shn_form_multi_select('minor', $stored_symptoms,'','length=100%');
    shn_form_submit(_t('Save'), "name='minor_symptom'");
    
    shn_form_fsclose();
    
    shn_form_fsclose();
    
    shn_form_fclose();		
}
//..............................................

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
    	add_confirmation(_t('Data updated successfully'));
		//print 'success';
	}
}

function _shn_dsm_disease_factors()
{
	$details = _shn_dsm_get_disease_factors($_SESSION['disease_id']);
	shn_form_fopen('edit_disease','dsm',array('req'=>false));
	//shn_form_hidden(array ('seq' => 'page3'));
	
	shn_form_fsopen(_('Causative Factors'));
	//var_dump($details);
	shn_form_fsclose();
	
	shn_form_fclose();
}

function _shn_update_disease_factors()
{
    $sql = "UPDATE ";
	$ok = _shn_dsm_execute($sql);
    if ($ok) {
		add_confirmation(_t('Data updated successfully'));
    	//print 'success';
	}  
}

function _shn_update_disease_details()
{
	$sql = "UPDATE dsm_diseases SET dis_name='{$_POST['name']}' WHERE dis_id='{$_SESSION['disease_id']}'";
	$ok = _shn_dsm_execute($sql);
	if ($ok) {
		add_confirmation(_t('Data updated successfully'));
		//print 'success';
	}
}

