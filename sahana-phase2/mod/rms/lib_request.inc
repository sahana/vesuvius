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


function _shn_rms_clear_reqsession()
{
    unset($_SESSION['rms_requester']);        
    unset($_SESSION['rms_site']);
    unset($_SESSION['rms_request']);
    unset($_SESSION['rms_item']);
}


function _shn_rms_get_site($id)
{
    global $global;
    $sql = "SELECT * FROM rms_req_site WHERE id='$id'";
    $rs = $global['db']->Execute($sql);
    $arr = $rs->GetArray();
    return $arr[0];
}

function _shn_rms_get_requesterter($id)
{
    global $global;
    $sql = "SELECT * FROM rms_org_psn WHERE id='$id'";
    $rs = $global['db']->Execute($sql);
    $arr = $rs->GetArray();
    
    if ($rs == null)
    {
        _shn_rms_adderror("Please enter a valid ID");
        return false;
    }
    
    if (1>$rs->RecordCount())
    {
        _shn_rms_adderror("Requester does not exist");
        return false;
    }
    
    return $arr[0];
}

function _shn_rms_get_items($id)
{
    global $global;
    $sql = "SELECT itm.id AS id, itm.name AS name, itm.cat_id AS cat_id, " .
                "itm.unit AS unit, itm.qty AS qty, ri.priority_id AS pry_id " .
            "FROM rms_item itm, rms_req_item ri " .
            "WHERE ri.req_id='$id'" .
            "AND ri.item_id=itm.id";
    $rs = $global['db']->Execute($sql);
    $arr = $rs->GetArray();
    return $arr;
}

function _shn_rms_get_req_stat($req_id)
{
    global $global;
    $sql = "SELECT status FROM rms_request WHERE id=$req_id";
    $rs = $global['db']->Execute($sql);
    
    if ($rs == null)
        return null;
    
    $arr = $rs->GetArray();
    return $arr[0][0];
}

function _shn_rms_show_req_stat($req_id)
{
    
    print "<h4>" . _("Request Status") . " : " . strtoupper(_shn_rms_get_req_stat($req_id)) . "</h4>";
}

function _shn_rms_show_items($items)
{
?>
<div>
<h4>Requested Items</h4>
<table id="result">
    <tr id="head">
        <td><?php print _("Category") ?></td>
        <td><?php print _("Item") ?></td>
        <td><?php print _("Units") ?></td>
        <td><?php print _("Quantity") ?></td>
        <td><?php print _("Priority") ?></td>
    </tr>
<?php
    foreach($items as $item)
    {
        $cat = _shn_rms_get_catname($item['cat_id']);
        $itm = $item['name'];
        $unt = $item['unit'];
        $qty = $item['qty'];
        $pry = _shn_rms_get_pryname($item['pry_id']);
?>
    <tr>
        <td><?php print  $cat; ?></td>
        <td><?php print  $itm; ?></td>
        <td><?php print  $unt; ?></td>
        <td><?php print  $qty; ?></td>
        <td><?php print  $pry; ?></td>
    </tr>
        
<?php
    }
?>
</table>
</div>
<?php
}

function _shn_rms_show_requester ($requester)
{
    print "<div>" .
            "<h4>Requester Information</h4>";
    shn_form_label("Requester ID : ", $requester['id']);
    shn_form_label("Requester Name : ", $requester['name']);
    shn_form_label("Location : ", $requester['location']);
    shn_form_label("Telephone # : ", $requester['telephone']);
    shn_form_label("Email : ", $requester['email']);
    shn_form_label("Address (postal) : ", $requester['address']);
    shn_form_label("Comments : ", $requester['comments']);
    print "</div><br/>";
}

function _shn_rms_show_site($site)
{
    print "<div>" .
            "<h4>Site Information</h4>";
    shn_form_label("Site ID : ", $site['id']);
    shn_form_label("Site Name : ", $site['name']);
    shn_form_label("Address : ", $site['address']);
    shn_form_label("Location : ", $site['location']);
    print "</div><br/>";
}

function _shn_rms_show_request($id)
{
    global $global;
    $sql = "SELECT * FROM rms_request WHERE id='$id'";
    $rs = $global['db']->Execute($sql);
    
    if (1>$rs->RecordCount())
    {
        _shn_rms_adderror("Invalid Request ID. Please enter a valid ID");
        return false;
    }
    $request    = $rs->GetArray();
    $request    = $request[0];
    $requester  = _shn_rms_get_requesterter($request['requester_id']);
    $site       = _shn_rms_get_site($request['site_id']);
    $items      = _shn_rms_get_items($id);
    
    _shn_rms_show_req_stat($request['id']);
    _shn_rms_show_requester($requester);
    _shn_rms_show_site($site);
    _shn_rms_show_items($items);
    print "<br/>";
    
}


?>