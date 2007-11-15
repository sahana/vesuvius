
<?php
/* $Id: home.inc,v 1.19 2007-11-15 12:28:11 isurunishan Exp $ */

/** 
 * Home Page of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
?>
<div id="home">
<h2><?= _('Missing Person Registry'); ?></h2>
<?php
global $global;
if(file_exists($global['approot'].'/www/tmp/mprfound.png')){
?>
<img src="tmp/mprfound.png"/>
<img src="tmp/mprfound.png"/>
<?php
}
?>
<p>
<?= _('The Missing person registry is an online bulletin board of missing and found people.
It captures information about the people missing and found, as well as information of the person seeking them, increasing the chances
of people finding each other. For example if two members of the a family unit is
looking for the head of the family, we can use this data at least to connect those two
family members.'); ?>

<?= _('Features include:');?></p>
<ul>
    <li><?= _('Meta data around the individual such identity numbers, visual
appearance, last seen location, status, etc'); ?></li>
    <li><?= _('Sounds-like name search (using metafore and soundex
algorithms)'); ?></li>
    <li><?= _('Uploading of a persons picture'); ?></li>
    <li><?= _('Grouping by family unit or other groups types'); ?></li>
</ul>
</div>
<?php
/*
 *  Recent Found People people Top 6
 */
 global $global;
	require ($global['approot'] . 'mod/mpr/mpr_lib.inc');
?>
<div id="home_recent">
<h1><?= _('Latest updates on Found People'); ?></h1>
<?php
$limit = 6;
$type = "found";
$rs=shn_mpr_home_show_mpr($type,$limit,0);
shn_mpr_search_show_verticle($_SESSION['result']);

?>
<?php


/*
 *  Recent Missing People Top 6
 */
?>
<h1><?= _('Latest updates on Missing People'); ?></h1>
<?php
$limit = 6;
$type = "missing";
shn_mpr_home_show_mpr($type,$limit,0);
shn_mpr_search_show_verticle($_SESSION['result']);
?>
</div>
<?php
/**
 * Shows the latest updates on missing and found perople
 * 
 * @param string $type 
 * @param int $limit 
 * @access public
 * @return void
 */
 
 
 

?>

