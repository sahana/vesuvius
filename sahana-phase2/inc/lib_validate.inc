<?php
// General-purpose validation functions

// Test if a field is between min and  max length
function shn_valid_len_range($field, $minlength, $maxlength)
{
   if ((strlen($field) > $minlength) && (strlen($field) < $maxlength))
   {
      return true;
   }
   return false;
}

//zipcode validator 
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
function shn_valid_email($field)
{
   // Check syntax
   $validEmailExpr =  "^[0-9a-z~!#$%&_-]([.]?[0-9a-z~!#$%&_-])*" .
                      "@[0-9a-z~!#$%&_-]([.]?[0-9a-z~!#$%&_-])*$";

   if (!eregi($validEmailExpr, $field))
   {
      return false;
   }

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

   return true;
}

function shn_valid_date($date,$pattern='/^\d{4}-\d{2}-\d{2}$/')
{
    if(preg_match($pattern,$date))
        return true;
    else
        return false;
}

function shn_valid_number($str,$pattern='/^\d+$/')
{
    if(preg_match($pattern,$date))
        return true;
    else
        return false;
}

function shn_is_null($field)
{
    if (null==$field){
        return true;
    }else {
        return false;
    }
}

function shn_is_opt_field($opt_field)
{
    global $global;
    $result = $global['db']->GetOne("SELECT * FROM field_options WHERE field_name LIKE '$opt_field'");
    if($result)
        return true;
    else
        return false;
}

?>
