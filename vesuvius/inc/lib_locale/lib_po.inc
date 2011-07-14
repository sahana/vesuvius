<?
/**
 * @name         Pootle Library
 * @version      1.0
 * @package      framework
 * @author       Sudheera R. Fernando <sudheera@opensource.lk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */



function shn_lc_pot2db() {
	global $global;
	$pot_path = $global['approot']."/res/locale/";
	$pot_file = "sahana.pot";

	$file   = $pot_path.$pot_file;
	$table  = 'lc_pot';
	$new_rec = false;
	$msg_str = false;
	$com_str = false;

	$lines = file ($file);

	foreach ($lines as $line)
	{
		if (preg_match( "/#.*\n/", $line, $array )) {

			if (!$msg_str && !$com_str) {
				$new_rec = true;
				$com_str = true;
			} else if ($msg_str) {
				$new_rec = false;
				$msg_str = false;
				print_r ($rec);
				$rec['comments'] = null;
				$rec['string'] = null;
				//break;
			}
			$rec['comments'] .= $array[0];
		}
		elseif (preg_match( "/\".*\"/", $line, $array )) {
			if ($array[0] != '""') {
				$rec['string'] .= $array[0];
			}
			$msg_str = true;
			$com_str = false;
		}
	}
}



function shn_lc_create_pot() {
	global $global;
	$pot_path = $global['approot']."/res/locale/";
	$pot_file = "sahana.pot";

	if (is_writable($pot_path)) {
		$return = array();
		$cmd = 'xgettext --keyword=__ --keyword=_e ' .
			'--keyword=_t  --default-domain=sahana ' .

			'--language=php ../*/*/*.inc ../*/*.inc ../*/*/*/*/*.inc ' .

			'--language=php ../*/*.inc ../*/*.inc ../*/*/*/*/*.inc ' .
			'--output=../res/locale/sahana.pot';

		system($cmd, &$return);
		return true;
	} else {
		add_error(_t("The path $pot_path is not writable!!"));
		display_errors();
		return false;
	}
}

