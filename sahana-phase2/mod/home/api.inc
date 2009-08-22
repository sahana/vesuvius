<?php
/** API of the Home module 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><http://r4vi.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage home
*/

/**
 * This returns the FAQ list
 * @param string $question question to search for
 * @param string $module context of the search
 * @param string $action action
 * @access public
 * @return array
 */
 
function shn_search_answer_db($FAQinput){
	$question=$FAQinput["question"];
	$module=$FAQinput["module"];
	$action=$FAQinput["action"];
//function shn_search_answer_db($question="test",$module="home",$action="test"){
		global $global;
		require_once($global['approot']."/inc/user_feedback.inc");
	//	file_put_contents("/tmp/a.txt","question".$question,FILE_APPEND);
		$faq_list=_shn_search_get_answer_db($question,$module,$action);
		return $faq_list;
}
