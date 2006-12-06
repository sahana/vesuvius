<?php
/* $Id: conf_admin.inc,v 1.6 2006-12-06 17:56:22 chamindra Exp $ */
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
        add_confirmation($_POST['conf_key']." has been updated with value ".
                $_POST['conf_value']);
    }

    ksort($conf);
    shn_config_database_fetch(&$dconf,'all');
?>
    <div id="result">
    <table>
    <thead>
<?php
    shn_form_table_row(array('Config Variable','Current Value','Modified Value','Action'));
?> 
    </thead>
<?php

    foreach ($conf as $key => $value) {

        $edit ='<a href="?mod=admin&act=conf_var&key='.$key.'">(edit)</a>';

        // truncate the strings if they are too long
        $str_value = shn_html_bool2str(shn_html_truncate($value,25));
        $str_dconf = shn_html_bool2str(shn_html_truncate($dconf[$key],25));

        shn_form_table_row(array($key,$str_value,$str_dconf,$edit));
    }
?>
    </table>
    </div>
<?php
}

function shn_html_bool2str($boolean) 
{
    if (is_bool($boolean)) {
        $boolean = ($boolean == true)? "true":"false";
    }
    return $boolean;

}

function shn_html_truncate($string, $max_length) 
{
    if (is_string($string) && strlen($string) > $max_length) {
        $string = substr($string, 0, ($max_length/2)-1 ).
               "<a href=\"#\" title=\"$string\">...</a>".
                substr($string, -($max_length/2)+1);
    }
    return $string; 
}


function shn_admin_conf_var() 
{
    global $conf;

    shn_form_fopen('conf_list');
    shn_form_fsopen(_('Change Config Value'));
    shn_form_hidden(array('conf_key'=>$_GET['key']));

    if ( is_bool($conf[$_GET['key']]) ) {
        shn_form_select(array('true'=>'true','false'=>'false'),$_GET['key'],'conf_value',null,
                        array('value'=> shn_html_bool2str($conf[$_GET['key']])));
    } else {
        shn_form_text($_GET['key'],'conf_value','size="60"',array('value'=>$conf[$_GET['key']]));
    }

    shn_form_fsclose();
    shn_form_submit(_('Change value'));
    shn_form_fclose();
}

?>
