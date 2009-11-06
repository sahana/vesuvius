<?php
/**
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Sheran Corera (sheran@opensource.lk) 
 * @copyright  Lanka Software Foundation (http://www.opensource.lk)
 * @package    mod
 * @subpackage hr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
 include_once ('add_to_session.inc');
 
function shn_hr_search()
{
	
	
	_shn_hr_print_header(_t("Quick Search Homeless Family(ies), Damaged House(s), Contractor(s) Or Site(s)"));
	shn_hr_search_hf(true);
	shn_hr_search_damaged_house(true);
	shn_hr_search_contractor(true);
	shn_hr_search_site(true);

}

function shn_hr_search_hf($quick_search=false)
{
    shn_form_fopen("add_to_session",null,array('enctype'=>'enctype="multipart/form-data"'));
    if($quick_search) shn_form_fsopen(_t("Primary Detail Search Of Homeless Famil(ies)"));
    else shn_form_fsopen(_t("Primary Detail Search"));
    shn_form_hidden(array('seq'=>'search_hf'));


    print '<div class="info">';
    print _t("Please use this form to search for information of the Homeless Famil(ies) in the Sahana system");
    print '<br />';
    print '</div>';
    print '<br />'; 


    $extra_opts['value']=$_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_name'];
    $extra_opts['req']=false;
    $extra_opts['help']=(_t("Please specify the Full Name of the Head Of Family"));
    shn_form_text(_t("Head Of Family Full Name"),'search_family_head_name',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['search_hf']['primary_detail_search']['search_family_head_uid'];
    $extra_opts['req']=false; 
    $extra_opts['help']=_t("Please specify the Unique ID of the Head Of Family");
    shn_form_text(_t("Head Of Family Unique ID"),'search_family_head_uid',null,$extra_opts);
    shn_form_fsclose();
    shn_form_submit(_t("Search"));
    shn_form_fclose();
    print '<br />'; 
}

function shn_hr_search_damaged_house($quick_search=false)
{
	shn_form_fopen("add_to_session",null,array('enctype'=>'enctype="multipart/form-data"'));
	if($quick_search) shn_form_fsopen(_t("Primary Detail Search Of Damaged House(s)"));
    else shn_form_fsopen(_t("Primary Detail Search"));
    shn_form_hidden(array('seq'=>'search_damaged_house'));


    print '<div class="info">';
    print _t("Please use this form to search for information of the Damaged House(s) in the Sahana system");
    print '<br />';
    print '</div>';
    print '<br />'; 


    $extra_opts['value']=$_SESSION['hr']['search_hf']['primary_detail_search']['optn_dstrctn_lvl'];
    $extra_opts['req']=false;
    $extra_opts['help']=(_t("Please specify the Destruction Level"));
    shn_form_opt_select('optn_dstrctn_lvl','Destruction Level',null,$extra_opts);
    shn_form_fsclose();
    shn_form_submit(_t("Search"));
    shn_form_fclose();
    print '<br />'; 
}

function shn_hr_search_contractor($quick_search=false,$assign_to_site=false)
{
    shn_form_fopen("add_to_session",null,array('enctype'=>'enctype="multipart/form-data"'));
    if($quick_search) shn_form_fsopen(_t("Primary Detail Search Of Contractor(s)"));
    else shn_form_fsopen(_t("Primary Detail Search"));
    if($assign_to_site) shn_form_hidden(array('seq'=>'assign_to_site'));
    else shn_form_hidden(array('seq'=>'search_contractor'));
    

    print '<div class="info">';
    print _t("Please use this form to search for information of the Contractor(s) in the Sahana system");
    print '<br />';
    print '</div>';
    print '<br />'; 


    $extra_opts['value']=$_SESSION['hr']['search_hf']['primary_detail_search']['optn_contractor_level'];
    $extra_opts['req']=false;
    $extra_opts['help']=(_t("Please specify the Contractor Level"));
    shn_form_opt_select('optn_contractor_level','Contractor Level',null,$extra_opts);
    
    $extra_opts['value']=$_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_name'];
    $extra_opts['req']=false;
    $extra_opts['help']=(_t("Please specify the Contractor Full Name"));
    shn_form_text(_t("Contractor Full Name"),'search_contractor_name',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['search_hf']['primary_detail_search']['search_contractor_uid'];
    $extra_opts['req']=false; 
    $extra_opts['help']=_t("Please specify the Contractor Unique ID");
    shn_form_text(_t("Contractor Unique ID"),'search_contractor_uid',null,$extra_opts);
    
    
    shn_form_fsclose();
    shn_form_submit(_t("Search"));
    shn_form_fclose();
    print '<br />'; 
}

function shn_hr_search_site($quick_search=false,$assign_contractor=false)
{
	shn_form_fopen("add_to_session",null,array('enctype'=>'enctype="multipart/form-data"'));
	if($quick_search) shn_form_fsopen(_t("Primary Detail Search Of Site(s)"));
    else shn_form_fsopen(_t("Primary Detail Search"));
    if($assign_contractor) shn_form_hidden(array('seq'=>'assign_contractor'));
    else shn_form_hidden(array('seq'=>'search_st'));
    

    print '<div class="info">';
    print _t("Please use this form to search for information of the Site(s) in the Sahana system");
    print '<br />';
    print '</div>';
    print '<br />'; 


    $extra_opts['value']=$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_name'];
    $extra_opts['req']=false;
    $extra_opts['help']=(_t("Please specify the Site Name"));
    shn_form_text(_t("Site Name"),'search_site_name',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_uid'];
    $extra_opts['req']=false; 
    $extra_opts['help']=_t("Please specify the Site Unique ID");
    shn_form_text(_t("Site Unique ID"),'search_site_uid',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['search_hf']['primary_detail_search']['optn_site_allocated_organization'];
    $extra_opts['req']=false; 
    $extra_opts['help']=_t("Please specify the Allocated Organization");
    shn_form_opt_select('optn_site_allocated_organization','Site Allocated Organization',null,$extra_opts);

    $extra_opts['value']=$_SESSION['hr']['search_hf']['primary_detail_search']['search_site_main_coordinator_name'];
    $extra_opts['req']=false; 
    $extra_opts['help']=_t("Please specify the Main Coordinator Full Name");
    shn_form_text(_t("Main Coordinator Full Name"),'search_site_main_coordinator_name',null,$extra_opts); 
    
    
    shn_form_fsclose();
    shn_form_submit(_t("Search"));
    shn_form_fclose();
    print '<br />'; 
}
?>
