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
<strong>Features include:</strong>
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
<br/>
</div>

