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

print _("The Sahana request management system is a central online repository " .
        "where all relief organizations, relief works, government agents and " .
        "camps can effectively match requests of aid and supplies to pledges " .
        "of support. It effectively looks like an online aid trading system " .
        "tracking request to fulfillment."
        );
?>

</p>

<br></br>
    <div><h3><b><em><?= (_("Features Include:")) ?></em></b></h3></div>
<br></br>

<ul>
    <li>
    <?php print _("Basic meta data on the request and pledges such as " .
                  "the category, the units, contact details and the status") ?>
    </li>
    <li>
    <?php print _("Customizable category of aid") ?>
    </li>
    <li>
    <?php print _("Filtered search of aid pledges and requests") ?>
    </li>
    <li>
    <?php print _("Ability to track partial fulfillment of the request") ?>
    </li>
</ul>


 <strong>Description of Actions:</strong><br/>
    <ul>
        <li><a href="index.php?mod=rms&act=req_new"><b><?= _('Make Request'); ?> </b></a><br/><?= _('Make a request to obtain items for relief operations'); ?></li>
        <li><a href="index.php?mod=rms&act=req_ls"><b><?= _('List Requests'); ?> </b> </a><br/><?= _('List all the requests done through the system'); ?></li>
        <li><a href="index.php?mod=rms&act=req_sch"><b><?= _('Search Request'); ?></b></a><br/><?= _('Search for requests'); ?></li>
        <li><a href="index.php?mod=rms&act=plg_new"><b><?= _('New Pledge'); ?></b></a><br/><?= _('Donate items through the  system'); ?>
        <li><a href="index.php?mod=rms&act=plg_ls"><b><?= _('List Pledges'); ?></b></a><br/><?= _('List all the donations done through the system'); ?></li>
        <li><a href="index.php?mod=rms&act=plg_sch"><b><?= _('Search Pledges'); ?></b></a><br/><?= _('Search for pledges'); ?></li>
        <li><a href="index.php?mod=rms&act=mng_ff"><b><?= _('Fullfill Requests'); ?></b></a><br/><?= _('Match requests and pledges in a disaster'); ?></li>
        
</ul>



<br/>
</div>
