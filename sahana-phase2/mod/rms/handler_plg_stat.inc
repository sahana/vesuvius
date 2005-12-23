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


function __change_plg_status()
{
?>

<h4>Pledge Status for pledge id : <?=$_REQUEST['plg_id']?> (<?=_shn_rms_get_plgstat($_REQUEST['plg_id'])?>)</h4>

<?php
    if(_shn_rms_get_plgstat($_REQUEST['plg_id']) == 'not confirmed')
    {    
        #back to list view
        print "Change Pledge Status to : <em>Confirmed</em>";
        shn_form_fopen("stat_plgs",null,array('req_message'=>false));
        shn_form_hidden(array('plg_id'=>$_REQUEST['plg_id']));
        shn_form_hidden(array('stat'=>'confirmed'));
        shn_form_hidden(array('seq'=>'set'));
        shn_form_hidden(array('from'=>$_POST['from']));
        shn_form_submit('Confirmed',"short");
        shn_form_fclose();
    }
    else
    {
        #back to list view
        print "Change Pledge Status to : <em>Not Confirmed</em>";
        shn_form_fopen("stat_plgs",null,array('req_message'=>false));
        shn_form_hidden(array('plg_id'=>$_REQUEST['plg_id']));
        shn_form_hidden(array('stat'=>'not confirmed'));
        shn_form_hidden(array('seq'=>'set'));
        shn_form_hidden(array('from'=>$_POST['from']));
        shn_form_submit('Not Confirmed',"short");
        shn_form_fclose();
    }
}

function _shn_rms_get_plgstat($id)
{
    global $global;
    
    $sql ="SELECT status FROM rms_pledge WHERE plg_id=$id";
    
    $rs = $global['db']->Execute($sql);
    
    $rs = $rs->GetArray();
    
    return $rs[0][0];
    
} 

function _shn_rms_setstat_plg($id,$stat)
{
    global $global;
    
    $from = $_POST['from'];   
    $sql ="UPDATE rms_pledge SET status = '$stat' WHERE plg_id=$id";
    
    $global['db']->Execute($sql);
    
    if($global['db']->ErrorMsg())
    {
        _shn_rms_adderror($global['db']->ErrorMsg());
        _shn_rms_showerrors();
    }
    else
    {
        print "<h3>The Pledge Status was successfully Updated to : '$stat'</h3>";
        
        if($from == 'list')
        {
            #back to list view
            shn_form_fopen("vw_plgs",null,array('req_message'=>false));
            shn_form_submit('Back to List',"short");
            shn_form_fclose();
        }
        elseif($from == 'view')
        {
            #back to list view
            shn_form_fopen("vw_plg",null,array('req_message'=>false));
            shn_form_hidden(array('plg_id'=>$id));
            shn_form_hidden(array('seq'=>'view'));
            shn_form_submit('Back to View',"short");
            shn_form_fclose();
        }
    }
}   
    
switch ($_REQUEST['seq'])
{
    case '':
            __change_plg_status();
            break;
    
    case 'set':
            _shn_rms_setstat_plg($_POST['plg_id'],$_POST['stat']);            
            break;                
}
?>