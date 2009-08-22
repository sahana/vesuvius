<?php

/**
* Functions page of the GPS Module
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package module
* @subpackage gps
* @author     sri <sri@opensource.lk>
* @author     Fran Boon <flavour@partyvibe.com>
* @author     Richard Smith <s0459387@sms.ed.ac.uk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

function shn_gps_default()
{
    global $conf;
?>
<div id="home">
<h2><?php echo $conf['mod_gps_name']?></h2>
<p><?php echo _t("The {$conf['mod_gps_name']} module provides the ability to use Sahana with a GPS.");?><br><br>
<?php echo _('The data is imported/exported via GPX files which can be transferred to/from a GPS device using, e.g. <a href="http://www.gpsbabel.org/" target=_blank>GPS Babel</a>.');?>
</p>

<hr>
    
<strong><?php echo _t('Description of Actions:')?></strong><br/>
    <ul>
        <li><a href="index.php?mod=gps&act=upload_seq"><b><?php echo  _t('Upload Waypoints'); ?></b></a><br/><?php echo  _t('Allow Waypoints from a GPS to be used as Markers in Sahana'); ?></li>
        <li><a href="index.php?mod=gps&act=download_seq"><b><?php echo  _t('Download Waypoints'); ?> </b> </a><br/><?php echo  _t('Allow Markers from Sahana to be used as Waypoints on a GPS'); ?></li>
        <li><a href="index.php?mod=gps&act=dynamic_download"><b><?php echo  _t('Download Route'); ?> </b> </a><br/><?php echo  _t('Allow Markers from Sahana to be used as a Route on a GPS'); ?></li>
    </ul>
</div>
<?php
}


