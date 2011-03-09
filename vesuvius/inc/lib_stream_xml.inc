<?
/**
 * @name         XML Stream Library
 * @version      1.0
 * @package      framework
 * @subpackage   stream_xml
 * @author       Janaka Wickramasinghe <janaka@opensource.lk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


function shn_stream_init($emit_xml_declaration = false) {
	$file = 'download.xml';
	if(isset($_GET['filename']))
		$file = $_GET['filename'];
	//todo need a way to pass header;

	header("Content-type: text/xml");
	if(isset($_GET['download'])) {
		header("Content-Disposition: attachment; filename=$file");
	}
	if ($emit_xml_declaration) {
		echo "<?xml version=\"1.0\" ?>\n";
	}
	shn_stream_display_error();
}



function shn_stream_close() {}



function shn_xml_check_perms() {
	//skip authentication
	return ALLOWED;
}



// let the XML stream have it's own error function
function shn_stream_display_error() {
	global $global;

	// return if there are no errors
	if (count($global['submit_errors']) == 0 ) {
		return;
	}
	echo '<errorset>';
		foreach ($global['submit_errors'] as $error){
			echo '<error>'._t($error).'</error>';
		}
	echo '</errorset>';
}



function _shn_soap_display_errors() {
	shn_stream_display_error();
	return;
}


