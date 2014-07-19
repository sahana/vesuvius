<?
/**
 * @name         Image Stream Librarya
 * @version      1.0
 * @package      framework
 * @subpackage   stream_image
 * @author       Janaka Wickramasinghe <janaka@opensource.lk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


function shn_stream_init($filename=null) {
	if(isset($_GET['imagetype'])) {
		header("Content-type: image/{$_GET['imagetype']}");
	} else {
		header("Content-type: image/jpeg");
	}
	if(isset($_GET['download'])) {
		header("Content-Disposition: attachment; filename=$file");
	}
}



function shn_stream_close($output = null) {
	echo $output;
}



function shn_image_check_perms() {
	return ALLOWED;
	//skip authentication
}



function _shn_image_display_errors() {
	// do nothing.
	return;
}

