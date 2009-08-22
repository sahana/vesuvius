<?php
	/**
	 *
	 * PHP version 5
	 *
	 * LICENSE: This source file is subject to LGPL license
	 * that is available through the world-wide-web at the following URI:
	 * http://www.gnu.org/copyleft/lesser.html
	 *
	 * @package    Sahana - http://sahana.sourceforge.net
	 * @author     Kethees <sdkethees@gmail.com>
	 * @copyright  Lanka Software Foundation - http://www.opensource.lk
	 */

	function shn_pr_basic_information($tab_header= null,$type=null, $person=null,$group=null)
	{
		shn_form_fsopen($tab_header);		
				
			if($type == 'group' && $group->g_uuid == null){
				shn_form_opt_select('opt_group_type', _t("Group"), null, array('sort'=>'option_code'));
				shn_form_opt_select('opt_relationship_type', _t("Relationship"), null, null);
			}
			else if($type == 'group' && $group->g_uuid != null){
				shn_form_opt_select('opt_relationship_type', _t("Relationship"), null, array('value'=>$_GET['relation_type']));
			}			
		
			shn_form_hidden(array('p_uuid'=>$person->p_uuid));
			shn_form_hidden(array('g_uuid'=>$group->g_uuid));
						
			shn_form_text(_t('First Name'),'first_name','',array('req'=>true,'value'=>$person->first_name));
			shn_form_text(_t('Last Name'),'last_name','',array('req'=>false,'value'=>$person->last_name));
			shn_form_text(_t('Middle Name(s)'),'middle_name','',array('value'=>$person->middle_name));
			shn_form_text(_t('Nick Name(s)'),'nick_name','',array('value'=>$person->nick_name));
			shn_form_opt_select('opt_title', _t("Title"), null, array('value'=>$person->title));
			shn_form_opt_select('opt_gender',_t('Gender'),'',array('value'=>$person->gender));
			shn_form_date(_t('Date of Birth'),'birth_date',array('value'=>$person->birth_date));			
			shn_form_opt_select('opt_age_group',_t('Age Group'),'',array('value'=>$person->age_group));
			shn_form_opt_select('opt_religion',_t('Religion'),'',array('value'=>$person->religion));
			shn_form_opt_select('opt_race',_t('Race'),'',array('value'=>$person->race));
			shn_form_opt_select('opt_marital_status',_t('Martial Status'),'',array('value'=>$person->martial_status));
			shn_form_text(_t('Occupation'),'occupation','',array('value'=>$person->occupation));
			shn_form_textarea(_t('Description'),'description','',array('value'=>$person->description));
			shn_form_upload(_t('Picture'),'picture');
		shn_form_fsclose();
	}
	
	function shn_pr_location($type = null, $person = null) 
	{		
		$location_id = $person->location_id;
		
		shn_form_fsopen(_t("Location Information"));
			if($type == 'group'){
				shn_form_checkbox(_t('As Group'),'as_group',null,null);		
			}
			//echo $location_id;
			shn_location($range,$location_id,null,null);	
		shn_form_fsclose();
	}
?>
	