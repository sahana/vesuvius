<?php
// General-purpose validation functions
include_once $global['approot']."/inc/lib_errors.inc";

// Test if a field is between min and  max length
/**
 * shn_valid_len_range 
 * 
 * @param mixed $field 
 * @param mixed $minlength 
 * @param mixed $maxlength 
 * @access public
 * @return void
 */
function shn_valid_len_range($field, $minlength, $maxlength)
{
   if ((strlen($field) > $minlength) && (strlen($field) < $maxlength))
   {
      return true;
   }
   return false;
}

//zipcode validator 
/**
 * shn_valid_zipcode 
 * 
 * @param mixed $country 
 * @param mixed $zipcode 
 * @access public
 * @return void
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
         print "The postcode/zipcode must be 5 digits in length";
         return false;
       }
       break;
    case "Greece":
      if (!ereg("^[0-9]{3}[ ][0-9]{2}$", $zipcode))
      {
         print "The postcode must have 3 digits, a space,
                and then 2 digits";
         return false;
      }
      break;
    case "Netherlands":
      if (!ereg("^[0-9]{4}[ ][A-Z]{2}$", $zipcode))
      {
         print "The postcode must have 4 digits, a space, and then 2
                letters";
         return false;
      }
      break;
    case "Poland":
      if (!ereg("^[0-9]{2}-[0-9]{3}$", $zipcode))
      {
         print "The postcode must have 2 digits, a dash,
                and then 3 digits";
         return false;
      }
      break;
    case "Sweden":
      if (!ereg("^[0-9]{3}[ ][0-9]{2}$", $zipcode))
      {
         print "The postcode must have 3 digits, a space,
                and then 2 digits";
         return false;
      }
      break;
    case "United Kingdom":
      if (!ereg("^(([A-Z][0-9]{1,2})|([A-Z]{2}[0-9]{1,2})|" .
                "([A-Z]{2}[0-9][A-Z])|([A-Z][0-9][A-Z])|" .
                "([A-Z]{3}))[ ][0-9][A-Z]{2}$", $zipcode))
      {
         print "The postcode must begin with a string of the format
                A9, A99, AA9, AA99, AA9A, A9A, or AAA,
                and then be followed by a space and a string
                of the form 9AA.
                A is any letter and 9 is any number.";
        return false;
      }
      break;
    default:
      // No validation
  }
  return true;
}


// Check a phone number
/**
 * shn_valid_phone 
 * 
 * @param mixed $field 
 * @access public
 * @return void
 */
function shn_valid_phone($field)
{
   $validPhoneExpr = "^([0-9]{2,3}[ ]?)?[0-9]{4}[ ]?[0-9]{4}$";

   if (!ereg($validPhoneExpr,$field))
   {
         "The {$field} field must be 8 digits in length, " .
         "with an optional 2 or 3 digit area code";
      return false;
   }
   return true;
}


// Check an email address
/**
 * shn_valid_email 
 * 
 * @param mixed $field 
 * @param mixed $required 
 * @access public
 * @return void
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
 * shn_valid_date 
 * 
 * @param mixed $date 
 * @param string $pattern 
 * @access public
 * @return void
 */
function shn_valid_date($date,$pattern='/^\d{4}-\d{2}-\d{2}$/')
{
    if(preg_match($pattern,$date))
        return true;
    else
        return false;
}

/**
 * shn_valid_number 
 * 
 * @param mixed $str 
 * @param string $pattern 
 * @access public
 * @return void
 */
function shn_valid_number($str,$pattern='/^\d+$/')
{
    if(preg_match($pattern,$date))
        return true;
    else
        return false;
}

/**
 * shn_is_null 
 * 
 * @param mixed $field 
 * @access public
 * @return void
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
 * shn_is_opt_field 
 * 
 * @param mixed $opt_field 
 * @param mixed $opt_value 
 * @access public
 * @return void
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
 * shn_is_location 
 * 
 * @param mixed $field 
 * @access public
 * @return void
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
 * shn_clean 
 * 
 * @param mixed $field 
 * @access public
 * @return void
 */
function shn_clean($field){
    return trim($field);
}

/**
 * shn_validate_field 
 * 
 * @param mixed $field 
 * @param mixed $desc 
 * @param mixed $max_len 
 * @param mixed $check_null 
 * @access public
 * @return void
 */
function shn_validate_field($field,$desc,$max_len,$check_null=false){
    if ($check_null And shn_is_null($field)){
        add_error($desc." is a Required Field, Please Enter an value.");
        return false;
    }else {
        if (strlen(shn_clean($field))>$max_len){
            add_error("You Exceeded the field size for ".$desc.".Field size is ".$max_len);
            return false;
        }else {
            return true;
        }
    }
}

/**
 * shn_validate_opt_field 
 * 
 * @param mixed $type 
 * @param mixed $field 
 * @param mixed $desc 
 * @param mixed $max_len 
 * @param mixed $array 
 * @access public
 * @return void
 */
function shn_validate_opt_field($type,$field,$desc,$max_len,$array=false){
    if (shn_validate_field($field,$desc,$max_len,true)){
        $i=0;
        if(!$array){
             if (shn_is_opt_field($type,shn_clean($field)))
                return true;
        }else {
            $i=0;
            while ($i<count($field)){
                if (!shn_is_opt_field($type,shn_clean($field[$i]))){
                    add_error("You Have to Select a Value from the list box");
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
 * shn_validate_user_name 
 * 
 * @param mixed $field 
 * @access public
 * @return void
 */
function shn_validate_user_name($field){
    if (shn_validate_field($field,"User Name",100,true)){
        if (shn_is_user($field)){
            add_error("User Already Exists");
            return false;
        }else {
            return true;
        }
    }else {
        return false;
    }
}

/**
 * shn_validate_password 
 * 
 * @param mixed $field 
 * @access public
 * @return void
 */
function shn_validate_password($field){
   //return true;
   $PWDPOLICY="password must adhere to following rules:
    1. only numbers and letters.
    2. minimum length is 8.
    3. at least one number and one letter in the expression."; 
    $pattern='/([0-9]+[a-z]\+){8}/';
    if (shn_validate_field($field,"Password",100,true)){
            return true;
        /*
        if(preg_match($pattern,$field))
            return true;
        else{
            add_error($PWDPOLICY);
            return false;
        }
        */
    }else {
            return false;
    }
}
?>
