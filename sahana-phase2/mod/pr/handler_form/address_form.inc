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

	function shn_pr_contact_information($type = null,$person = null)
	{
		shn_xajax_registerFunction('pr_add_address_to_list');		
		
		shn_form_fsopen(_t('Contact Information'));
		
			shn_address_table($person->p_uuid);
		
			if($type == 'group'){
				shn_form_checkbox(_t('Same As Group'),'as_group','',null);	
			}			
			shn_form_hidden(array('a_uuid'=>$person->a_uuid));
			shn_form_opt_select('opt_address_type', _t("Address Type"), null, array('br'=>false,'req'=>true,'value'=>$person->address_type));
			echo "<span id='address_list_msg'></span>";
			echo "<br />";
			echo "<br />";
			shn_form_textarea(_t('Address'),'address','', null);			
			shn_form_text(_t('Postal Code'),'postal_code','', null);
						
			shn_form_text(_t('Telephone'),'telephone','',array('br'=>false));
			shn_form_button(_t('Add'),'onclick="pr_add_number(telephone_list,telephone);"',array('br'=>true));			
			echo "<span class='msg' style='display:none' id='telephone_msg'></span>";			
			
			//var_dump($person->phone_list);
			echo "<ol id='telephone_list'>";
//			if(is_array($person->phone_list) && count($person->phone_list) != 0){
//				foreach($person->phone_list as $phone){
//					echo "<li id='{$phone}'>" . $phone;
//					echo "<input type='hidden' name='telephone_array[]' value='$phone' />";					
//					echo " <a href='#' onclick=\"pr_remove_number('" . $phone . "','" . "telephone_list');\">" . "Remove" . "</a>";
//					echo "</li>";	
//				}				
//			} 
			echo "</ol>";
			
			shn_form_text(_t('Mobile'),'mobile','',array('br'=>false));
			shn_form_button(_t('Add'),'onclick="pr_add_number(mobile_list,mobile);"',array('br'=>true));			
			echo "<span class='msg' style='display:none' id='mobile_msg'></span>";			
			
			echo "<ol id='mobile_list'>";
//			if(is_array($person->mobile_list) && count($person->mobile_list) != 0){
//				foreach($person->mobile_list as $mobile){
//					echo "<li id='$mobile'>" . $mobile;
//					echo "<input type='hidden' name='mobile_array[]' value='$mobile' />";					
//					echo " <a href='#' onclick=\"pr_remove_number('" . $mobile . "','" . "mobile_list');\">" . "Remove" . "</a>";
//					echo "</li>";	
//				}
//			}
			echo "</ol>";

			shn_form_text(_t('Email'),'email','',array('br'=>false));
			shn_form_button(_t('Add'),'onclick="pr_add_number(email_list,email);"',array('br'=>true));			
			echo "<span class='msg' style='display:none' id='email_msg'></span>";			
			
			echo "<ol id='email_list'>";
//			if(is_array($person->email_list) && count($person->email_list) != 0){
//				foreach($person->email_list as $email){
//					echo "<li id='$email'>" . $email;
//					echo "<input type='hidden' name='email_array[]' value='$email' />";					
//					echo " <a href='#' onclick=\"pr_remove_number('" . $email . "','" . "email_list');\">" . "Remove" . "</a>";
//					echo "</li>";	
//				}
//			}			
			echo "</ol>";

			shn_form_text(_t('Web URL'),'web_url','',array('br'=>false));
			shn_form_button(_t('Add'),'onclick="pr_add_number(web_url_list,web_url);"',array('br'=>true));			
			echo "<span class='msg' style='display:none' id='web_url_msg'></span>";
			
			echo "<ol id='web_url_list'>";
//			if(is_array($person->web_list) && count($person->web_list) != 0){
//				foreach($person->web_list as $web){
//					echo "<li id='$web'>" . $web;
//					echo "<input type='hidden' name='web_url_array[]' value='$web' />";					
//					echo " <a href='#' onclick=\"pr_remove_number('" . $web . "','" . "web_url_list');\">" . "Remove" . "</a>";
//					echo "</li>";	
//				}
//			}			
			echo "</ol>";
			
			shn_form_submit(_t('Add address'), 'name="save_address" onclick="pr_add_address_to_list(xajax.getFormValues(this.form.name)); remove_all_list(this.form.name); return false;"');
		shn_form_fsclose();
	}
	
	function shn_address_table($p_uuid)
	{		
		$addresses = Address::get_all_addresses($p_uuid);		
		//var_dump($addresses);
		
	   	//echo "<table width='100%' style='display:none' id='address_table'>";
	   	echo "<table width='100%' id='address_table'>";
	   	echo "<thead>";
	   	echo "<tr>";
	   	echo "<td width='20px'>" . _t('Action') . "</td>";
	   	echo "<td>" . _t('Address Type') . "</td>";
	   	echo "<td>" . _t('Address') . "</td>";
	   	echo "<td>" . _t('Postal Code') . "</td>";
	   	echo "<td>" . _t('Telephone') . "</td>";
	   	echo "<td>" . _t('Mobile') . "</td>";
	   	echo "<td>" . _t('Email') . "</td>";
	   	echo "<td>" . _t('Web') . "</td>";	   	
	   	echo "</tr>";
	   	echo "</thead>";
	   	echo "<tbody valign='top' id='address_list'>";
	   	
	   	if(is_array($addresses) && count($addresses) != 0){
	   		foreach($addresses as $key=>$addresse){
	   			if($key != 'address_type'){
	   				$opt_address_type = Data::get_field_option_description('opt_address_type', $key);
		   			echo "<tr id='tr_$key'>";
		   			echo "<td align='center'><a href='#' onclick=\"pr_remove_field('tr_$key');\"><img src='theme/default/img/tbl_delete.png' alt='delete' /></a></td>";
		   			echo "<td>" . $opt_address_type  . "<input type='hidden' name='addresses[]' value='$key' /></td>";
		   			echo "<td>" . $addresses[$key]['address']  . "<input type='hidden' name='addresses[$key][address]' value='{$addresses[$key]['address']}'/></td>";
		   			echo "<td>" . $addresses[$key]['postal_code']  . "<input type='hidden' name='addresses[$key][postal_code]' value='{$addresses[$key]['postal_code']}'/></td>";
		   			echo "<td>";
		   			if(is_array($addresses[$key]['telephone']) && count($addresses[$key]['telephone'])!=0){
		   				echo "<ul class='table_ol_view'>";
		   				foreach($addresses[$key]['telephone'] as $number){
		   					echo "<li>" . $number . "<input type='hidden' name='addresses[$key][telephone][]' value='$number'/></li>";
		   				}
		   				echo "</ul>";
		   			} 
		   			echo "</td>";
		   			echo "<td>";
		   			if(is_array($addresses[$key]['mobile']) && count($addresses[$key]['mobile'])!=0){
		   				echo "<ul class='table_ol_view'>";
		   				foreach($addresses[$key]['mobile'] as $number){
		   					echo "<li>" . $number . "<input type='hidden' name='addresses[$key][mobile][]' value='$number'/></li>";
		   				}
		   				echo "</ul>";
		   			} 
		   			echo "</td>";
		   			echo "<td>";
		   			if(is_array($addresses[$key]['email']) && count($addresses[$key]['email'])!=0){
		   				echo "<ul class='table_ol_view'>";
		   				foreach($addresses[$key]['email'] as $number){
		   					echo "<li>" . $number . "<input type='hidden' name='addresses[$key][email][]' value='$number'/></li>";
		   				}
		   				echo "</ul>";
		   			} 
		   			echo "</td>";
		   			echo "<td>";
		   			if(is_array($addresses[$key]['web']) && count($addresses[$key]['web'])!=0){
		   				echo "<ul class='table_ol_view'>";
		   				foreach($addresses[$key]['web'] as $number){
		   					echo "<li>" . $number . "<input type='hidden' name='addresses[$key][web][]' value='$number'/></li>";
		   				}
		   				echo "</ul>";
		   			} 
		   			echo "</td>";
		   			echo "</tr>";
	   			}
	   		}
	   	}
	   	
	   	echo "</tbody>";
	   	echo "</table>";
	   	echo "<br/>";
	}	
