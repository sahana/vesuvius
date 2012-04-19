<?
/**
 * @name         HTML Stream Library
 * @version      10
 * @package      framework
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0222
 */


require_once($global['approot'].'inc/lib_menu.inc');

function shn_stream_init() {

	global $global;
	global $conf;

	require_once($global['approot'].'inc/lib_security/lib_acl.inc');
	$module = $global['module'];

	// include the html head tags
	shn_include_page_section('html_head', $module);

	// Start the body and the CSS container element
	if(isset($_SESSION['admin']['locale']['enable']) && $_SESSION['admin']['locale']['enable']=="set") {
		echo "<body onclick=\"whichElement(event)\" oncontextmenu=\"return false;\">";
	} else {
		echo "<body>";
	}
	echo "<div id=\"container\">";

	// include the page header provided there is not a module override
	shn_include_page_section('header', $module);

	// Now include the wrapper for the main content
	echo "<div id=\"wrapper\" class=\"clearfix\">";
	echo "<div id=\"wrapper_menu\">";

	// hack for the admin section such that the menu and login come from the admin section
	if (isset($global['effective_module']) && $global['effective_module'] != null) {
		$module = $global['effective_module'];
	}

	// include the mainmenu and login provided there is not a module override
	shn_include_page_section('mainmenu', $module);
	shn_include_page_section('login', $module);

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
	display_submit_message('confirmation', '&nbsp;');
	display_submit_message('warning', 'Warning');
	display_submit_message('information', 'Information');
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


