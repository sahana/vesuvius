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

/**
 * This is the configuration form which is used to set the frequency of generating reports and charts.
 * @access public
 * @return void
 */
function shn_rs_config_main_form()
{
    print "<h1>"._("Configuration")."</h1>";
    ?>
    <p><?= _('Here you can configure the frequency of updating module reports and charts.'); ?></p> 
    <?php

    global $global;
    $db=$global["db"];
    $extra_opts['value'] = '';

    shn_form_fopen('config_main_form_submit',null,null);
    $query="select option_code from field_options where field_name='opt_rs_rep_freq'";
    $res=$db->Execute($query);
    $current_freq=$res->fields["option_code"];
    $extra_opts['value'] = $current_freq;
    shn_form_fsopen(_('Set Report update Frequency'));
    shn_form_label(_('Current Frequency in minutes'),$current_freq);
    shn_form_text(_('Enter New Frequency in minutes'),'rep_new_freq','size="5"',$extra_opts);
    shn_form_fsclose();

    $query="select option_code from field_options where field_name='opt_rs_cht_freq'";
    $res=$db->Execute($query);
    $current_freq=$res->fields["option_code"];
    $extra_opts['value'] = $current_freq;
    shn_form_fsopen(_('Set Chart update Frequency'));
    shn_form_label(_('Current Frequency in minutes '),$current_freq);
    shn_form_text('New Frequency in minutes','chart_new_freq','size="5"',$extra_opts);
    shn_form_fsclose();

    shn_form_submit(_("Save"));
    shn_form_fclose();
}

/**
 * This function processes the POST values that are passed from the shn_rs_config_main_form() in config.inc
 * @access public
 * @return void
 */
function shn_rs_config_main_form_submit_result()
{
    global $global;
    $db=$global["db"];
    $new_rep_freq = trim($_POST['rep_new_freq']);
    $new_cht_freq = trim($_POST['chart_new_freq']);

    $query="select option_code from field_options where field_name='opt_rs_rep_freq'";
    $res=$db->Execute($query);
    $current_rep_freq=$res->fields["option_code"];

    $query="select option_code from field_options where field_name='opt_rs_cht_freq'";
    $res=$db->Execute($query);
    $current_cht_freq=$res->fields["option_code"];

    $new_rep_freq= (trim($_POST['rep_new_freq']) == '') ? $current_rep_freq : trim($_POST['rep_new_freq']);
    $new_cht_freq= (trim($_POST['chart_new_freq']) == '') ? $current_cht_freq : trim($_POST['chart_new_freq']);

    if(ereg("^[0-9]*$",$new_rep_freq))
    {
        $query1="update field_options set option_code='$new_rep_freq' where field_name='opt_rs_rep_freq' ";
        $res1=$db->Execute($query1);
        if($res1 == true)
	    {
            add_confirmation(_("Report creation Frequency of ").$new_rep_freq._("  was successfully saved"));
    	}
    	else
    	{
	        add_error(_("Update Failed... There an error occured while updating new frequency of chart creation."));
	    }
    }
    else
    {
	    add_error(_("You entered value which is not a valid digit. Please enter valid number for report creation frequency."));
    }


    if(ereg("^[0-9]*$",$new_cht_freq))
    {
        $query2="update field_options set option_code='$new_cht_freq' where field_name='opt_rs_cht_freq' ";
        $res2=$db->Execute($query2);
        if($res2 == true)
    	{
	        add_confirmation(_("Chart creation Frequency of ").$new_cht_freq._("  was successfully saved"));
	    }
	    else
    	{
	        add_error(_("Update Failed... There was an Error found in updating new frequency of chart creation."));
	    }
    }
    else
    {
	    add_error(_("You entered value which is not a valid digit. Please enter valid number for chart creation frequency."));
    }

}
?>