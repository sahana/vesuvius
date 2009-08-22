<?php
/*
 *
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana - http://sahana.sourceforge.net
 * @author     Ravith Botejue <ravithb@yahoo.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 *
 */

    global $global,$conf;
    
    if(version_compare("5",phpversion(),"<=")){
        // PHP 5 support
        include_once $global['approot']."3rd/browsercaps/Browscap_php5.php";
    }else{
        // PHP 4 support
        include_once $global['approot']."3rd/browsercaps/Browscap_php4.php";
    }
    
    /*
     * This stores the browser caps object in the $global variable under the key 'bcaps'
     */
    $bcaps = new Browscap($global['approot']."www/tmp/bcaps_cache");
    
    // Enable / Disable auto update according to the admin setting.
    if($conf['bcaps_auto_update']==true){
        $bcaps->doAutoUpdate = true;
    }else{
        $bcaps->doAutoUpdate = false;
    }
    $global['bcaps'] = $bcaps;
    
