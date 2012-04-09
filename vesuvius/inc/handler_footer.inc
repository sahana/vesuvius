<?
/**
 * @name         Footer Handler
 * @version      1.0
 * @package      framework
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */

global $conf;
global $global;

// We will allow themes to use their own footer if one is provided ---//
if (file_exists($global['approot']."www/theme/".$conf['theme']."/footer.php")) {
	include($global['approot']."www/theme/".$conf['theme']."/footer.php");

// Else, we will use the Sahana "Built-In" footer ---//
} else {
	?>
	<div align="center" id="footer">
		<a class="help" target="_blank" href="<?php echo $conf['sahana_url']; ?>" title="<?php echo _t("Sahana Home") ?>"><?php echo _t("Sahana") ?></a> |
		<a class="help" target="_blank" href="<?php echo $conf['wiki_url']; ?>" title="<?php echo _t("Sahana Wiki") ?>"><?php echo _t("Wiki") ?></a> |
		<a class="help" target="_blank" href="<?php echo $conf['chat_url']; ?>" title="<?php echo _t("Chats") ?>"><?php echo _t("Chats") ?></a>  |
		<a class="help" target="_blank" href="?mod=home&act=bug_report" title="<?php echo _t("Report a Bug") ?>"><?php echo _t("Report a Bug") ?></a><?php
		if($conf['shn_xform_enabled']==true) {
			?> | <a class="help" href="javascript:void(0)" onclick="shn_print_init()" title="<?php echo _t("OCR Form") ?>" ><?php echo _t("XForm"); ?></a><?php
		}
		?>
		<br /><br />
		<hr/>
		<a target="_blank" href="http://www.php.net" title="Powered by PHP">
		<img src="res/img/button-php.gif" width="80" height="15" alt="Powered by PHP" border="0" /></a> <a target="_blank" href="http://validator.w3.org/check/referer" title="Valid XHTML 1.0">
		<img src="res/img/button-xhtml.png" width="80" height="15" alt="Valid XHTML 1.0" border="0" /></a> <a target="_blank" href="http://jigsaw.w3.org/css-validator/check/referer" title="Valid CSS">
		<img src="res/img/button-css.png" width="80" height="15" alt="Valid CSS" border="0" /></a>
	</div>
	<?php
}
