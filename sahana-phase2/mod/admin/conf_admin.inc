<?php
/* $Id: conf_admin.inc,v 1.2 2006-07-27 23:46:23 chamindra Exp $ */
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

    if (isset($_POST['conf_key'])) {

        shn_config_database_update($_POST['conf_key'],$_POST['conf_value']);
        echo '<p>'.$_POST['conf_key']." has been updated with value ".
                $_POST['conf_value'].'</p>';
    }

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


function shn_admin_conf_var() 
{
    global $conf;

    shn_form_fopen('conf_list');
    shn_form_fsopen(_('Change Config Value'));
    shn_form_hidden(array('conf_key'=>$_GET['key']));
    shn_form_text($_GET['key'],'conf_value',null,array('value'=>$conf[$_GET['key']]));


    shn_form_fsclose();
    shn_form_submit(_('Change value'));
    shn_form_fclose();
}

?>
