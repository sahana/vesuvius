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
require_once('lib_rms.inc');

$user_id = $global['person_id'];
$org_id = $global['org_id'];

$req_count = count_req();
$user_req_count = count_user_req($user_id);
$org_req_count = count_user_req($org_id);
$org_reqff_count = count_user_reqff($user_id);
$user_oreq_count = count_user_reqstat($user_id,'open');
$user_creq_count = count_user_reqstat($user_id,'closed');
?>

<?php show_rms_heading(); ?>
<h4>The Request Management System tracks all requests and helps match pledges for support, aid and supplies to fullfilment</h4>
<br/>
<?php _shn_rms_search_home(); ?>
<div id="home_resent">
<br/><hr/><br/>
<div id="result">
<h3><?php print _("User Information")?></h3>
<hr/>
<?php print _("User Name" . " : ")?><br/>
<?php print _("User ID" . " : " . $user_id)?><br/>
<?php print _("Total Requests" . " : " . $user_req_count)?> (<a href="index.php?mod=rms&act=vw_req&user=user">View</a>)<br/>
<?php print _("Open Requests" . " : " . $user_oreq_count)?> (<a href="index.php?mod=rms&act=vw_req&user=user&stat=open">View</a>)<br/>
<?php print _("Closed Requests" . " : " . $user_creq_count)?> (<a href="index.php?mod=rms&act=vw_req&user=user&stat=closed">View</a>)<br/>
<hr/>
<strong><?php print _("Fulfilled (fully/partially) Requests" . " : " . $org_reqff_count)?></strong><br/>
</div>
<br/>
<div id="result">
<h3><?php print _("Organization Information")?></h3>
<hr/>
<?php print _("Org. Name" . " : ")?><br/>
<?php print _("Org. ID" . " : " . $org_id)?><br/>
<br/>
<strong><?php print _("Total Requests" . " : " . $org_req_count)?> (<a href="index.php?mod=rms&act=vw_req&user=user">View</a>)</strong> 
<br/>
</div>
<br/>
<div id="result">
<h3><?php print _("Full Statistics")?></h3>
<br/>
<hr/>
<strong><?php print _("Total Number of requests = ") . $req_count?> (<a href="index.php?mod=rms&act=vw_req&user=all">View</a>) </strong>
</div>
</div>