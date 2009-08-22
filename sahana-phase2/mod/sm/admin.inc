<?php

/**
 * Administration of the Situation Awareness module 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Fran Boon <fboon@oxfam.org.uk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage sm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once ($global['approot'] . '/inc/lib_form.inc');
include_once ($global['approot'] . '/inc/lib_validate.inc');


/* {{{ Sub Menus */
/**
 * shn_sm_adminmenu 
 * 
 * @access public
 * @return void
 */
function shn_sm_adminmenu() {
	global $global;
	$module = $global['module'];

	// Create the module menu
	shn_adm_menuopen(_t("Situation Awareness"));
	shn_adm_menuitem("adm_gen", _t("General Configuration"));
	shn_adm_menuclose();

}
/* }}} */

/* {{{ Default */
/**
 * shn_sm_adm_default 
 * 
 * @access public
 * @return void
 */
function shn_sm_adm_default() 
{
    shn_sm_adminmenu();
    ?> <br></br> 
    <p><b><?php echo _("Welcome to the Situation Awareness admin page");?> </b></p>
    <p><?php echo _("Please use the navigation menu above to configure each field.");?> </p>
<?php

}
/* }}} */


