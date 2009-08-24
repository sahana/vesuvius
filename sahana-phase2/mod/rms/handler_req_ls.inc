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

_shn_rms_print_hedder(_t("Request List"));

function _shn_rms_req_showlist($page = 1, $rows = 10, $filter = null, $odr_by = null)
{
	
    
    global $global;
    $db = $global['db'];
    $paging = false;
    $sql = "SELECT r.req_uuid as req_uuid, r.reqstr_uuid as reqstr_uuid, r.loc_uuid as loc_uuid, rd.date as req_date, r.status as status, r.user_id as user_id FROM rms_request r INNER JOIN rms_request_date rd ON r.req_uuid = rd.req_uuid";
   // print $sql;
    // apply filters if any
    if ($filter != null)
    {
        $requester = $filter['requester'];
        $location = $filter['location'];
        $status = $filter['status'];
        $fstr = ''; //filter string
        
        if ($filter['status'] == '' || !_shn_rms_is_reqstatus($status))
            $status = false;
            
        if (isset($filter['requester']))
        {
            $fstr = " WHERE reqstr_uuid='$requester'";
            
            if ($filter['location'])
                $fstr .= " AND loc_uuid='$location'";
            if ($status)
                $fstr .= " AND status='$status'";
        }
        elseif ($filter['location'])
        {
            $fstr = " WHERE loc_uuid='$location'";
            
            if ($status)
                $fstr .= " AND status='$status'";
        }
        elseif ($status)
        {
            $fstr = " WHERE status='$status'";
        }
        
        $sql .= $fstr;
        //echo $sql;
    }
   // print $sql;
    if (!isset($page) || $page == '' || !is_numeric($page))
        $page = 1;
    
    if (!isset($rows) || $rows == '' || !is_numeric($rows))
        $rows = 10;
    
    // create pagnating links
    $req_count = _shn_rms_get_recordcount('rms_request', $fstr);
    $page_count = ceil($req_count/$rows);
    
    if (1 < $page_count)
    {
        $paging = true;
        $page_list = _t(":: ");
        
        if (1 < $page)
        {
            $page_list .= '<a href="index.php?mod=rms&amp;act=req_ls' .
                              '&amp;page_no=' . ($page - 1) . '"> ' . 
                              _t("Previous") . '</a> ';
        }
        
        for ($i = 1; $i <= $page_count; $i++)
        {
            if ($page != $i)
            {
                $page_list .= ' <a href="index.php?mod=rms&amp;act=req_ls' .
                              '&amp;page_no=' . $i . '"> <small>' . $i . 
                              '</small></a> ';
            }
            else
            {
                $page_list .= '<small>' . $i . '</small>';
            }
        }
        
        if ($page_count != $page)
            $page_list .= '<a href="index.php?mod=rms&amp;act=req_ls' .
                              '&amp;page_no=' . ($page + 1) . '">' . 
                              _t("Next") . '</a>';
    }        
    
    //set order-by
    if ($odr_by != null && $odr_by != '')
        $sql .= " ORDER BY '$odr_by'";
    else
        $sql .= " ORDER BY 'req_date'";

    $rs = $db->PageExecute($sql, $rows, $page);
    $rs_arr = $rs->GetArray();
    
    
    
        
   
    
    //Result table hedder
    $th_res[] = array (
                         _t("Requester"), 
                         _t("Location"), 
                         _t("Date"), 
                         _t("Status"),
                         ''
                        );
    
//    echo "<pre>";
//    var_dump($rs_arr);
//    echo "</pre>";
    
    foreach ($rs_arr as $r)
    {
        $req_id = $r['req_uuid'];
       
        $reqstr = _shn_rms_get_requester($r['reqstr_uuid']);
        //need a function to get name
        
        $reqstr_d = '<strong>' . $reqstr['name'] . '</strong><br >' . 
                    'Contact: <a href="mailto:' . $reqstr['email'] .'">' . $reqstr['email'] . '</a> , ' .
                    $reqstr['mobile'];
        
        //$req_loc = _shn_rms_get_location($r['loc_uuid']);
	//$req_loc = _shn_ims_get_location($inv_id);

	//$location_name=_shn_rms_get_location_name($req_loc['location_id']);
	    $location_name = _shn_rms_get_name($r['loc_uuid']);
        //echo $location_name;

		if($req_loc['opt_person_loc_type']=='')
		{
	    //$loc_d = '<strong>' . $req_loc['location_id'] . '</strong>';
	    $loc_d =  $location_name;
	    //print $loc_d;
		}
		else
		{
           /* $loc_d = '<strong>' . $req_loc['location_id'] . '</strong> [' . 
                    $req_loc['opt_person_loc_type'] . ']';*/
	    $loc_d = '<strong>' .$location_name . '</strong> [' . 
                    $req_loc['opt_person_loc_type'] . ']';
		}
        
        $req_date = $r['req_date'];
        $req_stat = $r['status'];
        $req_usr = $r['user_id'];
        $view_url = '<a href=index.php?mod=rms&amp;act=req_ls' .
                    '&amp;seq=view_req&amp;req_id=' . $req_id .'>' .
                    _t("Details") . '</a>';
        
        //$tb_res[] = array ($req_id, $reqstr_d, $loc_d, $req_date, $req_stat, $view_url);
        $tb_res[] = array ($reqstr_d, $loc_d, $req_date, $req_stat, $view_url);
    }
    
    if (1 <= count($rs_arr))
    {//create the filter list
    $requesters = array();
    $location = array();
    
    $requesters = _shn_rms_get_requesters();
    
    $loc = _shn_rms_get_location_array($_SESSION['user_id']);
    
    $location = array();
    $location[''] = 'All';
    foreach ($loc as $l)
    {
      if(_shn_rms_get_location_name($l) != false){
      	$location[$l] = _shn_rms_get_location_name($l);
      }
      else{
      	$location[$l] = _shn_rms_get_name($l);
      }
      //array_push($location,$temp);
    
    }
    echo "<pre>";
    //var_dump($location);
    echo "</pre>";
    	
    	
        shn_html_table_open(array('class'=>'layout'));
        shn_html_tbody_open();
        shn_html_tr_open();
            shn_html_td_open();
            shn_form_fopen("req_ls",null, array('req_message'=>false,'style'=>'form_blank'));
            shn_form_hidden(array('seq'=>'filter'));
            shn_form_select($requesters, _t("Requesters"), 'reqstr', 'onChange="submit(this);"',array('br'=>false));
            shn_form_fclose();
            shn_html_td_close();
            
            shn_html_td_open();
            shn_form_fopen("req_ls",null, array('req_message'=>false,'style'=>'form_blank'));
            shn_form_hidden(array('seq'=>'filter'));
            shn_form_select($location, _t("Locations"), 'loc_id', 'onChange="submit(this);"',array('br'=>false));
            shn_form_fclose();
            shn_html_td_close();
            
            shn_html_td_open();
            shn_form_fopen("req_ls",null, array('req_message'=>false,'style'=>'form_blank'));
            shn_form_hidden(array('seq'=>'filter'));
            $stat['all'] = _t("All");
            $stat['open'] = _t("Open");
            $stat['closed'] = _t("Closed");
            shn_form_select($stat, _t("Status"), 'status', 'onChange="submit(this);"',array('br'=>false));
            shn_form_fclose();
            shn_html_td_close();
            
            shn_html_td_open();
            shn_form_fopen("req_ls",null, array('req_message'=>false,'style'=>'form_blank'));
            shn_form_hidden(array('seq'=>'filter_clr'));
            shn_form_submit(_t("Clear Filter"));
            shn_form_fclose();            
            shn_html_td_close();
            
            shn_html_td_open(array('align'=>'right'));
            shn_form_fopen("req_ls",null, array('req_message'=>false,'style'=>'form_blank'));
            shn_form_hidden(array('seq'=>'rows'));
            $opts = array ('1'=>'1', '2'=>'2', '10'=>'10', '25'=> '25');
            shn_form_select($opts,_t("Records"), 'rows', 'onChange="submit(this);"', array('value'=>$rows));
            shn_form_fclose();
            shn_html_td_close();
        shn_html_tr_close();
        shn_html_tbody_close();
        shn_html_table_close();
        
        print '<br />';
        
        if ($paging)
            print $page_list;
        
        shn_html_table($tb_res, $th_res, null, array('class'=>'wide'));
    }
    else
    {
        _shn_html_print_alert(_t("There are no requests on the Database that matches your criteria"));
    }
}

function _shn_rms_stat_request($req_id)
{
    $request = _shn_rms_get_request($req_id);
    if (!$request)
        return false;
    
    $status = $request['status'];
    
    $stat['open'] = _t("Open");
    $stat['closed'] = _t("Closed");
    
    if((_shn_rms_get_user_group()==true) || ($_SESSION['user_id']==$_SESSION['rms_ls_reqstr'])) {
        $st='onChange="submit(this);"';
    }else{
    	$st= 'disabled="DISABLED"';
    	//$st='onChange="submit(this);"';
    }
            
    shn_form_fopen("req_ls",null, array('req_message'=>false,'style'=>''));
    shn_form_hidden(array('seq'=>'chg_stat'));
    shn_form_hidden(array('req_id'=>$req_id));
    shn_form_select($stat, _t("Status"), 'status',$st,array('br'=>false,'value'=>$status));
    
    unset($_SESSION['rms_ls_reqstr']);
    
    shn_form_fclose();
}

switch ($_REQUEST['seq'])
{
    case '':
            $_SESSION['rms_req_filter'] = null;
            $_SESSION['rms_req_orderby'] = null;
            $page = $_REQUEST['page_no'];
            $rows = $_SESSION['rms_req_ls_rows'];
            _shn_rms_req_showlist($page, $rows);
            break;
    case 'filter':
            $page = $_REQUEST['page_no'];
            $rows = $_SESSION['rms_req_ls_rows'];
            $_SESSION['rms_req_filter']['requester'] = $_REQUEST['reqstr'];
            $_SESSION['rms_req_filter']['location'] = $_REQUEST['loc_id'];
            $_SESSION['rms_req_filter']['status'] = $_REQUEST['status'];
            _shn_rms_req_showlist($page, $rows, $_SESSION['rms_req_filter']);
            break;
    case 'odr_by':
            $page = $_REQUEST['page_no'];
            $rows = $_SESSION['rms_req_ls_rows'];
            $_SESSION['rms_req_orderby'] = $_GET['odr_by'];
            _shn_rms_req_showlist($page, $rows, $_SESSION['rms_req_filter'], $_SESSION['rms_req_orderby']);
            break;
    case 'rows':
            $page = $_REQUEST['page_no'];
            $_SESSION['rms_req_ls_rows'] = $_POST['rows'];
            $rows = $_SESSION['rms_req_ls_rows'];
            $_SESSION['rms_req_orderby'] = $_GET['odr_by'];
            _shn_rms_req_showlist($page, $rows, $_SESSION['rms_req_filter'], $_SESSION['rms_req_orderby']);
            break;
    case 'filter_clr':
            $_SESSION['rms_req_filter'] = null;
            $page = $_REQUEST['page_no'];
            $rows = $_SESSION['rms_req_ls_rows'];
            _shn_rms_req_showlist($page, $rows, $_SESSION['rms_req_orderby']);
            break;
    case 'view_req':
            $req_id = $_REQUEST['req_id'];
            _shn_rms_view_request($req_id);
            _shn_rms_stat_request($req_id);
            print '<br />' .
                  '[ <a href="index.php?mod=rms">' . _t("RMS Home") . '</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=req_ls">' . _t("Back to Request List") . '</a> ]';
            break;
    case 'chg_stat':           
            $req_id = $_POST['req_id'];
            $stat = $_POST['status'];
            _shn_rms_request_setstat($req_id, $stat);
            _shn_rms_view_request($req_id);
            _shn_rms_stat_request($req_id);
            print '<br />' .
                  '[ <a href="index.php?mod=rms">' . _t("RMS Home") . '</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=req_ls">' . _t("Back to Request List") . '</a> ]';
            break;
            
}

?>