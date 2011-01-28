<?php
/**
 * @name         Event Manager
 * @version      1.0
 * @package      em
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0125
 */

include_once ($global['approot'].'/inc/lib_menu.inc');
include_once ($global['approot'].'/inc/lib_errors.inc');
include_once ($global['approot'].'/inc/lib_log.inc');
include_once ($global['approot'].'/inc/handler_db.inc');
include_once ($global['approot'].'/inc/lib_xajax.inc');
include_once ($global['approot'].'/mod/em/xajax.inc');

shn_xajax_registerFunction('em_append_log');
shn_xajax_registerFunction('em_prepend_log');
shn_xajax_registerFunction('em_show_message');
shn_xajax_registerFunction('em_show_events');
shn_xajax_registerFunction('em_perform_edit');
shn_xajax_registerFunction('em_perform_delete');
shn_xajax_registerFunction('em_perform_insert');
shn_xajax_registerFunction('em_perform_save');
shn_xajax_registerFunction('em_perform_help');


function shn_em_default() {
	global $global;
	shn_xajax_printJavascript();
	echo "
		<div id=\"rezLog\" class=\"logArea\">Loading Events...<br><noscript>THIS MODULE REQUIRES THAT YOU ACTIVATE JAVASCRIPT!</noscript></div>
		<div id=\"rezControl\" class=\"controlArea\">&nbsp;</div>
		<div id=\"rezMain\" class=\"mainArea\"></div>
		<script>".file_get_contents($global['approot']."/mod/em/em.js")."</script>
		<script type=\"text/javascript\" src=\"https://maps-api-ssl.google.com/maps/api/js?v=3&client=gme-hhs&sensor=true\"></script>
		<script type=\"text/javascript\" src=\"res/js/jquery-1.4.4.min.js\" ></script>
		<script type=\"text/javascript\" src=\"res/js/jquery-ui-autocomplete.min.js\" ></script>
		<script type=\"text/javascript\" src=\"res/js/jquery-ui-datepicker.min.js\" ></script>
	";
}













