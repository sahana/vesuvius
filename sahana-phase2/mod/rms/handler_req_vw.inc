<?php
/**
* Description for file
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/ 

_shn_rms_show_headder(_("View Request"));

function _shn_rms_get_requestid()
{
?>

<?php
    shn_form_fopen("req_vw",null);
    
    shn_form_hidden(array('seq'=>'req_vw'));
    
    shn_form_fsopen('Request ID');
    shn_form_text('Enter Request ID','id');
    shn_form_fsclose();
    shn_form_submit('View');
    shn_form_fclose();
    
}

function _shn_rms_req_view()
{
    $req_id = $_POST['id'];
    
    if(!_shn_rms_show_request($req_id))
    {
        _shn_rms_showerrors();
        _shn_rms_get_requestid();
    }
    
    return true;
    
}

switch ($_REQUEST['seq'])
{
    case '':
            _shn_rms_get_requestid();
            break;
    
    case 'req_vw':
            _shn_rms_req_view();
            break;                
}

?>