<?php
/**
* Constants for use in the VM module
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

global $global;

// if true, all queries executed through the DAO will also be echoed along with a count.
define('debug_show_queries', false);

//Template Engine constants
define('SHN_VM_ENGINE_CACHE_DIR', $global['approot'].'www/tmp/vm_cache/');
define('SHN_VM_ENGINE_TEMPLATE_DIR', $global['approot'].'mod/vm/templates/');

// start the counter, if need be
if(debug_show_queries) $query_count = 0;

//tree constants
define('TREE_DIR', $global['approot'] . 'mod/vm/tree/');
define('TREE_IMAGE_PATH', "?mod=vm&stream=image&act=tree_image&img=");
define('TREE_JS_PATH', "?mod=vm&stream=text&act=display_js&js=");

//volunteer constants
define('VM_SHOW_ALL_VOLUNTEERS_ASSIGNED', 0);
define('VM_SHOW_ALL_VOLUNTEERS_UNASSIGNED', 1);
define('VM_SHOW_ALL_VOLUNTEERS', 2);
define('VM_SKILLS_ALL', 0);
define('VM_SKILLS_ANY', 1);
define('VM_OK', 1);	// returned by validation functions on success

//some info access constants for viewing a list of volunteers
define('VM_ACCESS_MINIMAL', 1);		//access to bare minimum info (regular volunteer)
define('VM_ACCESS_PARTIAL', 2);		//access to partial info (site manager)
define('VM_ACCESS_ALL', 3);			//access to all info

//pictures
define('VM_LIST_PICTURES', true);	// should we show picture thumbnails in lists of volunteers?
define('VM_IMAGE_QUALITY', 100);	// JPEG quality when resizing, can range from 0 - 100

// max width and height of image and thumb sizes, in pixels
define('VM_IMAGE_THUMB_WIDTH',	160);
define('VM_IMAGE_THUMB_HEIGHT',	120);
define('VM_IMAGE_BIG_WIDTH',	320);
define('VM_IMAGE_BIG_HEIGHT',	240);

//the delimeter used for separating skills categories and descriptions, can be regular expression describing more than one delimeter
define('VM_SKILLS_DELIMETER', '(\-|－|一)');

//the maximum acceptable levenshtein distance to use when sorting search results
define('VM_MAX_LEVENSHTEIN', 255);

//default number of rows per page for paging display
define('VM_DEFAULT_RPP', 5);
define('VM_DEFAULT_REPORTS_RPP', 20);
define('VM_DEFAULT_MAILBOX_RPP', 20);

//error constants

define('SHN_ERR_VM_NO_NAME',					_('Please specify a name'));
define('SHN_ERR_VM_BAD_DATES',					_('Please specify valid start and end dates for availability (yyyy-mm-dd)'));
define('SHN_ERR_VM_DATES_INCOMPATIBLE',			_('Please specify a start date that is before the end date'));
define('SHN_ERR_VM_INVALID_DOB',				_('Date of birth is not a valid date'));
define('SHN_ERR_VM_BAD_PROJECT_DATES',			_('Please make sure that the dates you specified are valid(yyyy-mm-dd)'));
define('SHN_ERR_VM_FUTURE_DOB',					_('Date of birth is in the future'));
define('SHN_ERR_VM_BAD_START_TIME',				_('Invalid start hours format'));
define('SHN_ERR_VM_BAD_END_TIME',				_('Invalid end hours format'));
define('SHN_ERR_VM_NO_SKILLS_SELECTED',			_('Please select at least one skill'));
define('SHN_ERR_VM_BAD_USER_NAME',				_('Please enter a valid user name'));
define('SHN_ERR_VM_BAD_PASSWORD',				_('Please enter valid passwords'));
define('SHN_ERR_VM_INCOMPATIBLE_PASSWORDS',		_('Passwords do not match'));
define('SHN_ERR_VM_BAD_CUR_PASSWORD',			_('Please enter a valid current password'));
define('SHN_ERR_VM_BAD_NEW_PASSWORD',			_('Please enter valid new passwords'));
define('SHN_ERR_VM_PASSWORD_NOT_MATCH',			_('Current Password does not match'));
define('SHN_ERR_VM_USER_EXISTS',				_('A Sahana account with the given username already exists.'));
define('SHN_ERR_VM_NO_TO_VOLS',					_('Please select at least one volunteer to send the message to'));
define('SHN_ERR_VM_NO_MESSAGE',					_('Please type a message'));
define('SHN_ERR_VM_SEARCH_NO_PARAMS',			_('Please enter at least one field to search by'));
define('SHN_ERR_VM_SEARCH_BAD_ID',				_('Please enter an ID at least 4 characters long if no other fields are specified'));
define('SHN_ERR_VM_BOTH_DATES',					_('Please specify both a start and an end date.'));
define('SHN_ERR_VM_NO_PROJECT',					_('Please select a project'));
define('SHN_ERR_VM_NO_MGR',						_('Please specify a project manager'));
define('SHN_ERR_VM_NO_START_DATE',				_('If you specify an end date for availability, please specify a start date as well'));
define('SHN_ERR_VM_BAD_DATE_RANGE',				_('If you specify searching for an entire available date range, please specify both a start and end date'));
define('SHN_ERR_VM_NO_REQUEST',					_('Please specify a situation to modify access to'));
define('SHN_ERR_VM_NO_TITLE',					_('Please specify a title'));
define('SHN_ERR_VM_NO_POSITION_TYPE',			_('Please specify a position_type'));
define('SHN_ERR_VM_NO_TARGET',					_('Please specify a non-zero target number of volunteers'));
define('SHN_ERR_VM_NO_DESCRIPTION',				_('Please specify a description'));
define('SHN_ERR_VM_NO_PAYRATE',					_('Please specify a non-zero pay rate'));

