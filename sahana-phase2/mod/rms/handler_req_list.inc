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

_shn_rms_show_headder(_("List of Current Requests"));

function _shn_rms_get_allreq()
{
    global $global;
    $sql = "SELECT * FROM rms_request";
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

function _shn_rms_get_reqitems($req_id)
{
    global $global;
    
    $sql = "SELECT distinct(i.name) FROM rms_item i, rms_req_item ri WHERE ri.req_id = $req_id AND i.id = ri.req_id";
    
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

function _shn_rms_get_reqcats($req_id)
{
    global $global;
    
    $sql = "SELECT distinct(i.cat_id) FROM rms_item i, rms_req_item ri WHERE ri.req_id = $req_id AND i.id = ri.req_id";
    
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

function _shn_rms_get_requestername($requester_id)
{
    global $global;
    
    $sql = "SELECT name FROM rms_org_psn WHERE id = $requester_id";
    
    $rs = $global['db']->Execute($sql);
    
    if ($rs == null || $global['db']->ErrorMsg() != null)
    {
        _shn_rms_adderror($global['db']->ErrorMsg());
        _shn_rms_showerrors();
        return false;
    }
    
    $arr = $rs->GetArray();
    return $arr[0][0];
}

function _shn_rms_get_sitename($site_id)
{
    global $global;
    
    $sql = "SELECT name FROM rms_req_site WHERE id = $site_id";
    
    $rs = $global['db']->Execute($sql);
    
    if ($rs == null || $global['db']->ErrorMsg() != null)
    {
        _shn_rms_adderror($global['db']->ErrorMsg());
        _shn_rms_showerrors();
        return false;
    }
    
    $arr = $rs->GetArray();
    return $arr[0][0];
}

function _shn_rms_show_requestlist()
{
    $reqs = _shn_rms_get_allreq();
?>
<div>
<table id="result">
    <tr id="head">
        <td><?php print _("ID") ?></td>
        <td><?php print _("Status") ?></td>
        <td><?php print _("Date") ?></td>
        <td><?php print _("Requester") ?></td>
        <td><?php print _("Site") ?></td>
        <td><?php print _("Categories") ?></td>
        <td><?php print _("Items") ?></td>
        <td><?php print _("More Details") ?></td>
    </tr>
<?php

    foreach($reqs as $rq)
    {
        $catarr = _shn_rms_get_reqcats($rq['id']);
        $itmarr = _shn_rms_get_items($rq['id']);
        $cats = '';
        $items = '';
        
        foreach ($catarr as $cat)
        {
            $cats .= _shn_rms_get_catname($cat['cat_id']) . "<br/>";
        }
        
        foreach ($itmarr as $itm)
        {
            $items .= $itm['name'] . "<br/>";
        }
        
        $req_id = $rq['id'];
        $stat = $rq['status']=='open'?$stat = '<strong>OPEN</strong>':$stat = '<em>'.$rq['status'].'</em>';
        $date = $rq['date'];
        $reqstr = _shn_rms_get_requestername($rq['requester_id']);
        $site = _shn_rms_get_sitename($rq['site_id']);
?>
    <tr>
        <td><?php print  $req_id; ?></td>
        <td><?php print  $stat; ?></td>
        <td><?php print  $date; ?></td>
        <td><?php print  $reqstr; ?></td>
        <td><?php print  $site; ?></td>
        <td><?php print  $cats; ?></td>
        <td><?php print  $items; ?></td>
        <td>
        <?php
            #more details button
            shn_form_fopen("req_list",null);
            shn_form_hidden(array('seq'=>'vw_req'));            
            shn_form_hidden(array('id'=>$rq['id']));
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

function _shn_rms_show_reqdetails()
{
    _shn_rms_show_request($_POST['id']);
    
    #back button
    shn_form_fopen("req_list",null);
    shn_form_hidden(array('seq'=>''));            
    shn_form_submit('Back',"short");
    shn_form_fclose();
    
}

switch ($_REQUEST['seq'])
{
    case '':
            _shn_rms_show_requestlist();
            break;
    
    case 'vw_req':
            _shn_rms_show_reqdetails();            
            break;                
}
?>