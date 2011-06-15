<?
/**
 * @name         PL User Services
 * @version      1.9.3
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0614
 */


global $global;
require_once($global['approot'].'/mod/lpf/lib_lpf.inc');

// figure out what to do and call the functions to do it
$confirm  = isset($_GET['confirm'])  ? $_GET['confirm']  : null;
$username = isset($_GET['username']) ? $_GET['username'] : null;

if($confirm == null || $username == null) {
	gotoInvalid();
} else {
	$q = "
		SELECT *
		FROM users
		WHERE user_name = '".mysql_real_escape_string($username)."';
	";
	$r = $global['db']->Execute($q);
	if($row = $r->FetchRow()) {
		if($row['active'] == "active") {
			gotoAlreadyActive();
		} else if($row['active'] == "pending" && $confirm == $row['confirmation']) {
			activateUser($username);
			gotoActivated();
		} else {
			gotoInvalid();
		}
	} else {
		gotoInvalid();
	}
}

function gotoInvalid()       {header("Location: ".makeBaseUrlMinusEvent()."?mod=rez&act=default&page_id=-3");}
function gotoAlreadyActive() {header("Location: ".makeBaseUrlMinusEvent()."?mod=rez&act=default&page_id=-4");}
function gotoActivated()     {header("Location: ".makeBaseUrlMinusEvent()."?mod=rez&act=default&page_id=-5");}

function activateUser($username) {
	global $global;
	$q = "
		UPDATE users
		SET status = 'active'
		WHERE = '".mysql_real_escape_string($username)."';
	";
	$r = $global['db']->Execute($q);
}