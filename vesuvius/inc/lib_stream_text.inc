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
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */



function shn_stream_init() {
}



function shn_text_check_perms() {
	return ALLOWED;
}



function _shn_text_display_errors() {
	global $global;
	if (count($global['submit_errors']) > 0) {
		echo "Uhoh.. There were a few errors!<br><br>";
		$i = 1;
		foreach ($global['submit_errors'] as $err) {
			echo "#".$i." ".$err."<br>";
			$i++;
		}
	}

}



function shn_stream_close() {
	display_errors();
}


