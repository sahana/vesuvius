<?php
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
 * @author     Chamindra de Silva <chamindra@opensource.lk>
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @author     Greg Miernicki <g@miernicki.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

global $conf;
global $global;

//--- We will allow themes to use their own header if one is provided ---//

if (file_exists($global['approot']."www/theme/".$conf['theme']."/header.php")) { 
	include($global['approot']."www/theme/".$conf['theme']."/header.php");

//--- Else, we will use the Sahana "Built-In" header ---//

} else { ?>
<div id="header" class="clearfix">
	<h1><?php echo _t("Sahana FOSS Disaster Management System")?></h1>
	<?php 
	if(file_exists($global['approot'].'conf/sysconf.inc.php')) {
		shn_db_get_incident_select();
		_shn_lc_lang_list(); 
	}
	?>
</div>
<?php
}


