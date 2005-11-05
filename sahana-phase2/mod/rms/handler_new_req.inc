<?php
/**
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

global $global;

$global['items'] = false;
print ("<h3>USER : " . $global['person_id'] . "</h3>");
?>

<?php show_rms_heading(); ?>

<?php

if ($_GET['stat'] == 'add' && rms_validate_mform(1)) 
{    
    $vals = rms_get_initvals();
    //$req_date = $vals['req_date'];
    $req_name = $vals['req_name'];
    $req_contact = $vals['req_contact'];
    $req_address = $vals['req_address'];
    $req_site_name = $vals['req_site_name'];
    $req_site_district = $vals['req_site_district'];
    $req_site_address = $vals['req_site_address'];
    $req_comments = $vals['req_comments'];
    $user_id = $global['person_id'];
    
    
    
    $sql = "INSERT INTO rms_request (name, contact, address, site_name," .
            " site_district, site_address, comments, user_id) " .
           "VALUES ('$req_name', '$req_contact', '$req_address'," .
            " '$req_site_name', '$req_site_district', '$req_site_address'," .
            " '$req_comments', '$user_id')";
    
    if ($global['db']->Execute($sql) === false)
    {
        $msg = $global['db']->ErrorMsg();
        db_dbug($sql,$msg);
    }
    $req_id = $global['db']->Insert_ID();
    
    //Item info
    $req_category = $_POST['req_category'];
    $req_item = $_POST['req_item'];
    $req_units = $_POST['req_units'];
    $req_quantity = $_POST['req_quantity'];
    $req_priority = $_POST['req_priority'];
    
    $sql = "INSERT INTO rms_req_item (cat_id, item, units, " .
            "quantity, priority_id, req_id) " .
           "VALUES ($req_category, '$req_item', '$req_units', " .
            "$req_quantity, '$req_priority', $req_id)";
    
    if ($global['db']->Execute($sql) === false)
    {
        $msg = $global['db']->ErrorMsg();
        db_dbug($sql,$msg);
    }

?>
    <form action="index.php?mod=rms&amp;act=new_req&amp;req_id=<?php print $req_id ?>&amp;stat=more_itms&amp;add_item=1#items_form" name="req_new_frm" id="rmsforms" method="post">
    <?php show_init_vals(_("New Request")); ?>
    <a name="items_form"></a><br/>
    <?php show_items_table($req_id,true); ?>    
    <br/>
    <?php show_item_fields($req_id); ?>
    </form>
    <br/>
    <form action="index.php?mod=rms" id="rmsforms">
        <fieldset>
        <a id="clear" href="index.php?mod=rms&amp;act=new_req&amp;stat=3&amp;req_id=<?php print $req_id ?>">[<?php print _("Remove Request") ?>]</a>
        <?php 
            if ($global['items'])
            { 
        ?>
            <a id="finish" href="index.php?mod=rms&amp;act=new_req">[ &nbsp; <?php print _("Finish") ?> &nbsp; ]</a>
        <?php
            }
        ?>
        </fieldset>
    </form>
<?php
}

if ($_GET['stat'] == 'more_itms') 
{   
    $req_id = $_GET['req_id']; 
    if ($_GET['add_item'] == 1 && !isset($_GET['remove_item']) && rms_validate_mform())
    {        
        $req_category = $_POST['req_category'];
        $req_item = $_POST['req_item'];
        $req_units = $_POST['req_units'];
        $req_quantity = $_POST['req_quantity'];
        $req_priority = $_POST['req_priority'];
        
        unset($_SESSION['rms_iform_values']);
        $sql = "INSERT INTO rms_req_item (cat_id, item, units, " .
                "quantity, priority_id, req_id) " .
               "VALUES ($req_category, '$req_item', '$req_units', " .
                "$req_quantity, '$req_priority', $req_id)";
        
        if ($global['db']->Execute($sql) === false)
        {
            $msg = $global['db']->ErrorMsg();
            db_dbug($sql,$msg);
        }
    }
    
    if (isset($_GET['remove_item']))
    {
        global $global;
        $req_item_id = $_GET['remove_item'];
        $sql = "DELETE FROM rms_req_item WHERE req_id=$req_id AND req_item_id=$req_item_id";
        
        if ($global['db']->Execute($sql) === false)
        {
            $msg = $global['db']->ErrorMsg();
            db_dbug($sql,$msg);
        }
    }
?>
    <form action="index.php?mod=rms&amp;act=new_req&amp;stat=more_itms&amp;req_id=<?php print $req_id ?>&amp;add_item=1#items_form" name="req_new_frm" id="rmsforms" method="post">
    <?php show_init_vals(_("New Request")); ?>
    <a name="items_form"></a><br/>
    <?php show_items_table($req_id,true); ?>    
    <br/>
    <?php show_item_fields($req_id); ?>
    </form>
    <br/>
    <form action="index.php?mod=rms" id="rmsforms">
        <fieldset>
        <a id="clear" href="index.php?mod=rms&amp;act=new_req&amp;stat=rem_all&amp;req_id=<?php print $req_id ?>">[<?php print _("Remove Request") ?>]</a>
        <?php 
            if ($global['items'])
            { 
        ?>
        <a id="finish" href="index.php?mod=rms&amp;act=new_req">[ &nbsp; <?php print _("Finish") ?> &nbsp; ]</a>
        <?php
            }
        ?>
        </fieldset>
    </form>
<?php
    if ($_SESSION['rms_errors'])
        $_SESSION['rms_errors'] = false;
}


/**
 * Removing a request
 */
if ($_GET['stat'] == 'rem_all')
{
    global $global;
    $req_id = $_GET['req_id'];
    
    $sql_items = "DELETE FROM rms_req_item WHERE req_id=$req_id";    
    $sql_request = "DELETE FROM rms_request WHERE req_id=$req_id";
    
    if ($global['db']->Execute($sql_items) === false || $global['db']->Execute($sql_request) === false)
    {
        $msg = $global['db']->ErrorMsg();
        db_dbug($sql,$msg);
    } 
    print "<h3>request removed</h3>";   
}

if (!isset($_GET['stat']) || $_SESSION['rms_errors'])
{
?>
    <form action="index.php?mod=rms&amp;act=new_req&amp;stat=add&amp;add_item=1#items_form" name="req_new_frm" id="rmsforms" method="post">
    <?php show_rms_initform(); ?>
    <br/>
    <?php show_item_fields(false); ?>
    </form>
<?php
    if ($_SESSION['rms_errors'])
        $_SESSION['rms_errors'] = false;
}

?>