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
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

_shn_rms_print_hedder(_t("Request Search: Search for Requesters, Locations and Requests"));

function _shn_rms_sch_getkeywords()
{   
//------------------------------------------------------------------
	$reqstr_name=array();
	$reqstr_name = _shn_rms_get_requesters();
    if($reqstr_name!=null) {
	    $reqstr_name=array_reverse($reqstr_name,TRUE);
		array_push($reqstr_name,'All');
		$reqstr_name=array_reverse($reqstr_name,TRUE);
        //-------------------------------------------------------------
		if($_SESSION['isadmin']==true) {
	    	$loc_ids=_shn_rms_get_all_locations();
	    	//echo 'admin';
	    }else { 
		    $loc_ids = _shn_rms_get_location_array($_SESSION['user_id']);
	    }

        $location = array();
        $location[0] = 'All';
        //-----------------------------------------------------
//        foreach($loc_ids as $loc){
//            if(_shn_rms_is_location($loc)) {
//                $bsda_village = _shn_rms_get_location_name($loc);
//            }elseif(_shn_rms_is_camp($loc)) {
//                $bsda_village = _shn_rms_get_camp_name($loc);
//            }elseif(_shn_rms_is_org($loc)) {
//        	    $bsda_village = _shn_rms_get_org_name($loc);
//            }
//            $location[$loc]= $bsda_village;
//        }

        //------------------------------------------------------
        foreach($loc_ids as $loc){
            $location[$loc] =_shn_rms_get_name($loc);
        }
        //------------------------------------------------------------
        $priority = array();
        $pri_arr = array();
        array_push($priority, 'All');
        $pri_arr = _shn_rms_get_priorities(); 
        foreach ($pri_arr as $pri) {
            $priority[$pri['pri_uuid']] = $pri['priority'];
        }
        //------------------------------------------------------------
        $categories = array();
        array_push($categories, 'All');
        $cat_arr = _shn_rms_get_categories();
        foreach ($cat_arr as $cat) {
            $categories[$cat['ct_uuid']] = $cat['name'];
        }
        
        //--------------------------------------------------------------
        $status = array();
        $status['all'] = _t("All");
        $status['open'] = _t("Open");
        $status['closed'] = _t("Closed");
        //----------------------------------------------------------------
	    //shn_html_tr_open();
        //shn_html_td_open();
        //shn_form_fopen("req_sch",null, array('req_message'=>false,'style'=>'form_blank'));
        //shn_form_hidden(array('seq'=>'filter'));
        //shn_form_select($requesters, _t("Requesters"), 'reqstr', 'onChange="submit(this);"',array('br'=>false));
        //shn_form_fclose();
        //shn_html_td_close();
			 
        //shn_html_td_open();
        shn_form_fopen("req_sch",null, array('req_message'=>false,'style'=>'form_blank'));
        shn_form_fsopen("Select Criteria");
        shn_form_hidden(array('seq'=>'get_keywords'));
        
	    if($_SESSION['isadmin']==true) {
			shn_form_select($reqstr_name, _t("Requester"), 'reqstr_id',null,array('br'=>false));
			print '<br/>';
			print '<br/>';
	    }
        shn_form_select($location, _t("Locations"), 'loc_id', null,array('br'=>false));
        print '<br />';
        print '<br />';
		
        shn_form_select($priority,_t("Priority"),'priority',null,array('br'=>false));
        print '<br />';
        print '<br />';
        shn_form_select($categories,_t("Category"),'category',null,array('br'=>false));
        print '<br />';
        print '<br />';
        shn_form_select($status,_t("Status"),'status',null,array('br'=>false));
        shn_form_fsclose();
        //print '<br />';
        // print '<br />';
        shn_form_submit(_t("Search"));
        shn_form_fclose();
        //shn_html_td_close();
      }else{
    	add_warning(_t("No requests found"));
      }
}


function _shn_rms_shn_get_results()
{
global $global;
    
   /* $sql = "SELECT distinct(req_uuid),reqstr_uuid,full_name,req_date,status," .
            "contact_value,location_id,address,postcode " .
           "FROM " .
                "(SELECT req.req_uuid, req.reqstr_uuid, req.req_date, req.status, " .
                    "psn.full_name, cnt.contact_value, loc.location_id, " .
                    "loc.address, loc.postcode, loc.opt_person_loc_type " .
                 "FROM rms_request req, person_uuid psn, contact cnt, " .
                    "location_details loc " .
                 "WHERE req.reqstr_uuid=psn.p_uuid " .
                 "AND cnt.pgoc_uuid=psn.p_uuid " .
                 "AND req.loc_uuid=loc.location_id) tble " .
           "WHERE req_uuid='$kw' " .
           "OR reqstr_uuid='$kw' " .
           "OR LOWER(full_name) LIKE LOWER('%$kw%') " .
           "OR LOWER(location_id) LIKE LOWER('%$kw%') " .
           "OR LOWER(address) LIKE LOWER('%$kw%') " .
           "OR LOWER(contact_value) LIKE LOWER('%$kw%')";*/

//$sql = "SELECT req.req_uuid,req.reqstr_uuid,req.req_date,req.status,psn.full_name,loc.location_id FROM rms_request req, person_uuid psn,location_details loc WHERE req.reqstr_uuid=psn.p_uuid AND (LOWER(psn.full_name) LIKE LOWER('%$kw%') OR loc.address LIKE ('%$kw%'));";

    //$sql = "SELECT req.req_uuid,req.reqstr_uuid,req.req_date,req.status,psn.full_name,loc.loc_uuid FROM rms_request req, person_uuid psn,location_details loc,contact cnt WHERE req.reqstr_uuid=psn.p_uuid AND req.reqstr_uuid=loc.poc_uuid AND (LOWER(psn.full_name) LIKE LOWER('%$kw%') OR req.req_uuid LIKE ('%$kw%') OR loc.address LIKE ('%$kw%') OR loc.location_id LIKE ('%$kw%'));";
    //$sql ="SELECT req.req_uuid,req.reqstr_uuid,req.req_date,req.status,psn.full_name,req.loc_uuid FROM rms_request req, person_uuid psn,location loc,contact cnt WHERE req.reqstr_uuid=psn.p_uuid AND req.loc_uuid=loc.loc_uuid AND (LOWER(psn.full_name) LIKE LOWER('%$kw%') OR req.req_uuid LIKE ('%$kw%') OR loc.name LIKE ('%$kw%'))";

    //$sql = "SELECT * FROM rms_request req WHERE status='$kws'";
    
            
    
//print $sql;    
    
    $rs = $global['db']->Execute($sql);
    //print $sql;
    
    $rs = $rs->GetArray();
   
    foreach ($rs as $r)
    {
        $_SESSION['rms_req_schres'][$r['req_uuid']] = $r;
       //var_dump($r);
    }
}

//********************************************************
/**return search results from rms_request and rms_get_item tables
 *
 */
function _shn_rms_shn_get_schresults()
{
   global $global;
    $db = $global['db'];
    $reqstr = $_SESSION['rms_req_sch']['requester'];
    $pri = $_SESSION['rms_req_sch']['priority'];
    $loc = $_SESSION['rms_req_sch']['location'];
    $cat = $_SESSION['rms_req_sch']['category'];
    $stat = $_SESSION['rms_req_sch']['status'];

    $cat_qry = "SELECT serial FROM ct_catalogue WHERE ct_uuid='".$cat."'";  
    $res1 = $db->Execute($cat_qry);
	$res1->MoveFirst();

	$cat_serial = $res1->Fields('serial');
	
	$cat_qry2 = "SELECT ct.ct_uuid,req.loc_uuid,rrm.quantity,rrm.pri_uuid,req.reqstr_uuid,req.status,req.req_uuid,req.req_date FROM ct_catalogue as ct
                 JOIN rms_req_item as rrm ON rrm.item_uuid = ct.ct_uuid 
                 JOIN rms_request as req ON req.req_uuid=rrm.req_uuid
                 WHERE ct.final_flag = '1' AND ct.serial LIKE '".$cat_serial."%' ";
	
	if($_SESSION['isadmin']==true) {
	    if (_shn_rms_is_user($reqstr)) {
		    $cat_qry2 .= " AND req.reqstr_uuid='".$reqstr."' ";
	    }
	}else {
		$reqstr = $_SESSION['user_id'];
		$cat_qry2 .= " AND req.reqstr_uuid='".$reqstr."' ";
	}
    if($_SESSION['rms_req_sch']['location']!=null) {
   	    if($loc!='0') {
            $cat_qry2 .="AND loc_uuid='".$loc."' ";
   	    }
    } 
    if($_SESSION['rms_req_sch']['priority'] != null) {
   	   if($pri!='0') {
   	       $cat_qry2 .="AND pri_uuid='$pri' ";
   	   } 
    }
    if($stat != 'all') {
    	$cat_qry2 .= "AND req.status='$stat' ";
    }
	//$res2 = $db->Execute($cat_qry2);
	global $global;
    include_once $global['approot'] . "/inc/lib_paging.inc";
    $res2=shn_paging_get_report($cat_qry2,'10',$headers,array('post'=>true,'return'=>true));
    return $res2;

}

function _shn_rms_sch_results()
{   
    // clear older results
    $_SESSION['rms_req_schres'] = null;
    
    $results =_shn_rms_shn_get_schresults();
    $tbl_arr = array();
	$tbl_hd_arr = array();
    
    if (!$results->EOF)
	{
		if($_SESSION['isadmin']==TRUE) {
			$tbl_hd_arr[0] = array (
			_t("Requester"),
			//_t("Category"),
			_t("Item"),
			_t("Location"),
			//_t("Quantity"),
			_t("Date"),
			_t("Status"),
			_t("Priority"),
			''
			     );
		}else {
			$tbl_hd_arr[0] = array (

			//_t("Category"),
			_t("Item"),
			_t("Location"),
			//_t("Quantity"),
			_t("Date"),
			_t("Status"),
			_t("Priority"),
			''
                       );
		}
		$req_id = '';
		$view_url = '<a href=index.php?mod=rms&amp;act=req_sch' .
                        //'&amp;keywords=' . $kws . 
                        '&amp;seq=view_req&amp;req_id=' . ($results->Fields('req_uuid')) .'>' .
                        _t("Details") . '</a>';
		
        $i=0;
		while(!$results->EOF){
			if($_SESSION['isadmin']==TRUE) {
				$_reqstr = _shn_rms_get_person($results->Fields('reqstr_uuid'));
			
				$tbl_arr[$i] = array($_reqstr['name'],
									//_shn_rms_get_cataloguename(_shn_rms_get_parent_catalogue($results->Fields('ct_uuid'))),
									_shn_rms_get_cat_name($results->Fields('ct_uuid')),
									_shn_rms_get_name($results->Fields('loc_uuid')),
									//$results->Fields('quantity'),
									$results->Fields('req_date'),
									$results->Fields('status'),
									_shn_rms_get_priorityname($results->Fields('pri_uuid')),
									$view_url);
			}else{
				$tbl_arr[$i] = array(//_shn_rms_get_cataloguename(_shn_rms_get_parent_catalogue($results->Fields('ct_uuid'))),
									_shn_rms_get_cat_name($results->Fields('ct_uuid')),
									_shn_rms_get_name($results->Fields('loc_uuid')),
									//$results->Fields('quantity'),
									$results->Fields('req_date'),
									$results->Fields('status'),
									_shn_rms_get_priorityname($results->Fields('pri_uuid')),
									$view_url);
			}
			$results->MoveNext();
			$i++;
		}
		print '<br />';
		shn_html_table($tbl_arr, $tbl_hd_arr, null, array('class'=>'wide'));
	}else {
		print '<br />';
		_shn_html_print_alert(_t("There are no results that match your search criteria."));
	}
    
						//$kws = $_REQUEST['keywords'];
			   
			  			// $_REQUEST['keywords']=$_SESSION['rms_req_sch']['status'];
			  			// $kws = $_SESSION['rms_req_sch']['status'];
			   
						   // if (!isset($_REQUEST['keywords']) || $kws == '')
						   // {
						   //     add_error(_t("Please anter a valid keyword"));
						   //     print '<br />';
						   //     display_errors();
						   //     return false;
						   // }
						    
						   // $words = preg_split("/\s+/",$kws);
						    
						   // foreach ($words as $word)
						   // {
						    //   _shn_rms_shn_get_results();
						   // }*/
}



switch ($_REQUEST['seq'])
{
    case '':
    	    if (shn_acl_is_enabled()) {
    	        $_SESSION['isadmin'] = _shn_rms_get_user_group();
    	    } else {
    	    	$_SESSION['isadmin'] = true;
    	    }
            _shn_rms_sch_getkeywords();
            break;
            
   case 'get_keywords':
            _shn_rms_sch_getkeywords();
            // case 'filter':
            // $page = $_REQUEST['page_no'];
            $page = 5;
            $rows = $_SESSION['rms_req_sch_rows'];
            $_SESSION['rms_req_sch']['requester'] = $_REQUEST['reqstr_id'];
            $_SESSION['rms_req_sch']['priority'] = $_REQUEST['priority'];
            $_SESSION['rms_req_sch']['location'] = $_REQUEST['loc_id'];
            $_SESSION['rms_req_sch']['status'] = $_REQUEST['status'];
            $_SESSION['rms_req_sch']['category'] = $_REQUEST['category'];
            //_shn_rms_req_showlist($page, $rows, $_SESSION['rms_req_sch']);
            //break;
            //_shn_rms_shn_get_results();
            _shn_rms_sch_results();
            break;
    case 'view_req':
            $req_id = $_REQUEST['req_id'];
            _shn_rms_view_request($req_id);
            $keywords = $_REQUEST['keywords'];
            print '<br />' .
                  '[ <a href="index.php?mod=rms">' . _t("RMS Home") . '</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;' .
                        'act=req_sch&amp;seq=get_keywords' .
                        '&amp;keywords' . $keywords . '">' . 
                        _t("Back to Request Search") . '</a> ]';
            break;

	   
}

?>