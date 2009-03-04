<?php
/**
 * DSM lib_dsm_validation.inc
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @author     G.W.R. Sandaruwan <sandaruwan[at]opensource[dot]lk> <rekasandaruwan[at]gmail[dot]com
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage dsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function dsm_validation_get_rule_information($rule,$indx){
	switch($rule){
		case 'equals':
			$key = ($indx+1).'-'.$rule;
			return sprintf(_t('Add the equal value as a parameter with the key <b>"%s"</b> under parameters below'),$key);
			break;
		case 'not_empty':
			//$key = ($indx+1).'-'.$rule;
			//return sprintf(_t('Add the not equal value as a parameter with the key <b>"%s"</b> under parameters below'),$key);
			break;
		case 'less':
			$key = ($indx+1).'-'.$rule;
			return sprintf(_t('Add the less than value as a parameter with the key <b>"%s"</b> under parameters below'),$key);
			break;
		case 'greater':
			$key = ($indx+1).'-'.$rule;
			return sprintf(_t('Add the grater than value as a parameter with the key <b>"%s"</b> under parameters below'),$key);
			break;
		case 'less_equal':
			$key = ($indx+1).'-'.$rule;
			return sprintf(_t('Add the less than or equal value as a parameter with the key <b>"%s"</b> under parameters below'),$key);
			break;
		case 'greater_equal':
			$key = ($indx+1).'-'.$rule;
			return sprintf(_t('Add the greater than or equal value as a parameter with the key <b>"%s"</b> under parameters below'),$key);
			break;
		case 'not':
			$key = ($indx+1).'-'.$rule;
			return sprintf(_t('NOT is used to negate an existing rule. Add the rule number as a parameter with the key <b>"%s"</b> under parameters below'),$key);
			break;
		case 'and':
			$key1 = ($indx+1).'-'.$rule.'-L';
			$key2 = ($indx+1).'-'.$rule.'-R';
			return sprintf(_t('AND is used to combile two existing rules, where the response is valid only when both rules are satisfied. <br/>Add the rule numbers you need to AND as a parameters with the keys <b>"%s"</b> and <b>"%s"</b> under parameters below'),$key1,$key2);
			break;
		case 'or':
			$key1 = ($indx+1).'-'.$rule.'-L';
			$key2 = ($indx+1).'-'.$rule.'-R';
			return sprintf(_t('OR is used to combile two existing rules, where the response is valid when either of the rules are satisfied. <br/>Add the rule numbers you need to OR as a parameters with the keys <b>"%s"</b> and <b>"%s"</b> under parameters below'),$key1,$key2);
			break;
	}
}

function dsm_validation_get_rules(){
	return array('equals'=>_t('Equals'),
              'not_empty'=>_t('Not Empty'),
              'less'=>_t('Less Than'),
              'greater'=>_t('Greater Than'),
              'less_equal'=>_t('Less than or Equal'),
              'greater_equal'=>_t('Greater than or Equal'),
              'not' => _t('NOT'),
              'and' => _t('AND'),
              'or' => _t('OR')
	);

}

function dsm_validation_get_rule_text($rule){
	$tmp = dsm_validation_get_rules();
	return $tmp[$rule];
}

function dsm_validation_check_params($rule,$indx,$all_params){
	$no_errors = true;

	switch($rule){
		case 'equals':
		case 'not_equal':
		case 'less':
		case 'greater':
		case 'less_equal':
		case 'greater_equal':
		case 'not':
			$key = ($indx+1).'-'.$rule;
			if(isset($all_params[$key])==false){
				add_error(sprintf(_t('The validation rule no %1$d. "%2$s" requires a parameter value under key <b>"%3$s"</b>'),($indx+1),dsm_validation_get_rule_text($rule),$key));
				$no_errors = false;
			}
			break;

		case 'and':
		case 'or':
			$key1 = ($indx+1).'-'.$rule.'-L';
			$key2 = ($indx+1).'-'.$rule.'-R';
			if(isset($all_params[$key1])==false){
				add_error(sprintf(_t('The validation rule no %1$d. "%2$s" requires a parameter value under key <b>"%3$s"</b>'),($indx+1),dsm_validation_get_rule_text($rule),$key1));
				$no_errors = false;
			}
			if(isset($all_params[$key2])==false){
				add_error(sprintf(_t('The validation rule no %1$d. "%2$s" requires a parameter value under key <b>"%3$s"</b>'),($indx+1),dsm_validation_get_rule_text($rule),$key2));
				$no_errors = false;
			}
			break;
	}
	return $no_errors;
}

function dsm_validation_check_validity($dis_id){
	global $global;
	$db = $global['db'];
	//$db->debug = true;
	$query1 = "SELECT * FROM dsm_fields df JOIN dsm_definitions dd ON dd.field_id=df.field_id WHERE dd.dis_id=?";
	$res1 = $global['db']->Execute($query1,array($dis_id));
	$errors = false;
	while($row1 = $res1->FetchRow()){
		$field_id = $row1['field_id'];
		$value = $_POST[$row1['name']];
		$query2 = "SELECT fp.param_key,fp.param from dsm_field_params fp WHERE fp.field_id=?";
		$res2=$db->Execute($query2,array($field_id));
		$params = $res2->GetAssoc();

		$query3 = "SELECT fv.*,df.text FROM dsm_field_validation fv JOIN dsm_fields df ON df.field_id=fv.field_id WHERE df.field_id = ? ORDER BY fv.rule_order";
		$res3 = $db->Execute($query3,array($field_id));

		// allready checked rules stack
		// used in recursive check to avoid confusing messages
		$checked_rules = array();

		while($res3 && $row3=$res3->FetchRow()){
			//echo $row3['validation_id']."<br/>";
			//echo "before:";
			//var_dump($checked_rules);echo "<br/>";
			$msg = _check_validity($row3['rule'],$params,$row3['rule_order'],$row3['text'],$value,$field_id,$row3['validation_id'],&$checked_rules);
			if($msg!=null){
				add_error($msg);
			}
			$errors |= ($msg==null)?false:true;

		}
	}
	return $errors;
}

/**
 * Internal function to do the validation of values
 *
 * @param String $rule The rule as saved in the validation table
 * @param Array  $params All params related to the rule
 * @param Integer  $rule_indx The index of the rule in the rule set. (zero based)
 * @param String $text The text of the field
 * @param String $value The field value
 */
function _check_validity($rule,$params,$rule_indx,$text,$value,$field_id,$rule_id,&$checked_rules){
	static $recursion_counter;
	$recursion_counter++;// increment on recursive call // decrement on return

	if($recursion_counter>20){
		return _t("Validation rule too complex !");
	}
	//echo $field_id."-".$rule." - > rec: ".$recursion_counter."<br/>";
	//var_dump($recursion_counter);


	//var_dump(array_search($rule_id,$checked_rules));

	if(array_search($rule_id,$checked_rules)===FALSE){
		//echo $rule_id."<br/>";
		array_push(&$checked_rules,$rule_id);
		//var_dump($checked_rules);echo "<br/>";
		switch($rule){
			case 'equals':
				$key = ($rule_indx+1).'-'.$rule;
				if(isset($params) && isset($params[$key])){
					if($params[$key]==$value){
						return null;
					}else{
						return sprintf(_t('The value "%1$s" should be equal to "%2$s" for field "%3$s"'),$value,$params[$key],$text);
					}
				}
				break;
			case 'not_empty':
				if(isset($value)==false || strlen(trim($value))==0){
					return sprintf(_t('The value should not be empty for field %2$s.'),$value,$text);
				}
				break;
			case 'less':
				$key = ($rule_indx+1).'-'.$rule;
				if(isset($params) && isset($params[$key])){
					if($params[$key]>$value){
						return null;
					}else{
						return sprintf(_t('The value "%1$s" should be less than "%2$s" for field "%3$s"'),$value,$params[$key],$text);
					}
				}
				break;
			case 'greater':
				$key = ($rule_indx+1).'-'.$rule;
				if(isset($params) && isset($params[$key])){
					if($params[$key]<$value){
						return null;
					}else{
						return sprintf(_t('The value "%1$s" should be greater than "%2$s" for field "%3$s"'),$value,$params[$key],$text);
					}
				}
				break;
			case 'less_equal':
				$key = ($rule_indx+1).'-'.$rule;
				if(isset($params) && isset($params[$key])){
					if($params[$key]>=$value){
						return null;
					}else{
						return sprintf(_t('The value "%1$s" should be less than or equal to "%2$s" for field "%3$s"'),$value,$params[$key],$text);
					}
				}
				break;
			case 'greater_equal':
				$key = ($rule_indx+1).'-'.$rule;
				if(isset($params) && isset($params[$key])){
					if($params[$key]<=$value){
						return null;
					}else{
						return sprintf(_t('The value "%1$s" should be greater than or equal to "%2$s" for field "%3$s"'),$value,$params[$key],$text);
					}
				}
				break;

				/*
				 * The following conditions need recursive processing.
				 */
			case 'not':
				$key = ($rule_indx+1).'-'.$rule;
				if(isset($params) && isset($params[$key])){
					$target_rule_indx = $params[$key]-1;
					//var_dump($params[$key]);
					// fetch the rule
					$target_rule = _get_rule($field_id,$target_rule_indx);
					$target_rule_params = _get_rule_params($field_id,$target_rule['rule'],$target_rule_indx);

					//var_dump($target_rule);echo "<br/>";
					//var_dump($target_rule_params);

					$target_rule_result = _check_validity($target_rule['rule'],$target_rule_params,$target_rule_indx,$text,$value,$field_id,$target_rule['validation_id'],&$checked_rules);
					$recursion_counter--;
					//var_dump($target_rule_result);echo "<br/>";
					//var_dump($checked_rules);
					// return the inverse
					if($target_rule_result!=null){
						return null;
					}else{
						return sprintf(_t('The value "%1$s" is not valid for field "%2$s"'),$value,$text);
					}
				}
				break;
			case 'and':
				$key1 = ($rule_indx+1).'-'.$rule.'-L';
				$key2 = ($rule_indx+1).'-'.$rule.'-R';
				if(isset($params) && isset($params[$key])){
					$target_rule1_indx = $params[$key1]-1;
					$target_rule2_indx = $params[$key2]-1;

					// fetch the rule 1
					$target_rule1 = _get_rule($field_id,$target_rule1_indx);
					$target_rule1_params = _get_rule_params($field_id,$target_rule1['rule'],$target_rule1_indx);
					$target_rule1_result = _check_validity($target_rule1['rule'],$target_rule1_params,$target_rule1_indx,$text,$value,$field_id,$target_rule1['validation_id'],&$checked_rules);
					$recursion_counter--;

					// fetch the rule 2
					$target_rule2 = _get_rule($field_id,$target_rule2_indx);
					$target_rule2_params = _get_rule_params($field_id,$target_rule2['rule'],$target_rule2_indx);
					$target_rule2_result = _check_validity($target_rule2['rule'],$target_rule2_params,$target_rule2_indx,$text,$value,$field_id,$target_rule2['validation_id'],&$checked_rules);
					$recursion_counter--;

					//var_dump($target_rule_result);echo "<br/>";
					//var_dump($checked_rules);
					// return the and of the two results
					if($target_rule1_result==null && $target_rule2_result==null){
						return null;
					}else{
						return sprintf(_t('The value "%1$s" is not valid for field "%2$s"'),$value,$text);
					}

				}

				break;
			case 'or':
				$key1 = ($rule_indx+1).'-'.$rule.'-L';
				$key2 = ($rule_indx+1).'-'.$rule.'-R';
				if(isset($params) && isset($params[$key])){
					$target_rule1_indx = $params[$key1]-1;
					$target_rule2_indx = $params[$key2]-1;

					// fetch the rule 1
					$target_rule1 = _get_rule($field_id,$target_rule1_indx);
					$target_rule1_params = _get_rule_params($field_id,$target_rule1['rule'],$target_rule1_indx);
					$target_rule1_result = _check_validity($target_rule1['rule'],$target_rule1_params,$target_rule1_indx,$text,$value,$field_id,$target_rule1['validation_id'],&$checked_rules);
					$recursion_counter--;

					// fetch the rule 2
					$target_rule2 = _get_rule($field_id,$target_rule2_indx);
					$target_rule2_params = _get_rule_params($field_id,$target_rule2['rule'],$target_rule2_indx);
					$target_rule2_result = _check_validity($target_rule2['rule'],$target_rule2_params,$target_rule2_indx,$text,$value,$field_id,$target_rule2['validation_id'],&$checked_rules);
					$recursion_counter--;

					//var_dump($target_rule_result);echo "<br/>";
					// return the and of the two results
					if($target_rule1_result==null || $target_rule2_result==null){
						return null;
					}else{
						return sprintf(_t('The value "%1$s" is not valid for field "%2$s"'),$value,$text);
					}

				}
				break;
		}
	}
}

function _get_rule($field_id,$indx){
	global $global;
	$query = "SELECT * FROM dsm_field_validation WHERE field_id=? AND rule_order=?";
	$res = $global['db']->Execute($query,array($field_id,$indx));
	$rows = $res->GetArray();
	return $rows[0];
}

function _get_rule_params($field_id,$rule,$indx){
	global $global;
	//$global['db']->debug =true;
	$query = "SELECT fp.param_key,fp.param from dsm_field_params fp WHERE fp.field_id=? AND fp.param_key LIKE ?";
	$res = $global['db']->Execute($query,array($field_id,($indx+1).'-'.$rule.'%'));
	$rows = $res->GetAssoc();
	//var_dump($rows);
	return $rows;

}