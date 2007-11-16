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

_shn_rms_print_hedder(_("Search for Requests"));

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
        //echo $_SESSION['isadmin'];
		if($_SESSION['isadmin']==true) {
	    	$loc_ids=_shn_rms_get_all_locations();
	    	//echo 'admin';
	    }else { 
		    $loc_ids = _shn_rms_get_location_array($_SESSION['user_id']);
		    //echo 'sahana';
     	}

        $location = array();
        $location[0] = 'All';
        
        foreach($loc_ids as $loc){
            $location[$loc] =_shn_rms_get_location_name($loc);
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
        $status['all'] = _("All");
        $status['open'] = _("Open");
        $status['closed'] = _("Closed");
        //----------------------------------------------------------------
	    //shn_html_tr_open();
        //shn_html_td_open();
        //shn_form_fopen("req_sch",null, array('req_message'=>false,'style'=>'form_blank'));
        //shn_form_hidden(array('seq'=>'filter'));
        //shn_form_select($requesters, _("Requesters"), 'reqstr', 'onChange="submit(this);"',array('br'=>false));
        //shn_form_fclose();
        //shn_html_td_close();
			 
        //shn_html_td_open();
        shn_form_fopen("req_sch",null, array('req_message'=>false,'style'=>'form_blank'));
        shn_form_fsopen("Select Criteria");
        shn_form_hidden(array('seq'=>'get_keywords'));
        
	    if($_SESSION['isadmin']==true) {
			shn_form_select($reqstr_name, _("Requester"), 'reqstr_id',null,array('br'=>false));
			print '<br/>';
			print '<br/>';
	    }
        shn_form_select($location, _("Locations"), 'loc_id', null,array('br'=>false));
        print '<br />';
        print '<br />';
		
        shn_form_select($priority,_("Priotity"),'priority',null,array('br'=>false));
        print '<br />';
        print '<br />';
        //shn_form_select($categories,_("Category"),'category',null,array('br'=>false));
        //print '<br />';
        //print '<br />';
        shn_form_select($status,_("Status"),'status',null,array('br'=>false));
        shn_form_fsclose();
        //print '<br />';
        // print '<br />';
        shn_form_submit(_("Search"));
        shn_form_fclose();
        //shn_html_td_close();
    }else {
    	add_warning(_("No requests found"));
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
    //$sql="SELECT ";
    
    
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
    $reqstr = $_SESSION['rms_req_sch']['requester'];
    $pri = $_SESSION['rms_req_sch']['priority'];
    $loc = $_SESSION['rms_req_sch']['location'];
    $cat = $_SESSION['rms_req_sch']['category'];
    $stat = $_SESSION['rms_req_sch']['status'];
    
    $sql = "SELECT * FROM rms_request req,rms_req_item item WHERE req.req_uuid=item.req_uuid ";
    //echo $reqstr;
    //----------------set requesters----------------------------------------    
    if($_SESSION['isadmin']==true) {
        if(_shn_rms_is_user($reqstr)) {          
           $sql .= "AND reqstr_uuid='$reqstr' ";
        }else{
        	//if dornor criteria is "All" then clear the session variable
        }
    }else {
        $reqstr = $_SESSION['user_id'];
    	$sql .= "AND reqstr_uuid='$reqstr' ";
    }
    //------------------set priorities------------------------------------------
    if($_SESSION['rms_req_sch']['priority'] != null) {
   	   if($pri!='0') {
   	       $sql .="AND pri_uuid='$pri' ";
   	   } 
    }
    //------------------set category----------------------------------------
    if($_SESSION['rms_req_sch']['category']!=null) {
        if($cat!='0') {
    	    $p_cat = _shn_rms_get_parent_catalogue($cat);	
    	    $sql .= "AND item_uuid IN (SELECT ct_uuid from ct_catalogue WHERE parentid='$p_cat') ";
    	}
    }  
   	//------------------set location---------------------------------------------- 
    if($_SESSION['rms_req_sch']['location']!=null) {
   	    if($loc!='0') {
            $sql .="AND loc_uuid='$loc' ";
   	    }
    }
    //-------------------------------------------------------------------------------
    if($stat !=null) {
   	    if($stat!='all') {
            $sql .= "AND status='$stat'";
   	    }
    }
    //----------------------------------------------------------------------------------        

   $rs = $global['db']->Execute($sql);
        
   $rs = $rs->GetArray();
   
   foreach ($rs as $r)
    {
        $_SESSION['rms_req_schres'][$r['req_uuid']] = $r;
       //var_dump($r);
    }
}

function _shn_rms_sch_results()
{   
    // clear older results
    $_SESSION['rms_req_schres'] = null;
    
    _shn_rms_shn_get_schresults();
    
    $results = $_SESSION['rms_req_schres'];
    
    if (!empty($results))
    {
        //Result table hedder
    	if($_SESSION['isadmin']==true) {
            $th_res[] = array (
                            _("Requester"),  
                             _("Item"), 
                             _("Location"), 
                             _("Date"), 
                             _("status"),
                             _("Priority"),
                             ''
                            );
    	}else {
        $th_res[] = array ( 
                             _("Item"), 
                             _("Location"), 
                             _("Date"), 
                             _("status"),
                             _("Priority"),
                             ''
                            );
    	}
                            
        foreach ($results as $r)
        {
            $req_id = $r['req_uuid'];
            //-----------------------------------
            $reqstr_nm = _shn_rms_get_person($r['reqstr_uuid']);
            $reqstr_d = '<strong>' . $reqstr_nm['name'] . '</strong><br >' . 
                    '<a href="mailto:' . $reqstr_nm['email'] .'">' . $reqstr_nm['email'] . '</a>  ' .
                    $reqstr_nm['mobile'];
            //-------------------------------------------------------------------------
            $location = _shn_rms_get_location_name($r['loc_uuid']);
            //$loc = '<strong>' . $location . '</strong> <br />' . 
            //         $r['address'];
            
            $loc =  $location .'<br />' . $r['address'];
            $req_date = $r['req_date'];
            $req_stat = $r['status'];
            $item = $r['item_uuid'];
             //if($item!=null ||$item!='')
             if($item!=null)
             	{
                  $req_cat = _shn_rms_get_cataloguename($item);
             	}
//             else{
//             $req_cat = "no";
//             
//             }
           // var_dump($item);
            $req_pri = $r['pri_uuid'];
            $req_prio = _shn_rms_get_priorityname($req_pri);
            
            
            $view_url = '<a href=index.php?mod=rms&amp;act=req_sch' .
                        //'&amp;keywords=' . $kws . 
                        '&amp;seq=view_req&amp;req_id=' . $req_id .'>' .
                        _("Details") . '</a>';
            
            if($_SESSION['isadmin']==true) {
                $tb_res[] = array ( $reqstr_d, $req_cat, $loc, $req_date, $req_stat, $req_prio, $view_url);
            }else {
            	$tb_res[] = array ( $req_cat, $loc, $req_date, $req_stat, $req_prio, $view_url);
            }
        }
        
        print '<br />';
        shn_html_table($tb_res, $th_res, null, array('class'=>'wide'));
    }
    else
    {
        print '<br />';
        _shn_html_print_alert(_("There are no results that matches your search criteria."));
    }
						//$kws = $_REQUEST['keywords'];
			   
			  			// $_REQUEST['keywords']=$_SESSION['rms_req_sch']['status'];
			  			// $kws = $_SESSION['rms_req_sch']['status'];
			   
						   // if (!isset($_REQUEST['keywords']) || $kws == '')
						   // {
						   //     add_error(_("Please anter a valid keyword"));
						   //     print '<br />';
						   //     display_errors();
						   //     return false;
						   // }
						    
						   // $words = preg_split("/\s+/",$kws);
						    
						   // foreach ($words as $word)
						   // {
						    //   _shn_rms_shn_get_results();
						   // }
}



switch ($_REQUEST['seq'])
{
    case '':
    	    $_SESSION['isadmin'] = _shn_rms_get_user_group();
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
                  '[ <a href="index.php?mod=rms">' . _("RMS Home") . '</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;' .
                        'act=req_sch&amp;seq=get_keywords' .
                        '&amp;keywords' . $keywords . '">' . 
                        _("Back to Request Search") . '</a> ]';
            break;

	   
}

?>