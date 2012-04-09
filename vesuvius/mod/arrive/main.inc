<?php
/**
 * @name         Arrival Rate
 * @version      3
 * @package      arrive
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0213
 */


include_once ($global['approot'].'/inc/handler_db.inc');
include_once ($global['approot'].'/inc/lib_xajax.inc');
include_once ($global['approot'].'/mod/arrive/xajax.inc');

shn_xajax_registerFunction('arrive_append_log');
shn_xajax_registerFunction('arrive_fetch_last_updated');
shn_xajax_registerFunction('arrive_show_list');
shn_xajax_registerFunction('arrive_add_spacer');


function shn_arrive_default() {

	global $global;

	shn_xajax_printJavascript();
	echo "
		<div id=\"rezLog\" class=\"logArea\"></div>
		<div id=\"rezControl\" class=\"controlArea\">&nbsp;</div>
		<div id=\"rezMain\" class=\"mainArea\"></div>
		<script>".file_get_contents($global['approot']."/mod/arrive/arrive.js")."</script>
	";
}


