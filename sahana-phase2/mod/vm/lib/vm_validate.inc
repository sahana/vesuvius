<?php

/**
* Validating functions
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Antonio Alcorn
* @author       Giovanni Capalbo
* @author		Sylvia Hristakeva
* @author		Kumud Nepal
* @author		Ernel Wint
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @copyright    Trinity Humanitarian-FOSS Project - http://www.cs.trincoll.edu/hfoss
* @package      sahana
* @subpackage   vm
* @tutorial
* @license        http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

/**
 * A library to validate POST data
 */


/**
 * Checks to see if the date given is valid or not and outputs an error message
 * if so. Expects date in format YYYY-MM-DD.
 * Respects number of days in the month including February and leap years.
 *
 * @param $date				- the date to check
 * @param $error_message		- the error message to print (optional)
 * @return true if the date is valid, false if not
 */

function shn_vm_valid_date($date, $error_message=null)
{
	// get Y,M,D, and check if it's in the right format
	if(!preg_match('/^(\d{4})-(\d{2})-(\d{2})$/', trim($date), $matches)) {
		if($error_message != null)
			add_error($error_message);
		return false;
	}
	list($full, $year, $month, $day) = $matches;
	if(0 < $month && $month <= 12) { // check if month is in range
		if($month == 2) // February, with adjustments for leap years
			$max_days = 28 + ($year % 4 ? 0 : ($year % 100 ? 1 : ($year % 400 ? 0 : 1)));
		else // all other months
			$max_days = 30 + (($month > 7)? (($month + 1) % 2):($month % 2));
		if(0 < $day && $day <= $max_days) // check if day is in range
			return true;
		else {
			if($error_message != null)
				add_error($error_message);
			return false;
		}
	} else {
		if($error_message != null)
			add_error($error_message);
		return false;
	}
}

/**
 * Checks to see if the given input is empty or not and outputs an error message
 * if so.
 *
 * @param $input			- the input field to check
 * @param $error_message		- the error message to output if necessary (optional)
 * @return false if the input is null, true otherwise
 */

 function shn_vm_not_empty($input, $error_message=null)
 {
	if(trim($input) == null)
	{
		if($error_message != null)
			add_error($error_message);
		return false;
	}
	return true;
 }

/**
 * Checks to see if one date occurs before the other and outputs an error message
 * if not. This function assumes that the dates given are already valid dates and
 * explicitly allows the dates to be empty.
 *
 * @param $date_before		- the date that must be older
 * @param $date_after		- the date that must be younger
 * @param $error_message	- the error message to output if necessary (optional)
 * @return false if the dates are incompatible, true otherwise
 */

function shn_vm_compatible_dates($date_before, $date_after, $error_message=null)
{
 	$start_date = explode('-', $date_before);
	$end_date = explode('-', $date_after);

	if(mktime(0, 0, 0, $start_date[1], $start_date[2], $start_date[0]) > mktime(0, 0, 0, $end_date[1], $end_date[2], $end_date[0]))
	{
		if($error_message != null)
			add_error($error_message);
		return false;
	}

	return true;
}

/**
 * Checks to see if two fields match (case-sensitive) and outputs an error message if not.
 *
 * @param $field1			- the first field to check
 * @param $field2			- the second field to check
 * @param $error_message		- the error message to output if necessary (optional)
 * @return false if the dates are incompatible, true otherwise
 */

function shn_vm_fields_equal($field1, $field2, $error_message=null)
{

	if($field1 != $field2)
	{
		if($error_message != null)
			add_error($error_message);
		return false;
	}

	return true;
}

/**
 * Checks to see if the given time follows a valid time format and outputs an error
 * message if not.
 *
 * @param $time				- the time string to check
 * @param $error_message		- the error message to output if necessary (optional)
 * @return false if the time is invalid, otherwise true
 */

function shn_vm_valid_time($time, $error_message=null)
{
	$time_pattern ='/(^\d{1,2}:\d{2}$)|(^\d{1,2}:\d{2}:\d{2}$)/';

	if(!preg_match($time_pattern, $time))
	{
		if($error_message != null)
			add_error($error_message);
		return false;
	}
	else
	{
		$time_split = explode(':', $time);
		if($time_split[0] > 23 || $time_split[1] > 59)
		{
			if($error_message != null)
				add_error($error_message);
			return false;
		}

		if(count($time_split) > 2)
			if($time_split[2] > 59)
			{
				if($error_message != null)
					add_error($error_message);
				return false;
			}
	}

	return true;
}

/**
 * Validates that a user does not already exist and outputs an error message if the
 * user already exists.
 *
 * @param $user_name			- the user's name
 * @param $error_message		- the error message to output if necessary (optional)
 * @return false if the user exists, true otherwise
 */

function shn_vm_username_not_taken($user_name, $error_message=null)
{
	global $global;
	include_once($global['approot'].'inc/lib_security/lib_auth.inc');

	if(shn_is_user($user_name))
	{
		if($error_message != null)
			add_error($error_message);
		return false;
	}
	return true;
}

/**
 * Validates that at least one skill has been selected.
 *
 * @param $post_vars 		- the entire post data
 * @param $error_message 	- the error message to output if necessary (optional)
 * @access public
 * @return false if no skills are selected, and true otherwise;
 */

 function shn_vm_skill_selected($post_vars, $error_message=null)
 {
 	global $dao;
 	$skills = $dao->getSkillIDs();
 	$num_selected = 0;
 	foreach($skills as $skill_id)
 	{
 		if($post_vars["SKILL_$skill_id"]=='on')
 			$num_selected++;
 	}
 	$selected = $num_selected!=0;
 	if(!$selected)
 	{
 		if($error_message != null)
			add_error($error_message);
 	}
 	return $selected;

 }
 /**
  * Validate if the location fields are empty
  *
  * @param $error_message 	-the error message to be displayed
  * @return false if the form is empty and true otherwise;
  */
	function shn_vm_location_selected($error_message=null)
	{
		global $global;
		require_once($global['approot']. 'inc/lib_location.inc');
		$loc = shn_location_get_form_submit_loc();
		if($loc== -1 || $loc == '0')
		{
			if($error_message !=null)
				add_error($error_message);
			return false;
		}
		return true;
	}

	function validateShiftTimes($start, $end) {
		if($start > $end)
			return _("Shift start must be before shift end.");
		if($start > time())
			return _("Shift start must not be in the future.");
		if($end > time())
			return _("Shift end must not be in the future.");
		if($start == 0 || $end == 0)
			return _("Start and end times must not be blank.");
		return VM_OK;
	}
