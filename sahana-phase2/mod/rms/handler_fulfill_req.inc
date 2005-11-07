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
require_once('lib_rms.inc');

function clear_donor()
{
    $_SESSION['rms_donor_id'] = '';
    $_SESSION['rms_donor_name'] = '';
    $_SESSION['rms_donor_contact'] = '';
    $_SESSION['rms_donor_comments'] = '';
}
 
if ($_GET['seq'] == 'add' && rms_validate_mform(2))
{
    $itm = $_POST['ff_item'];
    $user = $global['person_id'];
    $qty = $_POST['ff_quantity'];
    $stat = $_POST['ff_status'];
    
    
    $d_id = $_SESSION['rms_donor_id'];
    $d_name = $_POST['ff_d_name'];
    $d_con = $_POST['ff_d_contact'];
    $d_comm = $_POST['ff_d_comments'];
    $d_same = $_POST['ff_same_donor'];
    
    print "<br/>" . $_SESSION['rms_donor_name'] . "<br/>$d_id";
    
    
    if ($d_id=='')
    {
        $sql = "INSERT INTO rms_req_ff (name,contact,comments) " .
                "VALUES ('$d_name','$d_con','$d_comm')";
                
        if ($global['db']->Execute($sql) === false)
        {
            $msg = $global['db']->ErrorMsg();
            db_dbug($sql,$msg);
        }
        
        $d_id = $global['db']->Insert_ID();
        
    }
    
    if ($d_same == 'same_donor')
    {
        $_SESSION['rms_donor_id'] = $d_id;
        $_SESSION['rms_donor_name'] = $d_name;
        $_SESSION['rms_donor_contact'] = $d_con;
        $_SESSION['rms_donor_comments'] = $d_comm;
    }
    
    $sql = "INSERT INTO rms_req_ff (req_item_id,user_id,quantity,ff_status,req_donor_id) " .
            "VALUES ($itm, $user, $qty, '$stat', $d_id)";
    
    if ($global['db']->Execute($sql) === false)
    {
        $msg = $global['db']->ErrorMsg();
        db_dbug($sql,$msg);
    }

    if ($d_same != 'same_donor')
    {
        clear_donor();
    }
}
else
{
    clear_donor();
}
?>

<?php show_rms_heading(); ?>
<h3><a name="list">Fulfil Requests</a></h3>

<form action="index.php?mod=rms&amp;act=fulfill_req&amp;req_id=<?php print $req_id ?>&amp;seq=add#form" name="req_new_frm" id="rmsforms" method="post">
<?php show_init_vals(_("Request Information")); ?>
<br/>
<a name="form"></a>
<?php show_ffitems_table(); ?>
</form>
<br/>
<a id="finish" href="index.php?mod=rms&amp;act=vw_req">[ &nbsp; <?php print _("Finish") ?> &nbsp; ]</a>