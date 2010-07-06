<?php
/**
 * Lost Person Finder v3 Theme HTML footer
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Greg Miernicki <g@miernicki.com>
 */
?>
<div id="blueBack">&nbsp;</div>
<div id="disaster_selekta">Event <?selekta(); ?><script>checkEvent('<? echo $_REQUEST['shortname']; ?>', '<? getDefaultEvent(); ?>');</script></div>
<div id="footer">
	<center>
	<table id="footerTable" style="width: 975px;">
		<tr>
		<td width="33%">
			<a href="http://www.nlm.nih.gov"><img src="theme/lpf3/img/nlm.png"></a>
			<a href="http://www.nih.gov"><img src="theme/lpf3/img/nih.png"></a>
			<a href="http://www.hhs.gov"><img src="theme/lpf3/img/hhs.png"></a><br>
			Hosted and Customized by the<br>
			National Library of Medicine
		</td>
		<td width="33%">
			<a href="http://www.bethesdahospitalsemergencypartnership.org/"><img src="theme/lpf3/img/bhepp.png"></a>
			<a href="http://www.suburbanhospital.org/"><img src="theme/lpf3/img/suburban.png"></a>
			<a href="http://www.bethesda.med.navy.mil/"><img src="theme/lpf3/img/nnmc.png"></a>
			<a href="http://clinicalcenter.nih.gov/"><img src="theme/lpf3/img/clinicalcenter.png"></a><br>
			Funded through the <br>
			Bethesda Hospital Emergency Preparedness Partnership
		</td>
		<td width="33%">
			<a href="https://sahanafoundation.org"><img src="theme/lpf3/img/sahana.png"></a><br>
			Powered by the <br>
			Sahana Disaster Management System
		</td>
		</tr>
	</table>
	<br><span>In this site's testing phase, it contains no PII (Publicly Identifiable Information) of actual patients or persons.</span>
	</center>
<?
/*
echo "<br>shortname(".$_GET['shortname'].")";
echo "<br><pre>".print_r($_REQUEST, true)."</pre>";
echo "<pre>".print_r($_SERVER, true)."</pre>";
//echo "<br><pre>".print_r($global, true)."</pre>";
//echo "<br><pre>".print_r($conf, true)."</pre>";
*/
?>
</div>
<?

// Displays the Event/Disaster Dropdown menu and allows redirection via the js code
function selekta() {
	global $global;
	global $conf;

	echo "<select onchange=\"changeEvent(this.value);\">";

	$sql = "SELECT * FROM incident WHERE parent_id IS NULL";  
	$arr = $global['db']->GetAll($sql);
	if (!empty($arr)) {
		foreach($arr as $row) {
			if ($_REQUEST['shortname'] == $row['shortname']) {
				$text = "selected=\"selected\"";
			} else {
				$text = "";
			}
			echo "<option value=\"".$row['shortname']."\" ".$text.">".$row['name']."</option>";
		}
	}
	echo "</select>";
}


// Check whether we are on the default event when we enter the site
function getDefaultEvent() {
	global $global;
	global $conf;

	$sql = "SELECT shortname FROM incident WHERE `default` = 1 LIMIT 1;";  
	$arr = $global['db']->GetAll($sql);
	if (!empty($arr)) {
		foreach($arr as $row) {
			echo $row['shortname'];
		}
	}
}

