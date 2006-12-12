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



function _shn_rms_requester($requester_id=null)
{
    $_SESSION['rms_reqstr_id'] = null;
    
    _shn_rms_print_hedder(_("Make New Request"));
    shn_form_fopen("req_new",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'add_reqstr'));
    shn_form_fsopen(_("New Requester"));
    print '<div class="info">';
    print _("Create New Requester: ");
    print _("A new Person will be added to the Sahana Database,");
    print '<br />';
    print _("Only the Full Name is required, But in order to Contact the Requester please add some contact information with this");
    print '<br />';
    print '</div>';
    print '<br />';
    
    
    shn_form_text(_("Full Name"),'name',null,array('req'=>true));
    shn_form_text(_("Mobile"),'mobile');
    shn_form_text(_("Email"),'email');
    shn_form_opt_select("opt_id_type",_("Available Card type"));
    shn_form_text(_("Card Number"),"card_number",null,array('req'=>true));
    shn_form_text(_("Telephone"),'telephone',null);
    shn_form_textarea(_("Address"),'address',null);
   // shn_form_textarea(_("Address"),'address',null);
    
    
    shn_form_fsclose();
    shn_form_submit(_("Next"));
    shn_form_fclose();
    print '<br />';
    
    
    shn_form_fopen("req_new",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'get_reqstr'));
    shn_form_fsopen(_("Existing Requester"));
    print '<div class="info">';
    print _("If you are a registered requester, Please enter the card number ");
    print '<br />';
    //print _("You can also use your 'id' if you have registered on the sahana system as a user, administrator, volunteer etc...");
    //print '<br />';
    
    print '</div>';
    print '<br />';
    shn_form_text(_("Any Card Number"),'card_number',null,array('req'=>true,'br'=>false));
    shn_form_fsclose();
    shn_form_submit(_("Next"), 'id="reqstr_next"');
    shn_form_fclose();
    print '<br />';
    
}


function _shn_rms_requester_new()
{
    if (trim($_POST['name']) != '' & $_POST['card_number']!='')
    {
        $requester['name'] = $_POST['name'];
        $requester['mobile'] = $_POST['mobile'];
        $requester['email'] = $_POST['email'];
        $requester['telephone'] = $_POST['telephone'];
        $requester['address'] = $_POST['address'];
        $requester['opt_id_type']=$_POST['opt_id_type'];
        $requester['card_number']=$_POST['card_number'];
        
        
        $id = _shn_rms_add_requester($requester);
        
        $_SESSION['rms_reqstr_id'] = $id;
        
        
       // $msg = _("Your Requester id: $id, Please write down this ID");
       // _shn_html_inform_add($msg);
      //  _shn_html_inform_show();
        return true;
        
    }
    else
    {
        add_error(_("Please fill all the required fields"));
        display_errors();
        _shn_rms_requester();
        return false;
    }
    
}

function _shn_rms_requester_update()
{
    $updated = null;
    $added = null;
    
    $id = $_POST['reqstr_id'];
    $name = $_POST['name'];
    $mobile = $_POST['mobile']; 
    $email = $_POST['email']; 
    $telephone = $_POST['telephone']; 
    $address = $_POST['address'];
    $requester = _shn_rms_get_person($id);
    
    
    //Add or update Full Name
    if ($requester['name'] != $name)
    {
        global $global;
        $sql = "UPDATE person_uuid SET full_name='$name' WHERE p_uuid='$id'";
        
        if ($global['db']->Execute($sql) === false)
        {
            $msg = $global['db']->ErrorMsg();
            add_error($msg . '<br />' . $sql);
            display_errors();
        }
        else
        {
            $updated[] = _("Full Name");
        }
    }
    
    //Add or update contact-mobile
    if ($requester['mobile'] != $mobile)
    {
        global $global;
        
        if (_snf_rms_db_is_contactex($id, 'mobile'))
        {
            $sql = "UPDATE contact SET contact_value='$mobile' " .
                    "WHERE pgoc_uuid='$id' AND opt_contact_type='mobile'";
            if ($global['db']->Execute($sql) === false)
            {
                $msg = $global['db']->ErrorMsg();
                add_error($msg . '<br />' . $sql);
                display_errors();
            }
            else
            {
                $updated[] = _("Mobile");
            }
        }
        else
        {
            _shn_rms_db_addcontact($id, 'mobile', $mobile);
            $added[] = _("Mobile");
        }
    }
    
    //Add or update contact-email
    if ($requester['email'] != $email)
    {
        global $global;
        
        if (_snf_rms_db_is_contactex($id, 'email'))
        {
            $sql = "UPDATE contact SET contact_value='$email' " .
                    "WHERE pgoc_uuid='$id' AND opt_contact_type='email'";
            if ($global['db']->Execute($sql) === false)
            {
                $msg = $global['db']->ErrorMsg();
                add_error($msg . '<br />' . $sql);
                display_errors();
            }
            else
            {
                $updated[] = _("Email");
            }
        }
        else
        {
            _shn_rms_db_addcontact($id, 'email', $email);
            $added[] = _("Email");
        }
    }
    
    //Add or update contact-telephone
    if ($requester['telephone'] != $telephone)
    {
        global $global;
        
        if (_snf_rms_db_is_contactex($id, 'telephone'))
        {
            $sql = "UPDATE contact SET contact_value='$telephone' " .
                    "WHERE pgoc_uuid='$id' AND opt_contact_type='telephone'";
            if ($global['db']->Execute($sql) === false)
            {
                $msg = $global['db']->ErrorMsg();
                add_error($msg . '<br />' . $sql);
                display_errors();
            }
            else
            {
                $updated[] = _("Telephone");
            }
        }
        else
        {
            _shn_rms_db_addcontact($id, 'telephone', $telephone);
            $added[] = _("Telephone");
        }
    }
    
    //Add or update contact-Address
    if ($requester['address'] != $address)
    {
        global $global;
        
        if (_snf_rms_db_is_contactex($id, 'address'))
        {
            $sql = "UPDATE contact SET contact_value='$address' " .
                    "WHERE pgoc_uuid='$id' AND opt_contact_type='address'";
            if ($global['db']->Execute($sql) === false)
            {
                $msg = $global['db']->ErrorMsg();
                add_error($msg . '<br />' . $sql);
                display_errors();
            }
            else
            {
                $updated[] = _("Address");
            }
        }
        else
        {
            _shn_rms_db_addcontact($id, 'address', $address);
            $added[] = _("Address");
        }
    }
    
    if ($added != null)
    {
        foreach ($added as $a)
        {
            _shn_html_inform_add($a . ' - ' . _("Added"));
        }
    }
    
    if ($updated != null)
    {
        foreach ($updated as $u)
        {
            _shn_html_inform_add($u . ' - ' . _("Updated"));
        }
    }
    
    _shn_html_inform_show();
}

function _shn_rms_requester_conf($id)
{
    _shn_html_print_alert(_("You seem to be a new requester, Please confirm the contact information and enter missing " .
                "information"));

    $psn = _shn_rms_get_person($id);
    shn_form_fopen("req_new",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'reqstr_up'));
    shn_form_hidden(array('reqstr_id'=>$id));
    shn_form_fsopen(_("Confirm Person Information"));
    shn_form_text(_("Full Name"),'name', 'class=""', array('req'=>true,'value'=>$psn['name']));
    shn_form_text(_("Mobile"),'mobile', null, array('value'=>$psn['mobile']));
    shn_form_text(_("Email"),'email', 'class=""', array('value'=>$psn['email']));
    shn_form_text(_("Telephone"),'telephone', null, array('value'=>$psn['telephone']));
    shn_form_textarea(_("Address"),'address', null, array('value'=>$psn['address']));
    shn_form_fsclose();
    shn_form_submit(_("Next"));
    shn_form_fclose();
}

function _shn_rms_location($id = null)
{
    if ($id == null)
        $id = $_SESSION['rms_reqstr_id'];
    
    _shn_rms_view_requester($id,true);
    
    
    print '<br />';
    shn_form_fopen("req_new",null,array('req_message'=>false));
    shn_form_fsopen(_("Request Location"));
    include_once('lib_ajax.inc');
    _shn_rms_ajax_init('loc_camp');
    
    print '<div class="info">';
    print _("<strong>Select Request Location:</strong><br /> ");
    print _("Please select the Location Type, ");
    print _("Then select an <strong>Existing Location</strong> that is associated with the requester or ");
    print _("if it doesn't contain the the location you need create a <strong>New Location</strong>.'");
    print '<br />';
    print '</div>';
?>
  <input type="radio" disabled="disabled" name="location" value="Camp" onClick='makeRequest("stream.php?mod=rms&amp;act=req_new&amp;seq=ax_loc_camp","")' /> Camp  
  <input type="radio" disabled="disabled" name="location" value="Organization" onClick='makeRequest("stream.php?mod=rms&amp;act=req_new&amp;seq=ax_loc_org","")' /> Organization
  <input type="radio" checked="Checked" name="location" value="Other" onClick='makeRequest("stream.php?mod=rms&amp;act=req_new&amp;seq=ax_loc_other","")' /> Other
<?php
    print '<br />';
    print '<br />';
    print '<div id="loc_camp">';
    _shn_rms_ax_location_other();
    print '</div>';
    
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_rms_ax_location_other($id=null)
{
	if ($id == null)
        $id = $_SESSION['rms_reqstr_id'];
        
    {
        print '<div id="loc_new">';
        shn_form_fopen("req_new",null,array('req_message'=>false,'anchor'=>'items'));
        shn_form_hidden(array('seq'=>'add_loc'));
        shn_form_fsopen(_("New Location"));
        shn_form_text(_("Location Name"),'loc_name',null,array('req'=>true));
        shn_form_text(_("Location ID"),'location_id',null,array('req'=>true));
        shn_form_text(_("Type"),'opt_person_loc_type');
        shn_form_text(_("Code"),'postcode',null);
        shn_form_textarea(_("Address"),'loc_address',null,array('req'=>true));
        shn_form_textarea(_("GIS"),'gis',null);
        shn_form_fsclose();
        shn_form_submit(_("Add Location"));
        shn_form_fclose();
        print '</div><br />';
    }
    
    
    
    if (_shn_rms_get_requester_locs($id))
    {
        shn_form_fopen("req_new",null,array('req_message'=>false,'anchor'=>'items'));
        shn_form_hidden(array('seq'=>'get_loc'));
        shn_form_fsopen(_("Existing Location"));
        shn_form_select(_shn_rms_get_requester_locs($id),_("Location"), 'loc');
        shn_form_fsclose();
        shn_form_submit(_("Next"));
        shn_form_fclose();
    }    
}

function _shn_rms_location_add()
{
    $loc['name'] = trim($_POST['loc_name']);
    $loc['id'] = trim($_POST['location_id']);
    $loc['type'] = trim($_POST['opt_person_loc_type']);
    $loc['postcode'] = trim($_POST['postcode']);
    $loc['address'] = trim($_POST['loc_address']);
    $loc['gis'] = trim($_POST['gis']);
    
    if ($loc['name'] == '' || $loc['id'] == '' || $loc['address'] == '')
    {
        add_error(_("Please fill all the required fields"));
        display_errors();
        _shn_rms_location();
    }
    else
    {
        $id = $_SESSION['rms_reqstr_id'];
        print _shn_rms_add_requester_loc($id, $loc);
        _shn_rms_location();
    }
    
}

function _shn_rms_items($category = null)
{
    $categories = array();
    $items = array();
    $priorities = array();
    
    $pri_arr = _shn_rms_get_priorities(); 
    foreach ($pri_arr as $pri)
    {
        $priorities[$pri['pri_uuid']] = $pri['priority'];
    }

    $cat_arr = _shn_rms_get_categories();
    if ($category == null)
    {
        $item_arr = _shn_rms_get_items($cat_arr[0]['ct_uuid']);
    }
    else
    {
        $item_arr = _shn_rms_get_items($category);
    }
    
    if ($cat_arr == false)
        return;
    
    foreach ($cat_arr as $cat)
    {
        $categories[$cat['ct_uuid']] = $cat['name'];
    }
    
    if (!empty($item_arr))
    {
        foreach ($item_arr as $item)
        {
            if (empty($_SESSION['rms_items']))
            {
                $items[$item['ct_uuid']] = $item['name'];
            }
            elseif (!_shn_rms_is_itemadded($item['ct_uuid']))
            {
                $items[$item['ct_uuid']] = $item['name'];
            }
                
        }
    }
    
    $units = _shn_rms_get_items($items);
    
    print '<a name="items"></a>';
    print '<div id="item_new">';
    shn_form_fopen("req_new",null,array('req_message'=>false,'anchor'=>'items'));
    shn_form_hidden(array('seq'=>'add_item'));
    shn_form_hidden(array('cat_sel'=>'false'));
    shn_form_fsopen(_("New Item"));
    
    include_once('lib_ajax.inc');
    _shn_rms_ajax_init('sub_cat');
    shn_form_select($categories, _("Category"),'category',"onChange='makeRequest(\"stream.php?mod=rms&amp;act=req_new&amp;seq=ax_sub_cat\",this.value)'", array('value'=>$category));
    
    print '<div id="sub_cat">';
    print '</div>';
    
    print '<div id="itm_unit">';
    print '</div>';

    shn_form_text(_("Quantity"),'qty',null,array('req'=>true,'value'=>''));
    shn_form_select($priorities, _("Priority"), 'priority');
    shn_form_fsclose();
    shn_form_submit(_("Add"));
    shn_form_fclose();
    print '</div>';
    
    _shn_rms_js_category();
}

function _shn_rms_get_subcat($cat_id)
{
	$car_arr = _shn_rms_get_sub_cat($cat_id);

    if (empty($car_arr))
    {
    	$item_arr = _shn_rms_get_items($cat_id);
        
        foreach ($item_arr as $item)
        {
            if (empty($_SESSION['rms_items']))
            {
                $items[$item['ct_uuid']] = $item['name'];
            }
            elseif (!_shn_rms_is_itemadded($item['ct_uuid']))
            {
                $items[$item['ct_uuid']] = $item['name'];
            }
                
        }
        
        if (!isset($items) || empty($items))
        {
            print "<div class=info>" . _("No items (left) for this category please select another category") . "</div>";
            return false;            
        }
        else
        {
            array_push($items,'-- Select item --');
            array_reverse($items);
            shn_form_select($items, _("Item"),'item',"onChange='makeRequest(\"stream.php?mod=rms&amp;act=req_new&amp;seq=ax_unit_itm\",this.value,showUnit)'");
            return true;
        }
        
    }
    else
    {
    	$categories[''] = '-- Select Category --';
        foreach ($car_arr as $cat)
        {
            $categories[$cat['ct_uuid']] = $cat['name'];
        }
        shn_form_select($categories, _("Sub Category"),'category',"onChange='makeRequest(\"stream.php?mod=rms&amp;act=req_new&amp;seq=ax_sub_cat\",this.value)'", array('value'=>$category));
    }
    
}

function _shn_rms_show_items()
{
    if (is_array($_SESSION['rms_items']))
    {        
        $rms_items = $_SESSION['rms_items'];

        $th_items[] = array (_("Item"), _("Quantity"), _("Item Priority"), '&nbsp;');
         
        foreach ($rms_items as $itm)
        {
            $remove_link = '<a href="index.php?mod=rms&amp;act=req_new' .
                           '&amp;seq=del_item&amp;itm_id=' .
                           $itm[0] . '#items">' . _("Remove Item") . '</a>';
                           
            $tb_items[] = array (
                                 _shn_rms_get_itemname($itm[0]), 
                                 $itm[1] . " " . _shn_rms_get_iunit_name($itm[3]) . "", 
                                 _shn_rms_get_priorityname($itm[2]),
                                 $remove_link
                                );
        }
        
        shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
        print '<br />';
        
        shn_form_fopen("req_new",null,array('req_message'=>false));
        shn_form_hidden(array('seq'=>'finish'));
        $msg = _("When all the request items are added, Please press 'Finish to complete the request'");
        _shn_html_print_message($msg);
        shn_form_submit(_("Finish"));
        shn_form_fclose();
    }
    
}

switch ($_REQUEST['seq'])
{
    case '':
            //reset the SESSION variables
            $_SESSION['rms_req_id'] = null;
            $_SESSION['rms_req_added'] = false;
                
            _shn_rms_requester();
            break;
    
    case 'new_requester':
             _shn_rms_new_requester();
             break;       
    case 'add_reqstr':
            $reqstr = _shn_rms_requester_new();
            if ($reqstr)
                _shn_rms_location();
            break;
            
    case 'reqstr_up':
            _shn_rms_requester_update();
            _shn_rms_location();
            break;
            
    case 'get_reqstr':
            $id = trim($_POST['card_number']);
            $_SESSION['rms_reqstr_id'] = $id;
            if ($id != '' && _shn_rms_is_requester($id))
                _shn_rms_location($id);
            else if (_shn_rms_is_person($id))
                _shn_rms_requester_conf($id);
            else
            {
                add_error(_("Please enter a valid Requester Id"));
                display_errors();
                
                _shn_rms_requester();
                // Add required js functions
                _shn_rms_js_requester();
            }
            break;
            
    case 'add_loc':
            _shn_rms_location_add();
            break;
            
    case 'get_loc':
            $loc = trim($_POST['loc']);
            $_SESSION['rms_reqstr_loc'] = $loc;
            $_SESSION['rms_items'] = null;
            
            _shn_rms_view_requester($_SESSION['rms_reqstr_id'],true);
            print '<br />';
            _shn_rms_view_location($_SESSION['rms_reqstr_loc'],true);
            print '<br />';
            
            _shn_rms_items();
            break;
    
    case 'ax_loc_other':
            _shn_rms_ax_location_other();
            break;
    case 'ax_sub_cat':
            $cat_id=$_REQUEST['par'];
            _shn_rms_get_subcat($cat_id);
            break;
            
    case 'ax_unit_itm':
            $itm_id=$_REQUEST['par'];
            $units_arr = _shn_rms_get_itm_units($itm_id);
            
            if(empty($units_arr))
                return false;
                
            foreach ($units_arr as $unit)
            {
                $units[$unit['unit_uuid']] = $unit['name'];                    
            }
            shn_form_select($units, _("Unit"),'unit');
            break;
    
    case 'add_item':
            _shn_rms_view_requester($_SESSION['rms_reqstr_id'],true);
            print '<br />';
            _shn_rms_view_location($_SESSION['rms_reqstr_loc'],true);
            print '<br />';
            
            if ($_POST['cat_sel'] == 'true')
            {
                _shn_rms_items($_POST['category']);
            }
            else
            {
                $itm = $_POST['item'];
                $qty = $_POST['qty'];
                $pri = $_POST['priority'];
                $unit = $_POST['unit'];

                if (!_shn_rms_is_itemadded($itm) && _shn_rms_add_item2session($itm, $qty, $pri, $unit))
                {
                    unset($_POST);
                    _shn_rms_items();
                }
                else
                {
                    display_errors();
                    _shn_rms_items();
                }
            }
            print '<br />';
            _shn_rms_show_items();
            break;
            
    case 'del_item':
            _shn_rms_del_itemfromsession($_REQUEST['itm_id']);
            _shn_rms_view_requester($_SESSION['rms_reqstr_id'],true);
            print '<br />';
            _shn_rms_view_location($_SESSION['rms_reqstr_loc'],true);
            print '<br />';
            _shn_rms_items();
            _shn_rms_show_items();
            break;
            
    case 'finish':
            $r_uuid = $_SESSION['rms_reqstr_id'];
            $l_uuid = $_SESSION['rms_reqstr_loc'];
            
            if (!$_SESSION['rms_req_added'])
            {
                $_SESSION['rms_req_id'] = _shn_rms_add_request($r_uuid, $l_uuid);
                $_SESSION['rms_req_added'] = true;
            }
            
            _shn_html_print_alert(_("The Request was successfully submitted"));
            _shn_rms_view_request($_SESSION['rms_req_id']);
            
            print '<br />' .
                  '[ <a href="index.php?mod=rms">RMS Home</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=req_new">New Request</a> ]';
            break;
}
?>
