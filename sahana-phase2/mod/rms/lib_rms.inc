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


function _shn_rms_print_hedder($string=null)
{
	if (!$string)
        print '<h2>' . _("Welcome to The Sahana ") . shn_get_module_name() . '</h2>';
    else
        print '<h2>' . $string . '</h2>';
}

function _shn_rms_add_requester($requester)
{
    global $global;
    
    $p_uuid = shn_create_uuid('p');
    $name   = $requester['name'];
    $mobile = $requester['mobile'];
    $email  = $requester['email'];
    $addr   = $requester['address'];
    
    $sql = "INSERT INTO person_uuid (p_uuid, full_name) " .
            "VALUES ('$p_uuid', '$name')";
    
    if ($global['db']->Execute($sql) === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
    }
    else
    {
        if (trim($mobile) != '')
            _shn_rms_db_addcontact($p_uuid, 'mobile', $mobile);
        if (trim($email) != '')
            _shn_rms_db_addcontact($p_uuid, 'email', $email);
        if (trim($addr) != '')
            _shn_rms_db_addcontact($p_uuid, 'address', $addr);
        
        return $p_uuid;
    }
    
    
}

function _shn_rms_is_person($id)
{
    global $global;
    
    $sql = "SELECT * FROM person_uuid WHERE p_uuid='$id'";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        return true;
    }
    
    return false;
}

function _shn_rms_get_person($id)
{
    global $global;
    
    $sql = "SELECT * FROM person_uuid WHERE p_uuid='$id'";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        $psn_arr = $rs->GetArray();
        $person['uuid'] = $psn_arr[0]['p_uuid'];
        $person['name'] = $psn_arr[0]['full_name'];
        
        $sql = "SELECT * FROM contact WHERE pgoc_uuid='$id'";
        $rs_cnt = $global['db']->Execute($sql);
        
        if ($rs_cnt !== null)
        {
            $rs_cnts = $rs_cnt->GetArray();
            foreach ($rs_cnts as $c)
            {
                $person[$c['opt_contact_type']] = $c['contact_value'];
            }
        }
        
        return $person;
    }
    
    return false;
}

function _shn_rms_is_requester($id)
{
    global $global;
    
    $sql = "SELECT * FROM rms_request WHERE reqstr_uuid='$id'";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        return true;
    }
    
    return false;
}

function _shn_rms_get_requester($id)
{
    if (_shn_rms_is_requester($id))
    {
        return _shn_rms_get_person($id);
    }

    return false;
}

function _shn_rms_get_location($loc_id)
{
    global $global;
    
    $sql = "SELECT * FROM location_details " .
            "WHERE location_id='$loc_id'";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        $rs = $rs->GetArray();
        return $rs[0];
    }
    
    return false;
}

function _shn_rms_add_requester_loc($id, $location)
{
    global $global;
    
    $poc_uuid = $id;
    $location_id = $location['id'];
    $type = $location['type'];
    $address = $location['address'];
    $postcode = $location['postcode'];
    $gis = $location['gis'];
    
    $sql = "INSERT INTO location_details ( " .
                                           "poc_uuid, " .
                                           "location_id, " .
                                           "opt_person_loc_type, " .
                                           "address, " .
                                           "postcode, " .
                                           "long_lat) " .
            "VALUES ('$poc_uuid', '$location_id', '$type', '$address', " .
                    "'$postcode', '$gis')";
            
    if ($global['db']->Execute($sql) === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    else
    {
        return true;
    }
}

function _shn_rms_get_requester_locs($id)
{
    global $global;
    
    $sql = "SELECT poc_uuid, location_id FROM location_details " .
            "WHERE poc_uuid='$id'";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        $rs = $rs->GetArray();
        foreach ($rs as $r)
            $locs[$r['location_id']] = $r['location_id'];      
        return $locs;
    }
    
    return false;
}

function _shn_rms_get_shnuser()
{
    $user_id = 'p-999';
    return $user_id;
}

function _shn_rms_get_categories()
{
    global $global;
    
    $sql = "SELECT * FROM ct_catalogue WHERE parentid=''";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        return $rs->GetArray();
    }
    
    return false;
}

function _shn_rms_get_priorities()
{
    global $global;
    
    $sql = "SELECT * FROM rms_priority";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        return $rs->GetArray();
    }
    else
    {
        return array();
    }
    
}

function _shn_rms_get_items($cat_id)
{
    global $global;
    
    $sql = "SELECT * FROM ct_catalogue WHERE parentid='$cat_id'";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        return $rs->GetArray();
    }
    
    return false;
}

function _shn_rms_add_item2session($itm, $qty, $pri)
{
    if ($qty != '' && is_numeric($qty))
    {
        $_SESSION['rms_items'][] = array ($itm, $qty, $pri);
        return true;    
    }
    else
    {
        add_error(_("Please Enter a valid Quantity"));
        return false;
    }
}

function _shn_rms_add_item2session_pl($itm, $qty, $stat)
{
    if ($qty != '' && is_numeric($qty))
    {
        $_SESSION['rms_items'][] = array ($itm, $qty, $stat);
        return true;    
    }
    else
    {
        add_error(_("Please Enter a valid Quantity"));
        return false;
    }
}

function _shn_rms_del_itemfromsession($itm_id)
{
    $items = $_SESSION['rms_items'];
    $_SESSION['rms_items'] = null;
    
    foreach ($items as $item)
    {
        if ($item[0] != $itm_id)
            $_SESSION['rms_items'][] = $item;
    }
}

function _shn_rms_is_itemadded($item)
{
    if (is_array($_SESSION['rms_items']))
    {
        foreach ($_SESSION['rms_items'] as $itm)
        {
            if ($itm[0] == $item)
                return true;
        }
    }
    return false;
}

function _shn_rms_get_itemname($itm_id)
{
    global $global;
    
    $sql = "SELECT name FROM ct_catalogue WHERE ct_uuid='$itm_id'";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        $rs = $rs->GetArray();
        return $rs[0][0];
    }
    
    return false;
}

function _shn_rms_get_priorityname($pri_id)
{
    global $global;
    
    $sql = "SELECT priority FROM rms_priority WHERE pri_uuid='$pri_id'";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        $rs = $rs->GetArray();
        return $rs[0][0];
    }
    
    return false;
}

/***
 * Request Specific functions
 */
function _shn_rms_add_request($reqstr_uuid, $loc_uuid)
{
    global $global;
    
    $req_uuid = shn_create_uuid('r');
    $status = 'open';
    $user_id = 'u-1';
    
    $sql = "INSERT INTO rms_request (req_uuid, reqstr_uuid, loc_uuid, status, user_id) " .
            "VALUES ('$req_uuid', '$reqstr_uuid', '$loc_uuid', '$status', '$user_id')";
    
    if ($global['db']->Execute($sql) === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
    }
    else
    {
        _shn_rms_add_reqitems($req_uuid);
        return $req_uuid;
    }
    
}

function _shn_rms_add_reqitems($req_uuid)
{
    global $global;
    
    foreach ($_SESSION['rms_items'] as $item)
    {
        $item_uuid = $item[0];
        $quantity = $item[1];
        $pri_uuid = $item[2];
        
        $sql = "INSERT INTO rms_req_item " .
                "VALUES ('$item_uuid', $quantity, '$pri_uuid', '$req_uuid')";
        
        if ($global['db']->Execute($sql) === false)
        {
            $msg = $global['db']->ErrorMsg();
            add_error($msg . '<br />' . $sql);
            display_errors();
        }
    }
}

function _shn_rms_get_recordcount($table, $fstr)
{
    global $global;
    
    $sql = "SELECT COUNT(*) FROM $table";
    $sql .= $fstr;
    $rs = $global['db']->Execute($sql);
    
    $rs = $rs->GetArray();
    return $rs[0][0];
}

function _shn_rms_get_reqitems($req_uuid)
{
    global $global;
    
    $sql = "SELECT * FROM rms_req_item WHERE req_uuid='$req_uuid'";
    
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        $rs = $rs->GetArray();
        return $rs;
    }
}

function _shn_rms_get_plgitems($plg_uuid)
{
    global $global;
    
    $sql = "SELECT * FROM rms_plg_item WHERE plg_uuid='$plg_uuid'";
    
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        $rs = $rs->GetArray();
        return $rs;
    }
}

function _shn_rms_get_itm_category($itm_id)
{
    $sql = "SELECT DISTINCT(cat.ct_uuid),cat.name " .
           "FROM ct_catalogue itm, ct_catalogue cat " .
           "WHERE itm.parentid=cat.ct_uuid " .
           "AND itm.ct_uuid='$itm_id'";
    
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        $rs = $rs->GetArray();
        $cat[$rs[0][0]] = $rs[0][1];
        return $cat;
    }
    
    return false;
}

/***
 * Donor Functions
 */
function _shn_rms_add_donor($donor)
{
    global $global;
    
    $p_uuid = shn_create_uuid('p');
    $name   = $donor['name'];
    $mobile = $donor['mobile'];
    $email  = $donor['email'];
    $addr   = $donor['address'];
    
    $sql = "INSERT INTO person_uuid (p_uuid, full_name) " .
            "VALUES ('$p_uuid', '$name')";
    
    if ($global['db']->Execute($sql) === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
    }
    else
    {
        if (trim($mobile) != '')
            _shn_rms_db_addcontact($p_uuid, 'mobile', $mobile);
        if (trim($email) != '')
            _shn_rms_db_addcontact($p_uuid, 'email', $email);
        if (trim($addr) != '')
            _shn_rms_db_addcontact($p_uuid, 'address', $addr);
        
        return $p_uuid;
    }
    
    
}

function _shn_rms_is_donor($id)
{
    global $global;
    
    $sql = "SELECT * FROM rms_pledge WHERE donor_uuid='$id'";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        return true;
    }
    
    return false;
}

function _shn_rms_get_donor($id)
{
    if (_shn_rms_is_donor($id))
    {
        return _shn_rms_get_person($id);
    }

    return false;
}

function _shn_rms_add_pledge($donor_uuid)
{
    global $global;
    
    $plg_uuid = shn_create_uuid('pl');
    $status = 'Not Delivered';
    $user_id = 'u-1';
    
    $sql = "INSERT INTO rms_pledge (plg_uuid, donor_uuid, status, user_id) " .
            "VALUES ('$plg_uuid', '$donor_uuid', '$status', '$user_id')";
    
    if ($global['db']->Execute($sql) === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    else
    {
        _shn_rms_add_plgitems($plg_uuid);
        return $plg_uuid;
    }
    
}

function _shn_rms_add_plgitems($plg_uuid)
{
    global $global;
    
    foreach ($_SESSION['rms_items'] as $item)
    {
        $item_uuid = $item[0];
        $quantity = $item[1];
        
        $sql = "INSERT INTO rms_plg_item (item_uuid, quantity, plg_uuid) " .
                "VALUES ('$item_uuid', $quantity, '$plg_uuid')";
        
        if ($global['db']->Execute($sql) === false)
        {
            $msg = $global['db']->ErrorMsg();
            add_error($msg . '<br />' . $sql);
            display_errors();
        }
    }
}

function _shn_rms_add_ff($req_uuid, $item_uuid, $plg_uuid, $qty)
{
    global $global;
    
    //$plg_uuid = shn_create_uuid('ff');
    //$user_id = 'u-1';
    
    $sql = "INSERT INTO rms_fulfil (req_uuid, item_uuid, plg_uuid, quantity) " .
            "VALUES ('$req_uuid', '$item_uuid', '$plg_uuid', $qty)";
    
    if ($global['db']->Execute($sql) === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    else
    {
        return true;
    }
    
}

/***
 * Html template helpers
 */
function _shn_html_inform_add($message)
{
    $_SESSION['html_info'][] = $message;
}

function _shn_html_inform_show()
{
    if (!isset($_SESSION['html_info']) || empty($_SESSION['html_info']))
        return false;
    
    $infor_msgs = $_SESSION['html_info'];
    
?>
<div id="error"> <!-- TODO: change style -->
    <p><em><?php print _("Information") . ' :'?></em></p>
    <ul>
<?php
    foreach ( $infor_msgs as $info )
    {
?>
    <li><?=$info?></li>
<?php
    }
?>
    </ul>
</div>
<?php
    $_SESSION['html_info'] = null;
}

function _shn_html_print_alert($alert)
{
?>
<div class="alert"> <!-- TODO: change style -->
    <strong><?php print _("Alert") . " : $alert"?></strong>
</div>
<?php
}

function _shn_html_print_message($msg,$br = false)
{
    $br_str = '';
    if ($br == true)
        $br_str = '<br />';
?>
    <div class="message">
    <strong><small><?php print $msg?></small></strong>
    <?php print $br_str ?>
    </div>
<?php
}

function _shn_rms_get_request($req_uuid)
{
    global $global;
    $sql = "SELECT * FROM rms_request WHERE req_uuid='$req_uuid'";
    
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        $rs = $rs->GetArray();
        return $rs[0];
    }
    else
    {
        return false;
    }
}

function _shn_rms_get_pledge($plg_uuid)
{
    global $global;
    $sql = "SELECT * FROM rms_pledge WHERE plg_uuid='$plg_uuid'";
    
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        $rs = $rs->GetArray();
        return $rs[0];
    }
}

function _shn_rms_is_reqstatus($status)
{
    $stats = array ('open', 'closed');
    
    foreach ($stats as $stat)
    {
        if ($stat == $status)
        {
            return true;
        }
    }
    
    return false;
}

function _shn_rms_is_plgstatus($status)
{
    $stats = array ('open', 'closed');
    
    foreach ($stats as $stat)
    {
        if ($stat == $status)
        {
            return true;
        }
    }
    
    return false;
}

function _shn_rms_view_requester($reqstr_id)
{
    print '<h4>' . _("Requester Contact Information") . '</h4>';
    
    $requester = _shn_rms_get_person($reqstr_id);
    $tmp_str = '<strong>' . _("RequesterID") . '</strong>';
    $tb_reqstr[] = array($tmp_str , '<strong>' . $reqstr_id . '</strong>');
    $tb_reqstr[] = array(_("Full Name"), $requester['name']);
    $tb_reqstr[] = array(_("Address"), $requester['address']);
    $tb_reqstr[] = array(_("email"), $requester['email']);
    $tb_reqstr[] = array(_("Mobile"), $requester['mobile']);
    $tb_reqstr[] = array(_("Telephone"), $requester['telephone']);
    
    shn_html_table($tb_reqstr,null,null,array('class'=>'wide'));
}

function _shn_rms_view_donor($donor_id)
{
    print '<h4>' . _("Donor Contact Information") . '</h4>';
    
    $requester = _shn_rms_get_person($donor_id);
    $tmp_str = '<strong>' . _("Donor ID") . '</strong>';
    $tb_reqstr[] = array($tmp_str , '<strong>' . $donor_id . '</strong>');
    $tb_reqstr[] = array(_("Full Name"), $requester['name']);
    $tb_reqstr[] = array(_("email"), $requester['email']);
    $tb_reqstr[] = array(_("Mobile"), $requester['mobile']);
    $tb_reqstr[] = array(_("Telephone"), $requester['telephone']);
    $tb_reqstr[] = array(_("Address"), $requester['address']);
    
    shn_html_table($tb_reqstr,null,null,array('class'=>'wide'));
}

function _shn_rms_view_location($loc_id)
{
    print '<h4>' . _("Request Location Information") . '</h4>';

    $location = _shn_rms_get_location($loc_id);
    $tmp_str = '<strong>' . _("Location ID") . '</strong>';
    $tb_loc[] = array($tmp_str , '<strong>' . $loc_id . '</strong>');
    $tb_loc[] = array(_("Name"), $location['location_id']);
    $tb_loc[] = array(_("Location Type"), $location['opt_person_loc_type']);
    $tb_loc[] = array(_("Address"), $location['address']);
    $tb_loc[] = array(_("Post code"), $location['postcode']);
    $tb_loc[] = array(_("GIS"), $location['long_lat']);
    
    shn_html_table($tb_loc,null,null,array('class'=>'wide'));
}

function _shn_rms_view_reqitems($req_id)
{
    global $global;
    
    $rms_items = _shn_rms_get_reqitems($req_id);
    $th_items[] = array (_("Item"), _("Quantity"), _("Item Priority")); 
    foreach ($rms_items as $itm)
    {
        $tb_items[] = array (
                             _shn_rms_get_itemname($itm[0]), 
                             $itm[1], 
                             _shn_rms_get_priorityname($itm[2])
                            );
    }
    
    print '<h4>' . _("Request Items") . '</h4>';
    shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
    print '<br />';
}

function _shn_rms_view_reqff($req_id)
{
    global $global;
    $rms_items = array();
    
    // @TODO: check compatibility of the sql statement
    $sql = "SELECT req.req_uuid AS req_uuid, req.item_uuid AS item_uuid, " .
                "req.pri_uuid AS pri_uuid, " .
                "ff.plg_uuid AS plg_uuid, req.quantity AS req_qty, " .
                "ff.quantity AS ff_qty, ff.ff_date AS ff_date " .
           "FROM rms_req_item req LEFT JOIN rms_fulfil ff " .
           "ON ff.item_uuid=req.item_uuid " .
           "AND req.req_uuid=ff.req_uuid " .
           "WHERE req.req_uuid='$req_id'";
    
    $rs = $global['db']->Execute($sql);

    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        $rs = $rs->GetArray();
        $rms_items = $rs;
    }
    else
    {
        return false;
    }
    
    $th_items[] = array (_("Item"), _("Priority"), _("Requested"), _("Fulfiled"), _("Date"), ''); 
    foreach ($rms_items as $itm)
    {
        $sel_url = '<a href=index.php?mod=rms&amp;act=mng_ff' .
                    '&amp;seq=sel_plg&amp;itm_id=' . $itm['item_uuid'] .'>' .
                    _("Select") . '</a>';
                    
        $tb_items[] = array (
                             _shn_rms_get_itemname($itm['item_uuid']), 
                             _shn_rms_get_priorityname($itm['pri_uuid']),
                             $itm['req_qty'],
                             $itm['ff_qty'],
                             $itm['ff_date'],
                             $sel_url
                            );
    }
    
    print '<h4>' . _("Request Fulfilment Status") . '</h4>';
    shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
    print '<br />';
}

function _shn_rms_view_request($req_id)
{
    $request = _shn_rms_get_request($req_id);
    if (!$request)
        return false;
    $date = $request['date'];
    $status = $request['status'];
    $shn_usr = $request['user_id'];
    
    print '<h3>' . _("The Request ID: ") . $req_id . '</h3>';
    print '<br />';
    _shn_rms_view_requester($request['reqstr_uuid']);
    print '<br />';
    _shn_rms_view_location($request['loc_uuid']);
    print '<br />';
    _shn_rms_view_reqitems($req_id);
}

function _shn_rms_view_plgitems($plg_id)
{
    global $global;
    
    $rms_items = _shn_rms_get_plgitems($plg_id);
    $th_items[] = array (_("Item"), _("Quantity")); 
    foreach ($rms_items as $itm)
    {
        $tb_items[] = array (
                             _shn_rms_get_itemname($itm[0]), 
                             $itm[1]
                            );
    }
    
    print '<h4>' . _("Pledge Items") . '</h4>';
    shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
    print '<br />';
    
}

function _shn_rms_view_pledge($plg_id)
{
    $pledge = _shn_rms_get_pledge($plg_id);
    $date = $pledge['date'];
    $status = $pledge['status'];
    $shn_usr = $pledge['user_id'];
    
    print '<h3>' . _("The Pledge ID: ") . $plg_id . '</h3>';
    print '<br />';
    _shn_rms_view_donor($pledge['donor_uuid']);
    print '<br />';
    _shn_rms_view_plgitems($plg_id);
}

?>
