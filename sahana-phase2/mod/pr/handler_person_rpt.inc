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

	function shn_pr_person_information($person)
	{
		echo "<p id='image'>";
		shn_show_thumb_url($person->p_uuid, 'database', 'dvr', 'person_img', false);
		echo "</p>";
		echo "<table id='report' width=40%>";
		echo "<tbody>";
		echo "<tr>";
		echo "<td colspan='2'><strong>" . _t('Basic Information') . "</strong></td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td>" . _t('Full Name') . "</td>" . "<td>" . $person->full_name . "</td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td>" . _t('Middle Name') . "</td>" . "<td>" . $person->middle_name . "</td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td>" . _t('Nick Name') . "</td>" . "<td>" . $person->nick_name . "</td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td>" . _t('Date of birth') . "</td>" . "<td>" . $person->birth_date . "</td>";
		echo "</tr>";		
		echo "<tr>";
		echo "<td>" . _t('Religion') . "</td>" . "<td>" . $person->religion . "</td>";
		echo "</tr>";		
		echo "<tr>";
		echo "<td>" . _t('Race') . "</td>" . "<td>" . $person->race . "</td>";
		echo "</tr>";		
		echo "<tr>";
		echo "<td>" . _t('Gender') . "</td>" . "<td>" . $person->gender . "</td>";
		echo "</tr>";		
		echo "<tr>";
		echo "<td>" . _t('Civil Status') . "</td>" . "<td>" . $person->martial_status . "</td>";
		echo "</tr>";
		echo "<td colspan='2'></td>";
		echo "<tr>";
		echo "<td colspan='2'><strong>" . _t('Contact Information') . "</strong></td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td>" . _t('Address Type') . "</td>" . "<td>" . $person->address_type . "</td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td>" . _t('Address') . "</td>" . "<td>" . $person->address . "</td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td>" . _t('Postal Code') . "</td>" . "<td>" . $person->postal_code . "</td>";
		echo "</tr>";
		echo "<tr>";		
		echo "<td>" . _t('Location') . "</td>" . "<td>" . $person->location_id . "</td>";
		echo "</tr>";
		
		echo "<tr>";		
		echo "<td>" . _t('Telephone') . "</td>";
		echo "<td></td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td colspan='2'></td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td></td>";
		echo "<td>";
		echo "<ul>";
		if(is_array($person->phone_list) && count($person->phone_list) != 0){
			foreach($person->phone_list as $phone){
				echo "<li>" . $phone ."</li>";	
			}				
		} 
		echo "</ul>";
		echo "</td>";
		echo "</tr>";
		
		echo "<tr>";		
		echo "<td>" . _t('Mobile') . "</td>";
		echo "<td></td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td colspan='2'></td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td></td>";
		echo "<td>";
		echo "<ul>";
		if(is_array($person->mobile_list) && count($person->mobile_list) != 0){
			foreach($person->mobile_list as $mobile){
				echo "<li>" . $mobile ."</li>";	
			}				
		} 
		echo "</ul>";
		echo "</td>";
		
		echo "<tr>";		
		echo "<td>" . _t('Email') . "</td>";
		echo "<td></td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td colspan='2'></td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td></td>";
		echo "<td>";
		echo "<ul>";
		if(is_array($person->email_list) && count($person->email_list) != 0){
			foreach($person->email_list as $email){
				echo "<li>" . $email ."</li>";	
			}				
		}
		echo "</ul>";
		echo "</td>";
		echo "</tr>";
		
		echo "<tr>";		
		echo "<td>" . _t('Web') . "</td>";
		echo "<td></td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td colspan='2'></td>";
		echo "</tr>";
		echo "<tr>";
		echo "<td></td>";
		echo "<td>";
		echo "<ul>";
		if(is_array($person->web_list) && count($person->web_list) != 0){
			foreach($person->web_list as $web){
				echo "<li>" . $web ."</li>";	
			}				
		} 
		echo "</ul>";
		echo "</td>";
		echo "</tr>";
		echo "<td colspan='2'></td>";
		echo "<tr>";
		echo "<td colspan='2'><strong>" . _t('Identity Information') . "</strong></td>";
		echo "</tr>";
		
		
		if(is_array($person->identity_list) && count($person->identity_list) != 0){
			foreach($person->identity_list as $identity){
				echo "<tr>";
				echo "<td>" . $identity['option_description'] . "</td>";
				echo "<td>" . $identity['identity_value'] . "</td>";
				echo "</tr>";												
			}
		}
		
		echo "</tbody>";
		echo "</table>";	

		echo "<br />";
		echo "<br />";
	}
	
	function _shn_pr_person_rpt()
	{
		$results = Data::get_person_id_list();
		
		echo "<table width='100%'>";
		echo "<thead>";
		echo "<tr>";
		echo "<td>" ._t('No'). "</td>";
		echo "<td>" ._t('Full Name'). "</td>";
		echo "<td>" ._t('Gender'). "</td>";
		echo "<td>" ._t('DOB'). "</td>";
		echo "<td>" ._t('Religion'). "</td>";
		echo "<td>" ._t('Civil Status'). "</td>";
		echo "<td>" ._t('Address'). "</td>";
		echo "<td>" ._t('Occupation'). "</td>";
		echo "</tr>";
		echo "</thead>";
		echo "<tbody>";
		
		
		$person_count = 1;
		
		if(is_array($results) && count($results) != 0){
			foreach($results as $result){
				$person = New Person();
				$person->get_person_information($result['p_uuid']);
				
				$detail_url = "index.php?mod=pr&amp;act=list_person&amp;act_type=view&amp;p_uuid=" . $result['p_uuid'];				
				
				echo "<tr>";
				echo "<td align='center'>" . $person_count++ . "</td>";
				echo "<td><a href='$detail_url' target='_blank'>" . $person->full_name . "</a></td>";
				echo "<td>" . $person->gender . "</td>";
				echo "<td>" . $person->birth_date . "</td>";
				echo "<td>" . $person->religion . "</td>";
				echo "<td>" . $person->martial_status . "</td>";
				echo "<td>" . $person->address . "</td>";
				echo "<td>" . $person->occupation . "</td>";
				echo "</tr>";
				
				$detail_url = '';
			}
		}
		echo "</tbody>";
		echo "</table>";
	}