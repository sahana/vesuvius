<?php
/* $Id: conf_admin.inc,v 1.1 2006-07-27 21:48:31 chamindra Exp $ */
/**
 *
 * Sahana HTML form library
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage admin
 * @author     Chamindra de Silva (chamindra@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once($global['approot'].'/inc/lib_config.inc');
include_once($global['approot'].'/inc/lib_form.inc');

function shn_admin_conf_list() 
{
    global $conf;

    ksort($conf);
    shn_config_database_fetch(&$dconf,'all');
?>
    <div id="result">
    <table>
    <thead>
<?php
    shn_form_table_row(array('Config Variable','Action',
                            'Database Value','Current Value'));
?> 
    </thead>
<?php

    foreach ($conf as $key => $value) {

        $str_edit ='<a href="?mod=admin&act=conf_var&key='.$key.'">(edit)</a>';
        shn_form_table_row(array($key,$str_edit,$dconf[$key],$value));
    }
?>
    </table>
    </div>
<?php
}
?>
