<?php
/**
 * modRez admin console
 *
 * @package	module
 * @subpackage	rez
 * @author 	Greg Miernicki
 * @copyright	www.nlm.nih.gov
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

include_once ($global['approot'].'/mod/rez/xajax.inc');
shn_xajax_registerFunction('rez_append_log');
shn_xajax_registerFunction('rez_prepend_log');
shn_xajax_registerFunction('rez_show_message');
shn_xajax_registerFunction('rez_show_pages');
shn_xajax_registerFunction('rez_show_help');
shn_xajax_registerFunction('rez_perform_edit');
shn_xajax_registerFunction('rez_perform_delete');
shn_xajax_registerFunction('rez_perform_insert');
shn_xajax_registerFunction('rez_perform_save');
shn_xajax_registerFunction('rez_perform_move_up');
shn_xajax_registerFunction('rez_perform_move_down');
shn_xajax_registerFunction('rez_perform_change_visibility');

/**
 * setup admin GUI for modRez and then let xajax do all the work
 * @access public
 * @return void
 */
function shn_rez_adm_default() {
	shn_xajax_printJavascript();
	?><h2><?php echo _t('Resources ~ Page Administration'); ?></h2>
	<div id="rezLog" class="logArea">Loading Pages...<br></div>
	<div id="rezControl" class="controlArea">&nbsp;</div>
	<div id="rezMain" class="mainArea">&nbsp;</div>
	<script>
		rez_show_message("Loading Pages...");
		setTimeout("rez_show_pages();", 1500);
	</script>
	<script type="text/javascript" src="res/nicedit/nicEdit.js"></script><?
}