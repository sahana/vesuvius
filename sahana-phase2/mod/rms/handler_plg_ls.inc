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

_shn_rms_show_headder(_("List of Current Pledges"));

function _shn_rms_get_allplgs()
{
    global $global;
    $sql = "SELECT * FROM rms_pledge";
    $rs = $global['db']->Execute($sql);
    
    if ($rs == null || $global['db']->ErrorMsg() != null)
    {
        _shn_rms_adderror($global['db']->ErrorMsg());
        _shn_rms_showerrors();
        return false;
    }
    
    $arr = $rs->GetArray();
    
    return $arr;
}

function _shn_rms_show_plglist()
{
    $plgs = _shn_rms_get_allplgs();
?>
<div>
<table id="result">
    <tr id="head">
        <td><?php print _("ID") ?></td>
        <td><?php print _("Status") ?></td>
        <td><?php print _("Date") ?></td>
        <td><?php print _("Donor") ?></td>
        <td><?php print _("Category") ?></td>
        <td><?php print _("Item") ?></td>
        <td><?php print _("More Details") ?></td>
    </tr>
<?php

    foreach($plgs as $plg)
    {
?>
    <tr id="body">
        <td><?php print  $plg['plg_id']; ?></td>
        <td><?php print  $plg['status']; ?></td>
        <td><?php print  $plg['date']; ?></td>
        <td><?php print  get_donor_name($plg['user_id']); ?></td>
        <td><?php print  get_plg_category($plg['cat_id']); ?></td>
        <td><?php print  $plg['item']; ?></td>
        <td>
        <?php
            #more details button
            shn_form_fopen("vw_plgs",null);
            shn_form_hidden(array('seq'=>'vw_plg'));            
            shn_form_hidden(array('id'=>$plg['plg_id']));
            shn_form_submit('More',"shorter");
            shn_form_fclose();
        ?>
        </td>
    </tr>
        
<?php
    }
?>
</table>
</div>
<?php
}

function _shn_rms_show_plgdetails()
{
    _shn_rms_plg_view($_POST['id']);
    
    #back button
    shn_form_fopen("vw_plgs",null);
    shn_form_hidden(array('seq'=>''));            
    shn_form_submit('Back',"short");
    shn_form_fclose();
    
}

switch ($_REQUEST['seq'])
{
    case '':
            _shn_rms_show_plglist();
            break;
    
    case 'vw_plg':
            _shn_rms_show_plgdetails();            
            break;                
}
?>