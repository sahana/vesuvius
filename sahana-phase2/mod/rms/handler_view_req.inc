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
?>

<?php show_rms_heading(); ?>
<?php 
if (!isset($_GET['seq']))
{
    $filter = $_REQUEST['filter'];
    $value = $_REQUEST['value'];
    $user = $_GET['user'];
    $stat = $_GET['stat'];
    
    $req_count = count_req();
    
    $url="index.php?mod=rms&amp;act=vw_req";
    $url_usr="index.php?mod=rms&amp;act=vw_req" .
              "&amp;user=$user";
?>
    <div id=req_list_top>
    <?php print _("Request Status")?> :
    <a href=<?php print $url_usr . "&amp;stat=open"; ?>><?php print _("Open requests")?></a> | 
    <a href=<?php print $url_usr . "&amp;stat=closed"; ?>><?php print _("Closed requests")?></a> | 
    <a href=<?php print $url. "&amp;user=$user" . "&amp;stat=all"; ?>><?php print _("All requests")?></a>
    <?php show_rms_categories($value) ?>
    </div>
    <div id=req_list>
    <br>
<?php
    show_request_list($filter,$value,$user,'open');
}
?>
    </div>
<?php
    
if ($_GET['seq'] == 'detail')
{
    $req_id = $_GET['req_id'];
    $user_id = $global['person_id'];
?>
    <h3>USER : <?php print $global['person_id']; ?></h3>
    <form id="rmsforms" action="">
    <?php show_init_vals(_("Request Information")); ?>
    <br/>
<?php
    if (is_requester($req_id,$user_id))
    {
        show_ffitems_table(false,false);
?>  
    <br/>
    [<a href="index.php?mod=rms&amp;act=mgt_req&amp;req_id=<?php print $req_id ?>">
     <?php print _("Change Request Status") ?> </a>]
<?php
    if (is_req_open($req_id))
    {
?> 
    | [<a href="index.php?mod=rms&amp;act=cstat_req&amp;req_id=<?php print $req_id ?>&amp;stat=closed">
     <?php print _("Close Request") ?> </a>]    
<?php
    }
    }
    else
    {
        show_ffitems_table(false,false);
?>
    <br/>
    [<a href="index.php?mod=rms&amp;act=fulfill_req&amp;req_id=<?php print $req_id ?>#form">
     <?php print _("Fulfill") ?></a>]
<?php
    }
}
?>