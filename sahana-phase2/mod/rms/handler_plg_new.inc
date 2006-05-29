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


_shn_rms_print_hedder(_("Enter New Pledge"));


function _shn_rms_donor()
{
    $_SESSION['rms_donor_id'] = null;
    
    print '<div id="donor_id">';
    shn_form_fopen("plg_new",null);
    shn_form_hidden(array('seq'=>'get_donor'));
    shn_form_fsopen(_("Existing Donor"));
    shn_form_text(_("Donor ID"),'donor_id',null,array('br'=>false));
    shn_form_submit(_("Next"), 'id="donor_next"');
    shn_form_fsclose();
    $help = _("* Create New Donor: " .
              "A new Person will be added to the Sahana Database, <br />" .
              "* Only the Full Name is required, But in order to Contact the Donor please add some contact information with this");
    shn_form_button(_("New Donor"),'onClick="showNewDonor();"',array('help'=>$help));
    shn_form_fclose();
    print '</div>';
    
    print '<div id="donor_new">';
    shn_form_fopen("plg_new",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'add_donor'));
    shn_form_fsopen(_("New Donor"));
    shn_form_text(_("Full Name"),'name','',array('req'=>true));
    shn_form_text(_("Mobile"),'mobile');
    shn_form_text(_("Email"),'email');
    shn_form_text(_("Telephone"),'telephone',null);
    shn_form_textarea(_("Address"),'address',null);
    shn_form_fsclose();
    shn_form_submit(_("Next"));
    shn_form_fclose();
    print '</div>';
    
}

function _shn_rms_donor_new()
{
    if (trim($_POST['name']) != '')
    {
        $donor['name'] = $_POST['name'];
        $donor['mobile'] = $_POST['mobile'];
        $donor['email'] = $_POST['email'];
        $donor['telephone'] = $_POST['telephone'];
        $donor['address'] = $_POST['address'];
        
        $id = _shn_rms_add_donor($donor);
        $_SESSION['rms_donor_id'] = $id;
        $msg = _("Your Donor id: $id, Please write down this ID");
        _shn_html_inform_add($msg);
        _shn_html_inform_show();
        return true;
    }
    else
    {
        add_error(_("Please fill all the required fields"));
        display_errors();
        _shn_rms_donor();
        // Unhide newrequester form
        _shn_rms_js_donor(true);
        return false;
    }
}

function _shn_rms_donor_update()
{
    $updated = null;
    $added = null;
    
    $id = $_POST['donor_id'];
    $name = $_POST['name'];
    $mobile = $_POST['mobile']; 
    $email = $_POST['email']; 
    $telephone = $_POST['telephone']; 
    $address = $_POST['address'];
    
    $donor = _shn_rms_get_person($id);
    
    //Add or update Full Name
    if ($donor['name'] != $name)
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
    if ($donor['mobile'] != $mobile)
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
    if ($donor['email'] != $email)
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
    if ($donor['telephone'] != $telephone)
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
    if ($donor['address'] != $address)
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

function _shn_rms_donor_display($id)
{
    $donor = _shn_rms_get_person($id);
    print_r($donor);
}

function _shn_rms_donor_conf($id)
{
    _shn_html_print_alert(_("New Donor; Please confirm the contact information and enter missing " .
                "information"));

    $psn = _shn_rms_get_person($id);
    shn_form_fopen("plg_new",null,array('req_message'=>false,'anchor'=>'items'));
    shn_form_hidden(array('seq'=>'donor_up'));
    shn_form_hidden(array('donor_id'=>$id));
    shn_form_fsopen(_("Confirm Person Information"));
    shn_form_text(_("Full Name"),'name', null, array('req'=>true,'value'=>$psn['name']));
    shn_form_text(_("Mobile"),'mobile', null, array('value'=>$psn['mobile']));
    shn_form_text(_("Email"),'email', null, array('value'=>$psn['email']));
    shn_form_text(_("Telephone"),'telephone', null, array('value'=>$psn['telephone']));
    shn_form_textarea(_("Address"),'address', null, array('value'=>$psn['address']));
    shn_form_fsclose();
    shn_form_submit(_("Next"));
    shn_form_fclose();
}

function _shn_rms_items($category = null)
{
    $categories = array();
    $items = array();
    
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
    
    print '<a name="items"></a>';
    print '<br />';
    print '<div id="item_new">';
    shn_form_fopen("plg_new",null,array('req_message'=>false,'anchor'=>'items'));
    shn_form_hidden(array('seq'=>'add_item'));
    shn_form_hidden(array('cat_sel'=>'false'));
    shn_form_fsopen(_("New Item"));
    shn_form_select($categories, _("Category"),'category','onChange="selectCat();"', array('value'=>$category));
    shn_form_select($items, _("Item"),'item');
    shn_form_text(_("Quantity"),'qty',null,array('req'=>true));
    shn_form_fsclose();
    shn_form_submit(_("Add"));
    shn_form_fclose();
    print '</div>';
    
    _shn_rms_js_category();
}

function _shn_rms_show_items()
{
    if (is_array($_SESSION['rms_items']))
    {        
        $rms_items = $_SESSION['rms_items'];
        $th_items[] = array (_("Item"), _("Quantity"), '&nbsp;'); 
        foreach ($rms_items as $itm)
        {
            $remove_link = '<a href="index.php?mod=rms&amp;act=plg_new' .
                           '&amp;seq=del_item&amp;itm_id=' .
                           $itm[0] . '">' . _("Remove Item") . '</a>';
            $tb_items[] = array (
                                 _shn_rms_get_itemname($itm[0]), 
                                 $itm[1], 
                                 $remove_link
                                );
        }
        
        print '<br />';
        shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
        print '<br />';
        shn_form_fopen("plg_new",null,array('req_message'=>false));
        shn_form_hidden(array('seq'=>'finish'));
        $msg = _("When all the items are added, Please press 'Finish'");
        _shn_html_print_message($msg);
        shn_form_submit(_("Finish"));
        shn_form_fclose();
    }
    
}

switch ($_REQUEST['seq'])
{
    case '':
            $_SESSION['rms_donor_id'] = null;
            $_SESSION['rms_items'] = null;
            $_SESSION['rms_plg_added'] = null;
            _shn_rms_donor();
            // Add required js functions
            _shn_rms_js_donor();
            break;
            
    case 'add_donor':
            $donor = _shn_rms_donor_new();
            if ($donor)
                _shn_rms_items();
            break;
            
    case 'donor_up':
            _shn_rms_donor_update();
            _shn_rms_items();
            break;
            
    case 'get_donor':
            $id = trim($_POST['donor_id']);
            $_SESSION['rms_donor_id'] = $id;
            if ($id != '' && _shn_rms_is_donor($id))
            {
                _shn_rms_view_donor($_SESSION['rms_donor_id']);
                _shn_rms_items();
            }
            elseif (_shn_rms_is_person($id))
                _shn_rms_donor_conf($id);
            else
            {
                add_error(_("Please enter a valid 'Donor Id'"));
                display_errors();
                
                _shn_rms_donor();
                // Add required js functions
                _shn_rms_js_donor();
            }
            break;
            
    case 'add_item':
            _shn_rms_view_donor($_SESSION['rms_donor_id']);
            if ($_POST['cat_sel'] == 'true')
            {
                _shn_rms_items($_POST['category']);
            }
            else
            {
                $itm = $_POST['item'];
                $qty = $_POST['qty'];
                //$stat = $_POST['status'];
                if (!_shn_rms_is_itemadded($itm) && _shn_rms_add_item2session($itm, $qty,''))
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
            _shn_rms_show_items();
            break;
            
    case 'del_item':
            _shn_rms_del_itemfromsession($_REQUEST['itm_id']);
            _shn_rms_view_donor($_SESSION['rms_donor_id']);
            _shn_rms_items();
            _shn_rms_show_items();
            break;
            
    case 'finish':
            $d_uuid = $_SESSION['rms_donor_id'];
            
            if (!$_SESSION['rms_plg_added'])
            {
                $_SESSION['rms_plg_id'] = _shn_rms_add_pledge($d_uuid);
                $_SESSION['rms_plg_added'] = true;
            }
            
            _shn_html_print_alert(_("The Pledge was successfully added"));
            _shn_rms_view_pledge($_SESSION['rms_plg_id']);
            
            print '<br />' .
                  '[ <a href="index.php?mod=rms">RMS Home</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=plg_new">New Pledge</a> ]';
            break;                  
}
?>
