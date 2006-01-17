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
<div id="home">
<h2><?php print _("Request Managment System")?></h2>
<p><?php print _("The Sahana request management system is a central online repository where all " .
		"relief organizations, relief works, government agents and camps can effectively " .
		"match requests of aid and supplies to pledges of support. It effectively looks like an " .
		"online aid trading system tracking request to fulfillment. Features include:") ?>
</p>
<ul>
    <li><?php print _("Basic meta data on the request and pledges such as the category, the units, contact details and the status") ?></li>
    <li><?php print _("Customizable category of aid") ?></li>
    <li><?php print _("Filtered search of aid pledges and requests") ?></li>
    <li><?php print _("Ability to track partial fulfillment of the request") ?></li>
</ul>
<br/>
</div>

<br/>
<?php _shn_rms_search_home(); ?>
<div id="home_resent">
<br/><hr/><br/>
<div id="result">
<h3><?php print _("User Information")?></h3>
<hr/>
<?php print _("User Name") . " : "?><br/>
<?php print _("User ID") . " : " . $user_id?><br/>
<?php print _("Total Requests") . " : " . $user_req_count?> (<a href="index.php?mod=rms&act=vw_req&user=user"><?php print _("View") ?></a>)<br/>
<?php print _("Open Requests") . " : " . $user_oreq_count?> (<a href="index.php?mod=rms&act=vw_req&user=user&stat=open"><?php print _("View") ?></a>)<br/>
<?php print _("Closed Requests") . " : " . $user_creq_count?> (<a href="index.php?mod=rms&act=vw_req&user=user&stat=closed"><?php print _("View") ?></a>)<br/>
<hr/>
<strong><?php print _("Fulfilled (fully/partially) Requests") . " : " . $org_reqff_count?></strong><br/>
</div>
<br/>
<div id="result">
<h3><?php print _("Organization Information")?></h3>
<hr/>
<?php print _("Org. Name") . " : "?><br/>
<?php print _("Org. ID") . " : " . $org_id?><br/>
<br/>
<strong><?php print _("Total Requests") . " : " . $org_req_count?> (<a href="index.php?mod=rms&act=vw_req&user=user"><?php print _("View") ?></a>)</strong> 
<br/>
</div>
<br/>
<div id="result">
<h3><?php print _("Full Statistics")?></h3>
<br/>
<hr/>
<strong><?php print _("Total Number of requests = ") . $req_count?> (<a href="index.php?mod=rms&act=vw_req&user=all"><?php print _("View") ?></a>) </strong>
</div>
</div>
