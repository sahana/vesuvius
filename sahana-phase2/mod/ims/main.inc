<?php
/**
* Sahana Inventory Management System main page
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author        Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright        Lanka Software Foundation - http://www.opensource.lk
* @package        Sahana
* @subpackage        ims
* @tutorial        
* @license          http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_table.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_location.inc";
include_once "lib_ims.inc";
include_once $global['approot'].'/mod/cs/lib_cs.inc';
include_once $global['approot'].'/mod/or/lib_or.inc';



//global $global;

/**
 * RMS main menu
 */
function shn_ims_mainmenu()
{
    global $global;
    $module = $global['module'];

    shn_mod_menuopen(shn_get_module_name());
    shn_mod_menuitem("default","Home",$module);
    shn_mod_menuitem("search_item",_("Find Items"),$module);
    shn_mod_menuitem("view_inv",_("List Inventories"),$module);
    
    shn_mod_menuitem("view_edit_item",_("List Items"),$module);
    shn_mod_menuitem("view_edit_reorder_page",_("Re-Order Level"),$module);
    
    shn_sub_mod_menuopen(_("Reports"));
    shn_sub_mod_menuitem("report_expired",_("expired item"),$module);
    shn_sub_mod_menuitem("report_destroyed",_("destroyed item"),$module);
    shn_sub_mod_menuitem("report_minimum",_("re-order level"),$module);
    shn_sub_mod_menuitem("report_prediction",_("prediction reports"),$module);
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen(_("Optimization"));
    shn_sub_mod_menuitem("alternate_item",_("Set Alternate"),$module);
    shn_sub_mod_menuitem("relation_item",_("Set Relation"),$module);
    shn_sub_mod_menuitem("optim_item",_("Prediction by Item"),$module);
    shn_sub_mod_menuitem("optim_inventory",_("Prediction by Inventory"),$module);
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
    //shn_sub_menuitem("Optim_main_page",_("Optimization"),$module);

    include $global['approot']."/inc/handler_mainmenu.inc";

}

/**
 * The Default IMS homepage
 */
function shn_ims_default()
{
    global $global;
    _shn_ims_expire_date_check();
    include_once ('home.inc');
    _shn_ims_default();    

}

/**
* Add a new Search item form
*/
function shn_ims_search_item()
{
    include_once('search.inc');
    _shn_ims_search_item();
}

function shn_ims_search_item_page()
{
    include_once('search.inc');
    _shn_ims_search_item_page();
}

/**
 *  Add Category Selection form
 */
function shn_ims_add_item_main_page()
{
    global $global;
    include_once ('add_item.inc');
    $inventory_id=$_REQUEST['inv_id'];
    //print $inventory_id;
    _shn_ims_add_item_main_page($inventory_id);
        
}

function shn_ims_add_item($parent_id=null)
{
    global $global;
    /*if(_shn_cs_validate_sub_cat_form())
    {
    display_errors();
    shn_ims_add_item_main_page();
    }
    else
    {
         
    include_once('add_item.inc');
    _shn_ims_add_item_header();
    shn_form_fopen("add_item_db");
    add_item($temp,$parent_id);
    shn_form_fclose();
    }*/
    include_once('add_item.inc');
    _shn_ims_add_item_header();
    shn_form_fopen("add_item_db");
    add_item($temp,$parent_id);
    shn_form_fclose();
        
}

/**
* Add new View and edit item form
*/
function shn_ims_view_edit_item()
{
    //$inventory_id=$_REQUEST['inv_id'];
    global $global;
    include_once ('view_edit_item.inc');
    _shn_ims_view_edit_header();
    //_shn_ims_view_edit($inventory_id);
    _shn_ims_view_edit();
}

function shn_ims_view_edit_item_actions()
{
    global $global;
    require_once ('view_edit_item.inc');
    _shn_ims_view_edit_item_actions();
}

function shn_ims_report_minimum()
{
    include_once ('report.inc');
    _shn_ims_report_minimum();
}

function shn_ims_report_expired()
{
    include_once ('report.inc');
    _shn_ims_report_expired();
}

function shn_ims_report_destroyed()
{
    include_once ('report.inc');
    _shn_ims_report_destroyed();
}

function shn_ims_report_prediction()
{
    include_once ('report.inc');
    _shn_ims_report_prediction();
}

function shn_ims_destroy_item()
{
    global $global;
    $item_id = trim($_REQUEST['item_id']);
    include_once ('report.inc');
    _shn_ims_destroy_item($item_id);
}


function shn_ims_add_item_db()
{

    global $global;
    require_once('add_item_db.inc');
    $parent_id=trim($_POST['parent_id']);
    
    if(_shn_ims_validate_additemform())
    {
    //print $parent_id;
    display_errors();
    shn_ims_add_item($parent_id);
    }
    else
    {
    _shn_ims_add_item_db();
    }
    
}

function shn_ims_search_item_db()
    {
        global $global;
        include_once ('search.inc');
        _shn_ims_search_item_db();
        //_shn_ims_search_item();
    }

/**
**function to edit item in the view and edit page
*/    
function shn_ims_add_item1()
{
    global $global;
    include_once ('view_edit_item.inc');
    _shn_ims_view_edit_header();
    $temp = trim($_REQUEST['item_id']);
    $parent_id = trim($_REQUEST['parent_id']);
    include_once ('add_item.inc');
    shn_form_fopen('edit_item_db');
    add_item($temp,$parent_id);
    shn_form_fclose();
    
}
function shn_ims_edit_item_db()
{

    global $global;
    require_once('add_item_db.inc');
    
    if(_shn_ims_validate_additemform())
    {
        display_errors();
        shn_ims_add_item1();
    }
    else
    {
        _shn_ims_edit_item_db();
    }
        
    /**global $global;
    include_once ('view_edit_item.inc');
    _shn_ims_edit_item_db();
    */
        
}

function shn_ims_delete_item_db()
{
    global $global;
    $db=$global["db"];
    require_once('view_edit_item.inc');
    //$parent_id=$_REQUEST['parent_id'];
    $item_id=$_REQUEST['item_id'];
    $sql="DELETE FROM ims_item_records WHERE item_id='$item_id';";
    $ims=$db->Execute($sql);
?>
<div>
<h5 align="center" <?php print ("Successfully Deleated");?>></h5></div>
<?php
    shn_ims_view_edit_item();
}

/**
**function to add add_inventory
*/
/*
function shn_ims_add_inventory()
{
    include_once ('add_inventory.inc');
    _shn_or_ims_regform_org($error);
}*/

/**
**function to add the search inventory form
*/
/*
function shn_ims_search_inventory()
{
    include_once ('search_inventory.inc');
    _shn_or_ims_form_search();
}
*/
/**
**function to add the view and edit inventory form
*/
/*
function shn_ims_view_edit_inventory()
{
    include_once ('view_edit_inventory.inc');
    if(NULL == $_REQUEST['id'])
    {
?>
    <h2> Inventory Registry</h2>
<?php
        _shn_or_ims_viewform_allorg();
    }
    else
    {
        _shn_or_ims_viewform_org($_REQUEST['id']);
        }
}
*/    

/**function shn_ims_add_item_db()
{
    include_once ('add_item_db.inc');
    _shn_ims_search_database();        
}*/


/*function shn_ims_reg_org_cr()
{
    include_once("process_org.inc");
    _shn_or_ims_reg_org_cr();
}*/

function shn_ims_reg_inv($error=false)
{
    include_once ("reg_inv.inc"); 
    _shn_ims_regform_org($error);
}

function shn_ims_reg_inv_cr()
{
    include_once("process_inv.inc");
    _shn_ims_reg_inv_cr();
}

function shn_ims_reg_operation_cr(){
    include_once("process_inv.inc");
    _shn_ims_reg_operation_cr();
}

function shn_ims_view_inv_submit(){
    include_once("process_inv.inc");
    include_once ("view_inv.inc");
    require_once ($global['approot'].'inc/lib_security/authenticate.inc');
    $act=$_POST{"action"};
    $acl_enabled=shn_acl_get_state("or");
    $req_act="_shn_ims_".$act."_org";
    $allow = (!shn_acl_check_perms_action($_SESSION['user_id'],$req_act) || 
             !$acl_enabled)? true : false;
    if(!$allow){
        ?>
        <div id="error">
        <p><em><?=_('Sorry, you do not have permisssion to access this section')?></em>.<br/><br/><?=_('This could be because:')?></ul>
        <ul>
        <li><?=_('You have not logged in or Anonymous access is not allowed to this section')?></li>
        <li><?=_('Your username has not been given permission to access this section')?></li>
        </ul>
        <p><?=_('To gain access to this section please contact the administrator')?></p>
        </div> <!-- /error -->
        <?
        return false;
    }
    switch ($act) {
        case "edit":
            _shn_ims_edit_org();
            break;
        case "del":
            _shn_ims_del_org();
            break;
        default:
            shn_ims_view_inv();
            break;
    }
}

function shn_ims_view_inv()
{
    include_once ("view_inv.inc");
?>
<?php
    if(NULL == $_REQUEST['id']){
    ?>
<h2> Inventory Registry</h2>
<?php
        _shn_ims_viewform_allorg();
    }else{
        _shn_ims_viewform_org($_REQUEST['id']);
    }
}

function shn_ims_drill_report()
{
    include_once("report.inc");
    $parent=$_GET["id"];
     _shn_ims_level($parent);
}
function shn_ims_org_sector()
{
    include_once("report.inc");
    _shn_ims_report_org_sector();
}
// default page, welcome page 
/*function shn_ims_default()
{
    include_once ("home.inc");
}*/
function shn_ims_search()
{
    include_once "search.inc";
     _shn_ims_form_search();
}
function shn_ims_search_cr(){
    global $global;
    include_once $global['approot']."/inc/lib_location.inc";
    include_once "view_inv.inc";
    $VARCHAR=100;
    $db=$global["db"];
  //   list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Inventory Sector",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
    $post_loc=$_POST{"loc_sel"};
    $locs=shn_location_get_descendants($post_loc);
    $loc="($locs)";
    $i=0;
    $org=array();
    $org_type=$_POST{"inventory_type"};
    while($i<count($sector)){
        $q="select inv_uuid from location_details,sector,ims_inventory_records where location_details.location_id in $loc and location_details.poc_uuid=sector.pgoc_uuid and  ims_inventory_records.inv_uuid=sector.pgoc_uuid";
        $res_org=$db->Execute($q);
        while(!$res_org==NULL && !$res_org->EOF){
            array_push($org,$res_org->fields[0]);
            $res_org->MoveNext();
        }
        $i=$i+1;
    }
?>
<h2><?=_("Search Result")?></h2>
    <div id ="result">
        <table>
            <thead>
                <td><?=_("Inventory Name")?></td>
                <td><?=_("Country of Origin")?></td>
                <td><?=_("Contact Address")?></td>
                <td><?=_("Contact Number")?></td>
                <td><?=_("Contact Email")?></td>
                <td><?=_("Man Power")?></td>
                <td><?=_("Facilities")?></td>
        <td><?=_("Space")?></td>
            </thead>
            <tbody>
<?php
    $i=0;
    $org=array_unique($org);
    $i=0;
    while($i<count($org)){
        _shn_display_org($org[$i],false,true);
        $i=$i+1;
    }
?>
        </tbody>
    </table>
</div>
<?php
}

/*function shn_ims_add_item_temp()
{
    global $global;
    include_once 'add_item.inc';
    _shn_ims_add_item_header();
    shn_form_fopen('add_item');
    add_item($temp);
    shn_form_fclose();
}*/
function shn_ims_minimum_quantity_action()
{
    global $global;
    require_once 'mini_quantity.inc';
    _shn_ims_minimum_quantity_action();
}
function shn_ims_minimum_quantity_item()
{
    include_once 'mini_quantity.inc';
    _shn_ims_mini_quantity_item_select();
}

function shn_ims_minimum_quantity()
{
    
    include_once 'mini_quantity.inc';
    _shn_ims_mini_quantity($catalog_id=null,$inv_id=null);
    
}

function shn_ims_mini_quantity_db()
{
    require_once 'mini_quantity.inc';
    //$inv_id=trim($_POST['inv_id']);
    //$catalog_id=trim($_POST['catalog_id']);
    if (_shn_ims_validate_minimum_quantity())
    {
        display_errors();
        //_shn_ims_mini_quantity($catalog_id,$inv_id);
        
	//shn_ims_minimum_quantity_item();
        shn_ims_reorder_level_edit();    
    }
    else
    {
        _shn_ims_mini_quantity_db();
    
    }
}

function shn_ims_view_edit_reorder()
{
    include_once 'mini_quantity.inc';
    _shn_ims_view_edit_reorder();
}    

function shn_ims_view_edit_reorder_page()
{
    include_once 'mini_quantity.inc';
    _shn_ims_view_edit_reorder_page();
}

function shn_ims_reorder_level_edit()
{
    global $global;
    include_once 'mini_quantity.inc';
    $catalog_id = trim($_REQUEST['catalog_id']);
    $inv_id = trim($_REQUEST['inv_id']);
    _shn_ims_mini_quantity($catalog_id, $inv_id);
    //shn_ims_minimum_quantity($catalog_id,$inv_id);
    //$sql="UPDATE ims_reorder_level SET WHERE";
}



function shn_ims_reorder_level_delete()
{
    global $global;
    include_once 'mini_quantity.inc';
    $catalog_id = trim($_REQUEST['catalog_id']);
    $inv_id = trim($_REQUEST['inv_id']);
    $db=$global["db"];
    $sql="DELETE FROM ims_reorder_level WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
    $ims=$db->Execute($sql);
    shn_ims_view_edit_reorder_page();
}
function shn_ims_send_item()
{    
    global $global;
    include_once('transfer_inv.inc');
    _shn_ims_send_main();
}

function shn_ims_receive_item()
{
    global $global;
    include_once('transfer_inv.inc');
    _shn_ims_receive();
}

function shn_ims_receive_item_page()
{
    global $global;
    $transit_id = trim($_REQUEST['transit_id']);
    $suplier_id = trim($_REQUEST['suplier_id']);
    include_once('transfer_inv.inc');
    _shn_ims_receive_item_page($transit_id,$suplier_id);
}

function shn_ims_receive_item_db()
{
    
    global $global;
    require_once('transfer_inv.inc');
    
    if(_shn_ims_validate_receive_item_page())
    {
        display_errors();
        shn_ims_receive_item_page();
    }
    else
    {
        _shn_ims_receive_item_db();
    }
    /**global $global;
    include_once('transfer_inv.inc');
    _shn_ims_receive_item_db();*/


}

function shn_ims_send_item_page($cate=null)
{
    global $global;
    $catalog_id=$cate;
    include_once('transfer_inv.inc');
    //_shn_ims_send();
    _shn_ims_send_item_table_view_($catalog_id);
}

function shn_ims_send_item_data_collectpage()
{
    global $global;
    $item_id = trim($_REQUEST['item_id']);
    $parent_id=trim($_REQUEST['parent_id']);
    $unit_id_send=trim($_REQUEST['unit_id']);
    include_once('transfer_inv.inc');
    _shn_ims_send($item_id,$parent_id,$unit_id_send);
}

function shn_ims_send_item_db()
{

    global $global;
    require_once('transfer_inv.inc');
    
    if(_shn_ims_validate_send_item_page())
    {
        display_errors();
        shn_ims_send_item_data_collectpage();
    }
    else
    {
        _shn_ims_send_db();
    }
    /*global $global;
    include_once('transfer_inv.inc');
    _shn_ims_send_db();*/
}

//Item Prediction Reports
function shn_ims_optim_item()
{
	include_once ("optimize.inc");
	_shn_ims_optim_item_main_page();
}

function shn_ims_optim_inventory()
{
    include_once("optimize.inc");
    _shn_ims_optim_inventory();
}

function shn_ims_prediction_inv()
{
    global $global;
    include_once("optimize.inc");
    _shn_ims_prediction_inv_actions();
}

function shn_ims_optim_relation_inventories()
{
	global $global;
	$catalog_id=trim($_REQUEST['catalog_id']);
	$inv_id=trim($_REQUEST['inv_id']);
	$time_period=trim($_REQUEST['time_period']);

	include_once("optimize.inc");
	_shn_ims_optim_relation_inventories($catalog_id,$inv_id,$time_period);
}

function shn_ims_prediction_page()
{
	include_once ("optimize.inc");
	_shn_ims_prediction_page();

}

function shn_ims_prediction_report()
{
	global $global;
	include_once ("optimize.inc");
	_shn_ims_optim_item_actions();
}

function shn_ims_optimize_relation_items()
{
	global $global;
	include_once ("optimize.inc");
	_shn_ims_optimize_relation_items();
}

/*function shn_ims_optim_main_page()
{
    include_once('optimize.inc');
    _shn_ims_optim_main_page();
}*/

function shn_ims_alternate_item()
{
	include_once ("optimize.inc");
	_shn_ims_alternate_item();
}

function shn_ims_alternate_item_page()
{
	include_once ("optimize.inc");
	_shn_ims_alternate_item_page();
}

function shn_ims_alternate_item_table()
{
	include_once ('optimize.inc');
	_shn_ims_alternate_item_table();
}

function shn_ims_alternate_item_db()
{
	global $global;
        $parent_id=$_REQUEST['parent_id'];
	$catalog_id=$_REQUEST['catalog_id'];
	$inv_id=$_REQUEST['inv_id'];
	include_once ('optimize.inc');
	_shn_ims_alternate_item_db($parent_id,$catalog_id,$inv_id);
}

function shn_ims_relation_item()
{
	include_once("optimize.inc");
	_shn_ims_relation_item();
}

function shn_ims_relation_item_page()
{
	include_once("optimize.inc");
	_shn_ims_relation_item_page();
}

function shn_ims_relation_item_table()
{
	include_once("optimize.inc");
	_shn_ims_relation_item_table();
}

function shn_ims_relation_item_db()
{
	global $global;
	$parent_id=$_REQUEST['parent_id'];
	$catalog_id=$_REQUEST['catalog_id'];
	$inv_id=$_REQUEST['inv_id'];
	include_once ('optimize.inc');
	_shn_ims_relation_item_db($parent_id,$catalog_id,$inv_id);
}

?>

