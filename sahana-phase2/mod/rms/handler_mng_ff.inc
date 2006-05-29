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

_shn_rms_print_hedder(_("Fulfil Requests"));

function _shn_rms_mng_request()
{
    $_SESSION['rms_req_id'] = null;
    
    print '<div id="req_id">';
    shn_form_fopen("mng_ff",null, array('req_message'=>false));
    shn_form_hidden(array('seq'=>'get_req'));
    shn_form_fsopen(_("Request"));
    shn_form_text(_("Request ID"),'req_id',null,array('br'=>false));
    shn_form_submit(_("Next"));
    shn_form_fsclose();
    shn_form_fclose();
    print '</div>';
}

function _shn_rms_mng_getrequest($req_id)
{
    $req = _shn_rms_view_request($req_id);
    if ($req === false)
    {
        add_error(_("Please Enter a valid Request ID"));
        display_errors();
        _shn_rms_mng_request();
        return false;
    }
    print '<br />';
    
    shn_html_table_open(array('class'=>'wide'));
    shn_html_tbody_open();
    shn_html_tr_open();
        
        shn_html_td_open();
        shn_form_fopen("mng_ff",null, array('req_message'=>false));
        shn_form_hidden(array('seq'=>''));
        shn_form_submit(_("Back"));
        shn_form_fclose();
        shn_html_td_close();
        
        shn_html_td_open(array('align'=>'right'));
        shn_form_fopen("mng_ff",null, array('req_message'=>false));
        shn_form_hidden(array('seq'=>'sel_itm'));
        shn_form_submit(_("Next"));
        shn_form_fclose();
                  
    shn_html_tr_close();
    shn_html_tbody_close();
    shn_html_table_close();
}

function _shn_rms_mng_select_item()
{
    $req_id = $_SESSION['rms_req_id'];
    _shn_rms_view_reqff($req_id);
}

function _shn_rms_mng_select_pledge()
{
    global $global;
    $_SESSION['rms_plg_id'] = null;
    $itm = $_SESSION['rms_req_item'];
    
    print '<div id="req_id">';
    shn_form_fopen("mng_ff",null, array('req_message'=>false));
    shn_form_hidden(array('seq'=>'get_plg'));
    shn_form_fsopen(_("Request"));
    shn_form_text(_("Pledge ID"),'plg_id',null,array('br'=>false));
    shn_form_submit(_("Next"));
    shn_form_fsclose();
    shn_form_fclose();
    print '</div>';
    
    $sql = "SELECT plg.plg_uuid AS plg_uuid, plg.item_uuid AS item_uuid, " .
                "plg.quantity AS plg_qty, SUM(ff.quantity) AS ff_qty  " .
           "FROM rms_plg_item AS plg LEFT JOIN rms_fulfil AS ff " .
           "ON plg.plg_uuid=ff.plg_uuid AND plg.item_uuid=ff.item_uuid " .
           "WHERE plg.item_uuid='$itm' " .
           "AND ff.quantity IS NULL " .
           "OR plg.quantity>ff.quantity " .
           "GROUP BY item_uuid";
    
    $rs = $global['db']->Execute($sql);
    $rs_arr = $rs->GetArray(); 
    
    if (1 <= count($rs_arr)) 
    {
        $th_plg[] = array (_("PledgeID"), _("Item"), _("Qty"), _("Used"), '');
         
        foreach ($rs_arr as $plg)
        {
            $max_qty = $plg['plg_qty'] - $plg['ff_qty'];
            $sel_url = '<a href=index.php?mod=rms&amp;act=mng_ff' .
                        '&amp;seq=add_ff&amp;max_qty=' . $max_qty .
                        '&amp;plg_id=' . $plg['plg_uuid'] .'>' .
                        _("Select") . '</a>';
                        
            $tb_plg[] = array (
                                 $plg['plg_uuid'],
                                 _shn_rms_get_itemname($plg['item_uuid']), 
                                 $plg['plg_qty'],
                                 $plg['ff_qty'],
                                 $sel_url
                                );
        }
        
        print '<br />';
        shn_html_table($tb_plg, $th_plg, null, array('class'=>'wide'));
    }  

}

function _shn_rms_mng_addff($max_qty)
{
    $req_id = $_SESSION['rms_req_id'];
    $req_item = $_SESSION['rms_req_item'];
    $plg_id = $_SESSION['rms_req_plg'];
    
    _shn_rms_view_reqff($req_id);
    
    _shn_html_print_message(_("Allocate items from the selected pledge to the request"));
    
    shn_form_fopen("mng_ff",null, array('req_message'=>false));
    shn_form_hidden(array('seq'=>'finish'));
    shn_form_fsopen(_("Allocate"));
    shn_form_text(_("Item"),'itm_id','readonly="true"',array('value'=>_shn_rms_get_itemname($req_item)));
    shn_form_text(_("Maximum Allocatable Quantity"),'max_qty','readonly="true"',array('value'=>$max_qty));
    shn_form_text(_("Quantity"),'qty',null);
    shn_form_submit(_("Next"));
    shn_form_fsclose();
    shn_form_fclose();
    
}

switch ($_REQUEST['seq'])
{
    case '':
            $_SESSION['rms_req_id'] = null;
            $_SESSION['rms_mng_ff_added'] = false;
            _shn_rms_mng_request();
            break;
            
    case 'get_req':
            $req_id = $_REQUEST['req_id'];
            $_SESSION['rms_req_id'] = $req_id;
            $_SESSION['rms_mng_ff_added'] = false;
            _shn_rms_mng_getrequest($req_id);
            break;
    
    case 'sel_itm':
            $_SESSION['rms_req_item'] = null;
            _shn_rms_mng_select_item();
            break;
    
    case 'sel_plg';
            $_SESSION['rms_req_id'] = $_REQUEST['req_id'];
            $_SESSION['rms_req_item'] = $_REQUEST['itm_id'];
            _shn_rms_mng_select_pledge();
            break;
            
    case 'add_ff';
            $_SESSION['rms_req_plg'] = $_REQUEST['plg_id'];
            $max_qty = $_REQUEST['max_qty'];            
            _shn_rms_mng_addff($max_qty);
            break;
            
    case 'finish';
            if ($_POST['qty'] > $_POST['max_qty'])
            {
                add_error(_("Please enter a valid 'Quantity', The 'Quantity' should be equal or less than the Maximum Value"));
                display_errors();
                _shn_rms_mng_addff($_POST['max_qty']);
                return false;
            }
            
            if (!$_SESSION['rms_mng_ff_added'])
            {
                $req_id = $_SESSION['rms_req_id'];
                $req_item = $_SESSION['rms_req_item'];
                $plg_id = $_SESSION['rms_req_plg'];
                $qty = $_POST['qty'];
                
                $res = _shn_rms_add_ff($req_id, $req_item, $plg_id, $qty);
                $_SESSION['rms_mng_ff_added'] = $res;
            }
            
            if ($_SESSION['rms_mng_ff_added'])
            {
                _shn_html_print_alert(_("The Fulfilment Data was successfully added"));
                _shn_rms_view_reqff($_SESSION['rms_req_id']);
            }
            
            print '<br />' .
                  '[ <a href="index.php?mod=rms">RMS Home</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=mng_ff&amp;seq=get_req&amp;req_id='. $_SESSION['rms_req_id'] .'">Fullfil Another Item From the Same Request</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=mng_ff">Fullfil Other Request</a> ]';
            break;
            break;
}
?>
