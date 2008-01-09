


<?php
global $conf;

/* $Id: handler_footer.inc,v 1.11 2008-01-09 11:05:27 isurunishan Exp $ */
/**
 *
 * Sahana HTML footer
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    moduleAPI
 * @subpackage form
 * @author     Chamindra de Silva (chamindra@opensource.lk>
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
?>
<div align="center" id="footer"><a class="help" target="_blank"
	href="<? echo $conf['sahana_url']; ?>" title="<?php echo _("Sahana Home") ?>"><?php echo _("Sahana") ?></a> | <a
	class="help" target="_blank"
	href="<? echo $conf['wiki_url']; ?>" title="<?php echo _("Sahana Wiki") ?>"><?php _("Wiki") ?></a>
| <a class="help" target="_blank" href="<? echo $conf['forum_url']; ?>"
	title="<?php echo _("Forums") ?>"><?php echo _("Forums") ?></a> | <a class="help" target="_blank"
	href="<? echo $conf['chat_url']; ?>" title="<?php echo _("Chats") ?>"><?php echo _("Chats") ?></a>  
	| <a class="help" target="_blank"
	href="?mod=home&act=bug_report" title="<?php echo _("Report a Bug") ?>"><?php echo _("Report a Bug") ?></a> <br /><br />
	<hr/>
<a target="_blank" href="http://www.php.net" title="Powered by PHP"><img
	src="res/img/button-php.gif" width="80" height="15"
	alt="Powered by PHP" border="0" /></a> <a target="_blank"
	href="http://validator.w3.org/check/referer" title="Valid XHTML 1.0"><img
	src="res/img/button-xhtml.png" width="80" height="15"
	alt="Valid XHTML 1.0" border="0" /></a> <a target="_blank"
	href="http://jigsaw.w3.org/css-validator/check/referer"
	title="Valid CSS"><img src="res/img/button-css.png" width="80"
	height="15" alt="Valid CSS" border="0" /></a></div>

