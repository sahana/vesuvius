<?php

/**
 *
 * This is the validation library. A vital component of the framework.
 * It is hoped that the module writers add or change functions here rather 
 * than writing with in the module. 
 * 
 * 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    moduleAPI
 * @subpackage validation
 * @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 * @todo       password validation
 * @todo       username validation
 */

include_once $global['approot']."/inc/lib_errors.inc";

/**
 * Test if a field is between min and  max length 
 * 
 * @param mixed $field 
 * @param int $minlength 
 * @param int $maxlength 
 * @access public
 * @return bool
 */
function shn_valid_len_range($field, $minlength, $maxlength)
{
   if ((strlen($field) > $minlength) && (strlen($field) < $maxlength))
   {
      return true;
   }
   return false;
}

 
/**
 * zipcode validator 
 * 
 * @param mixed $country 
 * @param mixed $zipcode 
 * @access public
 * @return bool
 */
function shn_valid_zipcode($country, $zipcode)
{
  switch ($country)
  {
    case "Austria":
    case "Australia":
    case "Belgium":
    case "Denmark":
    case "Norway":
    case "Portugal":
    case "Switzerland":
     if (!ereg("^[0-9]{4}$", $zipcode))
      {
        // print "The postcode/zipcode must be 4 digits in length";
         return false;
      }
      break;
    case "Finland":
    case "France":
    case "Germany":
    case "Italy":
    case "Spain":
    case "USA":
      if (!ereg("^[0-9]{5}$", $zipcode))
      {
         print _t("The postcode/zipcode must be 5 digits in length");
         return false;
       }
       break;
    case "Greece":
      if (!ereg("^[0-9]{3}[ ][0-9]{2}$", $zipcode))
      {
         print _t("The postcode must have 3 digits, a space, and then 2 digits");
         return false;
      }
      break;
    case "Netherlands":
      if (!ereg("^[0-9]{4}[ ][A-Z]{2}$", $zipcode))
      {
         print _t("The postcode must have 4 digits, a space, and then 2 letters");
         return false;
      }
      break;
    case "Poland":
      if (!ereg("^[0-9]{2}-[0-9]{3}$", $zipcode))
      {
         print _t("The postcode must have 2 digits, a dash, and then 3 digits");
         return false;
      }
      break;
    case "Sweden":
      if (!ereg("^[0-9]{3}[ ][0-9]{2}$", $zipcode))
      {
         print _t("The postcode must have 3 digits, a space, and then 2 digits");
         return false;
      }
      break;
    case "United Kingdom":
      if (!ereg("^(([A-Z][0-9]{1,2})|([A-Z]{2}[0-9]{1,2})|" .
                "([A-Z]{2}[0-9][A-Z])|([A-Z][0-9][A-Z])|" .
                "([A-Z]{3}))[ ][0-9][A-Z]{2}$", $zipcode))
      {
         print _t("The postcode must begin with a string of the format
                A9, A99, AA9, AA99, AA9A, A9A, or AAA,
                and then be followed by a space and a string
                of the form 9AA.
                A is any letter and 9 is any number.");
        return false;
      }
      break;
    default:
      // No validation
  }
  return true;
}

/**
 * Check the validity of a phone number 
 * 
 * @param mixed $field 
 * @access public
 * @return bool
 */
function shn_valid_phone($field)
{
   $validPhoneExpr = "^([0-9]{2,3}[ ]?)?[0-9]{4}[ ]?[0-9]{4}$";

   if (!ereg($validPhoneExpr,$field))
   {
         print _t("The ").$field._t(" field must be 8 digits in length, with an optional 2 or 3 digit area code");
      return false;
   }
   return true;
}

/**
 * Check the validity of an email address
 * 
 * @param mixed $field 
 * @param bool $required 
 * @access public
 * @return bool
 */

function shn_valid_email($field,$required=false)
{
   if((!$required) && $field==NULL){
       return true;
    }
   // Check syntax
   $validEmailExpr =  "^[0-9a-z~!#$%&_-]([.]?[0-9a-z~!#$%&_-])*" .
                      "@[0-9a-z~!#$%&_-]([.]?[0-9a-z~!#$%&_-])*$";

   if (!eregi($validEmailExpr, $field))
   {
      return false;
   }
/*
   // linux only version to check the existance of the host
   if (function_exists("getmxrr") && 
       function_exists("gethostbyname"))
   {
     // Extract the domain of the email address
     $maildomain = 
        substr(strstr($field, '@'), 1);

     if (!(getmxrr($maildomain, $temp) || 
           gethostbyname($maildomain) != $maildomain))
     {
       return false;
     }
   }
*/
   return true;
}

/**
 * Check the validity of a date of birth
 * 
 * @param mixed $date
 * @param bool $check_null. whether to check for null
 * @param string $pattern 
 * @access public
 * @return bool
 */

function shn_valid_dob($date,$check_null=false,$pattern='/^\d{4}-\d{2}-\d{2}$/',$des='Date')
{
	$string=explode("-",$date);	
	$num=mktime(0,0,0,$string[1],$string[2],$string[0]);

	if (!shn_valid_date($date,$check_null,$pattern,$des)){
		return false;
	}
    elseif( $date != '0000-00-00')
    {    
		$s=mktime(0,0,0,date(m),date(d),date(Y));
		if($num > $s){
			add_error(_t('Date of birth should be less than or equal to current date'));		
			return false;
		}
		else{
			return true;
		}
    }	
	else{
		return true;
	}
}

/**
 * Check the validity of a date 
 * 
 * @param mixed $date
 * @param bool $check_null. whether to check for null
 * @param string $pattern 
 * @access public
 * @return bool
 */
function shn_valid_date($date,$check_null=false,$pattern='/^\d{4}-\d{2}-\d{2}$/',$des='Date')
{    
    if (shn_is_null($date)){
        if ($check_null){
            add_error($des._t(" is a required field, Please enter a value."));
            return false;
        }else 
            return true;
    }
    else {
            if(preg_match($pattern,$date))
                return true;
            else{
	            add_error($des._t(" field should be valid (yyyy-mm-dd)"));
                return false;
            }
    }
}
/**
 * checks if the argument is a number 
 * 
 * @param mixed $str 
 * @param string $pattern 
 * @access public
 * @return bool
 */
function shn_valid_number($str,$pattern='/^\d+$/')
{
    if(preg_match($pattern,$str))
        return true;
    else
        return false;
}

/**
 * checks for null or 0 of the argumnet
 * 
 * @param mixed $field 
 * @access public
 * @return bool
 */
function shn_is_null($field)
{
    if ((null==$field)or (is_null($field))){
        return true;
    }else {
        return false;
    }
}

/**
 * Checks whether the value exists in the field options table 
 * 
 * @param mixed $opt_field 
 * @param mixed $opt_value 
 * @access public
 * @return bool
 */
function shn_is_opt_field($opt_field,$opt_value)
{
    global $global;
    $q="SELECT * FROM field_options WHERE option_code='$opt_value' and field_name='$opt_field'";
   $result = $global['db']->Execute($q);
    if(!$result->EOF)
        return true;
    else
        return false;
}
/**
 * Tests if the argument is a location in the database 
 * 
 * @param mixed $field 
 * @access public
 * @return bool
 */
function shn_is_location($field)
{
    global $global;
    $result = $global['db']->GetOne("SELECT * FROM location WHERE location_id LIKE '$field'");
    if($result)
        return true;
    else
        return false;
}
/**
 * Trims(cleans) the arguments
 * 
 * @param mixed $field 
 * @access public
 * @return void
 */
function shn_clean($field){
    return trim($field);
}

/**
 * Validates( null, length)  a field. 
 * 
 * @param mixed $field 
 * @param mixed $desc 
 * @param mixed $max_len 
 * @param mixed $check_null (should we check for null) 
 * @access public
 * @return bool
 */
function shn_validate_field($field,$desc,$max_len,$check_null=false){
    if ($check_null And shn_is_null($field)){
        add_error($desc._t(" is a required field, please enter a value."));
        return false;
    }else {
        if (strlen(shn_clean($field))>$max_len){
            add_error(_t("You exceeded the field size for ").$desc._t(".Field size is ").$max_len);
            return false;
        }else {
            return true;
        }
    }
}

/**
 * Checks whether the value is valid(null ,length)and whether the value exists in the
 * field options table 
 * 
 * @param mixed $type 
 * @param mixed $field 
 * @param mixed $desc 
 * @param mixed $max_len 
 * @param mixed $array (whether you have sent an array to validate)
 * @access public
 * @return bool
 */
function shn_validate_opt_field($type,$field,$desc,$max_len,$array=false){
    if (shn_validate_field($field,$desc,$max_len,true)){
        $i=0;
        if(!$array){
             if (($type!="select") and (shn_is_opt_field($type,shn_clean($field)))){
             	return true;
             }else{
             	add_error(_t("You have to select a value from the list box"));
             	return false;
             }
                
        }else {
            $i=0;
            while ($i<count($field)){
                if(($type=="select") or (!shn_is_opt_field($type,shn_clean($field[$i])))){
                	echo $type;
                    add_error(_t("You have to select a value from the list box"));
                    return false;
                }
                $i=$i+1;
            }
            return true;
        }
    }else {
        return false;
    }
}

/**
 * Validates a user name 
 * 
 * @param mixed $field 
 * @access public
 * @return bool
 */
function shn_validate_user_name($field){
    if (shn_validate_field($field,"User Name",100,true)){
        if (shn_is_user($field)){
            add_error(_t("User already exists"));
            return false;
        }else {
            return true;
        }
    }else {
        return false;
    }
}

/**
 * Checks whether the argument meets the password criteria(e.g. minimum length is 8) 
 * 
 * @param mixed $field 
 * @access public
 * @return bool
 */
function shn_validate_password($user=null,$pwd){
	global $global;
	require_once ($global['approot'].'inc/lib_security/lib_acl.inc');

/*
	$chars_to_escape='$\*%#@!~';
	$user=addcslashes($user, $chars_to_escape);
	
    if($user!=null){
    	
    		if (preg_match("/$user/", $pwd)) {

    			add_error("User Name cannot be part of the password");
    			shn_acl_log_msg("Password Change error:User Name cannot be part of the password");

    			add_error(_t("User name cannot be part of the password"));
    			shn_acl_log_msg("Password change error: User Name cannot be part of the password");

    			return false;
			}
    }


	$pwd=addcslashes($pwd, $chars_to_escape);
    if (preg_match("/^.*(?=.{8,})(?=.*[a-zA-Z])(?=.*[^a-zA-Z]).*$/", $pwd)) {
    	return true;
	} else {
		add_error(PWDPOLICY);

		shn_acl_log_msg("Password Change error: password does not comply with the policy");

		shn_acl_log_msg("Password change error: password does not comply with the policy");

    	return false;
	} 
 */
	$result = shn_check_password_matches_policy($pwd,$user);
	if($result!==true){
		add_error(shn_get_password_policy_message($result));
		shn_acl_log_msg("Password Change error: password does not comply with the policy");
		return false;
	}else{
		return true;
	}
}

/**
 * Validates a Longitude/Easting (X coordinate) 
 * 
 * @param mixed $field 
 * @access public
 * @return bool
 */
function shn_valid_x_coordinate($field){
   $LONG_ERROR="Longitude/Easting should be between -180 & 180";
   if (!preg_match ("/^([0-9.,-]+)$/", $field))
   {
      add_error($LONG_ERROR);
      return false;
   }
   
   if (($field > -180) && ($field < 180))
   {
      return true;
   }
   add_error($LONG_ERROR);
   return false;
}

/**
 * Validates a Latitude/Northing (Y coordinate) 
 * 
 * @param mixed $field 
 * @access public
 * @return bool
 */
function shn_valid_y_coordinate($field){
   $LAT_ERROR="Latitude/Northing should be between -90 & 90";
   if (!preg_match ("/^([0-9.,-]+)$/", $field))
   {
      add_error($LAT_ERROR);
      return false;
   }
   
   if (($field > -90) && ($field < 90))
   {
      return true;
   }
   add_error($LAT_ERROR);
   return false;
}


