<?php
/** 
* 
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

/**
 * Show GIS Map with Wiki info
 */
function show_wiki_map()
{
	global $global;
	include $global['approot']."/mod/gis/gis_fns.inc";
	shn_gis_map();
}

function add_wiki_detail()
{
	
}
?>
