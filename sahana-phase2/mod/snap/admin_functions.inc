<?php
/**
 * Snapshot ~ Admin Functions
 *
 * @package	module
 * @subpackage	snap
 * @version	1.0
 * @author 	Greg Miernicki
 * @copyright	www.nlm.nih.gov
 * @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

include_once ($global['approot'].'mod/snap/xajax.inc');
shn_xajax_registerFunction('snap_append_log');
shn_xajax_registerFunction('snap_prepend_log');
shn_xajax_registerFunction('snap_dim');
shn_xajax_registerFunction('snap_show_message');
shn_xajax_registerFunction('snap_show_backups');
shn_xajax_registerFunction('snap_perform_backup');
shn_xajax_registerFunction('snap_perform_restore');
shn_xajax_registerFunction('snap_perform_delete');
shn_xajax_registerFunction('snap_perform_rename');

function shn_snap_admin_default() {
	shn_xajax_printJavascript();
	?><h2><?php echo _t('Snapshot ~ Database Backup and Restore Module'); ?></h2>
	<div id="snapshotLog" class="logArea">Finding Snapshots...<br></div>
	<div id="snapshots" class="mainArea">&nbsp;</div>
	<div id="snapshotButton" class="controlArea"><input class="controlButton" id="newSnapshot" type="button" onclick="javascript: e = document.getElementById('newSnapshot'); e.disabled=true; snap_append_log('Creating a new Snapshot...<br>'); snap_dim(); setTimeout('snap_perform_backup();', 1000);" value="Create a new Snapshot"></div>
	<script>
		snap_show_message("Loading...");
		setTimeout("snap_show_backups()", 2000);
	</script><?
}