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

_shn_rms_print_hedder(_("Search for Donors and Pledges"));

function _shn_rms_sch_getkeywords()
{
	$donor_name=array();
    $donor_name = _shn_rms_get_donors();
    $donor_name=array_reverse($donor_name,TRUE);
    array_push($donor_name,'All');
    $donor_name=array_reverse($donor_name,TRUE);
	//-----------------------------------------------
	$categories = array();
    $cat_arr = _shn_rms_get_categories();
    array_push($categories, 'All');
    foreach ($cat_arr as $cat)
      {
        $categories[$cat['ct_uuid']] = $cat['name'];
      }
    //---------------------------------------------------------------------------------
    $status = array();
    $status['all'] = _("All");
    $status['not confirmed'] = _("Not Confirmed");
    $status['confirmed'] = _("Confirmed");
    $status['delivered'] = _("Delivered");
    $status['discarded'] = _("Discarded");
	//-----------------------------------------------------------------------------------
	$date=array();
	
	//---------------------------------------------------------------------------------
    shn_form_fopen("plg_sch",null,array('req_message'=>false));
    shn_form_fsopen("Select Criteria");
    shn_form_hidden(array('seq'=>'get_keywords'));
    if($_SESSION['isadmin']==true) {
        shn_form_select($donor_name, _("Donor"), 'donor_id',null,array('br'=>false));
        print '<br/>';
        print '<br/>';
    }
    shn_form_select($categories, _("Category"), 'category', null ,array('br'=>false));
    print '<br/>';
    print '<br/>';
    shn_form_select($status, _("Status"), 'status', null,array('br'=>false));
    print '<br/>';
    print '<br/>';
    //shn_form_text(_("Search Keywords"),'keywords',null,array('br'=>false,'value'=>''));
    shn_form_fsclose();
    shn_form_submit(_("Search"));
    
    shn_form_fclose();
}

function _shn_rms_shn_get_results()
{
   
    global $global;
    //$db = $global['db'];
    $paging = false;
    $sql = "SELECT * FROM rms_pledge plg,rms_plg_item itm WHERE plg.plg_uuid=itm.plg_uuid ";
    
    $dnid=$_SESSION['rms_plg_sch']['donor_id'];
    $ctgr=$_SESSION['rms_plg_sch']['category'];
    $stts=$_SESSION['rms_plg_sch']['status'];
    
    //--------------Donor----------------------------------    
    if($_SESSION['isadmin']==true) {
        if (_shn_rms_is_user($dnid)) {          
           $sql .= "AND donor_uuid='$dnid' ";
        }else{
        	$_SESSION['rms_plg_sch']['donor_id'];//if dornor criteria is "All" then clear the session variable
        }
    }else {
            $dnid = $_SESSION['user_id'];
    	    $sql .= "AND donor_uuid='$dnid' ";
    }
    
    //------------Category------------------------------
    //if ($ctgr != null) {
    //	$sql .= "AND ";
    
    //--------------status---------------------
    if($stts != 'all') {
    	$sql .= "AND itm.status='$stts' ";
    }
    //------------------------------------------------
	//echo $sql;

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
    }
    
    	
    	
    	
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
        $page_list = _(":: ");
        
        if (1 < $page)
        {
            $page_list .= '<a href="index.php?mod=rms&amp;act=plg_ls' .
                              '&amp;page_no=' . ($page - 1) . '"> ' . 
                              _("Previous") . '</a> ';
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
                              _("Next") . '</a>';
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
                         _("ID"), 
                         _("Donor"), 
                         _("Date"), 
                         _("status"),
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
                    _("Details") . '</a>';
        
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
    _shn_rms_shn_get_results();
    $results = $_SESSION['rms_plg_schres'];
        
    if (!empty($results))
    {
        if($_SESSION['isadmin']==TRUE) {                  
            $th_res[] = array ( 
                                 _("Donor"),
                                 _("Category"), 
                                 _("Date"), 
                                 _("status"),
                                 ''
                                );
        }else {
        	$th_res[] = array ( 
                                
                                 _("Category"), 
                                 _("Date"), 
                                 _("status"),
                                 ''
                                );
        }
        
        $donor_name=array();
        $dnid=$_SESSION['rms_plg_sch']['donor_id'];  
                          
        foreach ($results as $r)
        {
            $plg_id = $r['plg_uuid'];
            
            //----------------------------------------------------
            
            $donor = _shn_rms_get_person($dnid);
            $donor_name = $donor['name'] . '<br />' . $r['contact_value'];
            //----------------------------------------------------------
            $plg_date = $r['plg_date'];
            $plg_stat = $r['status'];
            
            $view_url = '<a href=index.php?mod=rms&amp;act=plg_sch' .
                        '&amp;seq=view_plg&amp;plg_id=' . $plg_id .'>' .
                        _("Details") . '</a>';
            if ($_SESSION['isadmin']==TRUE) {
               $tb_res[] = array ($donor_name,$plg_cat,$plg_date, $plg_stat, $view_url);	
            }else {
              $tb_res[] = array ($plg_cat,$plg_date, $plg_stat, $view_url);	
            }
            
        } 
         
        print '<br />';
        shn_html_table($tb_res, $th_res, null, array('class'=>'wide'));
    }
    else
    {
        print '<br />';
        _shn_html_print_alert(_("There are no results that matches your search criteria"));
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
    	    $_SESSION['rms_plg_sch']['category'] = $_REQUEST['catagery'];
            $_SESSION['rms_plg_sch']['status'] = $_REQUEST['status'];
            _shn_rms_sch_getkeywords();
            _shn_rms_sch_results();
            break;
            
    case 'view_plg':
            $plg_id = $_REQUEST['plg_id'];
            _shn_rms_view_pledge($plg_id);
            $keywords = $_REQUEST['keywords'];
            print '<br />' .
                  '[ <a href="index.php?mod=rms">' . _("RMS Home") . '</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;' .
                        'act=plg_sch">' . 
                        _("Back to Pledge Search") . '</a> ]';
            break;
}

?>
