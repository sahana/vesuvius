
<?php
/**
 * Home Page
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Isuru Samaraweera(isuru@opensource.lk) 
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
 ?>
<div id="home">
<h2><?= _('Disaster Victim Registry'); ?></h2>
<p>
<?php

	print _("The SAHANA Disaster Victim Registry is a central online repository " .
	"where information on all the disaster victims can be stored.Information like name,age" .
	",contact number,id card number,religion,race,displaced location,currentlocation and other " .
	"physical details are captured.Also victims picture and finger print details can be uploaded to" .
	"the system .Also the groupwise information is captured.This module can be used by" .
	" any NGO/organization prior or after to a disaster"  );
?>
</p>

<strong>Features include:</strong>
<ul>
    <li>
    <?php

	print _("Capture Information on Disaster Victimg groups(Toursists,Passengers" .
			",Families,etc..)")
?>
    </li>
    <li>
    <?php print _("Capture Information on each disaster victim") ?>
    </li>
    <li>
    <?php print _("Picture upload and fingure print upload facility")?>
    </li>
    <li>
    <?php print _("Searching for different groups and individuals") ?>
    </li>
    <li>
    <?php print _("Modify Information on groups and individuals") ?>
    </li>
    <li>
    <?php print _("Various Reporting functionalities") ?>
    </li>
    <li>
    <?php print _("Forecasting methods based on statistics") ?>
    </li>
</ul>
<br/>
</div>

<div id="home_recent">
<h1><?= _('Latest updates on Reported Groups'); ?></h1>
<h1><?= _('Latest updates on Reported  Victims'); ?></h1>
</div>
