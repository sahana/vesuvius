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

	function _shn_pr_add_person($p_uuid = null)
	{	
		if($_POST['p_uuid'] != null){
			$p_uuid = $_POST['p_uuid'];
		}
		
		$person = New Person();	
		$person->get_person($p_uuid);
		
		if(isset($_POST['save_person'])){
			$res = $person->save_person();
			
			if($res){
				add_confirmation(_t('Successfully saved'));
			}
			else{
				add_error(_t('Error in saving data'));
			}
		}
		else if(isset($_POST['update_person'])){
			$res = $person->update_person();		

			if($res){
				add_confirmation(_t('Successfully updated'));				
			}
			else{
				add_error(_t('Error in updating data'));
			}
		}
		
		echo "<h2>" . _t('Person Information') . "</h2>";

		shn_form_fopen('add_person','pr',array('tab'=>'float','name'=>'person_form','enctype' => 'enctype="multipart/form-data"'));			
		
		shn_pr_basic_information(_t('Basic Information'),null,$person);			
		shn_pr_contact_information(null, $person);
		shn_pr_identity_information($person);		
		shn_pr_location(null,$person);
		
		shn_form_drawtab();
		
		if($p_uuid != null){
			shn_form_submit(_t('Update'),'name="update_person"');
		}
		else{
			shn_form_submit(_t('Save'),'name="save_person"');
		}
		shn_form_button(_t('Clear'), 'onclick="form_clear(\'person_form\');"',null);
		shn_form_fclose();
	}

	