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
?>
<?php show_rms_heading(); ?>
<h3>Request Management</h3>
<br/>
<?php
if (is_req_open($req_id))
{
?>    
    <div id="">
    <?php print _("Change Request Status") ?> 
    <a href="index.php?mod=rms&amp;act=cstat_req&amp;req_id=<?php print $req_id ?>&amp;stat=closed">
    &lt;<?php print _("Close") ?>&gt;
    </a> | &lt;<?php print _("Open") ?>&gt;
    </div>
<?php
}
else
{
?>
    <div id="">
    <?php print _("Change Request Status") ?> &lt;<?php print _("Close") ?>&gt; | 
    <a href="index.php?mod=rms&amp;act=cstat_req&amp;req_id=<?php print $req_id ?>&amp;stat=open">
    &lt;<?php print _("Open") ?>&gt;
    </a>
    </div>
<?php
}
?> 