<?
/**
 * @name         PL User Services
 * @version      1.9.2
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0606
 */


/*
remove below two lines when 1.9.1 is deprecated
*/
define("UNDEFINED_HOSPITAL_CODE",            10);
define("UNDEFINED_HOSPITAL_MSG",             "Undefined Hospital ~ No hospital registered with this id");


// define error codes
define("ERRORCODES", serialize(array(
	0    => "No error.",
	1    => "Invalid username or password.",
	2    => "User account is not active.",
	3    => "Invalid confirmation request.",
	4    => "Account already active.",
	5    => "Account activated.",
	6    => "User exists with provided email address.",
	7    => "Username already in use.",
	8    => "Invalid email address.",
	9    => "Password does not meet the following criteria: 1. The minimum length of the password is 8 characters. 2. The maximum length of the password is 16 characters. 3. Must have at least one uppercase character. 4. Must have at least one lowercase character. 5. Must have at least one numeral (0-9). 6. The password cannot contain your username.",
	100  => "No hospital registered with this id.",
	200  => "sessionTimeout value missing from database.",
	9999 => "Unknown error.",
)));