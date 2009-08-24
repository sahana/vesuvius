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


_shn_rms_print_hedder(_t("Enter New Pledge"));


/**
 * When ACL is disabled, the new user should be added to track the user.
 *
 * @param unknown_type $id
 */
function _shn_rms_donor()
{
	$_SESSION['rms_donor_id'] = null;

    //_shn_rms_print_hedder(_t("Make New Pledge"));
    shn_form_fopen("plg_new",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'add_donor'));
    if(shn_acl_is_enabled()){
    	shn_form_fsopen('Use the user account');
    	shn_form_checkbox('User Account', 'user', 'onClick=submit(this)');
    	shn_form_fsclose();
    }
    shn_form_fsopen(_t("New Donor"));
    print '<div class="info">';
    print _t("Create New Donor: ");
    print _t("A new Person will be added to the Sahana Database,");
    print '<br />';
    print _t("Only the Full Name is required, But in order to Contact the Donor please add some contact information with this");
    print '<br />';
    print '</div>';
    print '<br />';

    $extra_opt['req']=true;
    shn_form_text(_t("Full Name"),'name',null,$extra_opt);
    //---------------------
    include_once $global['approot'] . '/mod/or/lib_or.inc';
    $suplier_name_array = array();
    $suplier_name_array = _shn_or_get_suplier_name($suplier_id);
   
    shn_form_select($suplier_name_array,_t("Organization : "),'org_id','size="1"',array('help'=>_t('If this box does not contain the organization name please go to the Organization Registry module and get your organization Registered ')));
    ?><!-- Add a Link to Add Organization -->
    <a href="index.php?mod=or&act=reg_org">Click to Register a new Organization</a>
    <br>
    <?php
    //---------------------
    shn_form_text(_t("Mobile"),'mobile');
    shn_form_text(_t("Email"),'email');
    shn_form_opt_select("opt_id_type",_t("Available Card type"));
    shn_form_text(_t("Card Number"),"card_number",null,$extra_opt);
    shn_form_text(_t("Telephone"),'telephone',null);
    shn_form_textarea(_t("Address"),'address',null);
   // shn_form_textarea(_t("Address"),'address',null);


    shn_form_fsclose();
    shn_form_submit(_t("Next"));
    shn_form_fclose();
    print '<br />';
}


function _shn_rms_donor_display($id)
{
    $donor = _shn_rms_view_donor($id, $summary=false);
    echo $donor;
}

function _shn_rms_donor_conf($id)
{
    _shn_html_print_alert(_t("New Donor; Please confirm the contact information and enter missing information"));

    $psn = _shn_rms_get_person($id);
    shn_form_fopen("plg_new",null,array('req_message'=>false,'anchor'=>'items'));
    shn_form_hidden(array('seq'=>'donor_up'));
    shn_form_hidden(array('donor_id'=>$id));
    shn_form_fsopen(_t("Confirm Person Information"));
    shn_form_text(_t("Full Name"),'name', null, array('req'=>true,'value'=>$psn['name']));
    shn_form_text(_t("Mobile"),'mobile', null, array('value'=>$psn['mobile']));
    shn_form_text(_t("Email"),'email', null, array('value'=>$psn['email']));
    shn_form_text(_t("Telephone"),'telephone', null, array('value'=>$psn['telephone']));
    shn_form_textarea(_t("Address"),'address', null, array('value'=>$psn['address']));
    shn_form_fsclose();
    shn_form_submit(_t("Next"));
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
    $categories["none"] = "";

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

    print '<a name="items"></a>';
    print '<br />';
    print '<div id="item_new">';
    shn_form_fopen("plg_new",null,array('req_message'=>false,'anchor'=>'items'));
    shn_form_hidden(array('seq'=>'add_item'));
    shn_form_hidden(array('cat_sel'=>'false'));

    $info=_t("Select an item first");
    ?><div class="info"><?php echo $info;?></div><br /><?

	shn_form_fsopen(_t("New Item"));
    include_once('lib_ajax.inc');
    _shn_rms_ajax_init('sub_cat', 'item_div');
    shn_form_select($categories, _t("Category"),'category',"onChange='makeRequest(\"index.php?mod=rms&amp;act=req_new&amp;stream=text&amp;seq=ax_sub_cat\",this.value, \"cat\")'", array('req'=>true, 'value'=>$category));
    //shn_form_select($categories, _t("Category"),'category','onChange="selectCat();"', array('value'=>$category));
    //shn_form_select($items, _t("Item"),'item');

    print '<div id="sub_cat">';
    print '</div>';
    print '<div id="item_div">';
    print '</div>';
    print '<div id="itm_unit">';
    print '</div>';

    shn_form_text(_t("Quantity"),'qty',null,array('req'=>true));
    shn_form_fsclose();

    $info=_t("Select an Inventory");
    ?><div class="info"><?php echo $info;?></div><br /><?

    shn_form_fsopen(_t('Inventory Selection'));
    $inventory_array=array();
    global $global;
    $db=$global['db'];
    $sql="SELECT * FROM ims_inventory_records;";
    $res=$db->Execute($sql);
    while($res!=NULL && !$res->EOF)
    {
        $inventory_array[$res->fields['inv_uuid']]=$res->fields['inventory_name'];
        $res->MoveNext();
    }
    shn_form_select($inventory_array,_t('Inventory Selection : '),'inventory',null);
    shn_form_fsclose();
    shn_form_submit(_t("Add"));
    shn_form_fclose();
    print '</div>';

    _shn_rms_js_category();
}

function _shn_rms_show_items()
{
    if (is_array($_SESSION['rms_items']))
    {
        $rms_items = $_SESSION['rms_items'];

        $th_items[] = array (_t("Item"), _t("Quantity"), '&nbsp;');
        foreach ($rms_items as $itm)
        {
            $remove_link = '<a href="index.php?mod=rms&amp;act=plg_new' .
                           '&amp;seq=del_item&amp;itm_id=' .
                           $itm[0] . '">' . _t("Remove Item") . '</a>';
            $tb_items[] = array (
                                 _shn_rms_get_itemname($itm[0]),
                                 $itm[1] . " " . _shn_rms_get_iunit_name($itm[3]) . "" ,
                                 $remove_link
                                );
        }

        print '<br />';
        shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
        print '<br />';
        shn_form_fopen("plg_new",null,array('req_message'=>false));
        shn_form_hidden(array('seq'=>'finish'));
        $msg = _t("When all the items are added, Please press 'Finish'");
        _shn_html_print_message($msg);
        shn_form_submit(_t("Finish"));
        shn_form_fclose();
    }

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
        if(_shn_rms_check_catalog_item($itm))
        {
	add_error(_t("Please Select a Catalog Item"));
        return false;
        }

        if (!isset($items) || empty($items))
        {
            print "<div class=info>" . _t("No items (left) for this category please select another category") . "</div>";
            return false;
        }
        else
        {
            array_push($items,'-- Select item --');
            shn_form_select($items, _t("Item"),'item',"onChange='makeRequest(\"index.php?mod=rms&amp;act=plg_new&amp;stream=text&amp;seq=ax_unit_itm\",this.value, \"item\", showUnit)'", array('req'=>true));
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
        shn_form_select($categories, _t("Sub Category"),'category',"onChange='makeRequest(\"index.php?mod=rms&amp;act=plg_new&amp;stream=text&amp;seq=ax_sub_cat\",this.value, \"subcat\")'", array('req'=>true, 'value'=>$category));
    }

}

switch ($_REQUEST['seq'])
{
    case '':

            $_SESSION['rms_items'] = null;
            $_SESSION['rms_plg_added'] = null;
            _shn_rms_donor();
            break;

    case 'add_donor':

    	    if(!isset($_POST['user']) && ($_POST['name']!=null && $_POST['card_number']!=null)) {
    	        $donor['name'] = $_POST['name'];
	            $donor['mobile'] = $_POST['mobile'];
	            $donor['telephone'] = $_POST['telephone'];
	            $donor['email'] = $_POST['email'];
	            $donor['address'] = $_POST['address'];
	            $donor['opt_id_type'] = $_POST['opt_id_type'];
    	        $donor['card_number'] = $_POST['card_number'];
    	        $donor['org_id'] = $_POST['org_id'];
    	        //var_dump($donor);

                $_SESSION['rms_donor_id']=_shn_rms_add_donor($donor);
                if(!shn_acl_is_enabled()){
       	        	$_SESSION['user_id'] = $_SESSION['rms_donor_id'];
                }
                _shn_rms_donor_display($_SESSION['user_id']);
                _shn_rms_items();
    	        break;

    	    }elseif($_POST['name']==null && $_POST['card_number']==null) {
    	    	add_error(_t("Please fill the 'Name' and 'Card Number'"));
    	    	_shn_rms_donor();
    	    	break;
    	    }elseif($_POST['name']==null && $_POST['card_number']!=null) {
    	        add_error(_t("Please fill the 'Name'"));
    	    	_shn_rms_donor();
    	    	break;
    	    }elseif($_POST['name']!=null && $_POST['card_number']==null) {
    	    	add_error(_t("Please fill the 'Card Number'"));
    	    	_shn_rms_donor();
    	    	break;
    	    }
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
            shn_form_select($units, _t("Unit"),'unit');
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
                $unit = $_POST['unit'];
                $inv = $_POST['inventory'];
                if (!_shn_rms_is_itemadded($itm) && _shn_rms_add_item2session($itm, $qty,'',$unit, $inv))
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

            _shn_html_print_alert(_t("The Pledge was successfully added<br>Your Pledge Id is ".$_SESSION['rms_plg_id']));
            _shn_rms_view_pledge($_SESSION['rms_plg_id']);
            print '<br />' .
                  '[ <a href="index.php?mod=rms">RMS Home</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=plg_new">New Pledge</a> ]';
            break;
}
?>