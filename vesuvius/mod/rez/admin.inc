<?
/**
 * @name         Resources
 * @version      1.4
 * @package      rez
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0801
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
		window.rezPageSaved = false;

		function checkSaved() {
			if(!window.rezPageSaved) {
				var answer = confirm('Are you sure you want to close this document? It has not been saved.');
				if(answer) {
					rez_append_log('Closing editor...<br>');
					area2.removeInstance('pageContent');
					setTimeout('rez_show_pages();', 500);
					window.rezPageSaved = false;
				}
			} else {
					rez_append_log('Closing editor...<br>');
					area2.removeInstance('pageContent');
					setTimeout('rez_show_pages();', 500);
					window.rezPageSaved = false;
			}
		}
	</script>
	<script type="text/javascript" src="res/nicedit/nicEdit.js"></script><?
}