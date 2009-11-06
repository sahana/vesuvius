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
* @author     Chathra <chathra@opensource.lk>
* @author     Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

global $global;
include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_validate.inc');
include_once($global['approot'].'/inc/lib_errors.inc');


/**
 * shn_cms_reg_victim
 * @param $errors error
 * display Victim form
 */
function shn_cms_reg_victim($errors=false){
  echo '<h2>' . _t('Victim Registration') . '</h2>';
  if($errors)
	display_errors();

  global $global;
  $db=$global['db'];
  
  shn_form_fopen(cadd);
  shn_form_fsopen(_t('Individual Information'));
  shn_form_hidden(array('seq'=>'commit'));
  shn_form_text(_t('Full Name'),'full_name','size="50"',array('req'=>true));
  shn_form_text(_t('Family Name'),'family_name','size="50"');
  shn_form_text(_t('Local Name'),'local_name','size="50"');
  shn_form_text(_t('ID/SSN/Passport'),'id_no','size="50"',array('req'=>true));
  shn_form_opt_select('opt_age_group',_t('Age Group'));
  shn_form_opt_select('opt_status',_t('Person Status'));
  shn_form_opt_select('opt_race',_t('Race'));
  shn_form_opt_select('opt_religion',_t('Religion'));
  shn_form_opt_select('opt_marital_status',_t('Marital Status'));
  shn_form_opt_select('opt_contact_type',_t('Previous Contact  Type'));
  shn_form_textarea(_t('Previous Contact'),'org_name','size="200"');
  shn_form_fsclose();
  shn_form_fsopen(_t('Group/Family'));
  shn_form_text(_t('Group Name/Sirname/Family Name'),'group_name','size="50"');
  shn_form_text(_t('Contact Details'),'contact','size="50"');
  shn_form_text(_t('Number of Members in Group'),'group_no','size="50"');
  shn_form_checkbox(_t('Individual is head of Group/Family'),'is_head');
  shn_form_checkbox(_t('Members of Group/Family are Missing'),'is_missing');
  shn_form_fsclose();
  shn_form_submit(_t('Register'));
  shn_form_fclose();
  
}

function shn_cms_edit_victim()
{
	echo '<h2><center>' . _t('Edit Victim Information') . '</center></h2>';
}       

/**
 * shn_cms_commit_victim
 * commit information to persons tables
 * @todo check whether person exits in tables and handle
 * 
 */
function shn_cms_commit_victim()
{
	global $global;
	$db = $global['db'];
	$commit_person_uuid = '';
	$commit_person_details = '';
}

/**
 * shn_cms_create_puuid
 * @access private
 * @return unique uuid
 * create unique puuid
 */
function _shn_cms_create_puuid()
{
	return mktime().rand(0,1000);
	
}	                                      
?>
