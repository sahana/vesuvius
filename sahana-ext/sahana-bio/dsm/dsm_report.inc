<?php 
/**Reports of the Disease Surviellance Module 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Hayesha Somarathne <hayeshais@gmail.com>
             
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage dsm
*/

global $global;
include_once $global['approot'] . "/inc/lib_location.inc";



function _shn_dsm_weekly_report_of_communicable_diseases() { 

?>
 <h3 align="center"><?php print _t("Cases notified during the week"); ?></h3>
<br />
<div id="result">

    <?php
	
    	global $global;
    	$db = $global["db"];

    	$sql_B = "SELECT disease_name FROM rtbs_disease WHERE disease_type='B';";
    	$rtbs_disease_name_B = $db->Execute($sql_B);
		
		$disease_name_B = array();
		$B_counter = 0;
		while (!$rtbs_disease_name_B == NULL && !$rtbs_disease_name_B->EOF) {
		    $disease_name_B[$B_counter] = $rtbs_disease_name_B->fields["disease_name"]; 
			$B_counter++;
			$rtbs_disease_name_B->MoveNext();
		}

    ?>
    
    <table>  
    <thead>
    <tr>
    	<td rowspan="2"><?=_t("PHI Area") ?></td>
		<td colspan="3"><?=_t("Internationally Notifyable Diseases") ?></td>
		<?php
			foreach ($disease_name_B as $i => $value) {
				echo '<td rowspan="2">'; print ($disease_name_B[$i]);  echo '</td>';	
			}
		?>   
            
    </tr>
	
	<?php 
	
    	$sql_A = "SELECT disease_name FROM rtbs_disease WHERE disease_type='A';";
    	$rtbs_disease_name_A = $db->Execute($sql_A);
		
		$disease_name_A = array();
		$A_counter = 0;
		while (!$rtbs_disease_name_A == NULL && !$rtbs_disease_name_A->EOF) {
		    $disease_name_A[$A_counter] = $rtbs_disease_name_A->fields["disease_name"]; 
			$A_counter++;
			$rtbs_disease_name_A->MoveNext();
		}
	
	$disease_A_B = array();
	$disease_A_B += $disease_name_A;
	$disease_A_B += $disease_name_B;

	?>
	
    <tr>
		<?php
			foreach ($disease_name_A as $i => $value) {
				echo '<td>'; print ($disease_name_A[$i]);  echo '</td>';	
			}
		?>	
    </tr>
    </thead>
    <tbody>
	<?php

	$phi_area = array();
	$phi_area = _shn_dsm_list_phi_area();
	  for ($a = 0; $a < count($phi_area); $a++) {
		echo '<tr>';
		echo '<td>'.$phi_area[$a].'</td>'; 
		for ($b = 0; $b < count($disease_A_B); $b++) {  
			echo '<td>'._shn_dsm_weekly_disease_count($disease_A_B[$b]).'</td>'; 
		}
	    	echo '</tr>';
	  }	
	
	?>
 
 	<tr>
 	 <td colspan="26"><h3 align="center"><?php print _t("Weekly Summary"); ?></h3></td>
 	</tr>
 	
	<?php
	  $a = 0;
	  $case_description = array("New cases notified during the week", "Cases notified earlier and awaiting investigation at beginning of the week", "Cases decided as untraceable during the week", "Cases decided as belonging to other MOH areas during the week", "Cases confirmed as a non-notifiable disease during the week", "Cases confirmed as a notifiable disease during the week", "Cases awaiting investigation at the end of weeks");
	  
	  while ( $a < count($case_description) ) { 
	    echo '<tr>';
	    echo '<td>'.$case_description[$a].'</td>'; 
		if ($a == 0) {
			for ( $count = 0; $count < count($disease_A_B); $count++) {
				echo '<td>'.shn_dsm_cases_notified_during_the_week($disease_A_B[$count]).'</td>';
			}
		}
		if ($a == 1) {
			for ( $count = 0; $count < count($disease_A_B); $count++) {
				echo '<td>'.notified_awaiting_investigation_beginning_the_week($disease_A_B[$count]).'</td>';
			}
		}
		if ($a == 2) {
			for ( $count = 0; $count < count($disease_A_B); $count++) {
				echo '<td>'.decided_untraceable_during_the_week($disease_A_B[$count]).'</td>';
			}
		}
		if ($a == 3) {
			for ( $count = 0; $count < count($disease_A_B); $count++) {
				echo '<td>'.decided_belonging_to_other_MOH_areas_during_the_week($disease_A_B[$count]).'</td>';
			}
		}
		if ($a == 4) {
			for ( $count = 0; $count < count($disease_A_B); $count++) {
				echo '<td>'.confirmed_non_notifiable_disease_during_the_week($disease_A_B[$count]).'</td>';
			}
		}
		if ($a == 5) {
			for ( $count = 0; $count < count($disease_A_B); $count++) {
				echo '<td>'.confirmed_notifiable_disease_during_the_week($disease_A_B[$count]).'</td>';
			}
		}
		if ($a == 6) {
			for ( $count = 0; $count < count($disease_A_B); $count++) {
				echo '<td>'.awaiting_investigation_at_the_end_of_weeks($disease_A_B[$count]).'</td>';
			}
		} 
	    echo '</tr>';
	    $a++;
	  }
	?>  
     </tbody>
    </table>
</div>

<?php
}


function _shn_dsm_weekly_disease_count($disease) {
	global $global;
	$db = $global["db"];
	$count = 0; $date = 0;
		
		$date = _shn_dsm_get_date();
		echo $date;
		$sql_disease_count = "SELECT COUNT(disease_id) AS count FROM rtbs_h544 WHERE WEEKOFYEAR(CURDATE()) = '".$date."' AND disease_id = (SELECT disease_id FROM rtbs_disease WHERE disease_name = '".$disease."')"; 
		$res = $db->Execute($sql_disease_count);
		while(!$res == NULL && !$res->EOF) {
			$count = $res->fields['count'];
			$res->MoveNext();
		}		
 return $count;
}

function _shn_dsm_get_date() {
    	global $global;
    	$db = $global["db"];
	$date = null;
		
	$sql= "SELECT DISTINCT WEEKOFYEAR(date) AS day FROM rtbs_h544 WHERE WEEKOFYEAR(CURDATE())";
	$sql_date = $db->Execute($sql);

		$date = $sql_date->fields['day'];

 return $date;
}

function _shn_dsm_list_phi_area() {
    	global $global;
    	$db = $global["db"];

	$phi_area = array();
		
	$sql_phi_area = "SELECT * FROM rtbs_location WHERE district_id = (SELECT district_id FROM sahana_bio_rbts_district WHERE district_id ='".$_POST['district']."')";
	$res_phi = $db->Execute($sql_phi_area);

        $count = 0;
	while(!$res_phi == NULL && !$res_phi->EOF) {
		$phi_area[$count] = $res_phi->fields['phi_area'];
		$count++;
		$res_phi->MoveNext();
       	}

 return $phi_area;	
}


function _shn_dsm_get_province() {
    	global $global;
    	$db = $global["db"];
		$province = array();
		
		$sql_province = "SELECT state FROM rtbs_location";
		$res_province = $db->Execute($sql_province);
		while(!$res_province == NULL && !$res_province->EOF){
			$province[$depth] = $res_province->fields['province'];
			$depth++;
			$res_province->MoveNext();
		}
 return $province;
}


function _shn_dsm_get_district() {
    	global $global;
    	$db = $global["db"];
		
		$sql_district = "SELECT district FROM sahana_bio_rbts_district";
		$res = $db->Execute($sql_district);
		$district = array();
		$depth = 1;
		$district[0] = '';
		while(!$res == NULL && !$res->EOF){
			$district[$depth] = $res->fields['district'];
			$depth++;
			$res->MoveNext();
		}
 return $district;
}

function _shn_dsm_get_moh_area() {
    	global $global;
    	$db = $global["db"];
		
		$sql_moh_area = "SELECT moh_area FROM rtbs_location";
		$res = $db->Execute($sql_moh_area);
		$moh_area = array();
		$depth = 1;
		$moh_area[0] = '';
		while(!$res == NULL && !$res->EOF){
			$moh_area[$depth] = $res->fields['moh_area'];
			$depth++;
			$res->MoveNext();
		}
 return $moh_area;
}


function _shn_dsm_get_rdhs_div() {
    	global $global;
    	$db = $global["db"];
		$rdhs_div = array();
		
		$sql_rdhs_div = "SELECT rdhs_div FROM rtbs_location";
		$res = $db->Execute($sql_rdhs_div);
		while(!$res == NULL && !$res->EOF){
			$rdhs_div[$depth] = $res->fields['rdhs_div'];
			$depth++;
			$res->MoveNext();
		}
 return $rdhs_div;
}




function _shn_dsm_header_validate()
{
//     if($_POST['province'] <= 0 ){
//         add_error('Selecting the Province is required');
//         return false;
//     }
    if ($_POST['district'] <= 0 ){
        add_error('Selecting the District is required');
        return false;
    }
/*    if($_POST['moh_area'] <= 0 ){
        add_error('Selecting the M.O.H. Area');
        return false;
    }
    if ($_POST['rdhs_div'] <= 0){
        add_error('Selecting R.D.H.S. Div');
        return false;
    }*/	

    return true;
}



function shn_dsm_cases_notified_during_the_week($disease) {
	global $global;
	$db = $global["db"];
	$count = 0; $date = 0;
		
		$date = _shn_dsm_get_date();
		$sql = "SELECT COUNT(disease_id) AS count FROM rtbs_h544 WHERE WEEKOFYEAR(CURDATE()) = ".$date." AND disease_id = (SELECT disease_id FROM rtbs_disease WHERE disease_name = '".$disease."')"; 
		$res = $db->Execute($sql);
		while(!$res == NULL && !$res->EOF) {
			$count = $res->fields['count'];
			$res->MoveNext();
		}		
 return $count;
}


function notified_awaiting_investigation_beginning_the_week($disease) { 
	global $global;
	$db = $global["db"];
	$count = 0; $date = 0;
		
		$date = _shn_dsm_get_date();
		$date -= 1;
		$sql = "SELECT COUNT(disease_id) AS count FROM rtbs_h544 WHERE WEEKOFYEAR(CURDATE()) < ".$date." AND disease_id = (SELECT disease_id FROM rtbs_disease WHERE disease_name = '".$disease."') AND investigated = 0"; 
		$res = $db->Execute($sql);
		while(!$res == NULL && !$res->EOF) {
			$count = $res->fields['count'];
			$res->MoveNext();
		}		
 return $count;
}


function decided_untraceable_during_the_week($disease) { 
	global $global;
	$db = $global["db"];
	$count = 0; $date = 0;
		
		$date = _shn_dsm_get_date();
		$sql = "SELECT COUNT(disease_id) AS count FROM rtbs_h544 WHERE WEEKOFYEAR(CURDATE()) = ".$data." AND disease_id = (SELECT disease_id FROM rtbs_disease WHERE disease_name = '".$disease."') AND investigated = 0 AND WEEKOFYEAR(CURDATE()) <= WEEKOFYEAR(date_of_admission)"; 
		$res = $db->Execute($sql);
		while(!$res == NULL && !$res->EOF) {
			$count = $res->fields['count'];
			$res->MoveNext();
		}		
 return $count;
}


function decided_belonging_to_other_MOH_areas_during_the_week($disease) { 
	global $global;
	$db = $global["db"];
	$count = 0; $date = 0;
		
		$date = _shn_dsm_get_date();
		$sql = "SELECT COUNT(disease_id) AS count FROM rtbs_h544 WHERE WEEKOFYEAR(CURDATE()) = ".$date." AND disease_id = (SELECT disease_id FROM rtbs_disease WHERE disease_name = '".$disease."') AND notify_id = (SELECT DISTINCT notify_id FROM rtbs_location WHERE moh_area = 'Molpe')"; 
		$res = $db->Execute($sql);
		while(!$res == NULL && !$res->EOF) {
			$count = $res->fields['count'];
			$res->MoveNext();
		}		
 return $count;
}

function confirmed_non_notifiable_disease_during_the_week($disease) { 
	global $global;
	$db = $global["db"];
	$count = 0; $date = 0;
		
		$date = _shn_dsm_get_date();
		$sql = "SELECT COUNT(disease_id) AS count FROM rtbs_h544 WHERE WEEKOFYEAR(CURDATE()) = ".$date." AND disease_id = (SELECT disease_id FROM rtbs_disease WHERE disease_name = '".$disease."') AND investigated = 1 AND notifalble = 0"; 
		$res = $db->Execute($sql);
		while(!$res == NULL && !$res->EOF) {
			$count = $res->fields['count'];
			$res->MoveNext();
		}		
 return $count;
}


function confirmed_notifiable_disease_during_the_week($disease) { 
	global $global;
	$db = $global["db"];
	$count = 0; $date = 0;
		
		$date = _shn_dsm_get_date();
		$sql = "SELECT COUNT(disease_id) AS count FROM rtbs_h544 WHERE WEEKOFYEAR(CURDATE()) = ".$date." AND disease_id = (SELECT disease_id FROM rtbs_disease WHERE disease_name = '".$disease."') AND investigated = 1 AND notifalble = 1"; 
		$res = $db->Execute($sql);
		while(!$res == NULL && !$res->EOF) {
			$count = $res->fields['count'];
			$res->MoveNext();
		}		
 return $count;
}

function awaiting_investigation_at_the_end_of_weeks($disease) { 
	global $global;
	$db = $global["db"];
	$count = 0; $date = 0;
		
		$date = _shn_dsm_get_date();
		$sql = "SELECT COUNT(disease_id) AS count FROM rtbs_h544 WHERE WEEKOFYEAR(CURDATE()) = ".$date." AND disease_id = (SELECT disease_id FROM rtbs_disease WHERE disease_name = '".$disease."') AND investigated = 0"; 
		$res = $db->Execute($sql);
		while(!$res == NULL && !$res->EOF) {
			$count = $res->fields['count'];
			$res->MoveNext();
		}		
 return $count;
}

?>