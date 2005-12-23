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


_shn_rms_show_headder(_("Removing a Pledge"));


function _shn_rms_show_confirmdel()
{
    $id = $_REQUEST['plg_id'];
?>
<h4>You are about to remove the pledge ( Pledge id:<?=$_REQUEST['plg_id']?> )</h4>
(The information will be permanently deleted from the database)<br/>
<br/>
Please press "Remove" to remove the pledge.
<?php


    shn_form_fopen("del_plg",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'del'));
    shn_form_hidden(array('plg_id'=>$id));            
    shn_form_submit('Remove',"short");
    shn_form_fclose();
}

function _shn_rms_del_plg()
{
    global $global;
    $id = $_REQUEST['plg_id'];
    
    $sql = "DELETE FROM rms_pledge WHERE plg_id=$id";
    
    $global['db']->Execute($sql);
    
    if($global['db']->ErrorMsg())
    {
        _shn_rms_adderror($global['db']->ErrorMsg());
        _shn_rms_showerrors();
    }
    else
    {
        print "<h3>The Pledge was successfully Removed</h3>";
        
        #back to list view
        shn_form_fopen("vw_plgs",null,array('req_message'=>false));
        shn_form_submit('Back to List',"short");
        shn_form_fclose();
    }
}
    
switch ($_REQUEST['seq'])
{
    case 'confirm':
            _shn_rms_show_confirmdel();
            break;
    
    case 'del':
            _shn_rms_del_plg();            
            break;                
}
?>