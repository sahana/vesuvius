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
	
	
	global $global;
	array_push($global['xajax_functions'],'pr_add_address_to_list');
	array_push($global['xajax_functions'],'remove_address_row');
	
	function pr_add_address_to_list($data){
	   	global $global;
	   	
	   	$address_type = $data['opt_address_type'];
	   	$opt_address_type = get_option_desc('opt_address_type', $address_type);

	   	if(!in_array($address_type, $data['addresses'])){
		   	$html .= "<tr id='tr_$address_type'>";
		   	$html .= "<td align='center'><a href='#' onclick=\"pr_remove_field('tr_$address_type');\"><img src='theme/default/img/tbl_delete.png' alt='delete' /></a></td>";
		   	$html .= "<td>" . $opt_address_type . "<input type='hidden' name='addresses[]' value='$address_type' /></td>";
		   	$html .= "<td>" . $data['address'] . "<input type='hidden' name='addresses[$address_type][address]' value='{$data['address']}'/></td>";
		   	$html .= "<td>" . $data['postal_code'] . "<input type='hidden' name='addresses[$address_type][postal_code]' value='{$data['postal_code']}'/></td>";
		   	$html .= "<td>" . get_number_list($data['telephone_array'], $address_type, 'telephone') . "</td>";
		   	$html .= "<td>" . get_number_list($data['mobile_array'], $address_type, 'mobile') . "</td>";
		   	$html .= "<td>" . get_number_list($data['email_array'], $address_type, 'email') . "</td>";
		   	$html .= "<td>" . get_number_list($data['web_url_array'], $address_type, 'web') . "</td>";		   	
		   	$html .= "</tr>";	   	

			$global['xajax_res']->addAssign('address_table','style.display','');
		    $global['xajax_res']->addAppend('address_list','innerHTML',$html);
		    $global['xajax_res']->addAssign('address_list_msg','innerHTML','');
	   	}
	   	else{
	   		$html = "<span style='color:red'>" ._t('Addree type ' .strtolower($opt_address_type).' is alread selected') . "</span>";
	   		$global['xajax_res']->addAssign('address_list_msg','innerHTML',$html);
	   	}
	    
	    return $global['xajax_res']->getXML();
	}
		
	function get_option_desc($field_name, $option_code)
	{
	 	global $global;
      	$db = $global['db'];
      		
    	$sql = "SELECT option_description 
      			FROM field_options 
      			WHERE field_name = '$field_name' AND option_code = '$option_code'";
      		
    	$res = $db->GetOne($sql);

		return $res;      		
	 }
	 
	 function get_number_list($numbers, $address_type , $number_type)
	 {	 	
	 	$html = "";	 	
	 	if(is_array($numbers) && count($numbers)){
	 		$html .= "<ul class='table_ol_view'>";
	 		foreach($numbers as $number){
	 			$html .= "<li>" . $number . "<input type='hidden' name='addresses[$address_type][$number_type][]' value='$number'/></li>";
	 		}
	 		$html .= "</ul>";
	 	}	 	
	 	
	 	return $html;
	 }
