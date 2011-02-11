<?php
/**
 * Lost Person Finder v2 Theme HTML footer
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Greg Miernicki <miernickig@mail.nih.gov>
 */
?>
<div id="footer">
	<center>
	<table id="footerTable" style="width: 975px;">
		<tr>
		<td width="33%">
			<a href="http://www.nlm.nih.gov"><img src="theme/lpf2/img/logoNLM48px.png"></a>
			<a href="http://www.nih.gov"><img src="theme/lpf2/img/logoNIH48px.png"></a>
			<a href="http://www.hhs.gov"><img src="theme/lpf2/img/logoHHS48px.png"></a><br>
			Hosted and Customized by the<br>
			National Library of Medicine
		</td>
		<td width="33%">
			<a href="http://www.bethesdahospitalsemergencypartnership.org/"><img src="theme/lpf2/img/logoBHEPP48px.png"></a>
			<a href="http://www.suburbanhospital.org/"><img src="theme/lpf2/img/logoSuburban48px.png"></a>
			<a href="http://www.bethesda.med.navy.mil/"><img src="theme/lpf2/img/logoNNMC48px.png"></a>
			<a href="http://clinicalcenter.nih.gov/"><img src="theme/lpf2/img/logoClinical48px.png"></a><br>
			Funded through the <br>
			Bethesda Hospital Emergency Preparedness Partnership
		</td>
		<td width="33%">
			<a href="http://www.sahana.lk"><img src="theme/lpf2/img/logoSahana48px.png"></a><br>
			Powered by the <br>
			Sahana Disaster Management System
		</td>
		</tr>
	</table>
	<br><span>In this site's testing phase, it contains no PII (Publicly Identifiable Information) of actual patients or persons.</span>
	</center>
<?
echo "<br>disaster(".$_GET['disaster'].")";
echo "<br><pre>".print_r($_REQUEST, true)."</pre>";
echo "<pre>".print_r($_SERVER, true)."</pre>";
//echo "<br><pre>".print_r($global, true)."</pre>";
//echo "<br><pre>".print_r($conf, true)."</pre>";
?>
</div>
<?
