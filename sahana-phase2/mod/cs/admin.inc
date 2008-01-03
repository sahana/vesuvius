<?php
/**Admin controller of the catalog system 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sanjeewa Jayasinghe <sditfac@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage cs
*/

include_once($global['approot'] . '/inc/lib_form.inc');


function shn_cs_adm_default()
{
    shn_cs_sub_menu();
    ?>
    <p><?php echo _('Maximum Depth')." - "._("enable you to specify the default depth value for the catalog system item selection interface. "); ?></p>
    <p><?php echo _('Number of records for a page')." - "._('enable you to specify the number of records that should be shown in a page in the view and edit section'); ?></p>
    <br></br>
    <?php
}


function shn_cs_sub_menu()
{
    ?>
    <div id="submenu_v">
    <a href="index.php?mod=cs&act=adm_cs_maxdepth"><?php echo _("Maximum Depth"); ?></a> 
    <a href="index.php?mod=cs&act=adm_cs_page_records"><?php echo _("Number of records for a page"); ?></a>
    </div>
    
    <br>
    <?php
}

function shn_cs_adm_cs_maxdepth()
{

    shn_cs_sub_menu();

    global $global;
    $db = $global['db'];

    $query = "SELECT option_code FROM field_options WHERE field_name = 'opt_cs_depth'";
    $res = $db->Execute($query);
    $current_depth = $res->fields["option_code"];
    
    $options = array('1' => '1','2' => '2','3' => '3','4' => '4','5' => '5','6' => '6','7' => '7','8' => '8','9' => '9','10' => '10','11' => '11','12' => '12','13' => '13','14' => '14','15' => '15');
    shn_form_fopen("adm_max_depth_form_submit");
    shn_form_fsopen(_("Current Value of Maximum Depth"));

    $extra_opts['value'] = $current_depth;
    shn_form_text('','base_unit','size="5" readonly=true',$extra_opts);
    shn_form_fsclose();

    shn_form_fsopen(_("Select the New value of Maximum Depth"));
    shn_form_select($options,'','max_depth',$select_opts,array('req'=>true));
    shn_form_fsclose();
    shn_form_submit(_("Save"));
    shn_form_fclose();
}


function shn_cs_adm_max_depth_form_submit()
{
    global $global;
    $db = $global['db'];
    $depth = trim($_POST['max_depth']);

    $query = "UPDATE field_options SET option_code = '$depth' WHERE field_name = 'opt_cs_depth' ";
    $res = $db->Execute($query); 
    
    ?>
    <div id="result_msg">
    <?php print _("Maximum Depth ") . $depth . _("  was successfully saved"); ?>
    </div>
    <?php
    shn_cs_adm_cs_maxdepth();
}

function shn_cs_adm_cs_page_records()
{
    shn_cs_sub_menu();
    global $global;
    $db = $global['db'];

    $query = "SELECT option_code FROM field_options WHERE field_name = 'opt_cs_page_record'";
    $res = $db->Execute($query);
    $current_depth = $res->fields["option_code"];
    
    shn_form_fopen("adm_page_record_submit");
    shn_form_fsopen(_("Default number of records per page in view and edit"));
    
    $extra_opts['value'] = $current_depth;
    shn_form_text('','current_recs','size="5" readonly=true',$extra_opts);
    
    shn_form_text(_("Value   : "),'default_page_recs','size="50"',$extra_opts);
    shn_form_fsclose();
    shn_form_submit(_("Save"));
    shn_form_fclose();
}

function shn_cs_adm_page_record_submit()
{
    global $global;
    $db = $global['db'];
    $default_page_recs = trim($_POST['default_page_recs']);

    $query = "UPDATE field_options SET option_code = '$default_page_recs' WHERE field_name = 'opt_cs_page_record' ";
    $res = $db->Execute($query); 
    
    ?>
    <div id="result_msg">
    <?php print _("Default number of records ") . $default_page_recs . _("  was successfully saved"); ?>
    </div>
    <?php
    shn_cs_adm_cs_page_records();
}
?>
