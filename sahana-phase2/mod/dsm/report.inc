<?php

/**
 * DSM
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

include_once $global['approot'].'/inc/reporting/lib_chart.inc';
include_once $global['approot'].'/inc/reporting/lib_reporting.inc';
include_once $global['approot'].'/inc/lib_paging.inc';
include_once $global['approot'] . '/mod/dsm/lib_dsm.inc';
include_once $global['approot'].'/inc/lib_location.inc';

function shn_dsm_report_default(){
    shn_dsm_patients_diseases_chart();
    ?><div><?php
	shn_chart_display("shn_dsm_patients_diseases_chart");
	?></div><?php
    shn_dsm_disease_vs_location_chart();
    ?><div><?php
	shn_chart_display("shn_dsm_disease_vs_location_chart");
	?></div><?php
    shn_form_fopen('report','dsm',array('req'=>false));
    
	
	shn_form_fclose();
}

function shn_dsm_patients_diseases_chart()
{
	global $global;
    $sql = "SELECT disease,COUNT(pat_id) AS count FROM diagnosis GROUP BY disease";
    $res = _shn_dsm_execute($sql);
    if($res === false){
       $msg = $global['db']->ErrorMsg();
       add_error($msg);
       display_errors();
       return false;
    }
    else{
    	if ($res->RecordCount() <= 0){
    		add_alert(_t("No Requests are available"));
    		
    	}
    	else{
    		for($i = 0;$i < $res->RecordCount();$i++){
    			add_data(_shn_dsm_get_disease_name($res->fields['disease']), $res->fields['count']);
    			$res->MoveNext();
    		}
    	}
    }
	$keyword_arr = array('chart'=>'pie chart','mod'=>'dsm');	
	generate_piechart("Piechart","No of patients reported","","",$keyword_arr);
}

function shn_dsm_disease_vs_location_chart()
{
	global $global;
    $sql = "SELECT location,COUNT(pat_id) AS count FROM diagnosis WHERE disease='{$_SESSION['disease_id']}' GROUP BY location";
    $res = _shn_dsm_execute($sql);print $sql;
     if($res === false){
       $msg = $global['db']->ErrorMsg();
       add_error($msg);
       display_errors();
       return false;
    }
    else{
    	if ($res->RecordCount() <= 0){
    		add_alert(_t("No Requests are available"));
    		
    	}
    	else{
    		for($i = 0;$i < $res->RecordCount();$i++){
    			add_data(shn_location_string($res->fields['location']), $res->fields['count']);
    			$res->MoveNext();
    		}
    	}
    }
	$keyword_arr = array('chart'=>'pie chart','mod'=>'dsm');	
	generate_piechart("Piechart","No of patients by location","","",$keyword_arr);
    
}
