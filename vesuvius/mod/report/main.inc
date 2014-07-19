<?
/**
 * @name         Report (a person)
 * @version      22
 * @package      report
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0213
 */



// default action
function shn_report_default() {

	global $global;
	require_once($global['approot'].'/mod/lpf/lib_lpf.inc');

	if(isset($_GET['create'])) {
		shn_report_create();
		return;
	}

	// check if event is closed...
	$q = "
		SELECT *
		FROM incident
		WHERE shortname = '".mysql_real_escape_string($_GET['shortname'])."';
	";
	$result   = $global['db']->Execute($q);
	if($result === false) { daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, $global['db']->ErrorMsg(), "report default 1 ((".$q."))"); }
	$row      = $result->FetchRow();
	$closed   = $row['closed'];
	$external = $row['external_report'];

	// status 1 means event is closed to all reporting
	if($closed == 1) {
		echo _t("ReportAPerson-ReportingClosed-Message|
			<h2>Reporting Closed</h2>
			<br>
			This event is closed and is no longer accepting new person reports.
		");
		return;

	// status 2 means we can still report via an external iframe widget
	} elseif($closed == 2) {
		echo _t("ReportAPerson-External-Heading|
			<h2>External Reporting</h2>
			").htmlspecialchars_decode($external)."<br>
		";
		return;
	}

	// check if the person is not logged in or is anonymous (must be logged in and not anonymous to report)
	if(!isset($_SESSION['logged_in']) || $_SESSION['logged_in'] != 1 || !isset($_SESSION['group_id']) || $_SESSION['group_id'] == 3) {
		echo '
			<div class="message information"><br/>'._t('ReportAPerson-Message|You must log in before you can report a new person to the registry.').'
			<br><br></div>
			<br>
		';
		require_once($global['approot'].'mod/pref/main.inc');
		shn_pref_loginForm();
		return;
	}

	// all good, so present them with a button to click that creates a stub person
	echo _t('Report-Header|
		<h2>Report a Person</h2>').
		'<br>
		'._t('ReportAPerson-QuickSearch-Link|You may wish to perform a <a href="search">quick search</a> before reporting. Otherwise...').'<br>
		<br>
		<br>
		<input id="login" class="styleTehButton" type="button" value="'._t('ReportAPerson-CreateNew-Button|Create a New Person Report').'" onclick="report();">
		<script>
			function report() {
				window.location = \'report?create\';
			}
		</script>
	';
}



/** build the stub record and redirect the user to it... */
function shn_report_create() {

	global $conf;

	$p = new person();
	$p->createUUID();
	$p->rep_uuid = $_SESSION['user_p_uuid'];
	$p->setEvent($_GET['shortname']);
	$p->opt_status = "unk";
	$p->creation_time = date('Y-m-d H:i:s');
	$p->last_updated  = date('Y-m-d H:i:s');
	$p->useNullLastUpdatedDb = true;
	$p->expiry_date = "0000-01-01 00:00:00"; // special value for expiry date denotes a new record!
	$p->makePfifNote = false;
	$p->arrival_website = true;
	$p->insert();
	$p->rapReportLog();

	$url = $conf['https'].$p->p_uuid;
	header("Location: ".$url);

	// fall back redirect if header() fails for some reason
	echo "
		<script>
			window.location = '".$url."';
		</script>
		<a href=\"".$url."\">"._t("ReportAPerson-NoRedirect-Link|click here if not automatically redirected...")."</a>
	";
}



