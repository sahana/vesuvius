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

global $global;
include_once $global['approot']."/mod/ims/lib_ims.inc";

function _shn_rms_requester($requester_id=null)
{
    $_SESSION['rms_reqstr_id'] = null;
    
    _shn_rms_print_hedder(_t("Make New Request"));
    shn_form_fopen("req_new",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'add_reqstr'));
    shn_form_fsopen(_t("New Requester"));
    print '<div class="info">';
    print _t("Create New Requester: ");
    print _t("A new Person will be added to the Sahana Database,");
    print '<br />';
    print _t("Only the Full Name is required, But in order to Contact the Requester please add some contact information with this");
    print '<br />';
    print '</div>';
    print '<br />';
    
    $extra_opt['req']=true;
    shn_form_text(_t("Full Name"),'name',null,$extra_opt);
    shn_form_text(_t("Mobile"),'mobile');
    shn_form_text(_t("Email"),'email');
    shn_form_opt_select("opt_id_type",_t("Available Card type"));
    shn_form_text(_t("Card Number"),"card_number",null,$extra_opt);
    shn_form_text(_t("Telephone"),'telephone',null);
    $date = Date("Y-m-d");
    shn_form_date(_t("Date"), 'date', array('value'=>$date));
    shn_form_textarea(_t("Address"),'address',null);
   // shn_form_textarea(_t("Address"),'address',null);
    
    
    shn_form_fsclose();
    shn_form_submit(_t("Next"));
    shn_form_fclose();
    print '<br />';
    
    /**
    *shn_form_fopen("req_new",null,array('req_message'=>false));
    *shn_form_hidden(array('seq'=>'get_reqstr'));
    *shn_form_fsopen(_t("Existing Requester"));
    *print '<div class="info">';
    *print _t("If you are a registered requester, Please enter the card number ");
    *print '<br />';
    *print _t("You can also use your 'id' if you have registered on the sahana system as a user, administrator, volunteer etc...");
    *print '<br />';
    *
    *print '</div>';
    *print '<br />';
    *shn_form_text(_t("Requester ID"),'card_number',null,array('req'=>true,'br'=>false));
    *shn_form_fsclose();
    *shn_form_submit(_t("Next"), 'id="reqstr_next"');
    *shn_form_fclose();
    *print '<br />';
    */
    
}

function _shn_rms_requester_conf($id)
{
    _shn_html_print_alert(_t("You seem to be a new requester, Please confirm the contact information and enter missing information"));

    $psn = _shn_rms_get_person($id);
    shn_form_fopen("req_new",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'reqstr_up'));
    shn_form_hidden(array('reqstr_id'=>$id));
    shn_form_fsopen(_t("Confirm Person Information"));
    shn_form_text(_t("Full Name"),'name', 'class=""', array('req'=>true,'value'=>$psn['name']));
    shn_form_text(_t("Mobile"),'mobile', null, array('value'=>$psn['mobile']));
    shn_form_text(_t("Email"),'email', 'class=""', array('value'=>$psn['email']));
    shn_form_text(_t("Telephone"),'telephone', null, array('value'=>$psn['telephone']));
    shn_form_textarea(_t("Address"),'address', null, array('value'=>$psn['address']));
    shn_form_fsclose();
    shn_form_submit(_t("Next"));
    shn_form_fclose();
}
//*********************************************************************************************   
      
function _shn_rms_location($id = null)
{
    if ($id == null)
        $id = $_SESSION['rms_reqstr_id'];
         
    _shn_rms_view_requester($id,true);
    print '<br />';
	if (_shn_rms_get_location_array($id))
	{
		$loc = _shn_rms_get_location_array($id);
		_shn_rms_display_location_array($loc);
	}
    
   
    shn_form_fopen("req_new",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'add_loc'));
 	
    shn_form_fsopen(_t("Select New Requester Location"));
    $extra_opts["camps"]=true;
    $extra_opts["org"]=true;
    
    shn_location(null,null,null,$extra_opts);
   	shn_form_fsclose();
    print '<br />';
    $_SESSION['rms']['req']['date'] = $_POST['date'];
    $date = $_SESSION['rms']['req']['date'];
    shn_form_hidden(array('date'=>$date));
    shn_form_submit(_t("Add Location"));
    shn_form_fclose();
}



function _shn_rms_ax_location_other($id=null)
{
	
	if ($id == null)
        $id = $_SESSION['rms_reqstr_id'];
       
       
    {
        print '<div id="loc_new">';
        shn_form_fopen("req_new",null,array('req_message'=>false,'anchor'=>'items'));
        shn_form_hidden(array('seq'=>'get_loc'));
        //shn_form_fsopen(_t("New Location"));
        //shn_form_text(_t("Location Name"),'loc_name',null,array('req'=>true));
        //shn_form_text(_t("Location ID"),'location_id',null,array('req'=>true));
        //shn_form_text(_t("Type"),'opt_person_loc_type');
        //shn_form_text(_t("Code"),'postcode',null);
        //shn_form_textarea(_t("Address"),'loc_address',null,array('req'=>true));
        //shn_form_textarea(_t("GIS"),'gis',null);
        //shn_form_fsclose();

       if (_shn_rms_get_requester_locs($id))
    {
	    $location_array=array();
	   
	    $bsd_village = _shn_rms_get_requester_locs($id);
	    $info=_t("Select a location where the request is related.")."<br />";
        $info.=_t("If you want to make the request for a new location, add the location first.")."<br />";
	    ?><div class="info"><?php echo $info;?></div><br /><?
	    
	    shn_form_fopen("req_new",null,array('req_message'=>false,'anchor'=>'items'));
        shn_form_hidden(array('seq'=>'get_loc'));
        shn_form_fsopen(_t("Existing Location"));
        

       for($i=0;$i<count($bsd_village);$i++){
	    
	    	$name = _shn_org_location_string($bsd_village[$i]);   //return the location
	    
	    	array_push($location_array,$name);		
	    }
        
       
        shn_form_select($location_array,_t("Location"), 'loc');
        shn_form_fsclose();
        shn_form_submit(_t("Next"));
        print '<br />';
        print '<br />';
        shn_form_fclose();
	
    }     
        //==============<newly commented>==========   
	    /*shn_form_fsopen("Location");
	    $range=array("start"=>1,"end"=>5);
	    shn_location($range,$value=null,$parent=null,$extra_opts=null);
	    _shn_rms_location_add();
	
	    shn_form_fsclose();

	    shn_form_hidden(array('seq'=>'img'));
        //call appropriate gis api method
        shn_gis_add_marker_map_form();
	    shn_form_hidden(array('seq'=>'get_loc'));


        shn_form_submit(_t("Add Location"));
        shn_form_fclose();*/
    //=============<newly commented/>==========================
    
        print '</div>';     
      
    }
}

function _shn_rms_location_add()
{
    /*=================<newly commented>=======================
	global $global;
    $db=$global['db'];

    $_SESSION['ims_1']=$_POST['1'];
    $_SESSION['ims_2']=$_POST['2'];
    $_SESSION['ims_3']=$_POST['3'];
    $_SESSION['ims_4']=$_POST['4'];
    $_SESSION['ims_5']=$_POST['5'];

    $bsd_village=_shn_ims_get_locid();
    //print $bsd_village;
    $location=_shn_rms_get_location_name($bsd_village);
    

    $loc['name'] = $location;
    //$loc['id'] = trim($_POST['location_id']);
    $loc['id'] = $bsd_village;
    $loc['type'] = null;
    $loc['postcode'] = null;
    $loc['address'] = null;
    $loc['gis'] = null;
    /*$loc['type'] = trim($_POST['opt_person_loc_type']);
    $loc['postcode'] = trim($_POST['postcode']);
    $loc['address'] = trim($_POST['loc_address']);
    $loc['gis'] = trim($_POST['gis']);
    
    if ($bsd_village == '')
    {
        add_error(_t("Location is Essential. Please Complete and submit again"));
        display_errors();
        _shn_rms_location();
    }
    else
    {
        $id = $_SESSION['rms_reqstr_id'];
        //print _shn_rms_add_requester_loc($id, $loc);
	
    

    
    //print $bsd_village;
    shn_gis_dbinsert($id,0,null,$_POST['loc_x'],$_POST['loc_y'],null);

    //$q="INSERT INTO location_details(poc_uuid,location_id) VALUES('{$id}','{$bsd_village}')";
    //$res=$db->Execute($q);

    _shn_rms_add_requester_loc($id, $loc);
    _shn_rms_location();
    }
    ====================<newly commented/>============================*/
	
	/*=====================<newly added>============================
	global $global;
    $db=$global['db'];

    $_SESSION['ims_1']=$_POST['1'];
    $_SESSION['ims_2']=$_POST['2'];
    $_SESSION['ims_3']=$_POST['3'];
    $_SESSION['ims_4']=$_POST['4'];
    $_SESSION['ims_5']=$_POST['5'];

    $bsd_village=_shn_ims_get_locid();
    print $bsd_village;
    $location=_shn_rms_get_location_name($bsd_village);
    

    $loc['name'] = $location;
    //old-----$loc['id'] = trim($_POST['location_id']);
    $loc['id'] = $bsd_village;
    $loc['type'] = null;
    $loc['postcode'] = null;
    $loc['address'] = null;
    $loc['gis'] = null;
    /*$loc['type'] = trim($_POST['opt_person_loc_type']);
    $loc['postcode'] = trim($_POST['postcode']);
    $loc['address'] = trim($_POST['loc_address']);
    $loc['gis'] = trim($_POST['gis']);*/
    
   /*if ($bsd_village == '')
    {
        add_error(_t("Location is Essential. Please Complete and submit again"));
        display_errors();
        _shn_rms_location();
    }
    else
    {
        $id = $_SESSION['rms_reqstr_id'];
        print _shn_rms_add_requester_loc($id, $loc);*/
	
    

    
    //print $bsd_village;
    //--new--shn_gis_dbinsert($id,0,null,$_POST['loc_x'],$_POST['loc_y'],null);

    //$q="INSERT INTO location_details(poc_uuid,location_id) VALUES('{$id}','{$bsd_village}')";
    //$res=$db->Execute($q);

    ///_shn_rms_add_requester_loc($id, $loc);
    ///_shn_rms_location();
    //}
    
	//====================<newly added/>============================
	
	
}

function _shn_rms_items($category = null)
{
	$date = $_SESSION['rms']['req']['date'];
	//print $date;
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
    
    $units = _shn_rms_get_items($items);
    
    print '<a name="items"></a>';
    print '<div id="item_new">';
    shn_form_fopen("req_new",null,array('req_message'=>false,'anchor'=>'items'));
    shn_form_hidden(array('seq'=>'add_item'));
    shn_form_hidden(array('cat_sel'=>'false'));
    shn_form_fsopen(_t("New Item"));
    
    include_once('lib_ajax.inc');
    _shn_rms_ajax_init('sub_cat', 'item_div');
    shn_form_select($categories, _t("Category"),'category',"onChange='makeRequest(\"index.php?mod=rms&amp;act=req_new&amp;stream=text&amp;seq=ax_sub_cat\",this.value, \"cat\")'", array('req'=>true, 'value'=>$category));
    
    print '<div id="sub_cat">';
    print '</div>';
    print '<div id="item_div">';
    print '</div>';
    print '<div id="itm_unit">';
    print '</div>';

    shn_form_text(_t("Quantity"),'qty',null,array('req'=>true,'value'=>''));
    shn_form_select($priorities, _t("Priority"), 'priority');
    shn_form_fsclose();
    shn_form_submit(_t("Add"));
    shn_form_fclose();
    print '</div>';
    
    _shn_rms_js_category();
}

function _shn_rms_get_subcat($cat_id)
{
	$car_arr = _shn_rms_get_sub_cat($cat_id);
    if (empty($car_arr))
    {
	$item_arr = array();
    	$item_arr = _shn_rms_get_items($cat_id);
        
        //foreach ($item_arr as $item)
	for($i=0;$i<count($item_arr);$i++)
        {
	    $item=$item_arr[$i];
            if (empty($_SESSION['rms_items']))
            {
                $items[$item['ct_uuid']] = $item['name'];
            }
            elseif (!_shn_rms_is_itemadded($item['ct_uuid']))
            {
                $items[$item['ct_uuid']] = $item['name'];
            }
                //NSERT INTO ext_location( p_uuid, location_id) VALUES ('sahap-17', '')
        }
        
        if (!isset($items) || empty($items))
        {
            print "<div class=info>" . _t("No items (left) for this category please select another category") . "</div>";
            return false;            
        }
        else
        {
            array_push($items,'-- Select item --');
            array_reverse($items);
            shn_form_select($items, _t("Item"),'item',"onChange='makeRequest(\"index.php?mod=rms&amp;act=req_new&amp;stream=text&amp;seq=ax_unit_itm\",this.value, \"item\", showUnit)'", array('req'=>true));
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
        shn_form_select($categories, _t("Sub Category"),'category',"onChange='makeRequest(\"index.php?mod=rms&amp;act=req_new&amp;stream=text&amp;seq=ax_sub_cat\",this.value, \"subcat\")'", array('req'=>true, 'value'=>$category));
    }
    
}

function _shn_rms_show_items()
{
    if (is_array($_SESSION['rms_items']))
    {        
        $rms_items = $_SESSION['rms_items'];

        $th_items[] = array (_t("Item"), _t("Quantity"), _t("Item Priority"), '&nbsp;');
         
        foreach ($rms_items as $itm)
        {
            $remove_link = '<a href="index.php?mod=rms&amp;act=req_new' .
                           '&amp;seq=del_item&amp;itm_id=' .
                           $itm[0] . '#items">' . _t("Remove Item") . '</a>';
                           
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
        $msg = _t("When all the request items are added, Please press 'Finish to complete the request'");
        _shn_html_print_message($msg);
        shn_form_submit(_t("Finish"));
        shn_form_fclose();
    }
    
}


switch ($_REQUEST['seq'])
{
    case '':
            //reset the SESSION variables
    	 
            $_SESSION['rms_req_id'] = null;
            $_SESSION['rms_req_added'] = false;
            if (shn_acl_is_enabled()) {
            	shn_form_fopen('req_new');
            	shn_form_fsopen('New Requester');
            	shn_form_hidden(array('seq'=>'new_reqstr'));
            	shn_form_checkbox('New Requester', 'new_req', 'onclick="submit(this)"');
            	shn_form_fsclose();
            	shn_form_fclose();
                $_SESSION['rms_reqstr_id'] = $_SESSION['user_id'];
                _shn_rms_location(); 	
            }else{
                _shn_rms_requester(null);
            }

            break;
    
    case 'new_reqstr':
            _shn_rms_requester(null);
            break;       
    case 'add_reqstr':
 
    	    if($_POST['name']!=null && $_POST['card_number']!=null) {
    	        $requester['name'] = $_POST['name'];
	            $requester['mobile'] = $_POST['mobile'];
	            $requester['telephone'] = $_POST['telephone'];
	            $requester['email'] = $_POST['email'];
	            $requester['address'] = $_POST['address'];
	            $requester['opt_id_type'] = $_POST['opt_id_type'];
    	        $requester['card_number'] = $_POST['card_number'];
    	        $_SESSION['rms']['req']['date'] = $_POST['date'];
                
                $_SESSION['rms_reqstr_id']=_shn_rms_add_requester($requester);
                if(!shn_acl_is_enabled()){
	              	$_SESSION['user_id'] = $_SESSION['rms_reqstr_id'];
	           }
                _shn_rms_location();
    	        break;
    	        
    	    }elseif($_POST['name']==null && $_POST['card_number']==null) {
    	    	add_error(_t("Please fill the 'Name' and 'Card Number'"));
    	    	_shn_rms_requester(null);
    	    	break;
    	    }elseif($_POST['name']==null && $_POST['card_number']!=null) {
    	        add_error(_t("Please fill the 'Name'"));
    	    	_shn_rms_requester(null);
    	    	break;
    	    }elseif($_POST['name']!=null && $_POST['card_number']==null) {
    	    	add_error(_t("Please fill the 'Card Number'"));
    	    	_shn_rms_requester(null);
    	    	break;
    	    }
           
            
            
    case 'reqstr_up':
            //_shn_rms_requester_update();
           // _shn_rms_location();
            break;
            
    case 'get_reqstr':
            $id = trim($_POST['card_number']);
            //$_SESSION['rms_reqstr_id'] = $id;
            if ($id != '' && _shn_rms_is_requester($id))
                _shn_rms_location($id);
            else if (_shn_rms_is_person($id))
                _shn_rms_requester_conf($id);
            else
            {
                add_error(_t("Please enter a valid Requester Id"));
                display_errors();
                
                _shn_rms_requester();
                // Add required js functions
                _shn_rms_js_requester();
            }
            break;
            
    case 'add_loc':
           
    	_shn_rms_requester_add_new_loc_t();
        _shn_rms_location(); 
    	//shn_form_hidden(array('seq'=>''));
    	//_shn_rms_location_add();
            break;
            
    case 'get_loc':
    	
    	   // $loc = shn_location_get_form_submit_loc();
    	$loc = trim($_POST['loc']);
    	//$loc = $_POST['loc'];  
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

    case 'ax_loc_org':
            break;
            
    case 'ax_loc_camp':
    	  
           $extra_opts['camps']=true;
        
           _shn_rms_ax_location_camp(); 
         
        
           // shn_location( null,null ,null ,$extra_opts);
        
       
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
            shn_form_select($units, _t("Unit"),'unit');
            break;
    
    case 'add_item':
            _shn_rms_view_requester($_SESSION['rms_reqstr_id'],true);
            //print '<br />';
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

                if (!_shn_rms_is_itemadded($itm) && _shn_rms_add_item2session($itm, $qty, $pri, $unit,null))
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
            $r_uuid = $_SESSION[ 'rms_reqstr_id'];
            $l_uuid = $_SESSION['rms_reqstr_loc'];
            
            if (!$_SESSION['rms_req_added'])
            {
            	//echo $l_uuid;
                $_SESSION['rms_req_id'] = _shn_rms_add_request($r_uuid, $l_uuid);
                $_SESSION['rms_req_added'] = true;
            }
            
            add_confirmation(_t("The Request was successfully submitted"));
            _shn_rms_view_request($_SESSION['rms_req_id']);
            
            print '<br />' .
                  '[ <a href="index.php?mod=rms">RMS Home</a> ] :: ' .
                  '[ <a href="index.php?mod=rms&amp;act=req_new">New Request</a> ]';
            break;

}
?>