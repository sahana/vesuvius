<?php
/**
 * Report configuration
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author       Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage rs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

function shn_rs_config_main_form()
{
    global $global;
    $db=$global["db"];
    $query="select option_code from field_options where field_name='opt_rs_freq'";
    $res=$db->Execute($query);
    $current_freq=$res->fields["option_code"];

    shn_form_fopen('config_main_form_submit',null,null);
    $extra_opts['value'] = $current_freq;
    shn_form_fsopen(_('Current Frequency '));
    shn_form_text('','cur_freq','size="5" readonly=true',$extra_opts);
    shn_form_fsclose();

    shn_form_fsopen(_('Set Report update Frequency '));
    shn_form_text('New Frequency in minites : ','new_freq','size="5"');
    shn_form_fsclose();

    shn_form_submit(_("Save"));
    shn_form_fclose();
}

function shn_rs_config_main_form_submit_result()
{
    global $global;
    $db=$global["db"];
    $new_freq = trim($_POST['new_freq']);

    $query="update field_options set option_code='$new_freq' where field_name='opt_rs_freq' ";
    $res=$db->Execute($query); 

    if($res == true)
    {
    ?>
            <div id="result_msg">
               <?php print "New Frequency ".$new_freq."  was successfully saved";?>
            </div>
    <?php
    }
    else
    {
    ?>
            <div id="result_msg">
               <?php print "Update <b>Failed...</b>.There was an <b>Error</b> found in updating New frequency.";?>
            </div>
    <?php
    }
shn_rs_config_main_form();
}
?>