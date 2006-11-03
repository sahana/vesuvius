<?php
/**
 * This is the main file for the Sahana module. Once the module is selected in the 
 * post all actions are passed to this file for processing.
 * <Description of file> 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Chamindra de Silva (http://www.linux.lk/~chamindra) 
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage skel
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * Place all your dependant libraries below. Given are some typical ones
 * required for the module
 */
include_once $global['approot'].'/inc/lib_menu.inc';
include_once $global['approot'].'/inc/lib_form.inc';
include_once $global['approot'].'/inc/lib_validate.inc';
include_once $global['approot'].'/inc/lib_errors.inc';



/**
 * This function allows you to override the mainmenu. This is often done 
 * to include the modules own menu
 * 
 * @access public
 * @return void
 */
function shn_skel_mainmenu() 
{
    global $global;
    $module = $global['module'];
    
    // Create the module menu
    shn_mod_menuopen(_('Skeleton Module'));

    shn_mod_menuitem('default',_('Home'));
    shn_sub_mod_menuopen(_('Sub Menu'));
    shn_sub_mod_menuitem('mio',_('Menu Item 1'));
    shn_sub_mod_menuitem('mit',_('Menu Item 2'));
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_('Sub Menu 2'));
    shn_mod_menuitem('report',_('Report'));
    shn_sub_mod_menuclose();

    shn_mod_menuclose();
   
    // include the main menu so that the user can navigate outside the module
    include $global['approot'].'/inc/handler_mainmenu.inc';

} 

/** 
 * Other sections you can override
 */
// function shn_skel_header() {}
// function shn_skel_footer() {}
// function shn_skel_html_head() {}

/**
 * This function displays the default page of the module when it is selected
 * This function has to exist! 
 *
 * @access public
 * @return void
 */
function shn_skel_default()
{

    global $global;

?>
<div id="home">
<h2><?= _('Skeleton Module'); ?></h2>
<p><?= _('This is a description of the module that we typically
give on the first page with it\' features listed below')?>
<?= _('Features include:');?></p>
<ul>
    <li><?=$global['shn_rs_sample_nicename']?></li>
    <li><?= _('Feature 2')?></li>
</ul>
</div>

<?php
}

/**
 * This is the call from menu item one, action mio
 *
 * @access public
 * @return void
 */
function shn_skel_mio()
{
    echo '<p>'._('You called menu item one action').'</p>';
    add_confirmation('This is a sample confirmation message after a form submit');
}

/**
 * This is the call from menu item two, action mit
 *
 * @access public
 * @return void
 */
function shn_skel_mit()
{
    echo '<p>'._('You called menu item two action').'</p>';
}

/**
 * This is the call for the action rpt 
 *
 * @access public
 * @return void
 */
function shn_skel_report()
{
    echo '<p>'._('You called the report action').'</p>';
}
