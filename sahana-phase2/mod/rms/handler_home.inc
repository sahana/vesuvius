<?php
/**
* The Sahana Resquest Management System
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

/**
 * Check for module dependancies.
 */
require_once 'handler_dep_check.inc';

?>

<div id="home">
<?php

//print the default headder
_shn_rms_print_hedder();

?>
<p>
<?php 

print _t("Sahana Request Management System is a central online repository where all relief organizations, relief workers, government agents and camp sites for displaced personnels can coordinate the supply of the aids with their demand. It allows users to allocate the available resources to fulfill the demands effectively and efficiently.");
?>

</p>

<br></br>
    <div><h3><b><em><?= (_t("Features Include:")) ?></em></b></h3></div>
<br></br>

<ul>
    <li>
    <?php print _t("Basic information on the requests and donations, such as category, the units, contact details and the status.") ?>
    </li>
    <li>
    <?php print _t("Customizable category of aid") ?>
    </li>
    <li>
    <?php print _t("Filtered search of aid pledges and requests") ?>
    </li>
    <li>
    <?php print _t("Ability to track partial fulfillment of the request") ?>
    </li>
</ul>


 <strong><?php print _t("Description of Actions:"); ?></strong><br/>
    <ul>
        <li><a href="index.php?mod=rms&act=req_new"><b><?= _t('Make Request'); ?> </b></a><br/><?= _t('Make a request to obtain items for relief operations'); ?></li>
        <li><a href="index.php?mod=rms&act=req_ls"><b><?= _t('List Requests'); ?> </b> </a><br/><?= _t('List all the requests done through the system'); ?></li>
        <li><a href="index.php?mod=rms&act=req_sch"><b><?= _t('Search Request'); ?></b></a><br/><?= _t('Search for requests'); ?></li>
        <li><a href="index.php?mod=rms&act=plg_new"><b><?= _t('New Pledge'); ?></b></a><br/><?= _t('Donate items through the  system'); ?>
        <li><a href="index.php?mod=rms&act=plg_ls"><b><?= _t('List Pledges'); ?></b></a><br/><?= _t('List all the donations done through the system'); ?></li>
        <li><a href="index.php?mod=rms&act=plg_sch"><b><?= _t('Search Pledges'); ?></b></a><br/><?= _t('Search for pledges'); ?></li>
        <li><a href="index.php?mod=rms&act=mng_ff"><b><?= _t('Fullfill Requests'); ?></b></a><br/><?= _t('Match requests and pledges in a disaster'); ?></li>
        
</ul>
<br/>
<div align=center><strong><?php echo _t('Status of requests') ?></strong> </div>
<div align=center>
<?  echo "<div class='message information' align='left' style='width: 765px; margin-left: 20px;'>";?>
<strong><?echo _t("Important:")."<br/>";?></strong><?
    echo _t("If new request has been added, It may take few minutes to update the pie chart.");
    echo "</div>";  ?>
</div>
<?php
	  shn_chart_display("shn_rms_request_status_chart");
	  
?>
</div>
<?php
    global $global;
    require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_add_feed('new_pledges',_t('New Pledges'));
    shn_rss_add_feed('new_requests',_t('New Requests'));
?>
</div>
