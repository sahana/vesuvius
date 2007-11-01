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

_shn_rms_print_hedder(_("Request Search: Search for Requesters, Locations and Requests"));

function _shn_rms_sch_getkeywords()
{
    shn_form_fopen("req_sch",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'get_keywords'));
    shn_form_text(_("Search Keywords"),'keywords',null,array('br'=>false,'value'=>'','req'=>true));
    shn_form_submit(_("Search"));
    shn_form_fclose();
}

function _shn_rms_shn_get_results($kw)
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

    //$sql = "SELECT req.req_uuid,req.reqstr_uuid,req.req_date,req.status,psn.full_name,loc.location_id FROM rms_request req, person_uuid psn,location_details loc,contact cnt WHERE req.reqstr_uuid=psn.p_uuid AND req.reqstr_uuid=loc.poc_uuid AND (LOWER(psn.full_name) LIKE LOWER('%$kw%') OR req.req_uuid LIKE ('%$kw%') OR loc.address LIKE ('%$kw%') OR loc.location_id LIKE ('%$kw%'));";
    $sql ="SELECT req.req_uuid,req.reqstr_uuid,req.req_date,req.status,psn.full_name,req.loc_uuid FROM rms_request req, person_uuid psn,location loc,contact cnt WHERE req.reqstr_uuid=psn.p_uuid AND req.loc_uuid=loc.loc_uuid AND (LOWER(psn.full_name) LIKE LOWER('%$kw%') OR req.req_uuid LIKE ('%$kw%') OR loc.name LIKE ('%$kw%'))";
    //print $sql;
    //$sql="SELECT ";
    
    
    $rs = $global['db']->Execute($sql);
    //print $sql;
    
    $rs = $rs->GetArray();
    
    foreach ($rs as $r)
    {
        $_SESSION['rms_req_schres'][$r['req_uuid']] = $r;
    }
}

function _shn_rms_sch_results()
{
    // clear older results
    $_SESSION['rms_req_schres'] = null;
    
    $kws = $_REQUEST['keywords'];
    if (!isset($_REQUEST['keywords']) || $kws == '')
    {
        add_error(_("Please anter a valid keyword"));
        print '<br />';
        display_errors();
        return false;
    }
    
    $words = preg_split("/\s+/",$kws);
    
    foreach ($words as $word)
    {
        _shn_rms_shn_get_results($word);
    }
    

    $results = $_SESSION['rms_req_schres'];
    
    if (!empty($results))
    {
        //Result table hedder
        $th_res[] = array (
                              
                             _("Requester"), 
                             _("Location"), 
                             _("Date"), 
                             _("status"),
                             ''
                            );
                            
        foreach ($results as $r)
        {
            $req_id = $r['req_uuid'];
            
            $reqstr = $r['full_name'] . '<br />' . $r['contact_value'];
            $location = _shn_rms_get_location_name($r['loc_uuid']);
            $loc =  $location .'<br />' . $r['address'];
            
            $req_date = $r['req_date'];
            $req_stat = $r['status'];
            
            $view_url = '<a href=index.php?mod=rms&amp;act=req_sch' .
                        //'&amp;keywords=' . $kws . 
                        '&amp;seq=view_req&amp;req_id=' . $req_id .'>' .
                        _("Details") . '</a>';
            
            $tb_res[] = array ($reqstr, $loc, $req_date, $req_stat, $view_url);
        }
        
        print '<br />';
        shn_html_table($tb_res, $th_res, null, array('class'=>'wide'));
    }
    else
    {
        print '<br />';
        _shn_html_print_alert(_("There are no results that matches your search criteria, Please use a different keyword"));
    }
}

switch ($_REQUEST['seq'])
{
    case '':
            _shn_rms_sch_getkeywords();
            break;
            
    case 'get_keywords':
            _shn_rms_sch_getkeywords();
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
