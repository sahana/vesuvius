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
    <p><?php echo _t('Maximum Depth')." - "._t("enable you to specify the default depth value for the catalog system item selection interface. "); ?></p>
    <p><?php echo _t('Number of records for a page')." - "._t('enable you to specify the number of records that should be shown in a page in the view and edit section'); ?></p>
    <br></br>
    <?php
}


function shn_cs_sub_menu()
{
    ?>
    <div id="submenu_v">
    <a href="index.php?mod=cs&act=adm_cs_maxdepth"><?php echo _t("Maximum Depth"); ?></a> 
    <a href="index.php?mod=cs&act=adm_cs_page_records"><?php echo _t("Number of records for a page"); ?></a>
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
    
    shn_form_fsopen(_t("Current Value of Maximum Depth"));
    shn_form_label(_t('Current Maximum Depth :'),$current_depth);
    shn_form_fsclose();

    shn_form_fsopen(_t("Select the New value of Maximum Depth"));
    shn_form_select($options,'','max_depth',$select_opts,array('req'=>true));
    shn_form_fsclose();
    shn_form_submit(_t("Save"));
    shn_form_fclose();
}


function shn_cs_adm_max_depth_form_submit()
{
    global $global;
    $db = $global['db'];
    $depth = $_POST['max_depth'];

    if ($_POST['max_depth']==null OR strlen(trim($_POST['max_depth']))==0){
        
        add_error('Maximum Depth field should not empty, please select the value for Maximum Depth field');
    }else{
        
        $query = "UPDATE field_options SET option_code =? WHERE field_name = 'opt_cs_depth' ";
        $res = $db->Execute($query,array($depth)); 
        
        add_confirmation(_t('Maximum Depth was successfully Updated to :'. $depth));
    }
    
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
    shn_form_fsopen(_t("Default number of records per page in view and edit"));
        
    shn_form_label(_t('current value :'),$current_depth);
    
    shn_form_text(_t("Value   : "),'default_page_recs','size="10"',array('req'=>true));
    shn_form_fsclose();
    shn_form_submit(_t("Save"));
    shn_form_fclose();
}

function shn_cs_adm_page_record_submit()
{
    global $global;
    $db = $global['db'];
    $default_page_recs = $_POST['default_page_recs'];
    
    if ($_POST['default_page_recs']==null OR strlen(trim($_POST['default_page_recs']))==0){
        
        add_error('value field should not empty, please fill the value field');
    }else{
        
        if(preg_match('/^\d+$/',$_POST['default_page_recs'])==0){
            
            add_error('please enter positive intiger');
        }else{
            
            $query = "UPDATE field_options SET option_code =? WHERE field_name = 'opt_cs_page_record' ";
            $res = $db->Execute($query,array($default_page_recs)); 
            
            add_confirmation(_t('Default number of records was successfully Updated'));
        }
        
    }

    shn_cs_adm_cs_page_records();
}

