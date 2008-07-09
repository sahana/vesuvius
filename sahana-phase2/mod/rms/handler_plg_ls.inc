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

_shn_rms_print_hedder(_t("Pledge List"));

function _shn_rms_plg_showlist($page = 1, $rows = 10, $filter = null, $odr_by = null)
{
    global $global;
    $db = $global['db'];
    $paging = false;
    $sql = "SELECT * FROM rms_pledge";
    
    // apply filters if any
    if ($filter != null)
    {
        $donor = $filter['donor'];

        $status = $filter['status'];
        $fstr = ''; //filter string
        
        if ($filter['status'] == '' || !_shn_rms_is_plgstatus($status))
            $status = false;
            
        if ($filter['donor'])
        {
            $fstr = " WHERE donor_uuid='$donor'";
            
            if ($status)
                $fstr .= " AND status='$status'";
        }
        elseif ($status)
        {
            $fstr = " WHERE status='$status'";
        }
        
        $sql .= $fstr;
    }
    
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
    $donors[''] = 'All';
    //Result table hedder
    /*$th_res[] = array (
                         _t("ID"), 
                         _t("Donor"), 
                         _t("Date"), 
                         _t("status"),
                         ''
                        );*/
    $th_res[] = array (
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
        
        //$tb_res[] = array ($plg_id, $donor_d, $plg_date, $plg_stat, $view_url);
        $tb_res[] = array ($donor_d, $plg_date, $plg_stat, $view_url);
    }
    
    if (1 <= count($rs_arr))
    {
        shn_html_table_open(array('class'=>'layout'));
        shn_html_tbody_open();
        shn_html_tr_open();
            shn_html_td_open();
            shn_form_fopen("plg_ls",null, array('req_message'=>false,'style'=>'form_blank'));
            shn_form_hidden(array('seq'=>'filter'));
            shn_form_select($donors, _t("Donors"), 'donor', 'onChange="submit(this);"',array('br'=>false));
            shn_form_fclose();
            shn_html_td_close();
            
            shn_html_td_open();
            shn_form_fopen("plg_ls",null, array('req_message'=>false,'style'=>'form_blank'));
            shn_form_hidden(array('seq'=>'filter'));
            $stat['all'] = _t("All");
            $stat['not_confirmed'] = _t("Not Confirmed");
            $stat['confirmed'] = _t("Confirmed");
            //$stat['not_delivered'] = _t("Not Delivered");
            $stat['delivered'] = _t("Delivered");
            $stat['discarded'] = _t("Discarded");
            
            shn_form_select($stat, _t("Status"), 'status', 'onChange="submit(this);"',array('br'=>false));
            shn_form_fclose();
            shn_html_td_close();
            
            shn_html_td_open();
            shn_form_fopen("plg_ls",null, array('req_message'=>false,'style'=>'form_blank'));
            shn_form_hidden(array('seq'=>'filter_clr'));
            shn_form_submit(_t("Clear Filter"));
            shn_form_fclose();            
            shn_html_td_close();
            
            shn_html_td_open(array('align'=>'right'));
            shn_form_fopen("plg_ls",null, array('req_message'=>false,'style'=>'form_blank'));
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
        _shn_html_print_alert(_t("There are no Pledges on the Database that matches your criteria"));
        print '<br />' .
                  '[ <a href="index.php?mod=rms">' . _t("RMS Home") . '</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=plg_ls">' . _t("Back to Pledge List") . '</a> ]';
    }
}

function _shn_rms_stat_pledge($plg_id)
{
    $plg = _shn_rms_get_pledge($plg_id);
    if (!$plg_id)
        return false;
    
    $status = $plg['status'];
    
    $stat['not_confirmed'] = _t("Not Confirmed");
    $stat['confirmed'] = _t("Confirmed");
    $stat['delivered'] = _t("Delivered");
    $stat['discarded'] = _t("Discarded");
            
    shn_form_fopen("plg_ls",null, array('req_message'=>false,'style'=>''));
    shn_form_hidden(array('seq'=>'chg_stat'));
    shn_form_hidden(array('plg_id'=>$plg_id));
    shn_form_select($stat, _t("Status"), 'status', 'onChange="submit(this);"',array('br'=>false,'value'=>$status));
    shn_form_fclose();
}

switch ($_REQUEST['seq'])
{
    case '':
            $_SESSION['rms_plg_filter'] = null;
            $_SESSION['rms_plg_orderby'] = null;
            $page = $_REQUEST['page_no'];
            $rows = $_SESSION['rms_plg_ls_rows'];
            _shn_rms_plg_showlist($page, $rows);
            break;
    case 'filter':
            $page = $_REQUEST['page_no'];
            $rows = $_SESSION['rms_plg_ls_rows'];
            $_SESSION['rms_plg_filter']['donor'] = $_REQUEST['donor'];
            $_SESSION['rms_plg_filter']['status'] = $_REQUEST['status'];
            _shn_rms_plg_showlist($page, $rows, $_SESSION['rms_plg_filter']);
            break;
    case 'odr_by':
            $page = $_REQUEST['page_no'];
            $rows = $_SESSION['rms_plg_ls_rows'];
            $_SESSION['rms_plg_orderby'] = $_GET['odr_by'];
            _shn_rms_plg_showlist($page, $rows, $_SESSION['rms_plg_filter'], $_SESSION['rms_plg_orderby']);
            break;
    case 'rows':
            $page = $_REQUEST['page_no'];
            $_SESSION['rms_plg_ls_rows'] = $_POST['rows'];
            $rows = $_SESSION['rms_plg_ls_rows'];
            $_SESSION['rms_plg_orderby'] = $_GET['odr_by'];
            _shn_rms_plg_showlist($page, $rows, $_SESSION['rms_plg_filter'], $_SESSION['rms_plg_orderby']);
            break;
    case 'filter_clr':
            $_SESSION['rms_plg_filter'] = null;
            $page = $_REQUEST['page_no'];
            $rows = $_SESSION['rms_plg_ls_rows'];
            _shn_rms_plg_showlist($page, $rows, $_SESSION['rms_plg_orderby']);
            break;
    case 'view_plg':
            $plg_id = $_REQUEST['plg_id'];
            _shn_rms_view_pledge($plg_id);
            _shn_rms_stat_pledge($plg_id);
            print '<br />' .
                  '[ <a href="index.php?mod=rms">' . _t("RMS Home") . '</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=plg_ls">' . _t("Back to Pledge List") . '</a> ]';
            break;
    case 'chg_stat':           
            $plg_id = $_POST['plg_id'];
            $stat = $_POST['status'];
            _shn_rms_pledge_setstat($plg_id, $stat);
            _shn_rms_view_pledge($plg_id);
            _shn_rms_stat_pledge($plg_id);
            print '<br />' .
                  '[ <a href="index.php?mod=rms">' . _t("RMS Home") . '</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=plg_ls">' . _t("Back to Pledge List") . '</a> ]';
            break;
}

?>