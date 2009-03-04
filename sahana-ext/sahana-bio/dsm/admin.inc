<?php
/**
 * DSM admin.inc
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

// icta stuff here.
include_once ("disease_definitions.inc");
//include_once ("add_dis.inc");

/**
 * DSM Administrative Section
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Viraj Edirisinghe
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    dsm
 * @subpackage  dsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * dsm 
 * 
 * @access public
 * @return void
 */
function shn_dsm_adm_default() {
?>
<p><b>
<?php echo _t("Welcome to the Disease Surviellance System admin page");?> </b></p>
    <p>
    <?php
   shn_dsm_adminmenu();
   ?>
   <br/>
     <p><b> <?php echo _t("Welcome to the DSM administration  page")?> </b></p>
     
    <p> <?php echo _t("Follow above links to administer the Disease Surviellance System")?></p>
<?php
}


function shn_dsm_adminmenu() {
	global $global;
	$module = $global['module'];
	// Create the module menuj
	shn_adm_menuopen(_t("Disease Surveillance System"));
 	shn_adm_menuitem("adm_dri_water", _t("Drinking Water Supply"));
 	shn_adm_menuitem("adm_age_groups", _t("Age Groups"));
 	shn_adm_menuitem("adm_nutrition_level", _t("Nutrition Level"));
 	shn_adm_menuitem("adm_sanitary", _t("Sanitary"));
 	shn_adm_menuitem("adm_seasons", _t("Seasons"));
 	shn_adm_menuitem('adm_delete_symptom',_t("Symptoms"));
 	shn_adm_menuitem("adm_disease_definitions", _t("Disease Definitions"));
 	//shn_adm_menuitem("adm_", _t(""));
 	//shn_adm_menuitem("adm_age_groups", _t("Age Groups"));

	//shn_adm_menuitem("adm_opt_age_group", _t("Manage Groups"));
	shn_adm_menuclose();

}

function shn_dsm_adm_dri_water()
{
    global $global;
    shn_dsm_adminmenu();
    
    ?><br /><h2><?=_t("Drinking Water"); ?></h2>
<?php

	_shn_dsm_adm_field_options_controller('dri_water');
}

function shn_dsm_adm_age_groups()
{
	global $global;
    shn_dsm_adminmenu();
    
    ?><br /><h2><?=_t("Age Groups"); ?></h2>
    <?php

	_shn_dsm_adm_field_options_controller('age_groups');
}

function shn_dsm_adm_nutrition_level()
{
	global $global;
    shn_dsm_adminmenu();
    
    ?><br /><h2><?=_t("Nutrition Levels"); ?></h2>
    <?php

	_shn_dsm_adm_field_options_controller('nutrition_level');
}

function shn_dsm_adm_sanitary()
{
	global $global;
    shn_dsm_adminmenu();
    
    ?><br /><h2><?=_t("Sanitary"); ?></h2>
    <?php

	_shn_dsm_adm_field_options_controller('sanitary');
}

function shn_dsm_adm_seasons()
{
	global $global;
    shn_dsm_adminmenu();
    
    ?><br /><h2><?=_t("Seasons"); ?></h2>
<?php

	_shn_dsm_adm_field_options_controller('seasons');
}

function _shn_dsm_adm_field_options_controller($type)
{
	global $global;
    shn_form_fopen('adm_' . $type,null,array("req"=>false));
    shn_form_fsopen(_t("Update"));
    ?>	   <table> 
	    <thead>
    <td><strong><?=_t('Code');?></strong></td>
    <td width="100%"><strong><?=_t('Description');?></strong></td>
    <td width="100%"><strong><?=_t('Delete');?></strong></td>
    </thead>
    <?php
 $button = $_POST['selection'];
    if ($button == 'Update') {
		$count=0;
		while ($_POST[$_SESSION['option_code'.$count]] != null) {
    		$code = $_POST[$_SESSION['option_code'.$count]];
    	    $desc = $_POST[$_SESSION['option_description'.$count]];
    		$todelete = $_POST[$count];
    		
            if($todelete=='on') { 
    	        _shn_dsm_delete_option($code);
            } elseif ($_POST[$_SESSION['option_description'.$count]] == null) {
                add_error(_t("Description should not be empty."));
            } elseif ($_POST[$_SESSION['option_description'.$count]] != $_SESSION['option_description'.$count]) {
                _shn_dsm_update_option($code,$desc);
                add_confirmation(_t($_SESSION['option_description'.$count].' changed to '.$_POST[$_SESSION['option_description'.$count]].'.'));
    	    }
		$count++;	
		}
    }	    
	elseif ($button == 'Add Item') {
	    _shn_dsm_adm_form_commit($type);
	}  

    $sql = "SELECT field_name, option_code, option_description FROM field_options WHERE field_name = '{$type}'";
	$sel = $global['db']->GetAll($sql);
    $result = array();
    $count=0;
    foreach ($sel as $row) {
        $_SESSION['option_code'.$count] = $row['option_code'];
        //$_SESSION[$count]['field_name'] = $row['field_name'];
        $_SESSION['option_description'.$count] = $row['option_description'];
        ?>
<tr>
    <td><input type="text" READONLY name="<?=$_SESSION['option_code'.$count];?>" 
            value="<?=$_SESSION['option_code'.$count];?>"  />
    </td>
    <td><input type="text" name="<?=$_SESSION['option_description'.$count];?>" 
            value="<?=$_SESSION['option_description'.$count];?>" />
    </td>
    <td><input type="checkbox" name="<?=$count;?>" />
    </td>
    <?php 
    $count++;
    } ?>
</tr>
</table>
<br></br>
<?php
    shn_form_submit(_t("Update"), "name = 'selection'");
    shn_form_fsclose();
    shn_form_fsopen(_t("Add New"));   
?>
<table>
	<tr>
	<td>
	<?php
	$extra_opts['req'] = true;	
	shn_form_text(_t("Description"),"service_name",'size="30"',$extra_opts);
	?>
	</td></tr>
	<tr><td>
	<?php
	
		
	shn_form_text(_t("Abbrevation [3 letter unique abbr. to store in the database]"),"service_abbr",'size="3" maxlength="3"',$extra_opts);
	?>
	</td></tr>
	</table>
	<?php
	
	shn_form_fsclose();
	shn_form_submit(_t("Add Item"), "name ='selection'");
	shn_form_fclose();
} 



function _shn_dsm_adm_form_commit($type)
{
	
    global $global;
	$db = $global['db'];
	
	if(!empty($_POST['service_name']))
	{
		if(!empty($_POST['service_abbr']))
		{
			$q1 = "SELECT * FROM field_options WHERE option_description='{$_POST['service_name']}' AND field_name='{$_type}'";
				$res1 = $db->Execute($q1);
				
				$q2 = "SELECT * FROM field_options WHERE option_code='{$_POST['service_abbr']}'";
				$res2 = $db->Execute($q2);
				if (1 <= $res1->RecordCount()) {
				    add_error(_t("Item already exists"));
				} elseif (1 <= $res2->RecordCount()) {
				    add_error(_t("Use different abbrevation."));
				} else {
				    $q = "INSERT INTO field_options(field_name,option_code,option_description) VALUES('{$type}','{$_POST['service_abbr']}','{$_POST['service_name']}')";
				    $res = $db->Execute($q);
				    $_POST['service_abbr']=null;
				    $_POST['service_name']=null;
			    }
				
		    } else {
		        add_error(_t("Please fill the abbrevation."));
		    }
	
	} else {
	add_error(_t("Please fill the service."));
	}
}

function _shn_dsm_delete_option($code)
{
    global $global;
	$sql= "DELETE FROM field_options WHERE option_code='$code'";
    $global['db']->Execute($sql);
    add_confirmation(_t('Service / Facility was removed successfully.'));
}

function _shn_dsm_update_option($optioncode, $optiondescription)
{
    global $global;	
    $sql="UPDATE field_options SET option_description='{$optiondescription}' WHERE option_code='{$optioncode}'";
    $global['db']->Execute($sql);
}

//delete symptom
function shn_dsm_adm_delete_symptom(){
	shn_dsm_adminmenu();
	echo "<h2>"._t("Delete Symptoms")."</h2>";
		
	global $global;
    $db = $global['db'];
    $module = $global['module'];
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM dsm_symptoms";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=10;

    $note_query = "SELECT sym_id,description FROM dsm_symptoms";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table>";
    echo "<th> Description</th> <th> </th>";
    while($row=$rs->FetchRow()){
        echo "<tr>";
        echo "<td>".$row['description']."</td>";
        echo "<td>";
        
            $q1 = "SELECT COUNT(*) AS c FROM dsm_disease_symptoms WHERE sym_id=?";
            $r1 = $db->Execute($q1,array($row['sym_id']));
            $count=$r1->fields['c'];
            if($count>0){
            	echo "This symptom is used one or more disease";
            }else{
            	
                shn_acl_secure_hyperlink('dsm','adm_delete_symptom_confirm','Delete Symptom',$stream=null,$params=array('sym_id'=>$row['sym_id']),$text_opts='');
            }
            
        echo "</td>";
        echo "</tr>";
    }
    echo "</table>";
    
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('dsm','adm_delete_symptom','First',$stream=null,$params=array('page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_delete_symptom','&lt',$stream=null,$params=array('page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_delete_symptom',($i+1),$stream=null,$params=array('page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_delete_symptom','&gt',$stream=null,$params=array('page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_delete_symptom','Last',$stream=null,$params=array('page'=>($page_count-1)),$text_opts='');
    }
    
    echo "<br><br>";
    shn_acl_secure_hyperlink('dsm','adm_default','Go to Admin Page',$stream=null,$params=null,$text_opts='');
   
}

//confirm to delete symptoms
function shn_dsm_adm_delete_symptom_confirm(){
	
	echo "<h2>"._t("Confirm to Delete Symptom")."</h2>";

    global $global;
    $db = $global['db'];
    $module = $global['module'];
    $sym_id = $_REQUEST['sym_id'];

    shn_form_fopen('adm_delete_symptom_cr','dsm',$form_opts = array('req_message'=>false));
    shn_form_hidden(array('sym_id'=>$sym_id));
	shn_form_fsopen('Symptom');
	
	$symptom_query = "SELECT sym_id,description FROM dsm_symptoms WHERE sym_id=?";
    $res = $db->Execute($symptom_query,array($sym_id));
    //$sym_id=$res->fields["sym_id"];
    $description = $res->fields['description'];
    echo "<p>"._t("Are you sure you need to delete this symptom <br/> <br/><em>Note that symptom will be deleted permanently!</em>")."</p><br/>";
    echo "<ul>";
        echo "<div> Description : ".$description."</div>";
    echo "</ul>";

    shn_form_fsclose();
    
    shn_form_submit(_t("Cancel"),'name="cancel"');
    shn_form_submit(_t("Delete"),'name="delete"');
    shn_form_fclose();
}

//delete symptom cr
function shn_dsm_adm_delete_symptom_cr(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    $sym_id = $_REQUEST['sym_id'];
   
    if(isset($_REQUEST['cancel'])){
        
        shn_dsm_adm_delete_symptom();
        
    }else{
    	
        $delete_symptom = "DELETE FROM dsm_symptoms WHERE sym_id=?";
        $res_sym_delete = $db->Execute($delete_symptom,array($sym_id));
        
        $delete_diseas_symptom = "DELETE FROM dsm_disease_symptoms WHERE sym_id=?";
        $res_dis_sym_delete = $db->Execute($delete_diseas_symptom,array($sym_id));
                
        shn_dsm_adm_delete_symptom();
    }
}

//delete disease
function shn_dsm_adm_delete_disease(){
    
    echo "<h2>"._t("Delete Disease")."</h2>";

    global $global;
    $db = $global['db'];
    
    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM dsm_diseases";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=10;
        
    $disease_query = "SELECT dis_id,dis_name,med_name,cause,carrier FROM dsm_diseases";
    $disease_res =  $db->SelectLimit($disease_query,$rpp,$page*$rpp);
        
    echo "<table width=\'100%\'>";
    echo "<th>"._t("Disease Name")."</th><th>"._t("Medical Name")."</th><th>"._t("Cause")."</th><th>"._t("Carrier")."</th><th>"._t("Disease Status")."</th>";
    
    while($row=$disease_res->fetchrow()){
        $dis_id=$row["dis_id"];
        $dis_name = $row["dis_name"];
        $med_name=$row["med_name"];
        $cause = $row["cause"];
        $carrier=$row["carrier"];
        
        echo "<tr>";
        echo "<td>".$dis_name."</td>";
        echo "<td>".$med_name."</td>";
        echo "<td>".$cause."</td>";
        echo "<td>".$carrier."</td>";
        echo "<td>";
        shn_acl_secure_hyperlink('dsm','adm_delete_disease_confirm','Delete',$stream=null,$params=array('dis_id'=>$dis_id,'dis_name'=>$dis_name),$text_opts='');
        echo "</td>";
        echo "<tr>";
    }
    echo "</table>";   
    echo "<br";

    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
 if($page>0){
        shn_acl_secure_hyperlink('dsm','adm_delete_disease','First',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_delete_disease','&lt',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_delete_disease',($i+1),$stream=null,$params=array('dis_id'=>$dis_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_delete_disease','&gt',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_delete_disease','Last',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>($page_count-1)),$text_opts='');
    }
    
     echo "<br><br>";
     shn_acl_secure_hyperlink('dsm','adm_disease_definitions','Admin Home',$stream=null,$params=null,$text_opts='');
    
}    

//delete disease confirm 
function shn_dsm_adm_delete_disease_confirm(){
	
	echo "<h2>"._t("Confirm to Delete Disease")."</h2>";
	
	global $global;
    $db = $global['db'];
    $module = $global['module'];
    $dis_id = $_REQUEST['dis_id'];
    $dis_name = $_REQUEST['dis_name'];
        
    shn_form_fopen('adm_delete_disease_cr','dsm',$form_opts = array('req_message'=>false));
    shn_form_hidden(array('dis_id'=>$dis_id));
    
	echo "<p>"._t("Are you sure you need to delete the disease&nbsp;:&nbsp;<strong>".$dis_name."</strong>?. <br/> <br/><em>Note that all information of disease and all data of disease will be deleted!</em>")."</p><br/>";
	
    shn_form_fsclose();
    
    shn_form_submit(_t("Cancel"),'name="cancel"');
    shn_form_submit(_t("Delete"),'name="delete"');

    shn_form_fclose();
}

//delete disease cr
function shn_dsm_adm_delete_disease_cr(){
    global $global;
    $db = $global['db'];

    if(isset($_REQUEST['cancel'])){
        shn_dsm_adm_delete_disease();
    }else{

        $module = $global['module'];
        $disease_id = $_REQUEST['dis_id'];
        
        $delete_case_data = "DELETE FROM dsm_case_data WHERE dis_id=?";
        $res_delete=$db->Execute($delete_case_data,array($disease_id));

        $delete_case_note = "DELETE FROM dsm_case_note WHERE dis_id=?";
        $res_delete2=$db->Execute($delete_case_note,array($disease_id));
        
        $delete_case_count = "DELETE FROM dsm_case_count WHERE dis_id=?";
        $res_delete3=$db->Execute($delete_case_count,array($disease_id));
        
        $delete_diseas_symptom = "DELETE FROM dsm_disease_symptoms WHERE dis_id=?";
        $res_dis_sym_delete = $db->Execute($delete_diseas_symptom,array($disease_id));

        $query_delete_disease = "DELETE FROM dsm_diseases WHERE dis_id=?";
        $res_delete_disease=$db->Execute($query_delete_disease,array($disease_id));
        
        $query_delete_disease_risks = "DELETE FROM dsm_diseases_risks WHERE dis_id=?";
        $res_delete_disease_risks=$db->Execute($query_delete_disease_risks,array($disease_id));
        
        $query1 = $db->Prepare('SELECT field_id FROM dsm_definitions WHERE dis_id=?');
        $res1=$db->Execute($query1,array($disease_id));

        foreach($res1 as $row){
            $field_id=$row["field_id"];

            $query1 = "DELETE FROM dsm_fields WHERE field_id=?";
            $res1 = $db->Execute($query1,array($field_id));

            $query2 = "DELETE FROM dsm_field_values WHERE field_id=?";
            $res2 = $db->Execute($query2,array($field_id));

            $query3 = "DELETE FROM dsm_field_params WHERE field_id=?";
            $res3 = $db->Execute($query3,array($field_id));

            $query4 = "DELETE FROM dsm_field_validation WHERE field_id=?";
            $res4 = $db->Execute($query4,array($field_id));

            $query5 = "DELETE FROM dsm_definitions WHERE field_id=?";
            $res5 = $db->Execute($query5,array($field_id));

        }
        shn_dsm_adm_delete_disease();
    }
}

//view diseas for delete cases
function shn_dsm_adm_view_disease_for_delete_case(){
    echo "<h2>"._t("View Disease for Delete Case")."</h2>";
    global $global;
    $db = $global['db'];

    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM dsm_diseases";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=10;

    $note_query = "SELECT dis_id, dis_name,med_name FROM dsm_diseases ";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table>";
    echo "<tr><th>"._t("Disease")."</th><th>&nbsp;</th></tr>";
    while($row=$rs->FetchRow()){
        $dis_id=$row["dis_id"];
        $dis_name = $row["dis_name"];
        //echo "<li><div>".$row['dis_id']."</div></li>";
        echo "<tr><td>".$row['dis_name'].((strlen(trim($row['med_name']))==0)?"":(" (".$row['med_name'].")"))."</td>";
        echo "<td>";
        shn_acl_secure_hyperlink('dsm','adm_view_disease_cases_for_delete_case','View cases of Disease',$stream=null,$params=array('dis_id'=>$dis_id),$text_opts='');
        echo "</td></tr>";
    }
    echo "</table>";
    echo "<br>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('dsm','adm_view_disease_for_delete_case','First',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_view_disease_for_delete_case','&lt',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_view_disease_for_delete_case',($i+1),$stream=null,$params=array('dis_id'=>$dis_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_view_disease_for_delete_case','&gt',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_view_disease_for_delete_case','Last',$stream=null,$params=array('dis_id'=>$dis_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    echo "<br><br>";
    shn_acl_secure_hyperlink('dsm','adm_disease_definitions','Go Back Admin Page',$stream=null,$params=null,$text_opts='');
    
}

//view cases for delete cases
function shn_dsm_adm_view_disease_cases_for_delete_case(){
    echo "<h2>"._t("View Cases to Delete")."</h2>";
    global $global;
    $db = $global['db'];
    $dis_id=$_REQUEST['dis_id'];

    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM dsm_case_count";
    $rs = $db->Execute($q);
    $count=$rs->fields['c'];
    $rpp=10;

    $note_query = "SELECT case_id FROM dsm_case_count WHERE dis_id='$dis_id'";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
    echo "<table>";
    echo "<th> Case ID </th>";
    echo "<th> </th>";

    while($row=$rs->FetchRow()){
        $case_id=$res1->fields["case_id"];
    //echo "<li><div>".$row['case_id']."</div></li>";
        echo "<tr><td>".$row['case_id']."</td><td>";
        shn_acl_secure_hyperlink('dsm','adm_view_individual_case_for_delete_case','View Case to Delete',$stream=null,$params=array('case_id'=>$row['case_id'],'dis_id'=>$dis_id),$text_opts='');
        echo "</td></tr>";
    }
    echo "</table>";
    echo "<br>";

    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
    if($page>0){
        shn_acl_secure_hyperlink('dsm','adm_view_disease_cases_for_delete_case','First',$stream=null,$params=array('case_id'=>$row['case_id'],'dis_id'=>$dis_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_view_disease_cases_for_delete_case','&lt',$stream=null,$params=array('case_id'=>$row['case_id'],'dis_id'=>$dis_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_view_disease_cases_for_delete_case',($i+1),$stream=null,$params=array('case_id'=>$row['case_id'],'dis_id'=>$dis_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_view_disease_cases_for_delete_case','&gt',$stream=null,$params=array('case_id'=>$row['case_id'],'dis_id'=>$dis_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_view_disease_cases_for_delete_case','Last',$stream=null,$params=array('case_id'=>$row['case_id'],'dis_id'=>$dis_id,'page'=>($page_count-1)),$text_opts='');
    }

        echo "<br><br>";
        shn_acl_secure_hyperlink('dsm','adm_view_disease_for_delete_case','Go Back',$stream=null,$params=null,$text_opts='');
       
}

//view individual case
function shn_dsm_adm_view_individual_case_for_delete_case(){
    echo "<h2>"._t("Case Information")."</h2>";
    global $global;
    $db = $global['db'];
    $case_id=$_REQUEST['case_id'];
    $dis_id=$_REQUEST['dis_id'];

    echo "<p>"._t("Are you sure you need to delete this case, <strong> Case Id :&nbsp;".$case_id."</strong>?. <br/> <br/><em>Note that all information of this case and all note of case will be deleted!</em>")."</p><br/>";
    
    shn_form_fopen('adm_delete_case','dsm',$form_opts);
    shn_form_hidden(array('case_id'=>$case_id,'shn_dsm_note'=>$shn_dsm_note,'dis_id'=>$dis_id));
    shn_form_fsopen(_t("Case Information"));

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

        if ($type=="text" || $type=="textarea" || $type=="date" || $type=="dropdown"){
            echo "<tr><td>".$text."</td><td>".$value[0]."</td></tr>";
        }
        
        else if($type=='radio'){
            echo "<tr><td>".$text."</td><td>".$val_text[0]."</td></tr>";
            
        }
        else if($type=="check"){
            
            echo "<tr><td>".$text."</td><td><ul>";
            
            foreach($val_text as $value){
                echo "<li>".$value."</li>";
            }

            
            echo "</ul></td></tr>";

        }
    }
    echo "</table>";
    
    shn_form_fsclose();

    shn_form_fsopen(_t("Notes"));

    $page=0;
    if(isset($_REQUEST['page'])){
        $page=$_REQUEST['page'];

    }
    $q="SELECT COUNT(*) AS c FROM dsm_case_note WHERE case_id=?";
    $rs = $db->Execute($q,array($case_id));
    $count=$rs->fields['c'];
    $rpp=2;

    $note_query = "SELECT note_id,date,note FROM dsm_case_note WHERE case_id=? ORDER BY note_id DESC";
    $rs = $db->SelectLimit($note_query,$rpp,$page*$rpp,array($case_id));
    echo "<ul>";
    while($row=$rs->FetchRow()){
    	echo "<li><div> Note ID : ".$row['note_id']."</div></li>";
        echo "<li><div> Date : ".$row['date']."</div></li>";
        echo "<div>".$row['note']."</div><br>";
        shn_acl_secure_hyperlink('dsm','adm_delete_case_note','Delete Note',$stream=null,$params=array('case_id'=>$case_id,'note_id'=>$row['note_id']),$text_opts='');
        //echo "<a href=index.php?mod=dsm&act=adm_delete_case_note&note_id=".$row['note_id']."&case_id=$case_id>"._t("Delete Note")."</a>
        echo "<br><br>";
    }
    echo "</ul>";
    $page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);

    if($page>0){
        shn_acl_secure_hyperlink('dsm','adm_view_individual_case_for_delete_case','First',$stream=null,$params=array('case_id'=>$case_id,'dis_id'=>$dis_id,'page'=>0),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_view_individual_case_for_delete_case','&lt',$stream=null,$params=array('case_id'=>$case_id,'dis_id'=>$dis_id,'page'=>($page-1)),$text_opts='');
    }
    for($i=0;$i<$page_count;$i++){
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_view_individual_case_for_delete_case',($i+1),$stream=null,$params=array('case_id'=>$case_id,'dis_id'=>$dis_id,'page'=>$i),$text_opts='');
        echo "&nbsp";
    }
    if($page<($page_count-1)){
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_view_individual_case_for_delete_case','&gt',$stream=null,$params=array('case_id'=>$case_id,'dis_id'=>$dis_id,'page'=>($page+1)),$text_opts='');
        echo "&nbsp";
        shn_acl_secure_hyperlink('dsm','adm_view_individual_case_for_delete_case','Last',$stream=null,$params=array('case_id'=>$case_id,'dis_id'=>$dis_id,'page'=>($page_count-1)),$text_opts='');
    }
    
    shn_form_fsclose();
      
    shn_form_submit(_t("Delete Case"),'name="delete_case"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    shn_form_fclose();
    echo "<br><br>";
    shn_acl_secure_hyperlink('dsm','adm_view_disease_cases_for_delete_case','Go Back',$stream=null,$params=array('dis_id'=>$dis_id),$text_opts='');
    
}    

//delete note
function shn_dsm_adm_delete_case(){
	global $global;
    $db = $global['db'];

    if(isset($_REQUEST['cancel'])){
    	
        shn_dsm_adm_view_disease_cases_for_delete_case();
        
    }else{

        $module = $global['module'];
        $case_id = $_REQUEST['case_id'];

        $delete_case_data = "DELETE FROM dsm_case_data WHERE case_id=?";
        $res_delete=$db->Execute($delete_case_data,array($case_id));

        $delete_case_note = "DELETE FROM dsm_case_note WHERE case_id=?";
        $res_delete2=$db->Execute($delete_case_note,array($case_id));
        
        $delete_case_count = "DELETE FROM dsm_case_count WHERE case_id=?";
        $res_delete3=$db->Execute($delete_case_count,array($case_id));
        
        shn_dsm_adm_view_disease_cases_for_delete_case();
    }
}

//delete note
function shn_dsm_adm_delete_case_note(){
	echo "<h2>"._t("Note")."</h2>";
    global $global;
    $db = $global['db'];
    $note_id=$_REQUEST['note_id'];
    $case_id=$_REQUEST['case_id'];
    
    echo "<p>"._t("Are you sure you need to delete this note, <strong> Note Id :&nbsp;".$note_id."</strong>?. <br/> <br/><em>Note that this note will be deleted permanently!</em>")."</p><br/>";
    
    shn_form_fopen('adm_delete_case_note_cr','dsm','');
    shn_form_hidden(array('case_id'=>$case_id,'note_id'=>$note_id));
    shn_form_fsopen(_t("Note"));
    
        $note = "SELECT note_id,date,note FROM dsm_case_note WHERE note_id=?";
        $res1 = $db->Execute($note,array($note_id));
        $date=$res1->fields["date"];
        $note=$res1->fields["note"];
        echo "<ul>";
        echo "<li><div> Note ID : ".$note_id."</div></li>";
        echo "<li><div> Date : ".$date."</div></li>";
        echo "<div>".$note."</div><br>";
        echo "</ul>";
    
    shn_form_fsclose();
    
    shn_form_submit(_t("Delete"),'name="delete_note"');
    shn_form_submit(_t("Cancel"),'name="cancel"');
    shn_form_fclose();
}

//delete note cr
function shn_dsm_adm_delete_case_note_cr(){
    global $global;
    $db = $global['db'];
    $module = $global['module'];
    $case_id = $_REQUEST['case_id'];
   
    if(isset($_REQUEST['cancel'])){
        
        shn_dsm_adm_view_individual_case_for_delete_case($case_id);
        
    }else{

        $note_id = $_REQUEST['note_id'];

        $delete_case_note = "DELETE FROM dsm_case_note WHERE note_id=";
        $res_delete2=$db->Execute($delete_case_note,array($note_id));
                
       shn_dsm_adm_view_individual_case_for_delete_case($case_id);
    }
	
}
//admin home page link
function shn_dsm_adm_disease_definitions(){
	
	shn_dsm_adminmenu();
	echo "<br>";
	echo "<h2>"._t('Disease Definition Manager')."</h2>";
	echo _t('<p>Welcome to the disease definitions manager. In this area you can add, edit and delete disease definitions.</p>
	        <p>New disease definitions are useful to generate custom data collection forms inorder to gather survillence on specific diseases</p>');
	echo "<br/><ul>";
	echo "<h4>"._('Use the following links to add and view disease definitions').'</h4>';
	echo "<li>";
	shn_acl_secure_hyperlink('dsm','adm_delete_disease','Delete Disease',$stream=null,$params=null,$text_opts='');
	echo "</li>";
	echo "<li>";
	shn_acl_secure_hyperlink('dsm','add_definition','Delete Disease Definition',$stream=null,$params=null,$text_opts='');
	echo "</li>";
	echo "<li>";
	shn_acl_secure_hyperlink('dsm','add_definition','Edit Disease Definitions',$stream=null,$params=null,$text_opts='');
	echo "</li>";
	echo "<li>";
	shn_acl_secure_hyperlink('dsm','adm_view_disease_for_delete_case','Delete Case',$stream=null,$params=null,$text_opts='');
	echo "</li>";
}
?>


