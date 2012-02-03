<?
/**
 * @name         Error Library
 * @version      11
 * @package      framework
 * @author       Janaka Wickramasinghe <janaka@opensource.lk>
 * @author       Chamindra de Silva <chaindra@opensource.lk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0202
 */


/** The following are three global containers to hold the messages or confirmation, warning and error following a submit */

require_once($global['approot'].'inc/lib_locale/gettext.inc');
$global['submit_errors'] = array();
$global['submit_warnings'] = array();
$global['submit_confirmations'] = array();
$global['submit_informations'] = array();



function add_warning($warning) {

	global $global;
	array_push($global['submit_warnings'],$warning);
}



function add_confirmation($confirmation) {

	global $global;
	array_push($global['submit_confirmations'],$confirmation);
}



function add_information($information) {

	global $global;
	array_push($global['submit_informations'],$information);
}



/** this function will display the submit message of a certain type as contained in the container specified by the type @TODO: add generic check for container existance */
function display_submit_message($type = 'warning', $msg = 'please note the following:') {

	global $global;
	$container = 'submit_'.$type.'s';

	// return if there are no errors
	if (count($global[$container]) == 0 ) {
		return;
	}
	echo '
		<div class="'.$type.' message">
			<p><em>'.$msg.'</em></p>
			<ul>
	';
	foreach($global[$container] as $i) {
		echo '<li>'.$i.'<br></li>';
	}
	echo '
			</ul>
		</div>
	';
	$global[$container] = null;
}



/** If you want to display the errors call this function. */
function display_errors($error_title = null, $return = false, $clean_errors = true) {

	global $global;
	$mod = $global['module'];
	$act = $global['action'];
	$stream = isset($_REQUEST['stream']) ? $_REQUEST['stream'] : "";
	if(strlen($stream) == 0) {
		$stream = 'html';
	}

	if(strtolower($stream)=='html') {
		if (null == $error_title) {
			$error_title = _t('Oops! There are a few errors :');
		}

		// return if there are no errors
		if (count($global['submit_errors']) == 0 ) return;

		$output = "<div class=\"error message\">";

		$output .= '<p><em>'.$error_title.'</em></p>';

		$output .= "<ul>";
		foreach ($global['submit_errors'] as $error){
			$output .= "<li>".$error.'<br/></li>';
		}
		$output .= "</ul>";
		$output .= "</div>";

		//Clean Errors
		if($clean_errors) {
			clean_errors();
		}

		if($return) {
			return $output;
		} else {
			echo $output;
			return 1;
		}
	} else {
		$custom_display_function = "_shn_".$stream."_".$mod."_".$act."__display_errors";

		if(function_exists($custom_display_function)){
			// call custom display error function.
			$custom_display_function();
		}else{
			// call generic display errors
			$generic_display_function = "_shn_".$stream."_display_errors";
			$generic_display_function();
		}
		//Clean Errors
		if($clean_errors) {
			clean_errors();
		}
	}
}



function add_error($error) {

	global $global;
	if(is_array($error))
	array_push($global['submit_errors'],$error);
	else
	$global['submit_errors'][] = $error;
}



function clean_errors() {

	global $global;
	$global['submit_errors'] = NULL;
}



function is_errors() {

	global $global;
	if(empty($global['submit_errors'])) {
		return false;
	} else {
		return true;
	}
}



function shn_error_display_restricted_access() {

	global $global;

	if($_SESSION['user'] == "Anonymous") {
		echo '
			<div class="error message">
				<br>
				<p><em>Sorry, you do not have permisssion to access this section. You must first login.</em></p><br>
			</div>
		';
		require_once($global['approot'].'mod/pref/main.inc');
		shn_pref_loginForm();

	} else {
		echo '
			<div class="error message">
				<p><em>Sorry, you do not have permisssion to access this section. To gain access to this section please contact the site admin or your hospital staff administrator.</em><br><br>
			</div>
		';
	}
}



function shn_error_get_restricted_access_message() {

	ob_start();
	if($_SESSION['user'] == "Anonymous") {
		echo '
			<div class="error message">
				<br>
				<p><em>Sorry, you do not have permisssion to access this section. You must first login.</em></p><br>
			</div>
		';

	} else {
		echo '
			<div class="error message">
				<p><em>Sorry, you do not have permisssion to access this section. To gain access to this section please contact the site admin or your hospital staff administrator.</em><br><br>
			</div>
		';
	}
	$contents = ob_get_contents();
	ob_end_clean();
}



