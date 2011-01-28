<?php
/** 
 * Home Page of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @author     Greg Miernicki <g@miernicki.com> <miernickig@mail.nih.gov>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */


?>
<div id="home">
	<h2><?php echo  _t('Missing and Found Person Registry'); ?></h2>
	<?php
	global $global;
	if(file_exists($global['approot'].'/www/tmp/mprfound.png')) {
		?><img src="tmp/mprfound.png"/><img src="tmp/mprfound.png"/><?php
	}
	$alternate_homepage = shn_db_get_config("mpr", "alternate_homepage");
	
	// new default MPR homepage
	if (($alternate_homepage == FALSE) || ($alternate_homepage == "0")) {
		$html = "<br>
This is an organized online bulletin board to aid in locating someone after a disaster affecting the Bethesda area.<br><br>
Anyone may use the search feature, without logging in. Get basic information about someone missing or found, including photos, as reported by family members, friends, or participating local hospitals. (Coming soon: search optimized for cell phones).<br>
<br>
To do more, create a login account with your contact information. Then you can:<br>
<br>
<ul>
	<li>Report someone as missing, and include photographs of them</li>
	<li>Update that report, e.g., if the person is found or their status changes</li>
	<li>Share the ability to update a report with family members and friends</li>
</ul>
<br>
<br>
<table style=\"width: 100%;\"><tr><td>
	<div id=\"reportPerson\" style=\"float: left;\" onclick=\"location.href='index.php?mod=mpr&act=report_select';\">
		<img src=\"theme/default/img/icon-girl-missing.png\" alt=\"Report a Person\" style=\"margin: 0px 20px 0px 0px;\" align=\"middle\">Report a Person
	</div>
	<div id=\"searchPerson\" style=\"float: left;\" onclick=\"location.href='index.php?mod=mpr&act=search&type=all';\">
		<img src=\"theme/default/img/icon-search.png\" alt=\"Search for a Person\" style=\"margin: 0px;\" align=\"middle\">Search for a Person
	</div>
</td></tr></table>
<br>
<br>
<br>
<br>
<br>
<br>
Participating local hospitals can report basic information about arriving disaster victims.&nbsp; (Suburban Hospital’s implementation is furthest along.)<br><br>
The site does no automatic notification at this time, so check back periodically.&nbsp; But hospital personnel may contact you.<br><br>
";
	echo $html;

	// <a href=\"index.php?mod=mpr&amp;act=addmp&amp;type=missing\">Report a Missing Person</a>
	// <a href=\"index.php?mod=mpr&amp;act=list_missing\">List all Missing People</a>
	// <a href=\"index.php?mod=mpr&amp;act=addmp&amp;type=found\">Report a Found Person</a>
	// <a href=\"index.php?mod=mpr&amp;act=list_found\">List all Found Persons</a>
	// <a href=\"index.php?mod=mpr&amp;act=search&amp;type=all\">Search for a Person</a>
	// <a href=\"index.php?mod=mpr&act=search&type=missing\">Edit Missing Person?</a>
	
	/*
	<tr><td colspan=\"2\" style=\"text-align: center;\">
				<img src=\"theme/lpf/img/icon-search.png\" alt=\"Search\" align=\"center\"><a href=\"index.php?mod=mpr&amp;act=search&amp;type=all\">Search for a Person</a>
			</td></tr>
			*/
	
	
	// old MPR homepage
	} else if ($alternate_homepage == "-1") {
		?>
		<p>
		<?php 
		echo  _t('The Missing person registry is an online bulletin board of missing and found people. It captures information about the people missing and found, as well as information on the person seeking them, increasing the chancesof people finding each other. For example if two members of a family unit are looking for the head of the family, we can use this data to at least connect those two family members.'); 
		?>
		</p>
		<br/></br>
		<div>
			<h3><b><em><?php echo  (_t("Features Include:")) ?></em></b></h3>
		</div>
		<br/></br>
		<ul>
			<li><?php echo  _t('Submitting information about the individual such as identification numbers, physical appearance, last seen location, status, etc'); ?></li>
			<li><?php echo  _t('\'Sounds-like\' name search allowing search even the spelling of the name is not known exactly'); ?></li>
			<li><?php echo  _t('Facilitate uploading of missing person\'s photograph'); ?></li>
			<li><?php echo  _t('Grouping by \'Family Unit\' or other group category'); ?></li>
		</ul>
		<strong><?php echo _t("Description of Actions:"); ?></strong><br/>
		<ul>
			<li><a href="index.php?mod=mpr&act=search&type=all"><b><?php echo  _t('Search for a person'); ?> </b></a><br/><?php echo  _t('Search to see whether a lost person is registered in the system'); ?></li>
			<li><a href="index.php?mod=mpr&act=addmp&type=missing"><b><?php echo  _t('Report a missing person'); ?> </b> </a><br/><?php echo  _t('Report details about a missing person'); ?></li>
			<li><a href="index.php?mod=mpr&act=search&type=missing"><b><?php echo  _t('Edit missing person'); ?></b></a><br/><?php echo  _t('Update the details of missing person entered to the database previously'); ?></li>
			<li><a href="index.php?mod=mpr&act=addmp&type=found"><b><?php echo  _t('Report a found person'); ?></b></a><br/><?php echo  _t('Report information if the displaced person is found'); ?>
			<li><a href="index.php?mod=mpr&act=list_missing"><b><?php echo  _t('List missing people'); ?></b></a><br/><?php echo  _t('List all information on missing persons available in the database'); ?></li>
			<li><a href="index.php?mod=mpr&act=list_found"><b><?php echo  _t('List found people'); ?></b></a><br/><?php echo  _t('List all the information on people found'); ?></li>
		</ul>
		<br/>
		<?php
		
	// use selected modResource page selected in MPR general configuration
	} else {
		$q = "select * from rez_pages where rez_page_id = '".$alternate_homepage."';";
		$res = $global['db']->Execute($q);
		if ($row = $res->FetchRow() ){
			echo $row['rez_content'];
		}
	}
	?>
</div>
<?php

global $global,$conf;
require($global['approot'].'mod/mpr/mpr_lib.inc');

?><div id="home_recent">
	<?php
	if (shn_db_get_config("mpr", "show_updates_found")) {
		?><h1><?php echo  _t('Latest updates on Found People'); ?></h1><?php
		$det_arr = shn_mpr_get_latest("found", (shn_db_get_config("mpr", "pictures_per_page")===FALSE) ? 6 : shn_db_get_config("mpr", "pictures_per_page"));
		shn_mpr_search_show_verticle($det_arr);
	}
	if (shn_db_get_config("mpr", "show_updates_missing")) {
		?><h1><?php echo  _t('Latest updates on Missing People'); ?></h1><?php
		$det_arr = shn_mpr_get_latest("missing", (shn_db_get_config("mpr", "pictures_per_page")===FALSE) ? 6 : shn_db_get_config("mpr", "pictures_per_page"));
		shn_mpr_search_show_verticle($det_arr);
	}
	?>
</div>
<?php



/**
 * Shows the latest updates on missing and found perople
 * 
 * @param string $type 
 * @param int $limit 
 * @access public
 * @return void
 */
 
function shn_mpr_get_latest($type,$limit=6) {
	global $global;
	$incident_join = "INNER JOIN resource_to_incident e ON a.p_uuid = e.x_uuid ";
	$sql_missing = "
		SELECT
			a.p_uuid AS p_uuid, a.full_name AS full_name, 
			b.height AS height, b.weight AS weight, 
			b.opt_eye_color AS opt_eye_color, 
			b.opt_skin_color AS opt_skin_color, b.opt_hair_color AS opt_hair_color, 
			c.last_seen AS last_seen, c.last_clothing AS last_clothing, 
			c.comments AS comments 
		FROM person_uuid a 
		LEFT OUTER JOIN person_physical b USING (p_uuid) 
		INNER JOIN person_missing c USING (p_uuid)
		INNER JOIN person_status d USING (p_uuid) 
		$incident_join 
		WHERE d.opt_status = 'mis' AND e.incident_id = '{$_SESSION['user_pref_ims_incident_id']}' 
		ORDER BY d.updated DESC";

	$sql_found = "
		SELECT
			a.p_uuid AS p_uuid, a.full_name AS full_name, 
			b.height AS height, b.weight AS weight, 
			b.opt_eye_color AS opt_eye_color, 
			b.opt_skin_color AS opt_skin_color, b.opt_hair_color AS opt_hair_color, 
			c.last_seen AS last_seen, c.last_clothing AS last_clothing, 
			c.comments AS comments 
		FROM person_uuid a 
		LEFT OUTER JOIN person_physical b USING (p_uuid) 
		INNER JOIN person_missing c USING (p_uuid)
		INNER JOIN person_status d USING (p_uuid) 
		$incident_join
		WHERE d.opt_status != 'mis' AND e.incident_id = '{$_SESSION['user_pref_ims_incident_id']}'
		ORDER BY d.updated DESC";

	$final_sql="";
	if($type=='missing') {
		$final_sql=$sql_missing;
		$rs = $global['db']->SelectLimit($sql_missing,$limit,$offset);
		
	} elseif ($type=='found') {
		$final_sql=$sql_found;     
		$rs = $global['db']->SelectLimit($sql_found,$limit,$offset);
	}
	$rs = $global['db']->SelectLimit($final_sql,$limit);
	if ($rs) {
		$arr = $rs->GetAll();
	}
	return $arr;
}