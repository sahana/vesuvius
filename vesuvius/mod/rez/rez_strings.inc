_t('RESOURCE_PAGES_TITLE|TriagePic Release Notes')
_t('RESOURCE_PAGES_CONTENT|<div style="overflow: show;">
<script type="text/javascript" src="res/js/jquery-1.4.4.min.js"></script>
<script type="text/javascript" src="res/js/animatedcollapse.js"></script>
<script>
animatedcollapse.addDiv('v122', 'fade=1,hide=1');
animatedcollapse.addDiv('v119', 'fade=1,hide=1');
animatedcollapse.addDiv('v117', 'fade=1,hide=1');
animatedcollapse.addDiv('v116', 'fade=1,hide=1');
animatedcollapse.addDiv('v115', 'fade=1,hide=1');
animatedcollapse.addDiv('v114', 'fade=1,hide=1');
animatedcollapse.init();
animatedcollapse.ontoggle=function($, divobj, state){}
</script>

<h1><span class="Apple-style-span" style="font-size: 13px; color: rgb(0, 0, 0); font-weight: normal; ">From January, 2011.  Earlier notes are available off-line.</span></h1><br>

<h2>June, 2011</h2>
<h3>Version 1.22</h3>
<hr style="height: 1px; background-color: rgb(255, 255, 255); border-width: 1px medium medium; border-style: solid none none; border-color: rgb(229, 234, 239) -moz-use-text-color -moz-use-text-color; margin-bottom: 15px;">
<ul>
<li>This version gets more information from â€œPL web servicesâ€, associated with the central NLM People Locator web site (pl.nlm.nih.gov).  So far, these are read-only web services.</li>
<li>TriagePic has been made less tall, and the photo viewer improved.</li>
<li>These changes triggered improvements to the layout and functionality.</li>
</ul>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="javascript:animatedcollapse.toggle('v122')">Show/Hide Details...</a>
<br>
<br>
<div id="v122" display="none;">
<ul>
<li>Specifically regarding the web services, the source of information under the â€œHospitalâ€ and â€œPolicyâ€ tabs has changed.  Previously, this was stored only on the local machine.  It now comes instead from PL web services.  This information comprises the organizationâ€™s contact information and the format of the mass casualty patient ID (i.e., prefix, count of numeric digits if fixed).</li>
<li>The foregoing â€œHospitalâ€ and â€œPolicyâ€ data is still cached locally for use when web services are unavailable.  The nature of the caching has changed.  Information previously in â€œHospitalSettings.xmlâ€ has been split into â€œHospitalContactInfo.xmlâ€, â€œHospitalPolicy.xmlâ€, and â€œHospitalStaffing.xmlâ€.  The last of these is not drawn from a web service.<br></li>
<li>After upgrade (but not fresh install), as the app starts for the first time, a dialog box will say:<br>
<br>
Updating data files in directory 'C:\Shared TriagePic Settings':</li>
<ul>
<li>HospitalSettings.xml is renamed to HospitalSettings[obsolete].xml.</li>
<li>Info about staffing of TriagePic station will now be stored in HospitalStaffing.xml</li>
<li>Info under 'Hospital' tab will be now gathered from a web service, and cached in HospitalContactInfo.xml</li>
<li>Info under 'Policies' tab, like Patient ID format, is also from a web service, &amp; cached in HospitalPolicy.xml</li>
</ul>
<li>After upgrade (or on fresh install), as the app starts up for the first time, a small dialog box will ask for the hospital.  There are currently only 3 choices [Suburban, NNMC, NLM (testing)], but this number can vary in the future.  Unlike before, these choices come from a PL web service, as discussed.  Once selected, the value will be retained.</li>
<li>The height of TriagePicâ€™s window is now reduced slightly to work better on some Windows platforms, making it more square.  The layout of the contents of tab pages have been changed somewhat to accommodate this (as mentioned further below).  Also, the unhelpful Maximize button in the title bar is disabled.</li>
<li>Under the â€œMain Tabâ€, individual fields for first name, middle names, nicknames, last names and suffix are simplified to two fields, with examples.  The gender and peds/adult settings have been moved.  These changes facilitate reducing TriagePicâ€™s window height.</li>
<li>The filmstrip control that shows photos has been modified.  The main photo was previously being undesirably clipped on its bottom and right side.  It is now shown in its entirety (though at the expense of giving up on centering; left/top is now abutted).  The thumbnail strip at bottom is now less high, so thereâ€™s more room for the main photo.</li>
<li>Under the â€œChecklist (Event, Staff)â€ tab, contents have been simplified, and the â€œSelect Known Eventâ€ combo box made wider.   (The map and inactive controls that were mockups for FEMA-network distribution have been moved to the â€œ[TO DO] Define New Eventâ€ popup.)</li>
<li>Checklist staff names entered are remembered locally as before.  These entries are not hospital-specific (also as before, but now more obvious).  Upon upgrade from version 1.20, the staff fields are blank (i.e., not carried over from HospitalSettings.xml).</li>
<li>Under the â€œDistributionâ€ tab, leftover â€œ[TO DO]â€¦â€ comments are now gone.  Instead, the â€œWeb Servicesâ€ setting has been moved here from the â€œHospitalâ€ tab, and its URL changed as described next.</li>
<li>Previously, the web services were now found through a URL stored in OtherSettings.xml.  It is desirable to add to the URL a parameter for a specific version of the web services.  This would guarantee selection by a particular version of TriagePic of the correct version of the web services, out of many simultaneously offered.  Currently (and provisionally), the OtherSettings value is ignored, and the URL with version parameter comes from app.config.</li>
<li>Before, the TriagePic user could only easily specify the deployment hospital at install time (or by XML file manipulation).  One can now specify the hospital any time, using a new combo control under the â€œHospitalâ€ tab.  The choices presented come from a PL web service, and currently are Suburban, NNMC, or NLM (testing).  The choice once made is remembered (in the cache file OtherSettings.xml).  Changing the choice will be reflected throughout, including in the title barâ€™s â€œâ€¦Deployed atâ€¦â€ designation.</li>
<li>After changing the hospital, you get a reminder:<br>
<br>
You've selected a new hospital.  Be sure to:
<ul>
<li>Adjust the next Patient ID number on the 'Main' tab.</li>
<li> Make it compatible with the format of the new hospital,
    as expressed under the 'Policies' tab.</li>
<li>Change the staffing under the 'Checklist' tab.</li>
</ul>
</li><li>An attempt to change the hospital may not succeed when certain web services are unavailable.  Instead, a warning message appears and the hospital remains unchanged.</li>
<li>The â€œNLM (testing)â€ choice now has more information.</li>
<li>While a particular hospital can be chosen, the detailed information about it is now treated as read-only within TriagePic.  (It may be edited by someone logged into PL with â€œhospital administratorâ€ credentials, from PLâ€™s â€œHospital Administrationâ€ page.)</li>
</ul>
</div>

<h2>March, 2011</h2>
<h3>Version 1.21</h3>
<hr style="height: 1px; background-color: rgb(255, 255, 255); border-width: 1px medium medium; border-style: solid none none; border-color: rgb(229, 234, 239) -moz-use-text-color -moz-use-text-color; margin-bottom: 15px;">
<ul>
<li>This fixes incorrect UTC timestamps within .lpf and .pfif email attachments.</li>
<li>TriagePic testers inside NLM only: If the update to 1.21 doesn't occur, due to a change in distribution method, you'll need to uninstall and reinstall TriagePic.</li>
</ul>

<h3>Version 1.20</h3>
<hr style="height: 1px; background-color: rgb(255, 255, 255); border-width: 1px medium medium; border-style: solid none none; border-color: rgb(229, 234, 239) -moz-use-text-color -moz-use-text-color; margin-bottom: 15px;">
<ul>
<li>The NLM certificate used to sign TriagePic updates has itself been updated for 2011.  You may be asked to take extra steps to accept the new certificate when upgrading to 1.20.</li>
<li>The name of the selected disaster event is sent to PL in both a short and long form within the .lpf file.  This allows better compatibility, and was first shown at the DIMRC Disaster Information Outreach Symposium at NLM.</li>
</ul>

<h2>February, 2011</h2>
<h3>Version 1.19</h3>
<hr style="height: 1px; background-color: rgb(255, 255, 255); border-width: 1px medium medium; border-style: solid none none; border-color: rgb(229, 234, 239) -moz-use-text-color -moz-use-text-color; margin-bottom: 15px;">
<ul>
<li>As each patient's arrival is reported, another file attachment is now sent out, summarizing all the previous patients who have passed through the triage station for the current disaster.  This is a .kml file, that would appear on Google Earth as a pushpin at the hospital location.  When clicked, its balloon shows brief identifying data and a compact, color-coded table with the statistics seen in TriagePic's "Outbox" tab.</li>
</ul>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="javascript:animatedcollapse.toggle('v119')">Show/Hide Details...</a>
<br>
<br>
<div id="v119" display="none;">
<ul>
<li>The same .kml file is included with both anonymized and normal distributions</li>
<li>The balloon contents are in html form, and could be easily extracted for other purposes.</li>
<li>Be aware that some email systems will empty .kml attachments, causing errors when attempting to view them on Google Earth.</li>
<li>This feature was motivated by, and first shown at, the Camp Roberts East/RELIEF exercise at VA Tech/Naval Postgraduate School, Balston, VA.</li>
</ul>
</div>

<h3>Version 1.18</h3>
<hr style="height: 1px; background-color: rgb(255, 255, 255); border-width: 1px medium medium; border-style: solid none none; border-color: rgb(229, 234, 239) -moz-use-text-color -moz-use-text-color; margin-bottom: 15px;">
<ul>
<li>Quick, temporary fix to event name reported in the .lpf file attachment, to address a problem with parsing when received at the PL site.</li>
</ul>

<h3>Version 1.17</h3>
<hr style="height: 1px; background-color: rgb(255, 255, 255); border-width: 1px medium medium; border-style: solid none none; border-color: rgb(229, 234, 239) -moz-use-text-color -moz-use-text-color; margin-bottom: 15px;">
<ul>
<li>Latitude and longitude fields are added to the Hospital tab.</li>
<li>There is now flexibility in determining where TriagePic should find its web services.</li>
<li>The event list, that populates the combo box on the Checklist tab, is now read from the PL web service, instead of relying exclusively on the cached eventList.xml file.</li>
</ul>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="javascript:animatedcollapse.toggle('v117')">Show/Hide Details...</a>
<br>
<br>
<div id="v117" display="none;">
<ul>
<li>The latitude and longitude are persisted in the HospitalSettings.xml file.  New and existing installs will get default coordinates as appropriate for NLM (and Generic), NNMC, and Suburban Hospital.  Lat/Long will eventually be tied into web services, and in the immediate term allows geolocation specification for the Camp Roberts East/RELIEF exercise.</li>
<li>The web services end point address is persisted in OtherSettings.xml and shown (perhaps temporarily) under the Hospital Settings tab, under a heading "Web Service Settings".  New and existing installs will get the default: "https://pl.nlm.nih.gov/?wsdl".</li>
</ul>
</div>

<h3>Version 1.16</h3>
<hr style="height: 1px; background-color: rgb(255, 255, 255); border-width: 1px medium medium; border-style: solid none none; border-color: rgb(229, 234, 239) -moz-use-text-color -moz-use-text-color; margin-bottom: 15px;">
<ul>
<li>Fixes two problems when saving email settings and outbox entries.</li>
<li>Allows local outbox history deletions.</li>
<li>Aligns disaster event categories better with PL.</li>
</ul>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="javascript:animatedcollapse.toggle('v116')">Show/Hide Details...</a>
<br>
<br>
<div id="v116" display="none;">
<ul>
<li>A recently introduced bug, where email setting changes were not saved, is fixed.</li>
<li>In the Outbox, the â€œPicâ€ column was earlier converted to counts (instead of Y/N), but this conversion wasnâ€™t getting saved in the outbox.xml file except for new entries.  Now it is.</li>
<li>Version 1.16 allows the user to go into the Outbox and delete one or more individual items from the outbox history.  These are local deletes for now - they are not reported to the central LPF database.</li>
<li>There are two ways to delete a particular selected Outbox row:  hit the â€œDeleteâ€ key (or DEL or Backspace) or open the Outbox Details window and hit the new â€œDeleteâ€ button.  The first method also allows multiple rows to be selected and deleted.  To facilitate this functionality, a single click on an Outbox row now selects it, instead of opening Outbox Details (which now takes a double click).</li>
<li>A delete is persisted by changing the contents of outbox.xml.  The contents removed from outbox.xml is moved to a separate file under the â€œdeletedâ€ directory, e.g., â€œ911-1234 Green [from outbox].xmlâ€.  Also moved are the associated *.lpf, *.pfif, and *.jpg files.</li>
<li>Deletion of one or more rows normally concludes with a dialog box saying:</li>
"Deleted patient data moved to the C:/Shared TriagePic Data/deleted/ folder:"<br>
followed by, for each deleted row, patient number, zone, and number of deleted files, e.g.:<br>
"2045 Green (4 files)"<br>
All the filenames will begin, in this case, with â€œ2045 Greenâ€¦â€ . There are typically 4 files, consisting of an outbox fragment .xml, an .lpf file, a .pfif file, and one .jpg file.  If problems arise during the deletion process, additional error dialog boxes may precede the normal one.<br>
<li>Specifically, when deleting a row, possible error messages are:</li>
<ol>
<li>"Could not open file C:/Shared TriagePic Data/sent/<some file="">"</some></li>
<li>For .lpf and .pfif attachments:</li>
"More than 1 file was found with the pattern C:/Shared TriagePic Data/sent/*.{some extension}<br>
All will be moved to the folder C:/Shared TriagePic Data/deleted/."<br>
<li>"It was planned to delete the file C:/Shared TriagePic Data/sent/{somefile.ext}<br>
by moving it to the archive C:/Shared TriagePic Data/deleted/,<br>
but a file of that name already exists there, which was renamed to <somefile (1).ext="">"</somefile></li>
<li>"There were no files to delete."  This might occur after an abnormal termination due to crash or debugging.</li>
</ol>
<li>If deleting the last row from history, a dummy blank row is automatically inserted into outbox.xml.  This prevents problems later.  The first real data replaces that row.</li>
<li>TriagePic previously had a 3-way categorization of events:  â€œTEST or DEMOâ€, â€œDRILLâ€, or â€œREAL â€“ NOT A DRILLâ€.  In the first category, a default instance was â€œUnnamed TEST or DEMOâ€.  PL has adopted a 2-way categorization:  â€œTESTâ€ or â€œREALâ€, which it is exposing through the web service (and cached by TriagePic); the default instance is â€œTest Eventâ€.  To align closer to PL, the TriagePic UI is now showing the two categories â€œTEST/DEMO/DRILLâ€ and â€œREAL â€“ NOT A DRILLâ€.  Additionl cleanups to support this re-categorization are discussed next.</li>
<li>If it is necessary to distinguish between a test and a drill (for instance, in filling out EDXL headers for the .lpf files), the mapping will be that â€œTest Eventâ€ is considered a test and all other events of PL type TEST are considered a drill.</li>
<li>Historical outbox entries where Event = â€œUnnamed TEST or DEMOâ€ are changed to Event = â€œTest Eventâ€.  This (and correction of related bugs) will allow the stat boxes for Current Event to show useful results when the current event for TriagePic is Test Event.</li>
<li>If the cached event list includes event â€œnew eventâ€, which PL once exposed, it is deleted.</li>
</ul>
</div>

<h2>January, 2011</h2>
<h3>Version 1.15</h3>
<hr style="height: 1px; background-color: rgb(255, 255, 255); border-width: 1px medium medium; border-style: solid none none; border-color: rgb(229, 234, 239) -moz-use-text-color -moz-use-text-color; margin-bottom: 15px;">
<ul>
<li>Fixes a few email settings bugs.</li>
</ul>

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="javascript:animatedcollapse.toggle('v115')">Show/Hide Details...</a>
<br>
<br>
<div id="v115" display="none;">
<ul>
<li>Version 1.15 fixes several problems with the newly introduced EmailSettings.xml file.  (And for those who upgraded to v 1.14 and had problems, a workaround replacement EmailSettings.xml file was distributed.)
</li><li>If migrating from TriagePic v 1.13 or earlier, email settings previously in SharedTriagePic.xml now migrate correctly to EmailSettings.xml.  In 1.14, only the default (new-install) contents for EmailSettings.xml appear.
</li><li>Related to that, if â€œNLM (Testing)â€ was in the profile in use (rather than Generic, Suburban Hospital, or NNMC), the default contents of the EmailSettings.xml file was incorrect (e.g., first line begins as "<options â€¦â€="" instead="" of="" â€œ=""><emailsettings â€¦â€)=""></emailsettings></options></li>
<li>The preceding problem caused the app to silently quit during startup, right after the â€œCould not connect to web serviceâ€¦â€ dialog.  Changed to be noisy, identifying the bad xml file.  Similar noisy reads are also now done for HospitalSettings.xml, OtherSettings.xml, and UsersAndVersions.xml.</li>
</ul>
</div>

<h3>Version 1.14</h3>
<hr style="height: 1px; background-color: rgb(255, 255, 255); border-width: 1px medium medium; border-style: solid none none; border-color: rgb(229, 234, 239) -moz-use-text-color -moz-use-text-color; margin-bottom: 15px;">
<ul>
<li>Improves the Outbox - the listing of sent items - particularly the information shown when clicking on a particular entry and seeing the dialog box now called â€œOutbox Detailsâ€.</li>
<li>Has some preliminary work on deletion capabilities, most of which is not exposed in this release.</li>
</ul>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="javascript:animatedcollapse.toggle('v114')">Show/Hide Details...</a>
<br>
<br>
<div id="v114" display="none;">
<ul>
<li>The Outbox â€œSentâ€ column before always showed â€œYâ€, whether the email send was successful or not.  It now should show â€œNâ€ if email send was not 100% successful to all recipients.  (Error cases have not been extensively tested.)  In code, the function myEmail.MySendMail now returns a Boolean value to indicate success, the two values of which (for anonymized and regular sends) determine the Outbox â€œSentâ€ value.  To achieve that, the function body, particularly inside the catch handlers, has been moderately modified.</li>
<li>The Outbox listing of sent items now includes nicknames/aliases in the â€œFirstâ€ name column, and avoids trailing spaces in the â€œFirstâ€ and â€œLastâ€ columns.  The format is now:</li>
&nbsp;&nbsp;&nbsp;First: William "Bill" A.<br>
&nbsp;&nbsp;&nbsp;Last: Stockton Jr.<br>
<li>The title bar of Outbox Details now includes the form name and an alias if present, and handles a missing patient name specially. Two examples:</li>
&nbsp;&nbsp;&nbsp;Outbox Details - [No Patient Name Given]<br>
&nbsp;&nbsp;&nbsp;Outbox Details - William "Bill" A. Stockton Jr.<br>
<li>Outbox Details is larger.  It now reveals both left and right filmstrip controls.  A new read-only area in the lower-left shows details of the selected record.  This is largely the same information thatâ€™s in the selected Outbox data row.  Since the Outbox data row items are sometimes truncated or scrolled from visibility, this gives a more complete picture at a glance.  Minor differences from Outbox, seen in Outbox Details, are:
</li><li>The â€œwhen sentâ€ timestamp is in a different format which includes the year, and shows the month as a number.  (There is a separate alternative-format timestamp field that could be shown, but we chose not to.)</li>
<li>The count of pictures is not needed, given that you can see them.</li>
<li>The read-only role (primary or secondary) &amp; optional caption for a selected photo is shown.  By default, the primary photo is selected when Outbox Details opens.  The selection can be changed just as under the Main Info tab.
</li><li>When opening an Outbox Details, you may get the warning message:<br>
"There is a mismatch between the 'Pic' count and the number of images found in the folder<br>
C:\TriagePicSharedData\sent<br>
If you just sent this email, wait a few seconds for background processing to complete and try again."</li>
<li>On startup, new folder C:/TriagePic Shared Data/deleted is created if not present.</li>
<li>The form, class, and .cs file â€œFormSentImagesâ€ has been renamed to â€œFormOutboxDetailsâ€.</li>
<li>For version 1.13, an â€œAboutâ€ entry is added to the System menu (upper left hand corner).  â€œAboutâ€ content  design is very much like the splash screen, but slightly bigger, with title bar, OK button, and mention of the LPF project.  The wordings on the splash screen and main title bar were slightly revised.
</li><li>During startup, a missing outbox.xml file is always checked for, not just when a new â€œoutbox queueâ€ directory is created.  If missing, a file defining an empty queue is substituted.</li>
<li>The file TriagePicSharedSettings.xml is split into 3 files:  EmailSettings.xml, HospitalSettings.xml, and OtherSettings.xml.  Internally, new I/O classes are created for them.  Startup code is added to do migration from the old to new structure, and to use the new structure for fresh installs (with Generic, NLM, NNMC, Suburban internal file resources).  For existing installs, after migration, the old settings file is retained but renamed TriagePicSharedSettings[obsolete].xml.
</li><li>The PatientID format setting is now retained, specifically in the HospitalSettings.xml file.  The representation is the fixed number of digits (not counting alphanumeric prefix); a variable number of digits is represented by -1.  For new installs, the default patient ID format for Suburban and NNMC is â€œfixed 4 digitâ€; for NLM and Generic, itâ€™s â€œvariableâ€ format.
</li><li>Under â€œHospitalâ€ tab, the leftover subheading â€œPolicies and Other Settingsâ€ was removedâ€¦ (See the separate â€œPoliciesâ€ tab instead, created in a prior version.)
</li><li>Edits to any field under the â€œHospitalâ€ tab now takes effect immediately, not just when TriagePic exits.  Likewise the Patient Prefix on the â€œPoliciesâ€ tab.
</li><li>For programmers, the TriagePic VS project now contains a set of Class Diagrams.</li></ul>
</div>

<br>
<br>
<br>



</div>')
_t('RESOURCE_PAGES_TITLE|TriagePic Overview')
_t('RESOURCE_PAGES_CONTENT|<h2>Overview</h2>
<br>
TriagePic, a hospital-based Windows application, helps quickly gather photos and minimal information about disaster victims arriving at a perimeter triage station, particularly to assist with family reunification.  Photos can be gathered using a webcam or paired Bluetooth camera.  TriagePic can be used with a hospital's preprinted triage forms, auto-incrementing mass casualty ID numbers.   As each patient is routed to a color-coded zone for treatment, information about that patient is emailed to designated recipients, such as hospital reunification counselors and emergency managers.  If set up as intended, the information is also sent to and read in by this web site.')
_t('RESOURCE_PAGES_TITLE|Access Denied')
_t('RESOURCE_PAGES_CONTENT|You do not have permission to access this event. If you believe this is in error, please contact lpfsupport@mail.nih.gov')
_t('RESOURCE_PAGES_TITLE|Account already active.')
_t('RESOURCE_PAGES_CONTENT|<div><br></div><div>This confirmation link is no longer valid. The account attached to it is already active.</div>')
_t('RESOURCE_PAGES_TITLE|Account activated.')
_t('RESOURCE_PAGES_CONTENT|<div><br></div><div>Your account has been successfully activated. You may now <a href="index.php?mod=pref&amp;act=loginForm" title="login" target="">login to the site</a> to begin using it.</div>')
_t('RESOURCE_PAGES_TITLE|Password Reset.')
_t('RESOURCE_PAGES_CONTENT|<div><br></div><div>Your password has been successfully reset and the new password emailed to you.</div>')
_t('RESOURCE_PAGES_TITLE|How do I search for a person?')
_t('RESOURCE_PAGES_CONTENT|<h2>Searching</h2>
1) Enter a name in the search box<br>
2) Click on the "Search" button, or hit Enter <br>
<br>
<i>Examples:</i><br>
<br>
 Joseph Doe<br>
 Doe, Jane<br>
 Joseph Joe Joey<br>
<br>
It is best to leave off titles (â€œDr.â€, â€œMrs.â€) and suffixes (â€œJrâ€) at this time.<br>
<br>
<br>
<h2>Search Options</h2>
Once you have performed a search, you may also limit your results by status, gender, and age.<br>
<br>
Status choices are missing (blue), alive and well (green), injured (red), deceased (black), found (brown) or unknown (gray).<br>
<br>
Gender choices are male, female, and other/unknown.<br>
<br>
Age choices are 0-17, 18+, or unknown.<br>
<br>
<br>
<h2>Results</h2>
Results include any of the search terms.<br>
<br>
Under the search box is the number of records found that match your search, and the total number in the database (eg, Found 2 out of 43).<br>
<br>
You may sort your results by Time, Name, Age, or Status.<br>
<br>
Interactive mode displays photos by page.  The default is 25 per page.  You may change it to 50 or 100 per page via the pull down menu at the top of the results.<br>
<br>
Hands Free mode displays photos as three as three scrolling rows of photographs.  The photos always distribute themselves evenly among the rows, starting at the right side and from top row to bottom.  If there are more images than can be shown at once, the rows will become animated to scroll horizontally with wrap-around.  There is no meaning to the ordering of the images at this time.<br>
<br>
<br>
<h2>Getting Details about a Given Photo</h2>
Click on the photo for more information.<br>
<br>
<br>
<h2>Pause and Play Buttons</h2>
If horizontal scrolling is occurring, Pause will stop that, and Play will resume it.  Even while paused, the search will be repeated every minute to look for fresh content.<br>
<br>
<br>
<h2>Other Information</h2>
What Information is being Searched, and How Often Is It Updated?<br>
<br>
Once a set of result images for a search is loaded, the search will be quietly repeated every minute to see if there is new content to include.<br>
<br>
Information is being input via Report a Person and records set to us directly by email.<br>
<br>
<br>
<h2>Data Updates</h2>
Once a set of result images for a search is loaded, the search will be quietly repeated every minute to see if there is new content.
Information is being input via the Report a Person page and records sent to us directly by email.
<br>
<br><br>')
_t('RESOURCE_PAGES_TITLE|About Us')
_t('RESOURCE_PAGES_CONTENT|<h2>About</h2>This site is provided by the <a href="http://www.nlm.nih.gov/">United States National Library of Medicine (NLM)</a> in Bethesda, Maryland.NLM is part of the <a href="http://www.nih.gov/">National Institutes of Health</a>, U.S. <a href="http://www.dhhs.gov/">Department of Health and Human Services</a>, and has in its mission the development and coordination of communication technology to improve the delivery of health services. This site is provided for the purpose of studying the utility of such tools in responding to disasters. The underlying technology was developed through NLMâ€™s <a href="http://archive.nlm.nih.gov/proj/lpf.php">Lost Person Finder (LPF) project</a>, part of NLMâ€™s contribution to the <a href="http://www.bhepp.org/">Bethesda Hospitalsâ€™ Emergency Preparedness Partnership (BHEPP)</a>.<br>
<br>
<h2>Privacy</h2>
All data contained on this Web are available to the public and are searchable by all visitors to the Web site. Data are received from multiple sources:&nbsp; direct submissions to NLM 
using the â€œFound in Haitiâ€ iPhoneâ„¢ application or email, from the Google Person Finder, and from other organizations, as indicated on individual records. The site may not be moderated, and NLM and other contributing organizations do not review or verify the accuracy of any of the data presented on this Web site. Note that data received by direct submission to NLM may be disseminated to other agencies, institutions, and organizations assisting the effort to locate missing people,including the Google Person Finder. For direct submissions to NLM, the senderâ€™s email address and iPhone device ID will be retained by NLM, but will not be displayed on the Web site. Contact email addresses that are explicitly provided by the submitter
 may be displayed, however, regardless of the manner in which the data were received.<br>
<br>
<h2>Technical Details</h2>
This site should work with the most recent versions of Firefox, Chrome, Safari, and Internet Explorer.')
_t('RESOURCE_PAGES_TITLE|Links')
_t('RESOURCE_PAGES_CONTENT|<h2>Find Family and Friends</h2>
<a href="https://safeandwell.communityos.org/cms//" title="Red Cross Safe and Well List">Red Cross Safe and Well List</a><br>
<a href="http://www.nokr.org/nok/restricted/home.htm" title="Next of Kin National Registry">Next of Kin National Registry</a><br>
<a href="http://www.lrcf.net/create-flyer/" title="Missing Person Flier Creation Tools" >Missing Person Flier Creation Tools</a><br>
<br>

<h2>Disaster Resources</h2>
<a target="" title="Disaster Assistance" href="http://www.disasterassistance.gov/">Disaster Assistance</a><br>
<a href="http://app.redcross.org/nss-app/" title="Red Cross Provides Shelters and Food">Red Cross Provides Shelters and Food</a><br>
<a target="" title="Tornado Information" href="http://disaster.nlm.nih.gov/enviro/tornados.html">Tornado Information from the Disaster Information Management Resource Center</a><br>
<a target="" title="Tornado Information" href="http://www.nlm.nih.gov/medlineplus/tornadoes.html">Tornado Information from MedlinePlus</a><br>
<a target="" title="2011 Tornado Information" href="http://www.noaanews.noaa.gov/2011_tornado_information.html">NOAA 2011 Tornado Information</a><br>
<a target="" title="" href="http://www.poynter.org/latest-news/making-sense-of-news/133446/joplin-globes-facebook-page-locates-reunites-missing-people-in-tornado-aftermath/">Joplin Globeâ€™s Facebook page locates, reunites missing people in tornado aftermath</a>




')
_t('RESOURCE_PAGES_TITLE|Contact us')
_t('RESOURCE_PAGES_CONTENT|<h2>
	<script>
	var kontakt = "Contact us via email"
	var uzer = "lpfsupport"
	var dohmain = "mail.nih.gov"
	document.write('<a href="'+'m'+'ai'+'l'+'to:'+uzer+'@'+dohmain+'?subject=Feedback for People Locator">Click here to email us.</a>')
	</script>
</h2>')
_t('RESOURCE_PAGES_TITLE|ABOUT')
_t('RESOURCE_PAGES_CONTENT|<meta http-equiv="content-type" content="text/html; charset=utf-8"><span class="Apple-style-span" style="font-family: 'Times New Roman'; font-size: medium; "><pre style="word-wrap: break-word; white-space: pre-wrap; ">Some of the Sahana Agasti modules are being actively developed, maintained, or customized by the U.S. National Library of Medicine (NLM), located on the National Institutes of Health (NIH) campus in Bethesda, Maryland. NLM is in a community partnership with 3 nearby hospitals (National Naval Medical Center, NIH Clinical Center, Suburban Hospital) to improve emergency responses to a mass disaster impacting those hospitals. The partnership, called the Bethesda Hospitals' Emergency Preparedness Partnership (BHEPP), received initial federal funding for LPF and other NLM IT projects in 2008-9. The LPF project is currently supported by the Intramural Research Program of the NIH, through NLMâ€™s Lister Hill National Center for Biomedical Communications (LHNCBC). Software development is headed by LHNCBC's Communication Engineering Branch (CEB), with additional content from LHNCBC's Computer Science Branch (CSB) and the Disaster Information Management Research Center (DIMRC), part of NLM's Specialized Information Services.</pre></span>')
_t('RESOURCE_PAGES_TITLE|PLUS Web Service API')
_t('RESOURCE_PAGES_CONTENT|<a href="https://pl.nlm.nih.gov/index.php?mod=rez&amp;act=default&amp;page_id=plus" title="" target="">PL User Service API</a>')
_t('RESOURCE_PAGES_TITLE|Lisbon')
_t('RESOURCE_PAGES_CONTENT|<br>')
_t('RESOURCE_PAGES_TITLE|General Resources')
_t('RESOURCE_PAGES_CONTENT|<br>')
_t('RESOURCE_PAGES_TITLE|old links')
_t('RESOURCE_PAGES_CONTENT|&lt;h2&gt;Bethesda Hospital Emergency Preparedness Partnership (BHEPP)&lt;/h2&gt;<br>&lt;a target="" title="" href="http://www.suburbanhospital.org/"&gt;Suburban Hospital&lt;/a&gt;&lt;br&gt;<br>&lt;a target="" title="" href="http://www.bethesda.med.navy.mil/"&gt;National Naval Medical Center&lt;/a&gt;&lt;br&gt;<br>&lt;a target="" title="" href="http://www.cc.nih.gov/"&gt;NIH Clinical Center&lt;/a&gt;&lt;br&gt;<br>&lt;a target="" title="" href="http://www.nlm.nih.gov/"&gt;National Library of Medicine&lt;/a&gt;&lt;br&gt;<br>&lt;br&gt;<br>&lt;h2&gt;Find Family and Friends&lt;/h2&gt;<br>&lt;a href="https://disastersafe.redcross.org/" title="Red Cross Safe and Well List"&gt;Red Cross Safe and Well List&lt;/a&gt;&lt;br&gt;<br>&lt;a href="http://www.nokr.org/nok/restricted/home.htm" title="Next of Kin National Registry"&gt;Next of Kin National Registry&lt;/a&gt;&lt;br&gt;<br>&lt;a href="http://www.militaryonesource.com/" title="Military Families Resources (Military OneSource)"&gt;Military Families Resources (Military OneSource)&lt;/a&gt;&lt;br&gt;<br>&lt;a href="http://www.usa.gov/Citizen/Topics/PublicSafety/Hurricane_Recovery/Telephone_Hotlines.shtml#vgn-international-evacuees-and-foreign-nationals-vgn" title="International Evacuees and Foreign Nationals"&gt;International Evacuees and Foreign Nationals&lt;/a&gt;&lt;br&gt;<br>&lt;a href="http://www.redcross.org/article/0,1072,0_312_8167,00.html" title="Red Cross Provides Shelters and Food"&gt;Red Cross Provides Shelters and Food&lt;/a&gt;&lt;br&gt;<br>&lt;a href="http://www.texasonline.com/portal/tol/en/emergency/evacuating" title="Texas Evacuation and Re-Entry"&gt;Texas Evacuation and Re-Entry&lt;/a&gt;&lt;br&gt;<br>&lt;a target="" title="" href="http://www.lrcf.net/create-flyer/specify.picture.html"&gt;Missing Person Flier Creation Tools&lt;/a&gt;&lt;br&gt;<br>&lt;a target="" title="" href="http://www.missingkidsmap.com/"&gt;National Center for Missing and Exploited Children (NCMEC)&lt;/a&gt;&lt;br&gt;<br>&lt;br&gt;<br>&lt;h2&gt;Emergency Preparedness&lt;/h2&gt;<br>&lt;a title="" href="http://nnlm.gov/ep/" target="_blank"&gt;National Network of Libraries of Medicine&lt;/a&gt;&lt;br&gt;<br>&lt;a target="" title="" href="http://www.montgomerycountymd.gov/hhstmpl.asp?url=/Content/HHS/phs/communicabledisease/Immunization/panflu/PanFlu_index.asp#InTheEvent"&gt;NIH-hosted listserve for Disaster Information Outreach by Librarians&lt;/a&gt;&lt;br&gt;<br>&lt;a target="" title="" href="http://www.miemss.org/"&gt;Maryland Institute for Emergency Medical Services Systems&lt;/a&gt;&lt;br&gt;<br>&lt;br&gt;<br>&lt;h2&gt;Montgomery County Based&lt;/h2&gt;<br>&lt;a target="" title="" href="http://www.montgomerycountymd.gov/hhstmpl.asp?url=/Content/HHS/phs/communicabledisease/Immunization/panflu/PanFlu_index.asp#InTheEvent"&gt;Late breaking news&lt;/a&gt;&lt;br&gt;<br>&lt;a target="" title="" href="http://www.montgomerycountymd.gov/mcgtmpl.asp?url=/content/homelandsecurity/index.asp"&gt;Family preparedness and other resources may be found here.&lt;/a&gt;&lt;br&gt;<br>&lt;a target="" title="" href="http://www.montgomerycountymd.gov/hhstmpl.asp?url=/content/hhs/phs/APC/index.asp"&gt;Public Health Emergency Preparedness and Response Program&lt;/a&gt;&lt;br&gt;<br>&lt;a target="" title="" href="https://alert.montgomerycountymd.gov/register.php"&gt;Register for DC Area Alerting Services&lt;/a&gt;&lt;br&gt;<br>&lt;a target="" title="" href="http://gcn.com/articles/2009/01/28/nih-expands-notification-system.aspx"&gt;NIH Notification System&lt;/a&gt;&lt;br&gt;<br>&lt;br&gt;<br>&lt;h2&gt;Other Disaster Resources&lt;/h2&gt;<br>&lt;a target="" title="" href="http://www.disasterassistance.gov/"&gt;Disaster Assistance&lt;/a&gt;&lt;br&gt;<br>&lt;br&gt;<br>&lt;br&gt;<br>')
_t('RESOURCE_PAGES_TITLE|old search')
_t('RESOURCE_PAGES_CONTENT|&lt;h2&gt;Searching&lt;/h2&gt;<br>1) Enter a name in the search box&lt;br&gt;<br>2) Click on the "Search" button, or hit Enter &lt;br&gt;<br>&lt;br&gt;<br>&lt;i&gt;Examples:&lt;/i&gt;&lt;br&gt;<br>&lt;br&gt;<br>&nbsp;Joseph Doe&lt;br&gt;<br>&nbsp;Doe, Jane&lt;br&gt;<br>&nbsp;Joseph Joe Joey&lt;br&gt;<br>&lt;br&gt;<br>It is best to leave off titles (â€œDr.â€, â€œMrs.â€) and suffixes (â€œJrâ€) at this time.&lt;br&gt;<br>&lt;br&gt;<br>&lt;br&gt;<br>&lt;h2&gt;Search Options&lt;/h2&gt;<br>You may also specify status, gender, and age to limit your search results.&nbsp; The default is to search all options.&nbsp; To access search options, click on the "+ More Options" link.&lt;br&gt;<br>&lt;br&gt;<br>Status choices are missing (blue), alive and well (green), injured (red), deceased (black), or unknown (gray)&lt;br&gt;<br>&lt;br&gt;<br>Gender choices are male, female, and other/unknown.&lt;br&gt;<br>&lt;br&gt;<br>Age choices are 0-17, 18+, or unknown.&lt;br&gt;<br>&lt;br&gt;<br>&lt;br&gt;<br>&lt;h2&gt;Results&lt;/h2&gt;<br>Results include any of the search terms.&lt;br&gt;<br>&lt;br&gt;<br>Under the search box is the number of records found that match your search, and the total number in the database (eg, Found 2 out of 43).&lt;br&gt;<br>&lt;br&gt;<br>You may sort your results by Time, Name, Age, or Status.&lt;br&gt;<br>&lt;br&gt;<br>Interactive mode displays photos by page.&nbsp; The default is 25 per page.&nbsp; You may change it to 50 or 100 per page via the pull down menu at the top of the results.&lt;br&gt;<br>&lt;br&gt;<br>Hands Free mode displays photos as three as three scrolling rows of photographs.&nbsp; The photos always distribute themselves evenly among the rows, starting at the right side and from top row to bottom.&nbsp; If there are more images than can be shown at once, the rows will become animated to scroll horizontally with wrap-around.&nbsp; There is no meaning to the ordering of the images at this time.&lt;br&gt;<br>&lt;br&gt;<br>&lt;br&gt;<br>&lt;h2&gt;Getting Details about a Given Photo&lt;/h2&gt;<br>Click on the photo for more information.&lt;br&gt;<br>&lt;br&gt;<br>&lt;br&gt;<br>&lt;h2&gt;Pause and Play Buttons&lt;/h2&gt;<br>If horizontal scrolling is occurring, Pause will stop that, and Play will resume it.&nbsp; Even while paused, the search will be repeated every minute to look for fresh content.&lt;br&gt;<br>&lt;br&gt;<br>&lt;br&gt;<br>&lt;h2&gt;Other Information&lt;/h2&gt;<br>What Information is being Searched, and How Often Is It Updated?&lt;br&gt;<br>&lt;br&gt;<br>Once a set of result images for a search is loaded, the search will be quietly repeated every minute to see if there is new content to include.&lt;br&gt;<br>&lt;br&gt;<br>Information is being input via TriagePic and records set to us directly by email (e.g., with our iPhone app).&lt;br&gt;<br>&lt;br&gt;<br>&lt;br&gt;<br>&lt;h2&gt;Data Updates&lt;/h2&gt;<br>Once a set of result images for a search is loaded, the search will be quietly repeated every minute to see if there is new content.<br>Information is being input via TriagePic and records sent to us directly by email (e.g., with our iPhone app).<br>&lt;br&gt;<br>&lt;br&gt;&lt;br&gt;<br>')
_t('RESOURCE_PAGES_TITLE|Pakistan_Flood_Relief_Page1')
_t('RESOURCE_PAGES_CONTENT|<!--[if gte mso 9]><xml>
 <w:WordDocument>
  <w:View>Normal</w:View>
  <w:Zoom>0</w:Zoom>
  <w:TrackMoves/>
  <w:TrackFormatting/>
  <w:PunctuationKerning/>
  <w:ValidateAgainstSchemas/>
  <w:SaveIfXMLInvalid>false</w:SaveIfXMLInvalid>
  <w:IgnoreMixedContent>false</w:IgnoreMixedContent>
  <w:AlwaysShowPlaceholderText>false</w:AlwaysShowPlaceholderText>
  <w:DoNotPromoteQF/>
  <w:LidThemeOther>EN-US</w:LidThemeOther>
  <w:LidThemeAsian>X-NONE</w:LidThemeAsian>
  <w:LidThemeComplexScript>AR-SA</w:LidThemeComplexScript>
  <w:Compatibility>
   <w:BreakWrappedTables/>
   <w:SnapToGridInCell/>
   <w:WrapTextWithPunct/>
   <w:UseAsianBreakRules/>
   <w:DontGrowAutofit/>
   <w:SplitPgBreakAndParaMark/>
   <w:DontVertAlignCellWithSp/>
   <w:DontBreakConstrainedForcedTables/>
   <w:DontVertAlignInTxbx/>
   <w:Word11KerningPairs/>
   <w:CachedColBalance/>
  </w:Compatibility>
  <w:BrowserLevel>MicrosoftInternetExplorer4</w:BrowserLevel>
  <m:mathPr>
   <m:mathFont m:val="Cambria Math"/>
   <m:brkBin m:val="before"/>
   <m:brkBinSub m:val="--"/>
   <m:smallFrac m:val="off"/>
   <m:dispDef/>
   <m:lMargin m:val="0"/>
   <m:rMargin m:val="0"/>
   <m:defJc m:val="centerGroup"/>
   <m:wrapIndent m:val="1440"/>
   <m:intLim m:val="subSup"/>
   <m:naryLim m:val="undOvr"/>
  </m:mathPr></w:WordDocument>
</xml><![endif]--><!--[if gte mso 9]><xml>
 <w:LatentStyles DefLockedState="false" DefUnhideWhenUsed="true"
  DefSemiHidden="true" DefQFormat="false" DefPriority="99"
  LatentStyleCount="267">
  <w:LsdException Locked="false" Priority="0" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Normal"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="heading 1"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 2"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 3"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 4"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 5"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 6"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 7"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 8"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 9"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 1"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 2"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 3"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 4"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 5"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 6"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 7"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 8"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 9"/>
  <w:LsdException Locked="false" Priority="35" QFormat="true" Name="caption"/>
  <w:LsdException Locked="false" Priority="10" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Title"/>
  <w:LsdException Locked="false" Priority="0" Name="Default Paragraph Font"/>
  <w:LsdException Locked="false" Priority="11" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Subtitle"/>
  <w:LsdException Locked="false" Priority="22" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Strong"/>
  <w:LsdException Locked="false" Priority="20" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Emphasis"/>
  <w:LsdException Locked="false" Priority="0" SemiHidden="false"
   UnhideWhenUsed="false" Name="Table Grid"/>
  <w:LsdException Locked="false" UnhideWhenUsed="false" Name="Placeholder Text"/>
  <w:LsdException Locked="false" Priority="1" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="No Spacing"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 1"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 1"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 1"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 1"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 1"/>
  <w:LsdException Locked="false" UnhideWhenUsed="false" Name="Revision"/>
  <w:LsdException Locked="false" Priority="34" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="List Paragraph"/>
  <w:LsdException Locked="false" Priority="29" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Quote"/>
  <w:LsdException Locked="false" Priority="30" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Intense Quote"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 1"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 1"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 1"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 1"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 1"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 1"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 2"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 2"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 2"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 2"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 2"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 2"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 2"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 2"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 3"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 3"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 3"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 3"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 3"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 3"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 3"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 3"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 4"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 4"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 4"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 4"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 4"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 4"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 4"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 4"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 5"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 5"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 5"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 5"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 5"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 5"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 5"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 5"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 6"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 6"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 6"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 6"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 6"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 6"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 6"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 6"/>
  <w:LsdException Locked="false" Priority="19" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Subtle Emphasis"/>
  <w:LsdException Locked="false" Priority="21" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Intense Emphasis"/>
  <w:LsdException Locked="false" Priority="31" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Subtle Reference"/>
  <w:LsdException Locked="false" Priority="32" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Intense Reference"/>
  <w:LsdException Locked="false" Priority="33" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Book Title"/>
  <w:LsdException Locked="false" Priority="37" Name="Bibliography"/>
  <w:LsdException Locked="false" Priority="39" QFormat="true" Name="TOC Heading"/>
 </w:LatentStyles>
</xml><![endif]--><!--[if gte mso 10]>
<style>
 /* Style Definitions */
 table.MsoNormalTable
	{mso-style-name:"Table Normal";
	mso-tstyle-rowband-size:0;
	mso-tstyle-colband-size:0;
	mso-style-noshow:yes;
	mso-style-priority:99;
	mso-style-qformat:yes;
	mso-style-parent:"";
	mso-padding-alt:0in 5.4pt 0in 5.4pt;
	mso-para-margin:0in;
	mso-para-margin-bottom:.0001pt;
	mso-pagination:widow-orphan;
	font-size:11.0pt;
	font-family:"Calibri","sans-serif";
	mso-ascii-font-family:Calibri;
	mso-ascii-theme-font:minor-latin;
	mso-fareast-font-family:"Times New Roman";
	mso-fareast-theme-font:minor-fareast;
	mso-hansi-font-family:Calibri;
	mso-hansi-theme-font:minor-latin;
	mso-bidi-font-family:Arial;
	mso-bidi-theme-font:minor-bidi;}
table.MsoTableGrid
	{mso-style-name:"Table Grid";
	mso-tstyle-rowband-size:0;
	mso-tstyle-colband-size:0;
	mso-style-unhide:no;
	border:solid windowtext 1.0pt;
	mso-border-alt:solid windowtext .5pt;
	mso-padding-alt:0in 5.4pt 0in 5.4pt;
	mso-border-insideh:.5pt solid windowtext;
	mso-border-insidev:.5pt solid windowtext;
	mso-para-margin:0in;
	mso-para-margin-bottom:.0001pt;
	mso-pagination:widow-orphan;
	font-size:10.0pt;
	font-family:"Times New Roman","serif";}
</style>
<![endif]-->

<p class="MsoNormal" dir="RTL" style="text-align:right;direction:rtl;unicode-bidi:
embed"><span lang="AR-SA">Ù…ÛŒÚº Ø±Ù¾ÙˆØ±Ù¹ Ú©ÛŒØ³Û’ Ú©Ø±ÙˆÚºØŸ</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ú©ÙˆØ¦ÛŒ Ø¨Ú¾ÛŒ Ù…Ø¹Ù„ÙˆÙ…Ø§Øª Ø¬Ùˆ Ø¢Ù¾Ø§Ø³ ÙˆÛŒØ¨ Ø³Ø§Ø¦Ù¹ ÛŒØ§ Ú¯ÙˆÚ¯Ù„ Ú©Û’ Ù¾Ø±Ø³Ù†
ÙØ§Ø¦Ù†ÚˆØ± Ù…ÛŒÚº Ø±Ù¾ÙˆØ±Ù¹ Ú©Ø±ØªÛ’</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">ÛÛŒÚºØŒ Ø§Ø³Û’ Ù¾Ø¨Ù„Ú© ÚˆÙˆÙ…ÛŒÙ† Ø³Ù…Ø¬Ú¾Ø§ Ø¬Ø§ØªØ§ ÛÛ’ Ø§ÙˆØ±
Ø¨Ú‘Û’ Ù¾ÛŒÙ…Ø§Ù†Û’ Ù¾Ø± Ù†Ø´Ø± Ú©ÛŒØ§ Ø¬Ø§ØªØ§</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">ÛÛ’Û”Ø¨Ø±Ø§Ø¦Û’ Ù…ÛØ±Ø¨Ø§Ù†ÛŒ Ø¬Ùˆ Ù…Ø¹Ù„ÙˆÙ…Ø§Øª Ø¨Ú¾ÛŒ Ø¢Ù¾
ÙØ±Ø§ÛÙ… Ú©Ø±ÛŒÚºØŒ Ø§Ø­ØªÛŒØ§Ø· Ø³Û’ ØºÙˆØ± Ú©Ø±Ù†Û’ Ú©Û’ Ø¨Ø¹Ø¯</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">ÙØ±Ø§ÛÙ… Ú©Ø±ÛŒÚºÛ”</span><span dir="LTR"><br>
</span><span lang="AR-SA">ÛŒÛØ§Úº Ø§Ø·Ù„Ø§Ø¹ Ø¯ÛŒÙ†Ø§</span><span dir="LTR"><br>
</span><span lang="AR-SA">ÙˆØ³ÛŒØ¹ Ù¾ÛŒÙ…Ø§Ù†Û’ Ù¾Ø± Ù†Ø´Ø± Ú©Ø±Ù†Û’ Ú©ÛŒÙ„Ø¦Û’ Ù†ÛŒÚ†Û’ â€™Ú¯ÙˆÚ¯Ù„ Ú©Û’ Ù¾Ø±Ø³Ù† ÙØ§Ø¦Ù†ÚˆØ±
: </span><span class="apple-style-span"><b><span style="font-size:
10.0pt;font-family:" arial","sans-serif";color:black"="" lang="AR-SA">Ù¾Ø§Ú©Ø³ØªØ§Ù†</span></b></span><span dir="LTR"></span><span class="apple-style-span"><b><span dir="LTR" style="font-size:10.0pt;font-family:" arial","sans-serif";color:black"="" lang="AR-SA"><span dir="LTR"></span> </span></b></span><span lang="AR-SA">Ø²Ù„Ø²Ù„Û â€˜ ÙØ§Ø±Ù… Ú©Û’ Ø°Ø±ÛŒØ¹Û’ Ø±Ù¾ÙˆØ±Ù¹
Ú©Ø±ÛŒÚº</span><span dir="LTR"><br style="mso-special-character:line-break">
<br style="mso-special-character:line-break">
</span></p>

<div align="right">

<table class="MsoTableGrid" dir="rtl" style="border-collapse:collapse;border:none;mso-border-alt:solid windowtext .5pt;
 mso-yfti-tbllook:480;mso-padding-alt:0in 5.4pt 0in 5.4pt;mso-table-dir:bidi" border="1" cellpadding="0" cellspacing="0">
 <tbody><tr style="mso-yfti-irow:0;mso-yfti-firstrow:yes;mso-yfti-lastrow:yes">
  <td style="width:6.15in;border:solid windowtext 1.0pt;
  mso-border-alt:solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="590">
  <p class="MsoNormal" dir="RTL" style="text-align:center;direction:
  rtl;unicode-bidi:embed" align="center"><span dir="LTR">â€™ </span><span lang="AR-SA">Ù¾Ø±Ø³Ù† ÙØ§Ø¦Ù†ÚˆØ± :
  </span><span class="apple-style-span"><b><span style="font-size:
  10.0pt;font-family:" arial","sans-serif";color:black"="" lang="AR-SA">Ù¾Ø§Ú©Ø³ØªØ§Ù†</span></b></span><span lang="AR-SA"> Ø²Ù„Ø²Ù„Û</span></p>
  <p class="MsoNormal" dir="RTL" style="text-align:center;direction:
  rtl;unicode-bidi:embed" align="center"><span lang="AR-SA">Ø¢Ù¾Ú©ÛŒ ØµÙˆØªØ­Ø§Ù„ Ú©ÛŒØ§ ÛÛ’ØŸ</span></p>
  <p class="MsoNormal" dir="RTL" style="text-align:center;direction:
  rtl;unicode-bidi:embed" align="center"><span style="background:yellow;mso-highlight:
  yellow" lang="AR-SA">Ù…ÛŒÚº Ú©Ø³ÛŒ Ú©Ùˆ ØªÙ„Ø§Ø´ Ú©Ø± Ø±ÛØ§ ÛÙˆÚº</span><span dir="LTR"></span><span dir="LTR" style="background:yellow;mso-highlight:yellow" lang="AR-SA"><span dir="LTR"></span> </span><span dir="LTR"><span style="mso-spacerun:yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span style="background:yellow;
  mso-highlight:yellow"><span style="mso-spacerun:yes">&nbsp;</span></span></span><span style="background:yellow;mso-highlight:yellow" lang="AR-SA">Ù…ÛŒØ±Û’ Ù¾Ø§Ø³ Ú©Ø³ÛŒ Ú©Û’
  Ø¨Ø§Ø±Û’ Ù…ÛŒÚº Ù…Ø¹Ù„ÙˆÙ…Ø§Øª ÛÛŒÚº</span></p>
  <p class="MsoNormal" dir="RTL" style="text-align:center;direction:
  rtl;unicode-bidi:embed" align="center"><span dir="RTL"></span><span style="mso-bidi-language:
  FA" lang="FA"><span dir="RTL"></span>ÛµÛµÛ³Û°Û°</span><span lang="AR-SA">Ø±ÛŒÚ©Ø§Ø±Úˆ Ù…ÙˆØ¬ÙˆØ¯ ÛÛŒÚºÛ”</span><span dir="LTR"><br>
  </span><span lang="AR-SA">Ø¨Ø±Ø§Ø¦Û’ Ù…ÛØ±Ø¨Ø§Ù†ÛŒ Ù†ÙˆÙ¹ Ú©Ø±ÛŒÚº: Ø¯Ø±Ø¬ Ú©ÛŒØ§ Ú¯ÛŒØ§ ØªÙ…Ø§Ù… Ø§Ø¹Ø¯Ø§Ø¯ÙˆØ´Ù…Ø§Ø±
  Ú©Ú¾Ù„Ù… Ú©Ú¾Ù„Ø§ Ø¯Ø³ØªÛŒØ§Ø¨</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">ÛÛŒÚºØŒ Ø¯ÛŒÚ©Ú¾Û’ Ø§ÙˆØ± Ø§Ø³ØªØ¹Ù…Ø§Ù„ Ú©ÛŒÛ’ Ø¬Ø§ Ø³Ú©ØªÛ’
  ÛÛŒÚºÛ” Ú¯ÙˆÚ¯Ù„</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span>
  </span><span lang="AR-SA">Ø§Ø¹Ø¯Ø§Ø¯ÙˆØ´Ù…Ø§Ø±Ú©Ø§ Ø¬Ø§Ø¦Ø²Û ÛŒØ§</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ø¯Ø±Ø³ØªÚ¯ÛŒ Ú©ÛŒ
  ØªÙˆØ«ÛŒÙ‚ Ù†ÛÛŒÚº Ú©Ø±ØªØ§Û”</span></p>
  <p class="MsoNormal" dir="RTL" style="text-align:center;direction:
  rtl;unicode-bidi:embed" align="center"><span dir="LTR">&nbsp;</span></p>
  <p class="MsoNormal" dir="RTL" style="text-align:center;direction:
  rtl;unicode-bidi:embed" align="center"><span lang="AR-SA">Ø§Ù¾Ù†ÛŒ Ø³Ø§Ø¦Ù¹ Ù¾Ø± Ø§Ø³ Ù¹ÙˆÙ„ Ú©Ùˆ Ù„Ú¯Ø§Ø¦ÛŒÛ’</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span style="mso-spacerun:yes">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </span></span><span lang="AR-SA">ÚˆÙˆÛŒÙ„Ù¾Ø±Ø²</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ø®Ø¯Ù…Øª Ú©ÛŒ Ø´Ø±Ø§Ø¦Ø·</span></p>
  </td>
 </tr>
</tbody></table>

</div>

<p class="MsoNormal" dir="RTL" style="text-align:right;direction:rtl;unicode-bidi:
embed"><span dir="LTR"><br>
</span><span lang="AR-SA">ÙÙˆØ±ÛŒ Ø·ÙˆØ± Ù¾Ø± Ø§ÛŒ Ù…ÛŒÙ„ Ú©Û’ Ø°Ø±ÛŒØ¹Û’ Ù†Ø§Ù…ØŒ Ø¯Ø±Ø¬Û Ø§ÙˆØ± ØªØµØ§ÙˆÛŒØ± Ú©ÛŒ
Ø§Ø·Ù„Ø§Ø¹ Ø¯ÛŒÙ†Ø§Û” Ø¢ Ù¾ Ù†Ø§Ù…</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">ÛŒØ§ Ø¯Ø±Ø¬Û’ Ú©Û’ Ø¨Ø§Ø±Û’ Ù…ÛŒÚº Ø¨Ø±Ø§Û Ø±Ø§Ø³Øª Ø§Ø·Ù„Ø§Ø¹ Ø§ÛŒ
Ù…ÛŒÙ„ Ú©Û’ Ø°Ø±ÛŒØ¹Û’ Ø¯Û’ Ø³Ú©ØªÛ’ ÛÛŒÚº(Ø¬ÛŒØ³Ø§ Ú©Û</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ø³ÛŒÙ„ ÙÙˆÙ† Ú©Û’ Ø°Ø±ÛŒØ¹Û’)Û” Ø§ÛŒØ³ÛŒ
Ù…Ø¹Ù„ÙˆÙ…Ø§Øª ÛÙ…Ø§Ø±Û’ ØªÙ„Ø§Ø´ Ú©Û’ Ù†ØªØ§Ø¦Ø¬ Ù…ÛŒÚº Ø²ÛŒØ§Ø¯Û Ø¬Ù„Ø¯ÛŒ Ø¸Ø§ÛØ±</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">ÛÙˆØªÛŒ ÛÛŒÚºØŒ Ø§ÙˆØ±
ÙˆØ³ÛŒØ¹ Ø·ÙˆØ± Ù¾Ø± Ù†Ø´Ø± Ú©Ø±Ù†Û’ Ú©ÛŒÙ„Ø¦Û’ Ú¯ÙˆÚ¯Ù„ Ù¾Ø±Ø³Ù† ÙØ§Ø¦Ù†ÚˆØ± Ù…ÛŒÚº Ø¨Ú¾ÛŒ Ù…Ù†ØªÙ‚Ù„</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ú©ÛŒ Ø¬Ø§ØªÛŒ ÛÛŒÚºÛ”Ø¢Ù¾</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">ØªØµÙˆÛŒØ±(Ø§ÛŒÚ© ÙˆÙ‚Øª Ù…ÛŒÚº Ø§ÛŒÚ©) Ø¨Ú¾ÛŒ Ø´Ø§Ù…Ù„ Ú©Ø± Ø³Ú©ØªÛ’ ÛÛŒÚºÛ” Ù‚Ø§Ø¨Ù„ Ù‚Ø¨ÙˆÙ„</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">ÙØ§Ø±Ù…ÛŒÙ¹Ø³ Ù…ÛŒÚº</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>
.jpg or .jpeg, .png,</span><span lang="AR-SA">Ø§ÙˆØ±</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>.gif </span><span lang="AR-SA">Ø´Ø§Ù…Ù„ ÛÛŒÚºÛ”Ø§Ø¨ Ú©ÛŒÙ„Ø¦Û’ØŒ Ø§ÛŒ
Ù…ÛŒÙ„</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ú©ÛŒ Ø¨Ø§ÚˆÛŒ Ù…ÛŒÚº Ù…ÙˆØ§Ø¯ Ú©Ùˆ Ù†Ø¸Ø± Ø§Ù†Ø¯Ø§Ø² Ú©ÛŒØ§ Ø¬Ø§ØªØ§ ÛÛ’Û”</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø§ÛŒ Ù…ÛŒÙ„ Ú©Ø±ÛŒÚº</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>: lostperson@nih.gov<br>
</span><span lang="AR-SA">Ø¹Ù†ÙˆØ§Ù† Ú©ÛŒ Ø³Ø·Ø±: Ú¯Ù…Ø´Ø¯Û ÛŒØ§ Ù…Ù„Û’ ÛÙˆØ¦Û’ Ø´Ø®Øµ Ú©Ø§ Ù†Ø§Ù… ÛŒØ§ Ø­ÛŒØ«ÛŒØª</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">ÛŒØ§</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø¹Ù†ÙˆØ§Ù† Ú©ÛŒ Ø³Ø·Ø±: Ú¯Ù…Ø´Ø¯Û ÛŒØ§ Ù…Ù„Û’ ÛÙˆØ¦Û’ Ø´Ø®Øµ Ú©Ø§ Ù†Ø§Ù… ÛŒØ§ Ø­ÛŒØ«ÛŒØª ÛŒØ§
Ø§Ø®ØªÛŒØ§Ø±ÛŒ Ø§Ø¶Ø§ÙÛŒ Ù…Ø¹Ù„ÙˆÙ…Ø§Øª Ø¬ÛŒØ³Û’ Ú©Û Ø¬Ú¯Û</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø¬ÛØ§Úº Ø¯Ø±Ø¬Û ÛÛ’</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>:<br>
</span><span lang="AR-SA">Ú¯Ù…Ø´Ø¯Û</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span> <br>
</span><span lang="AR-SA">Ø²Ù†Ø¯Û ÛŒØ§ Ø§Ú†Ú¾Ø§</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø²Ø®Ù…ÛŒ</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ù…Ø±Ø§ ÛÙˆØ§</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø¹Ù†ÙˆØ§Ù† Ú©ÛŒ Ø³Ø·Ø±Ú©ÛŒ Ù…Ø«Ø§Ù„</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>:â€™â€™ /Jean Baptiste</span><span lang="AR-SA">Ø²Ù†Ø¯Û Ø§ÙˆØ±
Ø§Ú†Ú¾ÛŒ</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>â€˜â€˜<br>
</span><span lang="AR-SA">Ø¯Ø±Ø¬Û Ú©Û’ Ø§Ù„ÙØ§Ø¸ Ú©ÛŒ Ù¹ÛŒØ¨Ù„</span></p>

<p class="MsoNormal" style="text-align:right" align="right">&nbsp;</p>

<p class="MsoNormal" style="text-align:right" align="right"><br style="mso-special-character:
line-break">
<br style="mso-special-character:line-break">
</p>

<table class="MsoTableGrid" style="border-collapse:collapse;border:none;mso-border-alt:solid windowtext .5pt;
 mso-yfti-tbllook:480;mso-padding-alt:0in 5.4pt 0in 5.4pt" border="1" cellpadding="0" cellspacing="0">
 <tbody><tr style="mso-yfti-irow:0;mso-yfti-firstrow:yes">
  <td style="width:221.4pt;border:solid windowtext 1.0pt;
  mso-border-alt:solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="295">
  <p class="MsoNormal" style="text-align:right" align="right"><span dir="RTL" lang="AR-SA">Ú©ÛŒÙ„Ø¦Û’ Ù…Ø¬ÙˆØ² Û Ø§Ù„ÙØ§Ø¸</span><span dir="LTR"></span><span dir="LTR"></span> (<span dir="RTL" lang="AR-SA">Ú©ÛŒØ³ Ø³Û’ ÙØ±Ù‚ Ù†ÛÛŒÚº Ù¾Ú‘ØªØ§</span><span dir="LTR"></span><span dir="LTR"></span>)<span dir="RTL" lang="AR-SA">Ù¾ÛÙ„ÛŒ</span><span dir="LTR"></span><span dir="LTR"></span> 147/148<span dir="RTL" lang="AR-SA"></span></p>
  </td>
  <td style="width:221.4pt;border:solid windowtext 1.0pt;
  border-left:none;mso-border-left-alt:solid windowtext .5pt;mso-border-alt:
  solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="295">
  <p class="MsoNormal" style="text-align:right" align="right"><span dir="RTL" lang="AR-SA">ÙØ±Ø¶ÛŒ Ø¯Ø±Ø¬Û</span><span dir="LTR"></span><span dir="LTR"></span>:<span dir="RTL" lang="AR-SA"></span></p>
  </td>
 </tr>
 <tr style="mso-yfti-irow:1">
  <td style="width:221.4pt;border:solid windowtext 1.0pt;
  border-top:none;mso-border-top-alt:solid windowtext .5pt;mso-border-alt:solid windowtext .5pt;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="295">
  <p class="MsoNormal" style="text-align:right" align="right"><span dir="RTL" lang="AR-SA">Ú¯Ù…Ø´Ø¯Û ØŒ ØªÙ„Ø§Ø´ Ú©ÛŒØ§ Ø¬Ø§ Ø±ÛØ§ØŒ Ú©Ú¾ÙˆÛŒØ§ ÛÙˆØ§ØŒØªÙ„Ø§Ø´ Ú©Ø±Ù†Ø§</span></p>
  </td>
  <td style="width:221.4pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  mso-border-top-alt:solid windowtext .5pt;mso-border-left-alt:solid windowtext .5pt;
  mso-border-alt:solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="295">
  <p class="MsoNormal" style="text-align:right" align="right"><span dir="RTL" lang="AR-SA">Ú¯Ù…Ø´Ø¯Û</span></p>
  </td>
 </tr>
 <tr style="mso-yfti-irow:2">
  <td style="width:221.4pt;border:solid windowtext 1.0pt;
  border-top:none;mso-border-top-alt:solid windowtext .5pt;mso-border-alt:solid windowtext .5pt;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="295">
  <p class="MsoNormal" style="text-align:right" align="right"><span dir="RTL" lang="AR-SA">Ø²Ù†Ø¯ÛØŒ Ù¹Ú¾ÛŒÚ©ØŒ ØµØ­Øª Ù…Ù†Ø¯ØŒ ØµØ­Øª ÛŒØ§Ø¨</span></p>
  </td>
  <td style="width:221.4pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  mso-border-top-alt:solid windowtext .5pt;mso-border-left-alt:solid windowtext .5pt;
  mso-border-alt:solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="295">
  <p class="MsoNormal" style="text-align:right" align="right"><span dir="RTL" lang="AR-SA">Ø²Ù†Ø¯Û ÛŒØ§ Ø§Ú†Ú¾Ø§</span></p>
  </td>
 </tr>
 <tr style="mso-yfti-irow:3">
  <td style="width:221.4pt;border:solid windowtext 1.0pt;
  border-top:none;mso-border-top-alt:solid windowtext .5pt;mso-border-alt:solid windowtext .5pt;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="295">
  <p class="MsoNormal" style="text-align:right" align="right"><span dir="RTL" lang="AR-SA">Ø²Ø®Ù…ÛŒ ØŒØ¨ÛŒÙ…Ø§Ø±ØŒ ØµØ­Øª ÛŒØ§Ø¨ ÛÙˆ Ø±ÛØ§ØŒ Ø¹Ù„Ø§Ø¬ Ú©ÛŒØ§ Ú¯ÛŒØ§</span></p>
  </td>
  <td style="width:221.4pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  mso-border-top-alt:solid windowtext .5pt;mso-border-left-alt:solid windowtext .5pt;
  mso-border-alt:solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="295">
  <p class="MsoNormal" style="text-align:right" align="right"><span dir="RTL" lang="AR-SA">Ø²Ø®Ù…ÛŒ</span></p>
  </td>
 </tr>
 <tr style="mso-yfti-irow:4;mso-yfti-lastrow:yes">
  <td style="width:221.4pt;border:solid windowtext 1.0pt;
  border-top:none;mso-border-top-alt:solid windowtext .5pt;mso-border-alt:solid windowtext .5pt;
  padding:0in 5.4pt 0in 5.4pt" valign="top" width="295">
  <p class="MsoNormal" style="text-align:right" align="right"><span dir="RTL" lang="AR-SA">Ù…Ø± Ú†Ú©Ø§ØŒ Ø¯ÙÙ†Ø§ Ø¯ÛŒØ§ Ú¯ÛŒØ§ØŒ Ù…ÛŒØª</span></p>
  </td>
  <td style="width:221.4pt;border-top:none;border-left:
  none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;
  mso-border-top-alt:solid windowtext .5pt;mso-border-left-alt:solid windowtext .5pt;
  mso-border-alt:solid windowtext .5pt;padding:0in 5.4pt 0in 5.4pt" valign="top" width="295">
  <p class="MsoNormal" style="text-align:right" align="right"><span dir="RTL" lang="AR-SA">Ù…Ø±Ø§ ÛÙˆØ§</span></p>
  </td>
 </tr>
</tbody></table>

<p class="MsoNormal" style="text-align:right" align="right">&nbsp;</p>

<p class="MsoNormal" dir="RTL" style="text-align:right;direction:rtl;unicode-bidi:
embed"><span lang="AR-SA">Ø¬Ø¨ Ø¯Ø±Ø¬Û Ø¯Ø±Ø¬ Ú©Ø± Ø±ÛÛ’ ÛÙˆÚº</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>:<br>
</span><span lang="AR-SA">Ù„ÙØ¸ â€™Ù†ÛÛŒÚºâ€˜ Ú©Ø§ Ø§Ø³ØªØ¹Ù…Ø§Ù„ Ù†Û Ú©Ø±ÛŒÚº</span><span dir="LTR"><br>
</span><span lang="AR-SA">ØµØ­Øª Ú©Û’ Ø¨Ø§Ø±Û’ Ù…ÛŒÚº ØªÛŒÙ† Ú©ÛŒÙ¹ÛŒÚ¯Ø±ÛŒØ²</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ù…ÛŒÚº Ø³Û’ Ú©Ø³ÛŒ Ø§ÛŒÚ©
Ú©ÛŒ Ù…Ø²ÛŒØ¯ ÙˆØ¶Ø§Ø­Øª Ú©Û’ Ø¨ØºÛŒØ±Ù„ÙØ¸ â€™Ù…Ù„Ø§</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>â€˜ </span><span lang="AR-SA">Ø§Ú©ÛŒÙ„Ø§ Ø§Ø³ØªØ¹Ù…Ø§Ù„ Ù†Û Ú©Ø±ÛŒÚºÛ”</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø¯ÙˆØ³Ø±Û’ Ø°Ø±Ø§Ø¦Ø¹ Ø³Û’ Ø¢Ù†Û’ ÙˆØ§Ù„ÛŒ Ø§Ø·Ù„Ø§Ø¹Ø§Øª Ú©Ùˆ Ø§ÙˆÙ¾Ø± Ú©Û’ ÙØ§Ø±Ù…ÛŒÙ¹ Ú©Û’
Ù…Ø·Ø§Ø¨Ù‚ Ù†Û ÛÙˆØªÛ’ ÛÙˆØ¦Û’</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ø¨Ú¾ÛŒØŒ Ø§Ù„ÙØ§Ø¸ ÛŒØ§ ÙÙ‚Ø±Û’ ( Ø¬Ùˆ Ø§ÙˆÙ¾Ø± Ú©ÛŒ Ø¯Ø±Ø¬Û Ú©Û’
Ø§Ù„ÙØ§Ø¸ Ú©ÛŒ Ù¹ÛŒØ¨Ù„ ØªÚ© Ù…Ø­Ø¯ÙˆØ¯</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ù†ÛÛŒÚº)Ø¬Ø³Ù…ÛŒÚº Ø³Û’ Ø³Ù¹ÛŒÙ¹Ø³ Ú©ÛŒ Ù…Ø¹Ù„ÙˆÙ…Ø§Øª Ú©Ùˆ Ù†Ú©Ø§Ù„Ø§
ÛŒØ§ Ù…Ù†Ø§Ø³Ø¨ Ø·ÙˆØ± Ù¾Ø± ÚˆØ§Ù„Ø§ Ø¬Ø§ Ø³Ú©ØªØ§ ÛÛ’ØŒ</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ù…Ø®ØªÙ„Ù Ø§Ù‚Ø³Ø§Ù… Ù…ÛŒÚº ØªÙ‚Ø³ÛŒÙ…
Ú©Ø±Ù†Ø§ Ø¨Ú¾ÛŒ Ø§Ø³ Ù¾Ø±Ø§Ø¬ÛŒÚ©Ù¹ Ú©Ø§ Ù…Ù‚ØµØ¯ ÛÛ’Û”</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø§ÛŒ Ù…ÛŒÙ„ Ú©Û’ Ø°Ø±ÛŒØ¹Û’ ÛÙ…Ø§Ø±ÛŒ Ù…ÙˆØ¨Ø§Ø¦Ù„ ÙÙˆÙ† Ø§Ù¾Ù„ÛŒÚ©ÛŒØ´Ù†</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span> ( 147Found in Pakistan148,iPhone153
App) </span><span lang="AR-SA">Ø§Ø³ØªØ¹Ù…Ø§Ù„ Ú©Ø±ØªÛ’ ÛÙˆØ¦Û’ Ø§Ø·Ù„Ø§Ø¹ Ø¯ÛŒÙ†Ø§Û”</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ù…Ø¯Ø¯Ú¯Ø§Ø± Ú©Ø§Ø±Ú©Ù†ÙˆÚº Ú©ÛŒ Ø®Ø§Øµ Ø¯Ù„Ú†Ø³Ù¾ÛŒ Ú©ÛŒÙ„Ø¦Û’ØŒÛÙ… Ø§ÛŒÚ© ÙØ±ÛŒ</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ø§Ù¾Ù„ÛŒÚ©ÛŒØ´Ù† ØŒØ¬Ø³Û’â€™ Ø§ÛŒÙ¾Ù„ Ø³Ù¹ÙˆØ±</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ú©Û’ Ø°Ø±ÛŒØ¹Û’ ÛÛŒÙ¹ÛŒ
Ù…ÛŒÚº Ù…Ù„Ø§ â€˜Ú©ÛØ§ Ø¬Ø§ØªØ§ ÛÛ’ØŒÙ…ÛÛŒØ§ Ú©Ø±ØªÛ’ ÛÛŒÚºÛ”(ÛŒÛØ§Úº ÛÛŒÙ¹ÛŒ Ù…ÛŒÚº Ù…Ù„Û’ ÛÙˆØ¦Û’</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ú©ÛŒÙ„Ø¦Û’ Ù…Ø¯Ø¯ ÛÛ’)Û”
ÛŒÛ Ø§ÛŒÚ© Ù…Ø±ØªØ¨ Ø§ÛŒ Ù…ÛŒÙ„ Ù…ÙˆØ§Ø¯Ù…ØªØ¹Ù„Ù‚Û ØªØµØ§ÙˆÛŒØ± Ú©Û’ Ø³Ø§ØªÚ¾ ØªØ´Ú©ÛŒÙ„ Ø¯ÛŒØªÛŒ</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">ÛÛ’(Ø¬Ùˆ Ø§ÛŒÚ© Ø¯ÙØ¹Û
Ù…ÛŒÚº Ø§ÛŒÚ© Ø¬Ù…Ø¹ Ú©Ø±ÙˆØ§Ù†Û’ ØªÚ© Ù…Ø­Ø¯ÙˆØ¯ ÛÛ’)Û” Ø§ÙˆÙ¾Ø± Ø¨ÛŒØ§Ù† Ú©Ø¦Û’ Ú¯Ø¦Û’ ØºÛŒØ±</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ù…Ø±ØªØ¨ Ø§ÛŒ Ù…ÛŒÙ„ Ú©Û’
Ø·Ø±ÛŒÙ‚Û’ Ú©ÛŒ Ù†Ø³Ø¨ØªØŒ</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ø§Ø³ Ø·Ø±ÛŒÙ‚Û’ Ø³Û’ Ø²ÛŒØ§Ø¯Û Ù…Ø¹Ù„ÙˆÙ…Ø§Øª ÛÙ… ØªÚ© Ø¨Ú¾ÛŒØ¬ÛŒ
Ø¬Ø§</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ø³Ú©ØªÛŒ ÛÛŒÚºÛ”</span><span dir="LTR"><br>
â€™</span><span lang="AR-SA">ÛÛŒÙ¹ÛŒ Ù…ÛŒÚº Ù…Ù„Ø§</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span> â€˜ </span><span lang="AR-SA">Ø§Ø³ ÙˆÙ‚Øª Ù…ÙˆØ¨Ø§Ø¦Ù„ ÙÙˆ Ù† ØªÚ¾Ø± ÛŒ Ø¬ÛŒØŒ Ù…ÙˆØ¨Ø§Ø¦Ù„
ÙÙˆÙ† Ø§Ùˆ Ø§ÛŒØ³3.0</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ù…ÙˆØ¨Ø§Ø¦Ù„ ÙÙˆÙ† ØªÚ¾Ø±ÛŒ Ø¬ÛŒ Ú©Û’ Ø³Ø§ØªÚ¾ ÛŒØ§ Ø§Ø³Ú©Û’
Ø¨Ø¹Ø¯Ú©Û’ Ù…Ø§ÚˆÙ„Ø² Ú©ÛŒ Ø­Ù…Ø§Ø¦ÛŒØª Ú©Ø±ØªÛŒ ÛÛ’Û”</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ø§Ù¾Ù„ÛŒÚ©ÛŒØ´Ù† Ú©Ø§ Ø§Ú¯Ù„Ø§ ÙˆØ±Ú˜Ù†</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span> iPod Touch 2G )</span><span lang="AR-SA">Ù„ÙˆÚ©ÛŒØ´Ù† Ø³Ø±ÙˆØ³Ø²) Ø§ÙˆØ± Ø¯ÙˆØ³Ø±ÛŒ Ø®ØµÙˆØµÛŒØ§Øª Ú©Û’</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ø³Ø§ØªÚ¾ Ù…Ø·Ø§Ø¨Ù‚Øª
Ù¾ÛŒØ´ Ú©Ø±Û’ Ú¯Ø§Û”</span><span dir="LTR"><br>
</span><span lang="AR-SA">ØµØ§Ø±ÙÛŒÙ† Ø§Ù¾Ù†Û’ Ù…ÙˆØ¨Ø§Ø¦Ù„ ÙÙˆÙ† Ú©ÛŒÙ…Ø±Û’ Ú©Ø§ Ø§Ø³ØªØ¹Ù…Ø§Ù„ Ú©Ø±ØªÛ’ ÛÙˆØ¦Û’ Ù†Ø¦ÛŒ
ØªØµÙˆÛŒØ±ØŒ ÛŒØ§ ØªØµÙˆÛŒØ±ÛŒ Ù„Ø§Ø¦Ø¨Ø±ÛŒØ±ÛŒ Ù…ÛŒÚº Ù¾ÛÙ„Û’ Ø³Û’ Ù…ÙˆØ¬ÙˆØ¯ ØªØµÙˆÛŒØ± Ú©Ø§ Ø§Ø³ØªØ¹Ù…Ø§Ù„ Ú©Ø± Ø³Ú©ØªÛ’ ÛÛŒÚºÛ”</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø§Ø³Ú©Û’ Ø¨Ø¹Ø¯ ÙˆÛ ØªØµÙˆÛŒØ± Ù…ÛŒÚº Ù…ÙˆØ¬ÙˆØ¯</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ø´Ø®Øµ Ú©Û’ Ø¨Ø§Ø±Û’
Ù…ÛŒÚº Ù…Ø¹Ù„ÙˆÙ…Ø§Øª Ù¹ÛŒÚ¯ Ú©Ø±Ø³Ú©ÛŒÚº Ú¯Û’Û” Ù…Ù†Ø¯Ø±Ø¬Û Ø°ÛŒÙ„ Ø®Ø§Ù†Û’ØŒ ØªÙ…Ø§Ù… Ø§Ø®ØªÛŒØ§Ø±ÛŒ ÛÛŒÚºØŒ ØªØ±Ù…ÛŒÙ… Ú©ÛŒÙ„Ø¦Û’
Ø¯Ø³ØªÛŒØ§Ø¨ ÛÛŒÚº</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>:<br>
</span><span lang="AR-SA">Ø¯ÛŒØ§ Ú¯ÛŒØ§ Ù†Ø§Ù…</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø®Ø§Ù†Ø¯Ø§Ù† Ú©Ø§ Ù†Ø§Ù…</span><span dir="LTR"><br>
</span><span lang="AR-SA">ØµØ­Øª Ú©Ø§ Ø¯Ø±Ø¬Û: (Ø²Ù†Ø¯Û ÛŒØ§ Ø§Ú†Ú¾Ø§</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span> / </span><span lang="AR-SA">Ø²Ø®Ù…ÛŒ</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span> / </span><span lang="AR-SA">Ù…Ø±Ø§
ÛÙˆØ§ /Ù†Ø§Ù…Ø¹Ù„ÙˆÙ…</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>(<br>
</span><span lang="AR-SA">Ø¬Ù†Ø³: (Ù…Ø±Ø¯ / Ø¹ÙˆØ±Øª / Ù†Ø§Ù…Ø¹Ù„ÙˆÙ…</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>(<br>
</span><span lang="AR-SA">Ø¹Ù…Ø± Ú©Ø§ Ú¯Ø±ÙˆÙ¾: ( 0-17</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span> / 18+ /</span><span lang="AR-SA">ÛŒØ§ Ù†Ø§Ù…Ø¹Ù„ÙˆÙ…)( ÛŒØ§
Ø§Ù†Ø¯Ø§Ø²Û’ Ú©Û’ Ù…Ø·Ø§Ø¨Ù‚ Ø¹Ù…Ø± Ø¯Ø±Ø¬ Ú©Ø±ÛŒÚº</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>(<br>
</span><span lang="AR-SA">Ù…ØªÙˆÙ‚Ø¹ Ø¹Ù…Ø± ØŒ Ø³Ø§Ù„ Ù…ÛŒÚº</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø¬Ú¯Û Ú©Ø§ Ø¯Ø±Ø¬Û: </span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>)</span><span lang="AR-SA">Ú¯Ù…Ø´Ø¯Û /Ù†Ø§Ù…Ø¹Ù„ÙˆÙ…</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>(<br>
</span><span lang="AR-SA">Ø¢Ø®Ø±ÛŒ Ù…Ø¹Ù„ÙˆÙ…Ø¬Ú¯Û(Ø§Ú¯Ø± Ù…ÙˆØ¬ÙˆØ¯)/ Ù…ÙˆØ¬ÙˆØ¯Û Ø¬Ú¯Û (Ø¯ÙˆØ³Ø±ÛŒ ØµÙˆØ±Øª Ù…ÛŒÚº</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>(<br>
</span><span lang="AR-SA">Ú¯Ù„ÛŒ(Ø¹Ø§Ù… Ø·ÙˆØ± Ù¾Ø±</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>(<br>
</span><span lang="AR-SA">Ù¹Ø§Ø¤Ù†(Ø¹Ø§Ù… Ø·ÙˆØ± Ù¾Ø±</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>(<br>
</span><span lang="AR-SA">Ø¢Ø¦ÛŒ ÚˆÛŒ Ù¹ÛŒÚ¯ Ø®ÙˆØ¯Ø¨Ø®ÙˆØ¯ ÛŒØ§ Ù¾ÛÙ„Û’ Ø³Û’ Ø·Û’ Ø´Ø¯Û Ú©Û’ Ù…Ø·Ø§Ø¨Ù‚ Ø­Ø§ØµÙ„
Ú©ÛŒØ§Û”Ø§Ù…Ø¯Ø§Ø¯ÛŒ Ú©Ø§Ø±Ú©Ù† ØªÙ†Ø¸ÛŒÙ… Ú©Ø§</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span> triage </span><span lang="AR-SA">Ù†Ù…Ø¨Ø± Ø¨Ø¯Ù„ Ø³Ú©ØªÛ’ ÛÛŒÚºÛ”</span><span dir="LTR"><br>
</span><span dir="RTL"></span><span lang="AR-SA"><span dir="RTL"></span>Ù“Ø§Ø¶Ø§ÙÛŒ Ù†ÙˆÙ¹Ø³</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>/ </span><span lang="AR-SA">ØªØ¨ØµØ±Û’</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø§Ø³ Ú©Û’ Ø¹Ù„Ø§ÙˆÛØŒØ±ÛŒÚ©Ø§Ø±Úˆ Ø¨Ù†Ø§ØªÛ’ ÙˆÙ‚Øª Ù…Ù†Ø¯Ø±Ø¬Û Ø°ÛŒÙ„ Ù…Ø¹Ù„ÙˆÙ…Ø§Øª Ù¾ÛŒØ´ Ú©ÛŒ
Ø¬Ø§ØªÛŒ ÛÛŒÚº</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>:<br>
</span><span lang="AR-SA">Ø¬ÛŒ Ù¾ÛŒ Ø§ÛŒØ³ Ù„ÙˆÚ©ÛŒØ´Ù†</span><span dir="LTR"><br>
</span><span lang="AR-SA">ØªØ§Ø±ÛŒØ® Ø§ÙˆØ±ÙˆÙ‚Øª</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span> <br>
</span><span lang="AR-SA">Ù¾Ú¾Ø± ØªØµÙˆÛŒØ± ÛŒØ§ Ù…ØªØ¹Ù„Ù‚Û Ù…Ø¹Ù„ÙˆÙ…Ø§Øª Ú©Ùˆ Ø®ÙˆØ¯Ú©Ø§Ø± Ø·Ø±ÛŒÙ‚Û’ Ø³Û’ Ø§ÛŒ Ù…ÛŒÙ„
Ú©Û’ Ø°Ø±ÛŒØ¹Û’ Ø§ÛŒÙ„ Ù¾ÛŒ Ø§ÛŒÙ ØªÚ© Ø¨Ú¾ÛŒØ¬Ø§ Ø¬Ø§ Ø³Ú©ØªØ§ ÛÛ’Û”</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ù…Ø¹Ù„ÙˆÙ…Ø§Øª ØªØµÙˆÛŒØ±Ú©Û’</span><span dir="LTR">EXIF </span><span lang="AR-SA">Ú©Û’ Ù¹ÛŒÚ¯ Ù…ÛŒÚº Ø¨Ú¾ÛŒ Ù…ÙˆØ¬ÙˆØ¯ ÛÙˆØªÛŒ ÛÛŒÚºÛ”Ø±ÛŒÚ©Ø§Ø±ÚˆØ²(Ø¬Ù† Ù…ÛŒÚº ØªØµØ§ÙˆÛŒØ±</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ø¨Ú¾ÛŒ Ø´Ø§Ù…Ù„ ÛÛŒÚº</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span>(<span style="mso-spacerun:yes">&nbsp; </span>SQLite </span><span lang="AR-SA">ÚˆÛŒÙ¹Ø§Ø¨ÛŒØ³ Ú©Û’ Ø·ÙˆØ±
Ù¾Ø± Ù…ÙˆØ¨Ø§Ø¦Ù„ Ù…ÛŒÚº Ø°Ø®ÛŒØ±Û Ú©Ø± Ù„ÛŒØ§ Ø¬Ø§ØªØ§</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">ÛÛ’Û”ÛŒÛ ÚˆÛŒÙ¹Ø§Ø¨ÛŒØ³</span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span> lpfsupport@mail.nih.gov</span><span lang="AR-SA">Ù¾Ø± Ø§ÛŒ Ù…ÛŒÙ„ Ú©ÛŒ Ø¬Ø§ Ø³Ú©ØªÛŒ ÛÛ’Û”Ø¬ÛØ§Úº</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ù…Ø¯Ø¯Ú¯Ø§Ø± Ø§ÙØ±Ø§Ø¯
Ø§Ø³Û’ ÛÙ…Ø§Ø±ÛŒ ÚˆÛŒÙ¹Ø§Ø¨ÛŒØ³ Ù…ÛŒÚº Ø´Ø§Ù…Ù„ Ú©Ø±Ù†Û’ Ú©Ø§ Ø§Ù†ØªØ¸Ø§Ù… Ú©Ø± Ø³Ú©ØªÛ’ ÛÛŒÚºÛ”Ø§Ø³ Ú©Û’</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span> </span><span lang="AR-SA">Ù†ØªÛŒØ¬Û’ Ù…ÛŒÚº Ø§Ø¹Ø¯Ø§Ø¯ÙˆØ´Ù…Ø§Ø± Ú©Ùˆ ØªØ¨ Ø¨Ú¾ÛŒ Ø¬Ù…Ø¹ Ú©ÛŒØ§ Ø¬Ø§ Ø³Ú©ØªØ§ ÛÛ’ Ø¬Ø¨ Ù…ÙˆØ¨Ø§Ø¦Ù„ ÙÙˆÙ†
Ú©Ù†Ú©Ø´Ù†</span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span>
</span><span lang="AR-SA">Ø¯Ø³ØªÛŒØ§Ø¨ Ù†Û ÛÙˆØŒ Ø§ÙˆØ± Ø¨Ø¹Ø¯ Ù…ÛŒÚº Ø¨Ú¾ÛŒØ¬Ø§ Ø¬Ø§ Ø³Ú©ØªØ§ ÛÛ’ Ø¬Ø¨ Ø±Ø§Ø¨Ø·Û
Ø¯Ø³ØªÛŒØ§Ø¨ ÛÙˆÛ” </span></p>

')
_t('RESOURCE_PAGES_TITLE|Pakistan_Flood_Relief_2')
_t('RESOURCE_PAGES_CONTENT|<!--[if gte mso 9]><xml>
 <w:WordDocument>
  <w:View>Normal</w:View>
  <w:Zoom>0</w:Zoom>
  <w:TrackMoves/>
  <w:TrackFormatting/>
  <w:PunctuationKerning/>
  <w:ValidateAgainstSchemas/>
  <w:SaveIfXMLInvalid>false</w:SaveIfXMLInvalid>
  <w:IgnoreMixedContent>false</w:IgnoreMixedContent>
  <w:AlwaysShowPlaceholderText>false</w:AlwaysShowPlaceholderText>
  <w:DoNotPromoteQF/>
  <w:LidThemeOther>EN-US</w:LidThemeOther>
  <w:LidThemeAsian>X-NONE</w:LidThemeAsian>
  <w:LidThemeComplexScript>AR-SA</w:LidThemeComplexScript>
  <w:Compatibility>
   <w:BreakWrappedTables/>
   <w:SnapToGridInCell/>
   <w:WrapTextWithPunct/>
   <w:UseAsianBreakRules/>
   <w:DontGrowAutofit/>
   <w:SplitPgBreakAndParaMark/>
   <w:DontVertAlignCellWithSp/>
   <w:DontBreakConstrainedForcedTables/>
   <w:DontVertAlignInTxbx/>
   <w:Word11KerningPairs/>
   <w:CachedColBalance/>
  </w:Compatibility>
  <w:BrowserLevel>MicrosoftInternetExplorer4</w:BrowserLevel>
  <m:mathPr>
   <m:mathFont m:val="Cambria Math"/>
   <m:brkBin m:val="before"/>
   <m:brkBinSub m:val="&#45;-"/>
   <m:smallFrac m:val="off"/>
   <m:dispDef/>
   <m:lMargin m:val="0"/>
   <m:rMargin m:val="0"/>
   <m:defJc m:val="centerGroup"/>
   <m:wrapIndent m:val="1440"/>
   <m:intLim m:val="subSup"/>
   <m:naryLim m:val="undOvr"/>
  </m:mathPr></w:WordDocument>
</xml><![endif]--><!--[if gte mso 9]><xml>
 <w:LatentStyles DefLockedState="false" DefUnhideWhenUsed="true"
  DefSemiHidden="true" DefQFormat="false" DefPriority="99"
  LatentStyleCount="267">
  <w:LsdException Locked="false" Priority="0" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Normal"/>
  <w:LsdException Locked="false" Priority="9" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="heading 1"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 2"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 3"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 4"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 5"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 6"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 7"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 8"/>
  <w:LsdException Locked="false" Priority="9" QFormat="true" Name="heading 9"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 1"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 2"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 3"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 4"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 5"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 6"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 7"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 8"/>
  <w:LsdException Locked="false" Priority="39" Name="toc 9"/>
  <w:LsdException Locked="false" Priority="35" QFormat="true" Name="caption"/>
  <w:LsdException Locked="false" Priority="10" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Title"/>
  <w:LsdException Locked="false" Priority="1" Name="Default Paragraph Font"/>
  <w:LsdException Locked="false" Priority="11" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Subtitle"/>
  <w:LsdException Locked="false" Priority="22" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Strong"/>
  <w:LsdException Locked="false" Priority="20" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Emphasis"/>
  <w:LsdException Locked="false" Priority="59" SemiHidden="false"
   UnhideWhenUsed="false" Name="Table Grid"/>
  <w:LsdException Locked="false" UnhideWhenUsed="false" Name="Placeholder Text"/>
  <w:LsdException Locked="false" Priority="1" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="No Spacing"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 1"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 1"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 1"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 1"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 1"/>
  <w:LsdException Locked="false" UnhideWhenUsed="false" Name="Revision"/>
  <w:LsdException Locked="false" Priority="34" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="List Paragraph"/>
  <w:LsdException Locked="false" Priority="29" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Quote"/>
  <w:LsdException Locked="false" Priority="30" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Intense Quote"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 1"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 1"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 1"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 1"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 1"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 1"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 1"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 2"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 2"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 2"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 2"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 2"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 2"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 2"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 2"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 2"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 2"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 3"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 3"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 3"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 3"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 3"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 3"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 3"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 3"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 3"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 3"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 4"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 4"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 4"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 4"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 4"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 4"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 4"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 4"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 4"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 4"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 5"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 5"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 5"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 5"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 5"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 5"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 5"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 5"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 5"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 5"/>
  <w:LsdException Locked="false" Priority="60" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Shading Accent 6"/>
  <w:LsdException Locked="false" Priority="61" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light List Accent 6"/>
  <w:LsdException Locked="false" Priority="62" SemiHidden="false"
   UnhideWhenUsed="false" Name="Light Grid Accent 6"/>
  <w:LsdException Locked="false" Priority="63" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="64" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Shading 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="65" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="66" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium List 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="67" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 1 Accent 6"/>
  <w:LsdException Locked="false" Priority="68" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 2 Accent 6"/>
  <w:LsdException Locked="false" Priority="69" SemiHidden="false"
   UnhideWhenUsed="false" Name="Medium Grid 3 Accent 6"/>
  <w:LsdException Locked="false" Priority="70" SemiHidden="false"
   UnhideWhenUsed="false" Name="Dark List Accent 6"/>
  <w:LsdException Locked="false" Priority="71" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Shading Accent 6"/>
  <w:LsdException Locked="false" Priority="72" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful List Accent 6"/>
  <w:LsdException Locked="false" Priority="73" SemiHidden="false"
   UnhideWhenUsed="false" Name="Colorful Grid Accent 6"/>
  <w:LsdException Locked="false" Priority="19" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Subtle Emphasis"/>
  <w:LsdException Locked="false" Priority="21" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Intense Emphasis"/>
  <w:LsdException Locked="false" Priority="31" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Subtle Reference"/>
  <w:LsdException Locked="false" Priority="32" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Intense Reference"/>
  <w:LsdException Locked="false" Priority="33" SemiHidden="false"
   UnhideWhenUsed="false" QFormat="true" Name="Book Title"/>
  <w:LsdException Locked="false" Priority="37" Name="Bibliography"/>
  <w:LsdException Locked="false" Priority="39" QFormat="true" Name="TOC Heading"/>
 </w:LatentStyles>
</xml><![endif]--><!--[if gte mso 10]>
<style>
 /* Style Definitions */
 table.MsoNormalTable
	{mso-style-name:"Table Normal";
	mso-tstyle-rowband-size:0;
	mso-tstyle-colband-size:0;
	mso-style-noshow:yes;
	mso-style-priority:99;
	mso-style-qformat:yes;
	mso-style-parent:"";
	mso-padding-alt:0in 5.4pt 0in 5.4pt;
	mso-para-margin:0in;
	mso-para-margin-bottom:.0001pt;
	mso-pagination:widow-orphan;
	font-size:11.0pt;
	font-family:"Calibri","sans-serif";
	mso-ascii-font-family:Calibri;
	mso-ascii-theme-font:minor-latin;
	mso-fareast-font-family:"Times New Roman";
	mso-fareast-theme-font:minor-fareast;
	mso-hansi-font-family:Calibri;
	mso-hansi-theme-font:minor-latin;
	mso-bidi-font-family:Arial;
	mso-bidi-theme-font:minor-bidi;}
</style>
<![endif]-->

<p class="MsoNormal" dir="RTL" style="text-align:right;direction:rtl;unicode-bidi:
embed"><span lang="AR-SA">Ø§Ø³ ÙˆÛŒØ¨ Ø³Ø§Ø¦Ù¹ Ú©Ø§ Ø§Ø³ØªØ¹Ù…Ø§Ù„ Ú©ÛŒØ³Û’ Ú©Ø±ÙˆÚºØŸ</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø¨Ø±Ø§Ø¤Ø²Ø± Ú©ÛŒ Ø³ÛÙˆÙ„Øª Ù…ÛÛŒØ§</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø§Ø³ Ø³Ø§Ø¦Ù¹ Ú©Ùˆ Ù…Ù†Ø¯Ø±Ø¬Û Ø°ÛŒÙ„ Ú©Û’ ØªØ§Ø²Û ØªØ±ÛŒÙ† ÙˆØ±Ú˜Ù† Ú©Û’ Ø³Ø§ØªÚ¾ Ú©Ø§Ù…
Ú©Ø±Ù†Ø§ Ú†Ø§ÛØ¦Û’</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span dir="LTR"></span>:<br>
</span><span lang="AR-SA">ÙØ§Ø¦Ø± ÙØ§Ú©Ø³</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ú©Ø±ÙˆÙ…</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø³ÙØ§Ø±ÛŒ</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø§Ù†Ù¹Ø± Ù†ÛŒÙ¹ Ø§ÛŒÚ©Ø³Ù¾Ù„ÙˆØ±Ø± </span><span style="mso-bidi-language:FA" lang="FA">Û¸</span><span lang="AR-SA"> Ø§ÙˆØ± </span><span style="mso-bidi-language:FA" lang="FA">Û·</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø§Ø¨Ú¾ÛŒ Ø¢Ù†Û’ ÙˆØ§Ù„Û’ ÛÛŒÚº</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span dir="LTR"></span>:<br>
</span><span lang="AR-SA">Ø§Ø¶Ø§ÙÛŒ Ø¨Ø±Ø§Ø¤Ø²Ø±Ø² Ø¬ÛŒØ³Û’(Ø§ÙˆÙ¾ÛŒØ±Ø§</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span dir="LTR"></span> Opera( </span><span lang="AR-SA">Ú©Û’ Ø°Ø±ÛŒØ¹Û’ Ø¬Ø§Ù†Ú†ØŒ Ø§ÙˆØ± Ø¢ÛŒ Ø§ÛŒ </span><span style="mso-bidi-language:
FA" lang="FA">Û¶</span><span lang="AR-SA"> Ú©Û’ Ø°Ø±ÛŒØ¹Û’ Ù…Ø¹Ù„ÙˆÙ… Ù…Ø³Ø§Ø¦Ù„ Ú©Ùˆ Ø­Ù„ Ú©Ø±Ù†Ø§</span><span dir="LTR"><br>
</span><span lang="AR-SA">ØªÙ„Ø§Ø´ Ú©ÛŒÙ„Ø¦Û’ Ù†Ø§Ù… Ø¯Ø±Ø¬ Ú©Ø±Ù†Ø§</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ù†Ø§Ù… Ú©Û’ Ø®Ø§Ù†Û Ù…ÛŒÚº Ú©Ú†Ú¾ Ø§ÛŒØ³Ø§ Ø¯Ø±Ø¬ Ú©Ø±ÛŒÚº</span><span dir="LTR"><br>
)</span><span lang="AR-SA">ÚˆÙˆ Ø¬ÙˆØ²Ù</span><span dir="LTR">Doe, Joseph(<br>
)</span><span lang="AR-SA">Ø¬ÙˆØ²Ù Úˆ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ùˆ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span dir="LTR">Joseph
Doe (<br>
)</span><span lang="AR-SA">Ø¬ÙˆÙ†ØŒØ¬ÙˆÙ†ÛŒ ØŒ Ø¬ÙˆÙ†ÛŒ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span dir="LTR"></span>(</span><span dir="RTL"></span><span dir="RTL"></span><span lang="AR-SA"><span dir="RTL"></span><span dir="RTL"></span>ØŒ</span><span dir="LTR">John Johnny Johnnie Jonnie<br>
)</span><span lang="AR-SA">Ø¬ÙˆÚ¾</span><span dir="LTR">Joh<span style="mso-spacerun:yes">&nbsp; </span>(<br>
</span><span lang="AR-SA">Ù¾Ú¾Ø± ØªÙ„Ø§Ø´ Ú©Ø§ Ø¨Ù¹Ù† Ø¯Ø¨Ø§Ø¦ÛŒÚºÛ”</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span>
</span><span dir="RTL"></span><span dir="RTL"></span><span lang="AR-SA"><span dir="RTL"></span><span dir="RTL"></span>[Ù¹Ùˆ ÚˆÙˆ ÛŒØ§ Ø§Ù†Ù¹Ø± Ú©Ø§ Ø¨Ù¹Ù†]Û”</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ù†ØªØ§Ø¦Ø¬ Ù„ÙˆÚˆ Ú©Ø±Ù†Û’ Ù…ÛŒÚº Ú©Ú†Ú¾</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">ÙˆÙ‚Øª Ù„Ú¯Û’ Ú¯Ø§Û”</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span>
</span><span lang="AR-SA">Ø³Ú©Ø±ÛŒÙ† Ù…ÛŒÚº Ø³Ø¨ Ø³Û’ Ø§ÙˆÙ¾Ø±</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span>
</span><span lang="AR-SA">Ø§Ø³ ÙˆÙ‚Øª ÚˆÛŒÙ¹Ø§ Ø¨ÛŒØ³ Ù…ÛŒÚº Ù…ÙˆØ¬ÙˆØ¯ Ø±ÛŒÚ©Ø§Ø±Úˆ Ú©ÛŒ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ú©Ù„ ØªØ¹Ø¯Ø§Ø¯ ÛÛ’Û” Ø§ÙˆØ±Ø¬ÛŒØ³Û’ Ø¬ÛŒØ³Û’ ÛØ± Ù…Ù„Ø§ ÛÙˆØ§
Ø±ÛŒÚ©Ø§Ø±Úˆ Ø§ÛŒÚ© ØªØµÙˆÛŒØ± Ú©Û’ Ø·ÙˆØ± Ù¾Ø±Ø¸Ø§ÛØ± ÛÙˆØªØ§</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">ÛÛ’ØŒ Ø§Ø³Ú©Ø§ Ø¨Ú‘Ú¾ØªØ§ ÛÙˆØ§ Ø´Ù…Ø§Ø±Û”</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ù†ØªØ§Ø¦Ø¬ Ù…ÛŒÚº ÙˆÛ Ø³Ø¨ Ú©Ú†Ú¾ Ø¬Ø³ Ù…ÛŒÚº Ø¢Ù¾Ú©Û’ Ø¯Ø±Ø¬ Ú©Ø±Ø¯Û</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ø§Ù„ÙØ§Ø¸ Ù…ÛŒÚº Ø³Û’ Ú©ÙˆØ¦ÛŒ Ø¨Ú¾ÛŒ Ù„ÙØ¸ ÛŒØ§</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ù„Ø§Ø­Ù‚Û Ù…ÙˆØ¬ÙˆØ¯ ÛÙˆØŒ Ø´Ø§Ù…Ù„ ÛÙˆ Ø³Ú©ØªØ§ ÛÛ’Û”Ø³ÙˆØ§Ø¦Û’
Ø§Ø¨ØªØ¯Ø§Ø¦ÛŒ Ø§Ù„ÙØ§Ø¸ Ú©Û’(Ø§ÛŒÚ© Ø®Ø· Ú©Û’ Ú©Ø³ÛŒ Ø¨Ú¾ÛŒ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ù„ÙØ¸ Ú©Ùˆ Ù†Ø¸Ø± Ø§Ù†Ø¯Ø§Ø² Ú©Ø± Ø¯ÛŒØ§ Ø¬Ø§Ø¦Û’ Ú¯Ø§)Û” Ø¬Ø¨ Ø¢Ù¾</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span>
</span><span dir="RTL"></span><span dir="RTL"></span><span lang="AR-SA"><span dir="RTL"></span><span dir="RTL"></span>[ â€™ÚˆØ§Ú©Ù¹Ø±</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span dir="LTR"></span>â€˜ </span><span dir="RTL"></span><span dir="RTL"></span><span lang="AR-SA"><span dir="RTL"></span><span dir="RTL"></span>ØŒ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span dir="LTR"></span>â€™</span><span lang="AR-SA">Ù…Ø³Ø²â€˜ ] Ø¬ÛŒØ³Û’
Ø¹Ù†ÙˆØ§Ù†Ø§Øª</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">ÛŒØ§
Ø§Ø¶Ø§ÙÛŒ Ø§Ù„ÙØ§Ø¸ Ø¬ÛŒØ³Û’ [â€™Ø¬ÙˆÙ†Ø¦ÛŒØ±â€˜] Ø¯Ø±Ø¬ Ú©Ø±ØªÛ’ ÛÛŒÚº ØŒ ÛŒÛ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span>
</span><span lang="AR-SA">ØºÛŒØ± Ù…Ø·Ù„ÙˆØ¨Û Ù†ØªØ§Ø¦Ø¬ Ú©ÛŒ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span>
</span><span lang="AR-SA">ØªØ¹Ø¯Ø§Ø¯ Ú©Ùˆ Ú©Ù… Ú©Ø±Ù†Û’ Ú©ÛŒ Ø¨Ø¬Ø§Ø¦Û’ Ø§Ù† Ù…ÛŒÚº Ø§Ø¶Ø§ÙÛ’ Ú©Ø§ Ø³Ø¨Ø¨ Ø¨Ù†ØªØ§ ÛÛ’Û”</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ø§Ø³ ÙˆÙ‚Øª</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span>
</span><span dir="LTR">)</span><span lang="AR-SA">Ø§ÛŒÚ©Ø³Ù†Ù¹Úˆ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span>
</span><span dir="LTR">accented( </span><span lang="AR-SA">Ø­Ø±ÙˆÙ Ø¯Ø±Ø¬ Ù†Û Ú©Ø±ÛŒÚº Ø¨Ù„Ú©Û Ø§Ù†
Ú©Û’ Ù…ØªØ±Ø§Ø¯Ù(Ø§Ù†</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ø§ÛŒÚ©Ø³Ù†Ù¹Úˆ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span dir="LTR">unaccented( </span><span lang="AR-SA">Ø§Ù„ÙØ§Ø¸
Ø¯Ø±Ø¬ Ú©Ø±ÛŒÚºÛ”</span><span dir="LTR"><br>
</span><span lang="AR-SA">ØªÙÛÛŒÙ… Ù†ØªØ§Ø¦Ø¬</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø¬Ø¨ Ú©ÙˆØ¦ÛŒ ØªØµÙˆÛŒØ± Ù…ÛÛŒØ§ Ù†ÛÛŒÚº Ú©ÛŒ Ø¬Ø§ØªÛŒ ØªÙˆ Ù†ØªØ§Ø¦Ø¬</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">ØªØµØ§ÙˆÛŒØ± ÛŒØ§(Ø³Ù„ Ú¾ÙˆÙ¹Û’</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span>
</span><span dir="LTR">silhouette ( </span><span lang="AR-SA">ØªØµØ§ÙˆÛŒØ± Ú©ÛŒ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">ØªÛŒÙ† Ù‚Ø·Ø§Ø±ÙˆÚº Ú©ÛŒ ØµÙˆØ±Øª Ù…ÛŒÚº Ø¸Ø§ÛØ± ÛÙˆØªÛ’
ÛÛŒÚºÛ”ØªØµØ§ÙˆÛŒØ± Ø¯Ø§Ø¦ÛŒÚº Ø·Ø±Ù Ø³Û’ Ø´Ø±ÙˆØ¹</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">ÛÙˆ Ú©Ø± Ø§ÙˆÙ¾Ø± Ø³Û’ Ù†ÛŒÚ†Û’ Ú©ÛŒ Ù‚Ø·Ø§Ø± ØªÚ© ÛŒÚ©Ø³Ø§Úº ØªÙ‚Ø³ÛŒÙ… ÛÙˆØªÛŒ ÛÛŒÚºÛ” Ø§Ú¯Ø± ØªØµØ§ÙˆÛŒØ± Ø²ÛŒØ§Ø¯Û</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">ÛÛŒÚº Ø¬Ù†ÛÛŒÚº ÙÙˆØ±ÛŒ Ø·ÙˆØ± Ù¾Ø± Ø¯Ú©Ú¾Ø§ÛŒØ§ Ø¬Ø§ Ø³Ú©ØªØ§ ÛÛ’
ØªÙˆ Ù‚Ø·Ø§Ø±ÛŒÚº Ø§ÙÙ‚ÛŒ Ø·ÙˆØ± Ù¾Ø± (Ø±ÛŒÙ¾</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ø§Ø±Ø§Ø¤Ù†Úˆ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span dir="LTR"></span><span style="mso-spacerun:yes">&nbsp;&nbsp; </span>wrap-around (</span><span lang="AR-SA">Ú©Û’ Ø³Ø§ØªÚ¾
Ù…ØªØ­Ø±Ú© ÛÙˆ Ø¬Ø§Ø¦ÛŒÚº Ú¯ÛŒÛ”Ø§Ø³ ÙˆÙ‚Øª ØªØµØ§ÙˆÛŒØ± Ú©Ùˆ Ø¢Ø±ÚˆØ± Ù…ÛŒÚº</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span>
</span><span lang="AR-SA">Ù†ÛÛŒÚº Ú©Ø± Ø³Ú©ØªÛ’Û”</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø¯ÛŒ ÛÙˆØ¦ÛŒ ØªØµØ§ÙˆÛŒØ± Ú©Û’ Ø¨Ø§Ø±Û’ Ù…ÛŒÚº ØªÙØµÛŒÙ„Ø§Øª Ø­Ø§ØµÙ„ Ú©Ø±Ù†Ø§</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ú©Ø³ÛŒ Ù…Ø®ØµÙˆØµ ØªØµÙˆÛŒØ± Ù¾Ø± Ø§Ù¾Ù†Ø§ Ù…Ø§Ø¤Ø³ Ù„Û’ Ø¬Ø§Ø¦ÛŒÚºÛ”(ÙˆÙ†ÚˆÙˆØ²</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span dir="LTR">window( </span><span lang="AR-SA">Ú©Û’
Ù†ÛŒÚ†Û’(Ø³Ù¹ÛŒÙ¹Ø³ Ø¨Ø§Ø±</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span dir="LTR"></span><span style="mso-spacerun:yes">&nbsp; </span>status
bar ( </span><span lang="AR-SA">Ù…ÛŒÚº Ù…ØªÙ† Ú©ÛŒ ØªÙØµÛŒÙ„Ø§Øª Ø¸Ø§ÛØ± ÛÙˆÙ†Ú¯ÛŒÛ”Ù†ÙˆÙ¹: Ø§Ú¯Ø± Ø¢Ù¾ Ø§Ù¾Ù†Ø§
Ú©Ø±Ø³Ø± Ú©Ø³ÛŒ Ø®Ø§Øµ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ø¬Ú¯Û
Ù¾Ø± Ú†Ú¾ÙˆÚ‘ Ø¯ÛŒÚº ØªÙˆ Ø§ÙÙ‚ÛŒ Ø³Ú©Ø±ÙˆÙ„Ø± ØªØµØ§ÙˆÛŒØ± Ú©Ùˆ Ú©Ø±Ø³Ø± Ú©Û’ Ù†ÛŒÚ†Û’ Ù„Û’ Ø¢Ø¦Û’ Ú¯Ø§Û”Ú©Ú†Ú¾</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ø¨Ø±Ø§Ø¤Ø²Ø±Ø² Ù…ÛŒÚº(Ø³Ù¹ÛŒÙ¹Ø³ Ø¨Ø§Ø±</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span dir="LTR">status bar ( </span><span lang="AR-SA">Ú©Ø§
Ù…ØªÙ† Ø®ÙˆØ¯Ø¨Ø®ÙˆØ¯ ØªØ¨Ø¯ÛŒÙ„ Ù†ÛÛŒÚº ÛÙˆ Ú¯Ø§ØŒØ¢Ù¾Ú©Ùˆ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ø§Ù¾Ù†Û’ Ù…Ø§Ø¤Ø³ Ú©ÛŒ Ø¬Ú¯Û Ø¨Ø¯Ù„Ù†ÛŒ Ù¾Ú‘Û’ Ú¯ÛŒÛ”</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø§Ø¶Ø§ÙÛŒ ÙÙ„Ù¹Ø± Ú†ÛŒÚ© Ø¨Ø§Ú©Ø³Ø²</span><span dir="LTR"><br>
</span><span lang="AR-SA">ÙØ·Ø±ÛŒ Ø·ÙˆØ± Ù¾Ø± ØŒØªÙ…Ø§Ù… Ø§ÙØ±Ø§Ø¯ ØŒ Ú¯Ù…Ø´Ø¯Û ÛŒØ§ Ø²Ù†Ø¯Û ØªÙ„Ø§Ø´ Ú©Ø¦Û’
Ú¯Ø¦Û’ØŒÙ¹Ú¾ÛŒÚ© ÛŒØ§ Ø²Ø®Ù…ÛŒØŒØ¯Ú©Ú¾Ø§Ø¦Û’ Ø¬Ø§Ø¦ÛŒÚº Ú¯Û’Û” Ø¢Ù¾ Ø§Ø³ Ù…ÛŒÚº ØªØ¨Ø¯ÛŒÙ„ÛŒ Ú©Ø± Ø³Ú©ØªÛ’ ÛÛŒÚºÛ”</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø±ÙˆÚ©Ù†Û’ Ø§ÙˆØ± Ú†Ù„Ø§Ù†Û’ ÙˆØ§Ù„Û’ Ø¨Ù¹Ù†</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø§Ú¯Ø± Ø§ÙÙ‚ÛŒ Ø³Ú©Ø±ÙˆÙ„Ù†Ú¯ Ù…ÙˆØ¬ÙˆØ¯ ÛÛ’ ØªÙˆ â€™Ø±ÙˆÚ©Ù†Û’ Ú©Ø§ Ø¨Ù¹Ù†â€˜ Ø§Ø³Û’ Ø±ÙˆÚ© Ø¯Û’
Ú¯Ø§ØŒ Ø§ÙˆØ± â€™Ú†Ù„Ø§Ù†Û’</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span dir="LTR"></span>â€˜ </span><span lang="AR-SA">Ú©Ø§ Ø¨Ù¹Ù† Ø§Ø³Û’ Ø¯ÙˆØ¨Ø§Ø±Û
Ø´Ø±ÙˆØ¹ Ú©Ø± Ø¯Û’ Ú¯Ø§Û”ÛŒÛØ§Úº ØªÚ© Ú©Û Ø§Ú¯Ø± Ø±ÙˆÚ© Ø¯ÛŒØ§ Ú¯ÛŒØ§ ØªÙˆØ¨Ú¾ÛŒ ØªØ§Ø²Û</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span>
</span><span lang="AR-SA">Ù…ÙˆØ§Ø¯ Ú©Ùˆ ØªÙ„Ø§Ø´ Ú©Ø±Ù†Û’ Ú©Û’ Ù„Ø¦Û’ Ø³Ø±Ú† ÛØ± Ù…Ù†Ù¹ Ø¯ÙˆÛØ±Ø§Ø¦ÛŒ Ø¬Ø§Ø¦Û’ Ú¯ÛŒÛ”</span><span dir="LTR"><br>
</span><span lang="AR-SA">ØµØ§Ù Ú©Ø±Ù†Û’ Ú©Ø§ Ø¨Ù¹Ù†</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ù†Ø¦ÛŒ Ø³Ø±Ú† Ú©ÛŒ ØªÛŒØ§Ø±ÛŒ Ú©ÛŒÙ„Ø¦Û’ Ø³Ú©Ø±ÛŒÙ† Ø³Û’ ØªØµØ§ÙˆÛŒØ± Ø§ÙˆØ± Ù†Ø§Ù… Ú©Û’ Ø®Ø§Ù†Û’
Ú©Ùˆ Ø®Ø§Ù„ÛŒ Ú©Ø±ØªØ§ ÛÛ’Û”</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ú©Ø³ Ù‚Ø³Ù… Ú©ÛŒ Ù…Ø¹Ù„ÙˆÙ…Ø§Øª Ú©Ùˆ ØªÙ„Ø§Ø´ Ú©ÛŒØ§ Ø¬Ø§ Ø±ÛØ§ ÛÛ’ Ø§ÙˆØ± Ú©ØªÙ†ÛŒ Ú©Ø«Ø±Øª
Ø³Û’ Ø§Ù†ÛÛŒÚº Ø§Ù¾ÚˆÛŒÙ¹ Ú©ÛŒØ§ Ø¬Ø§ØªØ§ ÛÛ’</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø¬Ø¨ Ø³Ø±Ú† Ú©Û’ Ù†ØªØ§Ø¦Ø¬ Ú©Û’ Ø·ÙˆØ± Ù¾Ø±ØªØµØ§ÙˆÛŒØ± Ú©Ø§ Ù…Ø¬Ù…ÙˆØ¹Û Ù„ÙˆÚˆ Ú©ÛŒØ§ Ø¬Ø§ØªØ§
ÛÛ’ ØªÙˆÛØ± Ù…Ù†Ù¹ ÛŒÛ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ø¯ÛŒÚ©Ú¾Ù†Û’ Ú©Û’ Ù„Ø¦Û’ Ú©Û Ø´Ø§Ù…Ù„ Ú©Ø±Ù†Û’ Ú©ÛŒÙ„Ø¦Û’ Ù†ÛŒØ§ Ù…ÙˆØ§Ø¯ ÛÛ’ØŒ Ø³Ø±Ú† Ø®Ø§Ù…ÙˆØ´ÛŒ Ø³Û’ Ø¯ÛØ±Ø§Ø¦ÛŒ
Ø¬Ø§ØªÛŒ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">ÛÛ’Û”</span><span dir="LTR"><br>
</span><span lang="AR-SA">ÙÛŒ Ø§Ù„Ø­Ø§Ù„ Ù…Ø¹Ù„Ùˆ Ù…Ø§Øª Ø§Ù† Ø°Ø±Ø§Ø¦Ø¹ Ø³Û’ Ø¢ Ø±ÛÛŒ ÛÛŒÚº</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span dir="LTR"></span>:<br>
</span><span lang="AR-SA">Ú¯ÙˆÚ¯Ù„ Ú©Ø§</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ù¾ÛŒÙ¾Ù„ ÙØ§Ø¦Ù†ÚˆØ±</span><span dir="LTR"><br>
</span><span lang="AR-SA">Ø¨Ø±Ø§ÛØ±Ø§Ø³Øª Ø§ÛŒ Ù…ÛŒÙ„ Ú©Û’ Ø°Ø±ÛŒØ¹Û’ Ø­Ø§ØµÙ„ Ú©ÛŒØ§ Ú¯ÛŒØ§ Ù…ÙˆØ§Ø¯</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span dir="LTR">)</span><span lang="AR-SA">Ù…Ø«Ø§Ù„ Ú©Û’ Ø·ÙˆØ± Ù¾Ø±
ÛÙ…Ø§Ø±ÛŒ Ù…ÙˆØ¨Ø§Ø¦Ù„ Ø§Ù¾Ù„ÛŒÚ©ÛŒØ´Ù†</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span dir="LTR"></span>(<br>
</span><span lang="AR-SA">ÛÙ…Ø§Ø±Û’ Ù¾Ø§Ø³ Ø§Ù† Ø§Ø¶Ø§ÙÛŒ Ø°Ø±Ø§Ø¦Ø¹ Ø³Û’ Ù…Ø¹Ù„ÙˆÙ…Ø§Øª Ø­Ø§ØµÙ„ Ú©Ø±Ù†Û’ Ú©ÛŒ ØªÚ©Ù†ÛŒÚ©ÛŒ
ØµÙ„Ø§Ø­ÛŒØª Ø¨Ú¾ÛŒ ÙˆØ¬ÙˆØ¯ ÛÛ’</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span dir="LTR"></span>:<br>
</span><span lang="AR-SA">Ø³ÛŒ Ø§ÛŒÙ† Ø§ÛŒÙ†(Ø¢Ø¦ÛŒ Ø±Ù¾ÙˆØ±Ù¹Ø³</span><span dir="LTR">iReports (<br>
</span><span lang="AR-SA">Ø¯ÙˆØ³Ø±ÛŒ(Ø³Ø§Ø­Ø§Ù†Ø§</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span dir="LTR"></span> Sahana( </span><span lang="AR-SA">Ù…Ø«Ø§Ù„ÛŒÚº(ÛÙ…Ø§Ø±Û’ Ø¹Ù„Ø§ÙˆÛ</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR"><span dir="LTR"></span><span dir="LTR"></span>(<br>
</span><span lang="AR-SA">Ø¨Ø±Ø§Û Ø±Ø§Ø³Øª Ø§ÛŒ Ù…ÛŒÙ„ Ø±Ù¾ÙˆØ±Ù¹Ù†Ú¯ Ú©Û’ Ø¹Ù„Ø§ÙˆÛØŒ ÛŒÛ Ø³Ø¨ Ø°Ø±Ø§Ø¦Ø¹ Ø¨ÛØª Ø³ÛŒ
Ø¬Ú¯ÛÙˆÚº Ù¾Ø±(Ø¬ÛŒØ³Û’</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span> </span><span lang="AR-SA">Ø§Ù†Ù¹Ø±
Ù†ÛŒØ´Ù†Ù„ Ø±ÛŒÚˆ Ú©Ø±Ø§Ø³ Ú©ÛŒ Ú©Ù…ÛŒÙ¹ÛŒ)Ù…Ø¬Ù…ÙˆØ¹ÛŒ Ù…Ø¹Ù„ÙˆÙ…Ø§Øª Ø¯ÛŒØªÛ’</span><span dir="LTR"></span><span dir="LTR"></span><span dir="LTR" lang="AR-SA"><span dir="LTR"></span><span dir="LTR"></span>
</span><span lang="AR-SA">ÛÛŒÚºÛ”</span><span dir="LTR"><br>
</span><span lang="AR-SA">ÛŒÛØ§Úº Ø¨Ù„Ø§Ø´Ø¨Û Ø±ÛŒÚ©Ø§Ø±Úˆ Ú©ÛŒ Ù†Ù‚ÙˆÙ„ Ø¨Ú¾ÛŒ Ù…ÙˆØ¬ÙˆØ¯ ÛÙˆÚº Ú¯ÛŒØŒ Ø¬Ù†ÛÛŒÚº ÛÙ…
ÙˆÙ‚Øª Ú©Û’ Ø³Ø§ØªÚ¾ Ø³Ø§ØªÚ¾ Ú©Ù… Ú©Ø±Ù†Û’ Ú©ÛŒ Ú©ÙˆØ´Ø´ Ú©Ø±ÛŒÚº Ú¯Û’Û”</span></p>

')
