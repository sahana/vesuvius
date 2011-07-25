<?
/**
 * @name         Internal
 * @version      1.0
 * @package      home
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0609
 */


// This is not a real Sahana module, but a module built for hosting internal NLM Project information


function shn_int_headerz() {
	echo '
		<ul>
		<li><a href="index.php?mod=int&act=servers">Internal Server List</a></li>
		<li><a href="index.php?mod=int&act=photos">Photos</a></li>
		<li><a href="index.php?mod=int&act=videos">Videos</a></li>
		<li><a href="index.php?mod=int&act=links">Links</a></li>
		<li><a href="index.php?mod=int&act=template">Sonya\'s Template</a></li>
		<li><a href="index.php?mod=int&act=unit">PLUS Web Service Unit Tests</a></li>
		<li><a href="index.php?mod=int&act=status">Tehseen\'s Status Report</a></li>
		</ul>
		<hr style="color: #fff; background-color: #fff; border-bottom: 1px solid #ddd; height: 0px;">
		<br>
	';
}



function shn_int_default() {
	global $global;
	shn_int_headerz();
	echo '
		<h2>Internal Resources for the Lost Person Finder Project</h2>
	';
}



function shn_int_servers() {
	global $global;
	shn_int_headerz();
	echo '
		<h2>Internal Servers</h2>
		<br>
		<a href="http://130.14.52.20/">http://130.14.52.20/</a> points to archive.nlm.nih.gov<br>
		<br>
		<a href="http://130.14.109.50/">http://130.14.109.50/</a> points to whistler.nlm.nih.gov<br>
		<br>
		<a href="http://130.14.109.88/">http://130.14.109.88/</a> points to archivestage.nlm.nih.gov<br>
		<br>
		<a href="http://130.14.109.100/">http://130.14.109.100/</a> points to plstage.nlm.nih.gov<br>
		<br>
		<a href="http://130.14.109.150/">http://130.14.109.150/</a> points to imedlinestage.nlm.nih.gov<br>
		<br>
	';
}



function shn_int_photos() {
	global $global;
	shn_int_headerz();
	echo '
		<h2>Photos</h2>
		<br>
		CMAX2008<br>
		<a href="tmp/int_cache/photos/CMAXgreg.zip">Greg Miernicki</a><br>
		<a href="tmp/int_cache/photos/CMAXgill.zip">Mike Gill</a><br>
		<a href="tmp/int_cache/photos/CMAXglenn.zip">Glenn Pearson</a><br>
		<br>
		CMAX2009<br>
		<a href="tmp/int_cache/photos/CMAX2009-Karen-Steely.zip">Karen Steely</a><br>
		<a href="tmp/int_cache/photos/CMAX2009-Sameer.zip">Sameer Antani</a><br>
		<a href="tmp/int_cache/photos/CMAX2009-LeLan.zip">Lan Le</a><br>
		<a href="tmp/int_cache/photos/CMAX2009-CindyLove.zip">Cindy Love</a><br>
		<a href="tmp/int_cache/photos/CMAX2009-DBennett.zip">Debbei Bennett</a><br>
		<a href="tmp/int_cache/photos/CMAX2009-SarahWard.zip">Sarah Ward</a><br>
		<a href="tmp/int_cache/photos/CMAX2009-HeatherSimons.zip">Cindy Love</a><br>
		<a href="tmp/int_cache/photos/CMAX2009-TehSeen.zip">Tehseen Sabir</a><br>
		<br>
		CMAX2010<br>
		<a href="tmp/int_cache/photos/CMAX2010-Article.zip">Article</a><br>
		<a href="tmp/int_cache/photos/CMAX2010-NNMC-DebBennett.zip">NNMC Debbie Bennett</a><br>
		<a href="tmp/int_cache/photos/CMAX2010-NNMC-KarenSteely.zip">NNMC Karen Steely</a><br>
		<a href="tmp/int_cache/photos/CMAX2010-NNMC-MikeGill.zip">NNMC Mike Gill</a><br>
		<a href="tmp/int_cache/photos/CMAX2010-NNMC-RicohCamera.zip">NNMC Ricoh Camera</a><br>
		<a href="tmp/int_cache/photos/CMAX2010-NNMC-TriagePic.zip">NNMC TriagePic cache</a><br>
		<a href="tmp/int_cache/photos/CMAX2010-Suburban-RicohCamera.zip">Suburban Ricoh Camera</a><br>
		<a href="tmp/int_cache/photos/CMAX2010-Suburban-SaraWard.zip">Suburban Sarah Ward</a><br>
		<a href="tmp/int_cache/photos/CMAX2010-Suburban-TehseenSabir.zip">Suburban Tehseen Sabir</a><br>
		<a href="tmp/int_cache/photos/CMAX2010-Suburban-TriagePic.zip">Suburban TriagePic cache</a><br>
	';
}



function shn_int_videos() {
	global $global;
	shn_int_headerz();
	echo '
		<h2>Videos</h2>
		<br>
		<a href="tmp/int_cache/videos/BHEPP.avi">BHEPP Promo Video 2010</a><br>
		<br>
	';
}




function shn_int_links() {
	global $global;
	shn_int_headerz();
	echo '
		<h2>Sahana Instances</h2>
		<a href="https://pl.nlm.nih.gov">PL</a><br>
		<a href="https://plstage.nlm.nih.gov">PL Stage</a><br>
		<a href="http://plstage.nlm.nih.gov/~gmiernicki/sahanaDev/www/index.php">PL Dev Greg</a><br>
		<a href="http://hepl.nlm.nih.gov">HEPL</a><br>
		<br>

		<h2>Sahana Links</h2>
		<a href="http://agasti.sahanafoundation.org">Sahana Agasti Launchpad</a><br>
		<a href="http://www.sahanafoundation.org">Sahana Foundation</a><br>
		<a href="http://wiki.sahanafoundation.org">Sahana Wiki</a><br>
		<br>

		<h2>OtherLinks</h2>
		<a href="http://nihrecord.od.nih.gov/newsletters/2010/07_09_2010/story4.htm">LPF in NIH Record</a><br>
		<a href="http://www.gazette.net/stories/10212009/silvnew184614_32547.shtml">CMAX2009 in the Gazette</a><br>
		<a href="http://code.google.com/p/nameparser/">nameParser</a><br>
		<a href="http://www.bethesdahospitalsemergencypartnership.org/pub_videos.html">BHEPP Videos</a><br>
		<br>
	';
}



function shn_int_template() {
	global $global;
	shn_int_headerz();
	echo '<h2>Find Family and Friends</h2>
			<a href="https://safeandwell.communityos.org/cms//" title="Red Cross Safe and Well List">Red Cross Safe and Well List</a><br>
			<a href="http://www.familylinks.icrc.org" title="International Committee of the Red Cross FamilyLinks" >International Committee of the Red Cross FamilyLinks</a></h1><br>
			<a href="http://www.nokr.org/nok/restricted/home.htm" title="Next of Kin National Registry">Next of Kin National Registry</a><br>
			<a href="http://www.lrcf.net/create-flyer/" title="Missing Person Flier Creation Tools" >Missing Person Flier Creation Tools</a><br>
			<br>
			<h2>Disaster Resources</h2>
			<a target="" title="Disaster Assistance" href="http://www.disasterassistance.gov/">Disaster Assistance</a><br>
			<a href="http://app.redcross.org/nss-app/" title="Red Cross Provides Shelters and Food">Red Cross Provides Shelters and Food</a><br>
			<a target="" title="" href="http://disaster.nlm.nih.gov/">Disaster Information Management Resource Center or specific page</a><br>
			<a target="" title="" href="http://www.usa.gov/Japan2011.shtml">USA.gov specific page</a><br>
			<a target="" title="" href="http://www.google.com/crisisresponse/">Google Crisis Response specific page</a>
			<br>';
}



function shn_int_unit() {
	global $global;
	shn_int_headerz();
	echo '
		<h2>PLUS Web Service Unit Tests</h2>
		<br>
		<i>NOTE: Please do not repeatedly visit these links, they are extremely taxing on the servers!</i><br>
		<br>
		<i>NOTE2: These tests will only work if you are behind the NLM firewall.</i><br>
		<br>
		<a href=    "http://whistler.nlm.nih.gov/~miernickig/sahanaDev/mod/plus/unitTest.php">Run Unit Tests on WHISTLER</a><br>
		<a href="http://archivestage.nlm.nih.gov/~miernickig/sahanaDev/mod/plus/unitTest.php">Run Unit Tests on ARCHIVESTAGE</a><br>
		<a href=     "http://plstage.nlm.nih.gov/~miernickig/sahanaDev/mod/plus/unitTest.php">Run Unit Tests on PLSTAGE</a><br>
		<br>
	';
}



function shn_int_status() {
	global $global;
	shn_int_headerz();
	echo '
		<h2>Tehseen\'s PL Status Reports</h2>
		<br>
		<a href="http://archivestage.nlm.nih.gov/~tsabir/lpf_history.php?result=0">Click here to view the reports.</a><br>
		<br>
	';
}