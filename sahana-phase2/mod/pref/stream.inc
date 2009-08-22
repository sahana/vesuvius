<?php
/* $Id */

/**
 * Main Controller of the User Preferences
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage pref 
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */


include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";

/*
 * include all xxx_main.inc
 */
$d = dir($global['approot'].'mod/pref/');
while (false !== ($f = $d->read())) {
    if (preg_match('/.*_main.inc$/',$f)){
        if (file_exists($global['approot'].'mod/pref/'.$f)){
            include ($global['approot'].'mod/pref/'.$f);
        }
    }
}
        
/**
 * This function defines the menu list.
 * @access public
 * @return void
 */
function shn_pref_mainmenu() 
{
    global $global;
    $module = $global['module'];

    // Create the module menu
    shn_mod_menuopen(_t("User Preferences"));

    shn_mod_menuitem("default",_t("Home"));
    
    /* get the sub menus */
    $d = dir($global['approot'].'mod/pref/');
    while (false !== ($f = $d->read())) {
        if (preg_match('/.*_menu.inc$/',$f)){
            if (file_exists($global['approot'].'mod/pref/'.$f)){
                include ($global['approot'].'mod/pref/'.$f);
            }
        }
    }


    shn_mod_menuclose();
   
    // include the main menu
    include $global['approot']."/inc/handler_mainmenu.inc";
} 

/**
 * 
 * This function displays the home page of the User Preferences
 *
 * @access public
 * @return void
 */
function shn_pref_default()
{
?>
<div id="home">
<h2><?php echo _t("Welcome to User Preferences");?></h2>
<p><?php echo _t("User Preferences Module will allow you to set any preferred configuration. ")."<br />".
_t("Which will help you to customize Sahana to your preference.")."<br />".
_t("Following Preferences can be set")."</p>";

echo "<ul>";

echo "<li><b>"._t("Multiple Incident Management")."</b></li>";
echo "</ul>";

?>
</div>
<?php
}

/**
 * This function cleans the POST values
 * @todo Put this somewhere else, i.e. form handling
 * @param mixed $local_post 
 * @access public
 * @return void
 */
function shn_tools_clean_post(&$local_post)
{
    //trim them all
    foreach($_POST as $k => $v){
        $v = trim($v);
        if($v != '')
            $local_post[$k] = $v;
    }
}


