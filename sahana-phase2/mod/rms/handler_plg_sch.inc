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
    shn_form_fopen("plg_sch",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'get_keywords'));
    shn_form_text(_("Search Keywords"),'keywords',null,array('br'=>false,'value'=>'','req'=>true));
    shn_form_submit(_("Search"));
    shn_form_fclose();
}

function _shn_rms_shn_get_results($kw)
{
    global $global;
    
    /*$sql = "SELECT distinct(plg_uuid),donor_uuid,full_name,plg_date,status," .
            "contact_value " .
           "FROM " .
                "(SELECT plg.plg_uuid, plg.donor_uuid, plg.plg_date, plg.status, " .
                    "psn.full_name, cnt.contact_value " .
                 "FROM rms_pledge plg, person_uuid psn, contact cnt " .
                 "WHERE plg.donor_uuid=psn.p_uuid " .
                 "AND cnt.pgoc_uuid=psn.p_uuid) tmptbl " .
           "WHERE plg_uuid='$kw' " .
           "OR donor_uuid='$kw' " .
           "OR LOWER(full_name) LIKE LOWER('%$kw%') " .
           "OR LOWER(contact_value) LIKE LOWER('%$kw%')";*/

    $sql = "SELECT plg.plg_uuid,plg.donor_uuid,plg.plg_date,plg.status,psn.full_name,cnt.contact_value FROM rms_pledge plg, person_uuid psn,contact cnt WHERE plg.donor_uuid=psn.p_uuid AND (LOWER(psn.full_name) LIKE LOWER('%$kw%') OR plg.donor_uuid LIKE ('%$kw%') OR cnt.contact_value LIKE ('%$kw%'));";
    
    $rs = $global['db']->Execute($sql);
    //print $sql;
    $rs = $rs->GetArray();
    
    foreach ($rs as $r)
    {
        $_SESSION['rms_plg_schres'][$r['plg_uuid']] = $r;
    }
}

function _shn_rms_sch_results()
{
    // clear older results
    $_SESSION['rms_plg_schres'] = null;
    
    $kws = $_REQUEST['keywords'];
    if (!isset($_REQUEST['keywords']) || $kws == '')
    {
        add_error(_("Please enter a valid keyword"));
        print '<br />';
        display_errors();
        return false;
    }
    
    $words = preg_split("/\s+/",$kws);
    
    foreach ($words as $word)
    {
        _shn_rms_shn_get_results($word);
    }
    

    $results = $_SESSION['rms_plg_schres'];
    
    if (!empty($results))
    {
        //Result table hedder
        $th_res[] = array (
                              
                             _("Donor"), 
                             _("Date"), 
                             _("status"),
                             ''
                            );
                            
        foreach ($results as $r)
        {
            $plg_id = $r['plg_uuid'];
            
            $donor = $r['full_name'] . '<br />' . $r['contact_value'];
            
            $plg_date = $r['plg_date'];
            $plg_stat = $r['status'];
            
            $view_url = '<a href=index.php?mod=rms&amp;act=plg_sch' .
                        '&amp;seq=view_plg&amp;plg_id=' . $plg_id .'>' .
                        _("Details") . '</a>';
            
            $tb_res[] = array ($donor, $plg_date, $plg_stat, $view_url);
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
