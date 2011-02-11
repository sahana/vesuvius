<?php
/**
 *
 * <Description goes here>
 *
 * PHP version 4 and 5
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage stream_html
 * @author     Chamindra de Silva <chamindra@opensource.lk>
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

require_once ($global['approot'].'inc/lib_menu.inc');

function shn_stream_init() {
	global $global;
	global $conf;
	require_once ($global['approot'].'inc/lib_security/lib_acl.inc');
	$module = $global['module'];

	// include the html head tags
	shn_include_page_section('html_head',$module);

	// Start the body and the CSS container element
	if(isset($_SESSION['admin']['locale']['enable']) && $_SESSION['admin']['locale']['enable']=="set") {
		echo "<body onclick=\"whichElement(event)\" oncontextmenu=\"return false;\">";
	} else {
		echo "<body>";
	}
	echo "<div id=\"container\">";

	// include the page header provided there is not a module override
	shn_include_page_section('header',$module);

	// Now include the wrapper for the main content
	echo "<div id=\"wrapper\" class=\"clearfix\">";
	echo "<div id=\"wrapper_menu\">";
	//echo "<p id=\"skip\">Jump to: <a href=\"#content\">". _t('Content')."</a> | <a href=\"#modulemenu\">". _t('Module Menu')."</a></p>";

	// hack for the admin section such that the menu and login come from the admin section
	if (isset($global['effective_module']) && $global['effective_module'] != null) {
		$module = $global['effective_module'];
	}

	// include the mainmenu and login provided there is not a module override
	shn_include_page_section('mainmenu',$module);
	shn_include_page_section('login',$module);

	// display the breadcrumbs: It is important that this happens after the menu definition the nice name is constructed from the query string
	$nicename = 'shn_q_'.$_SERVER['QUERY_STRING'].'_nicename';

	if (array_key_exists($nicename, $global)) {
		shn_breadcrumb_push($global[$nicename]);
	}

	shn_breadcrumb_display();

	// now include the main content of the page
	echo "</div>";
	echo "<!-- Left hand side menus & login form -->";
	echo "<div id=\"content\" class=\"clearfix\">";

	// start output buffer for the module output
	ob_start();
}



function shn_stream_close() {
	global $conf;
	global $global;

	// flush the output buffer
	$output = ob_get_contents();
	ob_end_clean();

	// check for exceptions
	$exception_list = $global['exception_list'];
	$result = null;
	$exception = null;
	$is_abort = false;

	if(isset($exception_list)) {
		foreach($exception_list as $ex){
			$res = $ex->getResult();
			$exception = $ex;
			$result = $res;
			if(isset($res) && $res==REPORT_AND_ABORT) {
				break;
			}
		}
		if ($result == REPORT_AND_ABORT) {
			add_error($exception->getMessage());
			$is_abort = true;
		} else if ($result == REPORT_AND_CONTINUE) {
			add_warning($exception->getMessage());
		}
	}

	// display the errors first before the rest of the module output
	display_errors();
	display_submit_message('confirmation','Submission Successful');
	display_submit_message('warning','Warning');
	display_submit_message('information','Information');
	if ($is_abort == false) {
		echo $output;
	}

	echo "</div>";
	echo "<!-- /content -->";

	// if xajax object exists print the javascript
	if (isset($global['xajax'])) {
		shn_xajax_printJavascript();
	}

	echo "</div>";
	echo "<!-- /wrapper -->";

	// include the footer provided there is not a module override
	shn_include_page_section('footer',$global['module']);

	echo "</div>";
	echo "<!-- /container -->";

	echo "</body>";
	echo "</html>";
}
