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

global $global;
$req_id = $_GET['req_id'];
 
if ($_GET['seq'] == 'add')
{
    $itm = $_POST['ff_item'];
    $user = $global['person_id'];
    $qty = $_POST['ff_quantity'];
    $stat = $_POST['ff_status'];
    
    $sql = "INSERT INTO rms_req_ff (req_item_id,user_id,quantity,ff_status) " .
            "VALUES ($itm,$user,$qty,'$stat')";
    
    if ($global['db']->Execute($sql) === false)
    {
        $msg = $global['db']->ErrorMsg();
        db_dbug($sql,$msg);
    }
}
?>

<?php show_rms_heading(); ?>
<h3><a name="list">Fulfil Requests</a></h3>

<form action="index.php?mod=rms&amp;act=fulfill_req&amp;req_id=<?php print $req_id ?>&amp;seq=add#form" name="req_new_frm" id="rmsforms" method="post">
<?php show_init_vals(_("Request Information")); ?>
<br/>
<a name="form"></a>
<?php show_ffitems_table(true); ?>
</form>
<a id="finish" href="index.php?mod=rms&amp;act=vw_req">[ &nbsp; <?php print _("Finish") ?> &nbsp; ]</a>