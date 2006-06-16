<?php
/**
* The Sahana 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

function _shn_html_print_alert($alert)
{
?>
<div class="alert"> <!-- TODO: change style -->
    <strong><?php print _("Alert") . " : $alert"?></strong>
</div>
<?php
}

function _shn_html_print_message($msg,$br = false)
{
    $br_str = '';
    if ($br == true)
        $br_str = '<br />';
?>
    <div class="message">
    <strong><?php print $msg?></strong>
    <?php print $br_str ?>
    </div>
<?php
}

?>
