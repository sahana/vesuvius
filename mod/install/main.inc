<?
/**
 * @name         Installer
 * @version      1
 * @package      install
 * @author       Ramindu Deshapriya <rasade88@gmail.com> <rdeshapriya@virtusa.com>
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2013.0911
 */





function shn_install_default() {

	global $global;
	echo "<p>Installer under construction</p>";
}


function shn_install_stream_init() {
    echo "<body>";
    echo "<div id=\"container\">";

    echo "<div id=\"wrapper\" class=\"clearfix\">";
    echo "<div id=\"wrapper_menu\">";
    echo "
		<div id=\"menuwrap\">
		<ul id=\"menu\">
	";
    echo "
		</ul>
		</div> <!-- /menuwrap -->
		</div>
	";
    ob_start();
}
function shn_install_stream_close() {
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


    echo "</div>";
    echo "<!-- /container -->";

    echo "</body>";
    echo "</html>";
    ob_flush();
}







