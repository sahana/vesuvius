<?php
/**
 * This is the admin file for the Sahana module. This file is optional
 * if it exists a section is created in the administation section of Sahana
 * to configure this module
 * IMPORTANT: The <action> part of the functions in shn_<mod name>_<action>
 * should be prefixed with "adm_" for this module to be reflected in admin
 * <Description of file> 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   <put your name here>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage skel
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * the default page for the the skeleton admin page 
 * 
 * @access public
 * @return void
 */
function shn_skel_adm_default()
{
?>
    <p><b><?php echo _t("Welcome to skeleton admin page")?> </b></p>
<?php
}
