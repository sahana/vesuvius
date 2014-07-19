<?
/**
 * @name         lib XHTML
 * @version      1.1
 * @package      framework
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0420
 */



/**
 * shn_display_xhtml_head
 *
 * @param $arrPostfix array stores the list of lines you want to insert into the header
 * @param $theme string decides on what css theme you are using
 * @param $title string if you want to change it from the default
 */

function shn_display_xhtml_head( $arrPostfix = null, $theme = null, $title = null ) {

	global $conf;
	global $global;

	// If theh theme specifies a site TITLE, then use it:
	if (file_exists($global['approot']."www/theme/".$conf['theme']."/info.php")) {
		require($global['approot']."www/theme/".$conf['theme']."/info.php");
		$title = $siteTitle;

	// if the database is configured, then select the
	// incident's name from the database via ADODB.
	} else if ($global['db'] == TRUE){
		# get an array of current incidents, and store them
		# in the $title_result variable
		$sql_incident = "
			SELECT name
			FROM incident a
			INNER JOIN user_preference b
			ON a.incident_id = b.value
			WHERE b.p_uuid = '{$_SESSION['user_id']}'
			AND b.pref_key = 'incident_id';
		";
		$title_result = $global['db']->GetAll($sql_incident);

		$title_part_1 = $conf['mod_'.$global['module'].'_name']; # the current module
		$title_part_2 = $title_result[0]['name'];                # the current incident
		$title_part_3 = (shn_db_get_config("base", "alternate_title_string")!== FALSE) ? shn_db_get_config("base", "alternate_title_string") : _t("Sahana Vesuvius");

		#if an incident has been created
		if ( count($title_result) != 0) {
			#use all three parts
			if (shn_db_get_config("base","alternate_title_method") === "TRUE") {
				$title = $title_part_3." :: ".$title_part_1." :: ".$title_part_2;
			} else {
				$title = $title_part_1." - ".$title_part_2." - ".$title_part_3;
			}
		} else {
			# otherwise, simply use the module name and Sahana's full name
			$title = $title_part_1." - ".$title_part_3;
		}
	} else {
		# Simply use Sahana's name as the title if a disaster
		# has not yet been set.
		$title = "Sahana";
	}

	# globalize title
	$global['title'] = $title;

	# set the theme if it is not given as a parameter
	$theme || $theme = $conf['theme'];
	$global['theme'] = $theme;

	if(file_exists($global['approot']."www/theme/".$theme."/head.php")) {
		require_once($global['approot']."www/theme/".$theme."/head.php");
		shn_theme_head();
	} else {
		echo "theme not setup correctly ~ theme(".$theme.")";
		die();
	}

	if ($arrPostfix != null) {
		foreach ($arrPostfix as $i) {
			echo '        '.$i."\n";
		}
	}
	echo "</head>\n";
}


