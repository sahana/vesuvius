<?
/**
 * @name         Extensible Streaming
 * @version      2.0
 * @package      xst
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0810
 */


function shn_text_xst_help() {
	if(empty($_GET['help_id'])) {

		echo "var help_arr = new Array(".count(isset($_SESSION['form_help']) ? $_SESSION['form_help'] : null).");\n";
		if(isset($_SESSION['form_help']))
		foreach($_SESSION['form_help'] as $help_id => $value){
			$clean_value = preg_replace(array('@([\r\n])[\s]+@','@"@'), array(' ',"'"),$value);
			echo "help_arr[".$help_id."] = \"$clean_value\";\n";
		}
	} else {
		echo $_SESSION['form_help'][$_GET['help_id']];
	}
}


function shn_xst_help(){}

function shn_ajax_xst_xajax(){}
