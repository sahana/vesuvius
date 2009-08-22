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

	function _shn_pr_add_group()
	{
		echo "<h2>" . _t('Group Information') . "</h2>";
		
		$group = New Group();
		$person = New Person();
		
		if($_GET['act_type'] != null){
		switch($_GET['act_type']){
			case 'edit':
				$group->get_group($_GET['g_uuid']);
				
				if($_GET['p_uuid'] != null){
					$person->get_person($_GET['p_uuid']);
				}
				else{
					$person->get_person($group->group_head_id);
				}
				break;
			case 'view':
				echo "view";
				break;
			case 'delete':
				$group->get_group($_GET['g_uuid']);
				break;
		}
		}
		else{
			if($_GET['g_uuid'] != null){
				$group->get_group($_GET['g_uuid']);
				$person->get_person($group->group_head_id);
			}			
		}	

		if(isset($_POST['save_group'])){
		
			if($_POST['g_uuid'] != null){
				$res = $group->save_group_member();
				unset($_POST);	
			}
			else{
				$res = $group->save_group();
				unset($_POST);
			}			
			
			if($res){
				add_confirmation(_t('Successfully saved'));
			}
			else{
				add_error(_t('Error in saving data'));
			}
		}
		else if(isset($_POST['update_group'])){			
			$res = $person->update_person();		
			$group->get_group($_POST['g_uuid']);
			
			if($res){
				add_confirmation(_t('Successfully updated'));				
			}
			else{
				add_error(_t('Error in updating data'));
			}
		}
		
		if($group->g_uuid != null){			
			$group->print_group_member_list();
		}
		
		shn_form_fopen('add_group','pr',array('tab'=>'float','name'=>'group_form','enctype' => 'enctype="multipart/form-data"'));
		shn_pr_basic_information(_t('Group Member Information'),'group',$person,$group);				
		shn_pr_contact_information(null, $person);
		shn_pr_identity_information($person);		
		shn_pr_location('group',$person);
		
		shn_form_drawtab();
		
		if($_GET['g_uuid'] != null){
			shn_form_submit(_t('Update'),'name="update_group"');
		}
		else{
			shn_form_submit(_t('Save'),'name="save_group"');
		}
		shn_form_button(_t('Clear'), 'onclick="form_clear(\'group_form\');"',null);
		shn_form_fclose();
	}

