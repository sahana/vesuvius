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
    $filter = $_GET['filter'];
    $value = $_GET['value'];
    show_request_list($filter,$value);
}
    
if ($_GET['seq'] == 'detail')
{
?>
    <form id="rmsforms" action="">
    <?php show_init_vals(_("Request Information")); ?>
    <br/>
    <?php show_items_table(false,false); ?>
    <br/>
    <a href="index.php?mod=rms&amp;act=fulfill_req&amp;req_id=<?php print $_GET['req_id'] ?>#form"> [Fulfill]</a> 
<?php
}
?>