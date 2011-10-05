<?
/**
 * @name         Header Handler
 * @version      1.0
 * @package      framework
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */

global $conf;
global $global;

// We will allow themes to use their own header if one is provided ---//
if (file_exists($global['approot']."www/theme/".$conf['theme']."/header.php")) {
	include($global['approot']."www/theme/".$conf['theme']."/header.php");

// Else, we will use the Sahana "Built-In" header ---//
} else { ?>
	<div id="header" class="clearfix">
		<h1><?php echo _t("Sahana FOSS Disaster Management System")?></h1>
	<?
		// show language selection if necessary...
		if(isset($conf['enable_locale']) && $conf['enable_locale'] == true) {
			_shn_lc_lang_list();
		}
	?>
	</div>
	<?php
}


