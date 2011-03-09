<?
/**
 * @name         Text Stream Library
 * @version      1.0
 * @package      framework
 * @subpackage   stream_text
 * @author       Janaka Wickramasinghe <janaka@opensource.lk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */



function shn_stream_init() {
	//for install hack
	$my_approot = realpath(dirname(__FILE__)) . '/../';
	if (!file_exists($my_approot . 'conf/sahana.conf')) {
		if(!isset($_SESSION)) {
			session_start();
		}
	}
	//install hack ends
}



function shn_text_check_perms() {
	return ALLOWED;
	//skip authentication at this step since , authentication is performed at the last step. i.e at method
	// invocation level. otherwise cannot let WSDL be visible to any one and still protect the methods.
}



function _shn_text_display_errors() {
	global $global;
	if (count($global['submit_errors']) > 0) {
		echo "There were a few errors....\r\n";
		$i = 1;
		foreach ($global['submit_errors'] as $err) {
			echo $i . ". " . $err . "\r\n";
			$i++;
		}
	}

}



function shn_stream_close() {
	display_errors();
}


