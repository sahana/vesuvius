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


include_once $global['approot'] . "/inc/lib_modules.inc";
include_once $global['approot'] . "/inc/lib_validate.inc";
include_once $global['approot'] . "/inc/lib_form.inc";
include_once $global['approot'] . "/inc/lib_table.inc";
include_once $global['approot'] . "/inc/lib_errors.inc";
include_once $global['approot'] . "/inc/lib_menu.inc";
include_once $global['approot'] . "/inc/lib_location.inc";
include_once $global['approot'] . "/inc/lib_uuid.inc";
include_once $global['approot'] . "/inc/lib_security/lib_acl.inc";
include_once "lib_ims.inc";
include_once $global['approot'] . '/mod/cs/lib_cs.inc';
include_once $global['approot'] . '/mod/or/lib_or.inc';
include_once $global['approot'] . "/inc/lib_gis/gis_fns.inc";
include_once $global['approot'] . "/inc/reporting/lib_reporting.inc";
include_once 'errors.inc';
include_once 'lib_ims_rss.inc';


//global $global;

/**
 * IMS main menu
 */
function shn_ims_mainmenu()
{
    global $global;
    $module = $global['module'];

    shn_mod_menuopen(shn_get_module_name());
    shn_mod_menuitem("default",_t("Home"),$module);
    shn_mod_menuitem("search_main",_t("Search"),$module);
    shn_mod_menuitem("view_inv",_t("Inventories"),$module);
    
   // shn_mod_menuitem("search_item",_t("Find Items"),$module);
   // shn_mod_menuitem("search_inventory",_t("Find Inventories"),$module);
   
    
    shn_mod_menuitem("view_edit_item",_t("Add/List Items"),$module);
    shn_mod_menuitem("view_edit_reorder_page",_t("Re-Order Level"),$module);
     shn_mod_menuitem("consolidated_items",_t("Consolidated Items"),$module);
     shn_mod_menuitem("buy_items",_t("Buy Items"),$module);
    
    shn_sub_mod_menuopen(_t("Reports"));
    shn_sub_mod_menuitem("report_inv_items",_t("Items by Inventory"),$module);
    shn_sub_mod_menuitem("report_org_items",_t("Items by Organization"),$module);
    shn_sub_mod_menuitem("report_expired",_t("Expired Items"),$module);
    shn_sub_mod_menuitem("report_destroyed",_t("Destroyed Items"),$module);
    shn_sub_mod_menuitem("report_minimum",_t("Re-order Level"),$module);
    shn_sub_mod_menuitem("report_transit_item",_t("Transfered Items"),$module);
    //shn_sub_mod_menuitem("report_prediction",_t("prediction reports"),$module);
    shn_sub_mod_menuitem("gis_inv",_t("Map by Inventory"),$module);
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen(_t("Optimization"));
    shn_sub_mod_menuitem("alternate_item",_t("Set Alternate"),$module);
    shn_sub_mod_menuitem("relation_item",_t("Set Relation"),$module);
    shn_sub_mod_menuitem("optim_item",_t("Prediction by Item"),$module);
    shn_sub_mod_menuitem("optim_inventory",_t("Prediction by Inventory"),$module);
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
    //shn_sub_menuitem("Optim_main_page",_t("Optimization"),$module);

    include $global['approot'] . "/inc/handler_mainmenu.inc";

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

function shn_ims_search_main($search_array=NULL)
{
    global $global;
    include_once ('search.inc');
    _shn_ims_search_main($search_array);    
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
    if (_shn_cs_validate_sub_cat_form()) {
        display_errors();
        shn_ims_search_item();
    } else {
        include_once('search.inc');
        _shn_ims_search_item_page();
    }
    
}
/**
 *  Add Category Selection form
 */
function shn_ims_add_item_main_page()
{
    global $global;
    include_once ('add_item.inc');
    $inventory_id = $_REQUEST['inv_id'];
    
    _shn_ims_add_item_main_page($inventory_id);
        
}
function shn_ims_add_item($parent_id = false)
{
    global $global;
    
    
    if (_shn_ims_validate_sub_cat_form() && $parent_id == null) {
       
        add_error(_t(SHN_ERR_IMS_CATALOGUE_MISSING));
        shn_ims_view_edit_item();
    } else {
        include_once('add_item.inc');
        _shn_ims_add_item_header();
        shn_form_fopen("add_item_db");
        add_item($temp,$parent_id);
        shn_form_fclose();
    }

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
    //$i=0;
    //_shn_ims_view_edit($inventory_id);
    _shn_ims_view_edit($i = 0,$Limit = 20);
}

function shn_ims_view_edit_item_actions()
{
    global $global;
    include_once ('view_edit_item.inc');
    _shn_ims_view_edit_item_actions();
}

function shn_ims_report_minimum()
{
    include_once ('ims_report.inc');
    _shn_ims_report_minimum();
}

function shn_ims_report_expired()
{
    include_once ('ims_report.inc');
    _shn_ims_report_expired();
}

function shn_ims_report_destroyed()
{
    include_once ('ims_report.inc');
    _shn_ims_report_destroyed();
}

function shn_ims_report_transit_item()
{
	print ("<h1><center>Transfered Items Report</center></h1>");
    include_once ('ims_report.inc');
    _shn_ims_transfer_item_report();
}

function shn_ims_report_prediction()
{
    include_once ('ims_report.inc');
    _shn_ims_report_prediction();
}

function shn_ims_destroy_item()
{
    global $global;
    $item_id = trim($_REQUEST['item_id']);
    include_once ('ims_report.inc');
    _shn_ims_destroy_item($item_id);
}


function shn_ims_add_item_db()
{

    global $global;
    include_once('add_item_db.inc');
    $parent_id = trim($_POST['parent_id']);
    
    if (_shn_ims_validate_additemform()) {
    
        display_errors();
        shn_ims_add_item($parent_id);
    } else {
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

function shn_ims_search_main_db()
{
    global $global;
    include_once ('search.inc');
    $search_array=$_POST['search_array'];
    shn_ims_search_main($search_array);
    /*if ($search_array=='inventory') {
        
    } else {

    }*/
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
    
    if (_shn_ims_validate_additemform()) {
        display_errors();
        shn_ims_add_item1();
    } else {
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
    $db = $global["db"];
?>

<?php
    require_once('view_edit_item.inc');
    //$parent_id=$_REQUEST['parent_id'];
    $item_id = $_REQUEST['item_id'];
    $sql = "DELETE FROM ims_item_records WHERE item_id='$item_id';";
    $ims = $db->Execute($sql);
    add_confirmation(_t("Record has been deleted successfully"));

    shn_ims_view_edit_item();
}

function shn_ims_delete_item_confirm()
{
    global $global;
    require_once('view_edit_item.inc');
    $parent_id = $_REQUEST['parent_id'];
    $item_id = $_REQUEST['item_id'];
?>
    <SCRIPT language="JavaScript">


    var where_to= confirm("Are You Sure you want to delete this record?");
    if (where_to== true)
    {
   //window.location="http://yourplace.com/yourpage.htm";
         window.location="index.php?mod=ims&act=delete_item_db&item_id=<?php echo $item_id; ?>&parent_id=<?php echo $catalog_id; ?>";
    }
    else
    {
         window.location="index.php?mod=ims&act=view_edit_item";
     }

</SCRIPT>
<?php
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

function shn_ims_search_inventory()
{
    include_once ('search.inc');
    _shn_ims_form_search();
}


function shn_ims_search_inventory_db()
{
    include_once ('search.inc');
    $action = $_POST['action'];
    if ($action == 'search_name') {
        if (_shn_ims_validate_search_inventories()) {
            add_error(SHN_ERR_IMS_INVENTORY_SEARCH_ERROR);
            shn_ims_search_inventory();
        } else {
            _shn_ims_search_inventory_db();
        }
    }
    if ($action == 'search_address') {
        if (_shn_ims_validate_search_inventories()) {
            add_error(SHN_ERR_IMS_INVENTORY_ADDRESS_ERROR);
            shn_ims_search_inventory();
        } else {
            _shn_ims_search_address();
        }
    }
}

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
function shn_ims_reg_inv_actions()
{
    include_once ('view_inv.inc');
    $action = trim($_POST['action']);
    _shn_ims_reg_inv_actions($action);

}

function shn_ims_reg_inv($error = false)
{
    require_once ("reg_inv.inc"); 
    //_shn_ims_test();
    _shn_ims_regform_inv($error);
}

function shn_ims_reg_inv_gis()
{
    require_once("reg_inv.inc");
    if (_shn_ims_validate_reg_inv()) {
        display_errors();
        shn_ims_reg_inv();
        
    } else {
        // print ("test");
        _shn_ims_reg_inv_gis();
    }
}

function shn_ims_reg_inv_cr()
{
    include_once("process_inv.inc");
    _shn_ims_reg_inv_cr();
}

function shn_ims_reg_operation_cr()
{
    include_once("process_inv.inc");
    _shn_ims_reg_operation_cr();
}

function shn_ims_view_inv_submit()
{
    include_once("process_inv.inc");
    include_once ("view_inv.inc");
    //require_once ($global['approot'] . 'inc/lib_security/authenticate.inc');
    $act = $_POST["action"];
   // $acl_enabled = shn_acl_get_state("or");
   // $req_act = "_shn_ims_" . $act . "_org";
   // $allow = (!shn_acl_check_perms_action($_SESSION['user_id'],$req_act) || !$acl_enabled)? true : false;
   
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
    if (NULL == $_REQUEST['id']) {
    ?>
<h2> <?php echo _t("Inventory Registry") ?></h2>
<?php	$Limit = 20;
        _shn_ims_viewform_allorg(null,null,$Limit);
    } else {
        _shn_ims_viewform_org($_REQUEST['id'],$Limit = 20);
    }
}

function shn_ims_drill_report()
{
    include_once("ims_report.inc");
    $parent = $_GET["id"];
     _shn_ims_level($parent);
}
function shn_ims_org_sector()
{
    include_once("ims_report.inc");
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
function shn_ims_search_cr()
{
    global $global;
    include_once $global['approot'] . "/inc/lib_location.inc";
    include_once "view_inv.inc";
    $VARCHAR = 100;
    $db = $global["db"];
  //   list($error,$sector)=(shn_validate_opt_field('opt_sector_type',$_POST{"opt_sector_type"},"Inventory Sector",$VARCHAR,true))?array($error,$_POST{"opt_sector_type"}):array(true,NULL);
    $post_loc = $_POST["loc_sel"];
    $locs = shn_location_get_descendants($post_loc);
    $loc = "($locs)";
    $i = 0;
    $org = array();
    $org_type = $_POST["inventory_type"];
    while ($i < count($sector)) {
        $q = "SELECT inv_uuid FROM location_details,sector,ims_inventory_records WHERE location_details.location_id in $loc AND location_details.poc_uuid=sector.pgoc_uuid AND  ims_inventory_records.inv_uuid=sector.pgoc_uuid";
        $res_org = $db->Execute($q);
        while (!$res_org == NULL && !$res_org->EOF) {
            array_push($org,$res_org->fields[0]);
            $res_org->MoveNext();
        }
        $i = $i + 1;
    }
?>
<h2><?=_t("Search Result")?></h2>
    <div id ="result">
        <table>
            <thead>
                <td><?=_t("Inventory Name")?></td>
                <td><?=_t("Country of Origin")?></td>
                <td><?=_t("Contact Address")?></td>
                <td><?=_t("Contact Number")?></td>
                <td><?=_t("Contact Email")?></td>
                <td><?=_t("Man Power")?></td>
                <td><?=_t("Facilities")?></td>
        <td><?=_t("Space")?></td>
            </thead>
            <tbody>
<?php
    $i = 0;
    $org = array_unique($org);
    $i = 0;
    while ($i < count($org)) {
        _shn_display_org($org[$i],false,true);
        $i = $i + 1;
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
    //$Limit=trim($_POST['records']);
    _shn_ims_minimum_quantity_action();
}
function shn_ims_minimum_quantity_item()
{
    include_once 'mini_quantity.inc';
    _shn_ims_mini_quantity_item_select();
}

function shn_ims_minimum_quantity()
{
    if (_shn_cs_validate_sub_cat_form()) {
        display_errors();
        shn_ims_view_edit_reorder_page();
    } else {
        include_once 'mini_quantity.inc';
        _shn_ims_mini_quantity($catalog_id = null,$inv_id = null);
    }
    
}

function shn_ims_mini_quantity_db()
{
    require_once 'mini_quantity.inc';
    //$inv_id=trim($_POST['inv_id']);
    //$catalog_id=trim($_POST['catalog_id']);
    if (_shn_ims_validate_minimum_quantity()) {
        display_errors();
        //_shn_ims_mini_quantity($catalog_id,$inv_id);
        
        //shn_ims_minimum_quantity_item();
        shn_ims_reorder_level_edit();    
    } else {
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
    //$Limit=20;
    _shn_ims_view_edit_reorder_page($page_number = 0,$Limit = 20);
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
    $db = $global["db"];
    $sql = "DELETE FROM ims_reorder_level WHERE catalog_id='$catalog_id' AND inv_id='$inv_id';";
    $ims = $db->Execute($sql);
    add_confirmation(_t("Record has been deleted successfully"));
    shn_ims_view_edit_reorder_page();
}

function shn_ims_reorder_level_delete_confirm()
{
    global $global;
    include_once 'mini_quantity.inc';
    $catalog_id = trim($_REQUEST['catalog_id']);
    $inv_id = trim($_REQUEST['inv_id']);

?>
    <SCRIPT language="JavaScript">


    var where_to= confirm("Are You Sure you want to delete this record?");
    if (where_to== true)
    {
   //window.location="http://yourplace.com/yourpage.htm";
         window.location="index.php?mod=ims&act=reorder_level_delete&inv_id=<?php echo $inv_id; ?>&catalog_id=<?php echo $catalog_id; ?>";
    }
    else
    {
         window.location="index.php?mod=ims&act=view_edit_reorder_page";
     }

</SCRIPT>
<?php

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
    
    _shn_ims_receive($Limit = 20,0);
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
    include_once('transfer_inv.inc');
    //$parent_id=trim($_POST['parent_id']);
    
    if (_shn_ims_validate_receive_item_page()) {
        display_errors();
        shn_ims_receive_item_page();
    } else {
        _shn_ims_receive_item_db();
    }
    /**global $global;
    include_once('transfer_inv.inc');
    _shn_ims_receive_item_db();*/


}

function shn_ims_send_item_page($cate = false)
{
    global $global;
    
    if (_shn_ims_validate_sub_cat_form() && $cate == NULL) {
        add_error(_t(SHN_ERR_IMS_CATALOGUE_MISSING));
        display_errors();
        shn_ims_view_edit_item();
    } else {
        $catalog_id = $cate;
        include_once('transfer_inv.inc');
        //_shn_ims_send();
        _shn_ims_send_item_table_view_t($catalog_id,$Limit = 20,$page_number = 0);
    }
}

function shn_ims_send_item_data_collectpage()
{
    global $global;
    $item_id = trim($_REQUEST['item_id']);
    $parent_id = trim($_REQUEST['parent_id']);
    $unit_id_send = trim($_REQUEST['unit_id']);
    include_once('transfer_inv.inc');
    _shn_ims_send($item_id,$parent_id,$unit_id_send);
}

function shn_ims_send_item_db()
{

    global $global;
    require_once('transfer_inv.inc');
    
    if (_shn_ims_validate_send_item_page()) {
        display_errors();
        shn_ims_send_item_data_collectpage();
    } else {
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
    
    print "<h1><center>"._t("Select Inventory to Predict")."</center></h1>";
    
    _shn_ims_optim_inventory();
}

function shn_ims_prediction_inv()
{
    global $global;
    include_once("optimize.inc");
    $action = trim($_POST['action']);
    if ($action == 'customizedreport') {
        if (_shn_ims_validate_prediction_page()) {
            shn_ims_optim_inventory();
        } else {
            _shn_ims_prediction_inv_actions();
        }
    } else {
        _shn_ims_prediction_inv_actions();
    }
}

function shn_ims_optim_relation_inventories()
{
        global $global;
        $catalog_id = trim($_REQUEST['catalog_id']);
        $inv_id = trim($_REQUEST['inv_id']);
        $time_period = trim($_REQUEST['time_period']);
        $algorithm = trim($_REQUEST['algorithm']);

        include_once("optimize.inc");
        _shn_ims_optim_relation_inventories($catalog_id,$inv_id,$time_period,$algorithm);
}

function shn_ims_prediction_page()
{
    if (_shn_cs_validate_sub_cat_form()) {
        display_errors();
        shn_ims_optim_item();
    } else {
        include_once ("optimize.inc");
        _shn_ims_prediction_page();
    }

}

function shn_ims_prediction_report()
{
    global $global;

    include_once ("optimize.inc");
    $action = trim($_POST['action']);

    if ($action == 'customizedreport') {
        if (_shn_ims_validate_prediction_page()) {
            //shn_ims_optim_item();
            _shn_ims_prediction_page();
        } else {
            _shn_ims_optim_item_actions();
        }
    } else {
        _shn_ims_optim_item_actions();
    }
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
    if (_shn_cs_validate_sub_cat_form()) {
        display_errors();
        shn_ims_alternate_item();
    } else {
        include_once ("optimize.inc");
        _shn_ims_alternate_item_page();
    }
}

function shn_ims_alternate_item_table()
{
        include_once ('optimize.inc');
        _shn_ims_alternate_item_table();
}

function shn_ims_alternate_item_db()
{
    global $global;
    $parent_id = $_REQUEST['parent_id'];
    $catalog_id = $_REQUEST['catalog_id'];
    $inv_id = $_REQUEST['inv_id'];
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
    if (_shn_cs_validate_sub_cat_form()) {
        display_errors();
        shn_ims_relation_item();
    } else {
        include_once("optimize.inc");
        _shn_ims_relation_item_page();
    }
}

function shn_ims_relation_item_table()
{
    include_once("optimize.inc");
    _shn_ims_relation_item_table();
}

function shn_ims_relation_item_db()
{
    global $global;
    $parent_id = $_REQUEST['parent_id'];
    $catalog_id = $_REQUEST['catalog_id'];
    $inv_id = $_REQUEST['inv_id'];
    include_once ('optimize.inc');
    _shn_ims_relation_item_db($parent_id,$catalog_id,$inv_id);
}

function shn_ims_gis_inv()
{
    //global $global;
    //$inv_id="all";		
    $inv_id = $_REQUEST['id'];

?>
    <h1 align="center"><?php print _t('Map by Inventory');?></h1>
<?php
    echo '<br>';
    echo '<br>';

    
    shn_form_fopen('view_inv',null,$form_opts=null);
    //shn_form_fsopen(null);
    $array = _shn_ims_gis_inv($inv_id);
    shn_gis_map_with_markers($array);
    //shn_form_fclose();
    //shn_form_fopen('view_inv');
    shn_form_fsopen(null);
    shn_form_submit("Go Back");
    shn_form_fsclose();
    //shn_form_fsclose();
    shn_form_fclose();
    //}

}

function shn_ims_expired_item_report1()
{
    //global $global;
    include_once 'ims_report.inc';
    $action = trim($_POST['action']);
    include_once 'report.inc';
    if ($action == 'pdf_expired') {
        shn_ims_expired_item_report();
        shn_report_download('shn_ims_expired_item_report',_t('Download The PDF report here'));
    } else if ($action == 'ods_expired') {
        shn_ims_expired_item_ods();
        shn_report_download('shn_ims_expired_item_ods',_t('Download the ODS report here'));
    } else if ($action == 'xhtml_expired') {
        shn_ims_expired_item_xhtml();
        shn_report_download('shn_ims_expired_item_xhtml',_t('Download the XHTML report here'));
    }
    
    
    
    
    //report_download_link('shn_ims_expired_item_report');
}

function shn_ims_destroyed_item_pdf()
{
    //global $global;
    include_once 'ims_report.inc';
    $action = trim($_POST['action']);
    include_once 'report.inc';
    if ($action == 'pdf_destroyed') {
        shn_ims_destroyed_item();
        shn_report_download('shn_ims_destroyed_item',_t('Download the PDF report here'));
    } else if ($action == 'ods_destroyed') {
        shn_ims_destroyed_item_ods();
        shn_report_download('shn_ims_destroyed_item_ods',_t('Download the ODS report here'));
    } else if ($action == 'xhtml_destroyed') {
        shn_ims_destroyed_item_xhtml();
        shn_report_download('shn_ims_destroyed_item_xhtml',_t('Download the XHTML report here'));
    }
}

function shn_ims_reorder_level_pdf()
{
    include_once 'ims_report.inc';
    $action = trim($_POST['action']);
    include_once 'report.inc';
    if ($action == 'pdf_reorder') {
        shn_ims_reorder_level_report_pdf();
        shn_report_download('shn_ims_reorder_level_report_pdf',_t('Download the PDF report here'));
    } else if ($action == 'ods_reorder') {
        shn_ims_reorder_level_report_ods();
        shn_report_download('shn_ims_reorder_level_report_ods',_t('Download the ODS report here'));
    } else if ($action == 'xhtml_reorder') {
        shn_ims_reorder_level_report_xhtml();
        shn_report_download('shn_ims_reorder_level_report_xhtml',_t('Download the XHTML report here'));
    }
}

/**
**********Paging*********
**/

function shn_ims_list_items_paging($Limit = NULL)
{
    global $global;

    include_once('view_edit_item.inc');
    $page_number = $_REQUEST['$i'];
    if ($page_number != NULL) {
        $Limit = $_REQUEST['Limit'];
    } else {
        $page_number = 1;
    }
?>
    <b><?php echo _t("Page Number : ") . $page_number; ?></b>
<?php
    $i = $page_number;
    _shn_ims_view_edit_header();
    _shn_ims_view_edit($i,$Limit);

}

function shn_ims_reorder_level_paging($Limit = null)
{
    global $global;

    include_once('mini_quantity.inc');
    $page_number = $_REQUEST['$i'];
    if ($page_number != NULL) {
        $Limit = $_REQUEST['$Limit'];
    } else {
        $page_number = 1;
    }
?>
    <b><?php echo _t("Page Number : ") . $page_number; ?></b>
<?php
    _shn_ims_view_edit_reorder_page($page_number,$Limit);

}

function shn_ims_inventory_paging($Limit = null)
{
    global $global;

    include_once('view_inv.inc');
    $page_number = $_REQUEST['$i'];
    

    if ($page_number != NULL) {
        $Limit = $_REQUEST['$Limit'];
    } else {
        $page_number = 1;
    }

    
?>
    <b><?php echo _t("Page Number : ") . $page_number; ?></b>
<?php

    _shn_ims_viewform_allorg($no = NULL,$page_number,$Limit);

}

function shn_ims_receive_item_paging()
{
    include_once('transfer_inv.inc');
    $Limit = trim($_POST['records']);
    $page_number = $_REQUEST['$i'];
    if ($page_number != 0) {
        $Limit = $_REQUEST['$Limit'];
    }
    if (!is_numeric($Limit)) {
        add_error(SHN_ERR_IMS_AMOUNT_NUMERIC);
        display_errors();
        _shn_ims_receive(20,$page_number = 0);
    }
    if ($Limit == '0' || $Limit < 0) {
        add_error(SHN_ERR_IMS_AMOUNT_NUMERIC);
        display_errors();
        _shn_ims_receive(20,$page_number = 0);
    }
    
    if (is_numeric($Limit)) {
     
        _shn_ims_receive($Limit,$page_number);
    }
}

function shn_ims_send_item_paging()
{
    include_once 'transfer_inv.inc';
    $Limit = trim($_POST['records']);
    $catalog_id = $_SESSION['catalog_id'];
    $page_number = $_REQUEST['$i'];
    if ($page_number != 0) {
        $Limit = $_REQUEST['$Limit'];
    }
    if (!is_numeric($Limit)) {
        add_error(SHN_ERR_IMS_AMOUNT_NUMERIC);
        display_errors();
        _shn_ims_send_item_table_view_t($catalog_id,20,$page_number = 0);
    }
    if ($Limit == '0' || $Limit < 0) {
        add_error(SHN_ERR_IMS_AMOUNT_NUMERIC);
        display_errors();
        _shn_ims_send_item_table_view_t($catalog_id,20,$page_number = 0);
    }
    if (is_numeric($Limit)) {
    
    _shn_ims_send_item_table_view_t($catalog_id,$Limit,$page_number);
    }
}

function shn_ims_report_inv_items()
{
	print ("<h1><center>Items by Inventory Report</center></h1>");
	global $global;
	$db = $global['db'];
	//echo 'test';	
	include_once 'ims_report.inc';
	_shn_ims_inv_items();
}

function shn_ims_report_org_items()
{
	print ("<h1><center>Items by Organization Report</center></h1>");
	global $global;
	$db = $global['db'];
	include_once 'ims_report.inc';
	_shn_ims_org_items();
}

function shn_ims_consolidated_items()
{
	//echo 'test';
	include_once 'handler_create_kit.inc';
}

function shn_ims_buy_items()
{
	include_once 'handler_handle_money.inc';
}



?>
