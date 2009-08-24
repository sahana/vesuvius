<?php
/**
 * The Sahana Resquest Management System
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author       Sudheera R. Fernando <sudheera@opensource.lk>
 * @copyright    Lanka Software Foundation - http://www.opensource.lk
 * @package      sahana
 * @subpackage   rms
 * @tutorial
 * @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General
 * Public License (LGPL)
 */

_shn_rms_print_hedder(_t("Search for Pledges"));

function _shn_rms_sch_getkeywords()
{
	$donor_name=array();
	$donor_name = _shn_rms_get_donors();
	if($donor_name!=null) {
		$donor_name=array_reverse($donor_name,TRUE);
		array_push($donor_name,'All');
		$donor_name=array_reverse($donor_name,TRUE);
		//-----------------------------------------------
		$categories = array();
		$cat_arr = _shn_rms_get_categories();
		array_push($categories, 'All');
		foreach ($cat_arr as $cat) {
			$categories[$cat['ct_uuid']] = $cat['name'];
		}
		//---------------------------------------------------------------------------------
		$status = array();
		$status['all'] = _t("All");
		$status['not confirmed'] = _t("Not Confirmed");
		$status['confirmed'] = _t("Confirmed");

		$status['delivered'] = _t("Delivered");
		$status['discarded'] = _t("Discarded");
		//-----------------------------------------------------------------------------------
		$date=array();
		//---------------------------------------------------------------------------------
		shn_form_fopen("plg_sch",null,array('req_message'=>false));
		shn_form_fsopen("Select Criteria");
		shn_form_hidden(array('seq'=>'get_keywords'));
		if($_SESSION['isadmin']==true || !shn_acl_is_enabled()) {
			shn_form_select($donor_name, _t("Donor"), 'donor_id',null,array('br'=>false));
			//shn_form_select($donor_name, _t("Donor"), 'donor_id',null,($donor_name['All']=='All')?array('br'=>false,'value'=>'All'):array('br'=>false,'value'=>''));
			print '<br/>';
			print '<br/>';
		}
		shn_form_select($categories, _t("Category"), 'category', null ,array('br'=>false));
		print '<br/>';
		print '<br/>';
		shn_form_select($status, _t("Status"), 'status', null,array('br'=>false));
		print '<br/>';
		print '<br/>';
		//shn_form_text(_t("Search Keywords"),'keywords',null,array('br'=>false,'value'=>''));
		shn_form_fsclose();
		shn_form_submit(_t("Search"));

		shn_form_fclose();
	}else {
		add_warning(_t("No pledges found"));
	}
}

function _shn_rms_shn_get_results()
{
	 
	global $global;
	$db = $global['db'];
	$paging = false;
	
	$dnid=$_SESSION['rms_plg_sch']['donor_id'];
	$ctgr=$_SESSION['rms_plg_sch']['category'];
	$stts=$_SESSION['rms_plg_sch']['status'];

	$cat_qry = "SELECT serial FROM ct_catalogue WHERE ct_uuid='".$_SESSION['rms_plg_sch']['category']."'";
	//var_dump($cat_qry);
	$res1 = $db->Execute($cat_qry);
	$res1->MoveFirst();

	$cat_serial = $res1->Fields('serial');

	$cat_qry2 = "SELECT ct.ct_uuid,rpm.status,rpm.inventory,rpm.quantity,plg.donor_uuid,plg.plg_date FROM ct_catalogue as ct
                 JOIN rms_plg_item as rpm ON rpm.item_uuid = ct.ct_uuid 
                 JOIN rms_pledge as plg ON plg.plg_uuid=rpm.plg_uuid
                 WHERE ct.final_flag = '1' AND ct.serial LIKE '".$cat_serial."%' ";
	
	if($_SESSION['isadmin']==true || !shn_acl_is_enabled()) {
	    if (_shn_rms_is_user($dnid)) {
		    $cat_qry2 .= " AND plg.donor_uuid='".$dnid."'";
	    }
	}else {
		$dnid = $_SESSION['user_id'];
		$cat_qry2 .= " AND plg.donor_uuid='".$dnid."'";
	}
    if($stts != 'all') {
    	$cat_qry2 .= "AND rpm.status='$stts' ";
    }
	//$res2 = $db->Execute($cat_qry2);
	global $global;
    include_once $global['approot'] . "/inc/lib_paging.inc";
    $res2=shn_paging_get_report($cat_qry2,'10',$headers,array('post'=>true,'return'=>true));
	return $res2;
	
	
	//--------------Donor----------------------------------
	/*if($_SESSION['isadmin']==true) {
	 if (_shn_rms_is_user($dnid)) {
	 $sql .= "AND donor_uuid='$dnid' ";
	 }else{
	 //if dornor criteria is "All" then clear the session variable
	 }
	 }else {
	 $dnid = $_SESSION['user_id'];
	 $sql .= "AND donor_uuid='$dnid' ";
	 }*/

	//------------Category------------------------------
	//if ($ctgr != null) {
	//	$sql .= "AND ";

		//--------------status---------------------
		/* if($stts != 'all') {
		$sql .= "AND itm.status='$stts' ";
		}*/
	//------------------------------------------------
	//echo $sql;
		/*
		$rs = $global['db']->Execute($sql);

		if ($rs === false)
		{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
		}
		elseif (1 <= $rs->RecordCount())
		{
		$rs = $rs->GetArray();
		 
		foreach ($rs as $r)
		{
		$_SESSION['rms_plg_schres'][$r['plg_uuid']] = $r;
		//var_dump($r);
		}
		}*/
	//=============================================================
	//echo'<PRE>';
	//var_dump($rs);
	//echo'</PRE>';
	 
	 
	//==============paging=========================================

	/*
	 if (!isset($page) || $page == '' || !is_numeric($page))
	 $page = 1;

	 if (!isset($rows) || $rows == '' || !is_numeric($rows))
	 $rows = 10;

	 // create pagnating links
	 $plg_count = _shn_rms_get_recordcount('rms_pledge', $fstr);
	 $page_count = ceil($plg_count/$rows);

	 if (1 < $page_count)
	 {
	 $paging = true;
	 $page_list = _t(":: ");

	 if (1 < $page)
	 {
	 $page_list .= '<a href="index.php?mod=rms&amp;act=plg_ls' .
	 '&amp;page_no=' . ($page - 1) . '"> ' .
	 _t("Previous") . '</a> ';
	 }

	 for ($i = 1; $i <= $page_count; $i++)
	 {
	 if ($page != $i)
	 {
	 $page_list .= ' <a href="index.php?mod=rms&amp;act=plg_ls' .
	 '&amp;page_no=' . $i . '"> <small>' . $i .
	 '</small></a> ';
	 }
	 else
	 {
	 $page_list .= '<small>' . $i . '</small>';
	 }
	 }

	 if ($page_count != $page)
	 $page_list .= '<a href="index.php?mod=rms&amp;act=plg_ls' .
	 '&amp;page_no=' . ($page + 1) . '">' .
	 _t("Next") . '</a>';
	 }

	 //set order-by
	 if ($odr_by != null && $odr_by != '')
	 $sql .= " ORDER BY '$odr_by'";
	 else
	 $sql .= " ORDER BY 'plg_date'";

	 $rs = $db->PageExecute($sql, $rows, $page);
	 //print $sql;
	 $rs_arr = $rs->GetArray();

	 //create the filter list
	 $donors = array();

	 foreach ($rs_arr as $r)
	 {
	 //        $donor = _shn_rms_get_donor($r['donor_uuid']);
	 //        $donors[$r['donor_uuid']] = $donor['name'];
	 $donors = _shn_rms_get_donors();
	 //print_r($donors);
	 }

	 //Result table hedder
	 $th_res[] = array (
	 _t("ID"),
	 _t("Donor"),
	 _t("Date"),
	 _t("status"),
	 ''
	 );

	 foreach ($rs_arr as $r)
	 {
	 $plg_id = $r['plg_uuid'];
	 //$donor_id = $r['donor_uuid'];
	 //print $donor_id;
	 $donor = _shn_rms_get_donor($r['donor_uuid']);
	 //$donor = _shn_rms_get_donor($donor_id);
	 //print $donor;
	 $donor_d = '<strong>' . $donor['name'] . '</strong><br >' .
	 'Contact: <a href="mailto:' . $donor['email'] .'">' . $donor['email'] . '</a> , ' .
	 $donor['mobile'];

	 $plg_date = $r['plg_date'];
	 $plg_stat = $r['status'];
	 $shn_usr = $r['user_id'];

	 $view_url = '<a href=index.php?mod=rms&amp;act=plg_ls' .
	 '&amp;seq=view_plg&amp;plg_id=' . $plg_id .'>' .
	 _t("Details") . '</a>';

	 $tb_res[] = array ($plg_id, $donor_d, $plg_date, $plg_stat, $view_url);
	 }
	 //	global $global;
	 //
	 //    /*$sql = "SELECT distinct(plg_uuid),donor_uuid,full_name,plg_date,status," .
	 //            "contact_value " .
	 //           "FROM " .
	 //                "(SELECT plg.plg_uuid, plg.donor_uuid, plg.plg_date, plg.status, " .
	 //                    "psn.full_name, cnt.contact_value " .
	 //                 "FROM rms_pledge plg, person_uuid psn, contact cnt " .
	 //                 "WHERE plg.donor_uuid=psn.p_uuid " .
	 //                 "AND cnt.pgoc_uuid=psn.p_uuid) tmptbl " .
	 //           "WHERE plg_uuid='$kw' " .
	 //           "OR donor_uuid='$kw' " .
	 //           "OR LOWER(full_name) LIKE LOWER('%$kw%') " .
	 //           "OR LOWER(contact_value) LIKE LOWER('%$kw%')";*/
	//
	//    $sql = "SELECT plg.plg_uuid,plg.donor_uuid,plg.plg_date,plg.status,psn.full_name,cnt.contact_value FROM rms_pledge plg, person_uuid psn,contact cnt WHERE plg.donor_uuid=psn.p_uuid AND plg.donor_uuid=cnt.pgoc_uuid AND (LOWER(psn.full_name) LIKE LOWER('%$kw%') OR plg.donor_uuid LIKE ('%$kw%') OR cnt.contact_value LIKE ('%$kw%'));";
	//
	//    $rs = $global['db']->Execute($sql);
	//    //print $sql;
	//    $rs = $rs->GetArray();
	//
	//    foreach ($rs as $r)
	//    {
	//        $_SESSION['rms_plg_schres'][$r['plg_uuid']] = $r;
	//    }*/
}

function _shn_rms_sch_results()
{

	$_SESSION['rms_plg_schres'] = null;
	$res = _shn_rms_shn_get_results();
	//$results = $_SESSION['rms_plg_schres'];

	$tbl_arr = array();
	$tbl_hd_arr = array();
	
	if (!$res->EOF)
	{
		if($_SESSION['isadmin']==TRUE) {
			$tbl_hd_arr[0] = array (
			_t("Donor"),
			_t("Category"),
			_t("Item"),
			_t("Quantity"),
			_t("Date"),
			_t("status"),
			_t("Inventory")
			     );
		}else {
			$tbl_hd_arr[0] = array (

			_t("Category"),
			_t("Item"),
			_t("Quantity"),
			_t("Date"),
			_t("status"),
			_t("Inventory")
                                 );
		}
		
		$view_url = '<a href=index.php?mod=rms&amp;act=plg_sch' .
                        '&amp;seq=view_plg&amp;plg_id=' . $plg_id .'>' .
			_t("Details") . '</a>';
		$i=0;
		while(!$res->EOF){
			if($_SESSION['isadmin']==TRUE) {
				$_pdata = _shn_rms_get_donor($res->Fields('donor_uuid'));
				$tbl_arr[$i] = array($_pdata['name'],
									_shn_rms_get_cat_name(_shn_rms_get_parent_catalogue($res->Fields('ct_uuid'))),
									_shn_rms_get_cat_name($res->Fields('ct_uuid')),
									$res->Fields('quantity'),
									$res->Fields('plg_date'),
									$res->Fields('status'),
									_shn_rms_get_inventory_name($res->Fields('inventory')));
			}else{
				$tbl_arr[$i] = array(_shn_rms_get_cat_name(_shn_rms_get_parent_catalogue($res->Fields('ct_uuid'))),
									_shn_rms_get_cat_name($res->Fields('ct_uuid')),
									$res->Fields('quantity'),
									$res->Fields('plg_date'),
									$res->Fields('status'),
									_shn_rms_get_inventory_name($res->Fields('inventory')));
			}
			$res->MoveNext();
			$i++;
		}
		print '<br />';
		shn_html_table($tbl_arr, $tbl_hd_arr, null, array('class'=>'wide'));
	}else {
		print '<br />';
		_shn_html_print_alert(_t("There are no results that match your search criteria."));
	}
}


function _shn_rms_get_donors_array()
{
	global $global;
	$db = $global['db'];

	$sql = "SELECT DISTINCT donor_uuid FROM rms_pledge";

	$rec = $db->Execute($sql);
	$donor =array();
	$i = 0;
	if ($rec === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	} elseif (1 <= $rec->RecordCount()){
		While(!$rec->EOF)
		{

			$donor[$i] = $rec->fields['donor_uuid'];
			$rec->MoveNext();
			$i++;
		}

		return $donor;
	}
}

switch ($_REQUEST['seq'])
{
	case '':
		$_SESSION['isadmin'] = _shn_rms_get_user_group();
		_shn_rms_sch_getkeywords();
		break;

	case 'get_keywords':
		 
		$_SESSION['rms_plg_sch']['donor_id'] = $_REQUEST['donor_id'];
		$_SESSION['rms_plg_sch']['category'] = $_REQUEST['category'];
		$_SESSION['rms_plg_sch']['status'] = $_REQUEST['status'];
		_shn_rms_sch_getkeywords();
		_shn_rms_sch_results();
		break;

	case 'view_plg':
		$plg_id = $_REQUEST['plg_id'];
		_shn_rms_view_pledge($plg_id);
		$keywords = $_REQUEST['keywords'];
		print '<br />' .
                  '[ <a href="index.php?mod=rms">' . _t("RMS Home") . '</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;' .
                        'act=plg_sch">' . 
		_t("Back to Pledge Search") . '</a> ]';
		break;
}

?>