<?php
/**
 * @name         Person Finder Interchange Format
 * @version      2
 * @package      pfif
 * @author       Carl H. Cornwell <ccornwell at aqulient dor com>
 * @author       Leif Neve <lneve@mail.nih.gov>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0223
 */


global $tabid;
$tabid = isset($_GET['tabid']) ? $_GET['tabid'] : 0;
$tabid = "&tabid=".$tabid;

global $global;
global $conf;
require_once($global['approot'].'/inc/lib_modules.inc');
require_once($global['approot'].'/inc/lib_form.inc');
require_once($global['approot'].'/inc/lib_validate.inc');
require_once($global['approot'].'/inc/lib_errors.inc');
require_once($global['approot'].'/inc/lib_image.inc');
require_once('lib_pfif.inc');
require_once('pfif.inc');



/** the default module action... */
function shn_pfif_default() {

	global $global;

	$control = "";

	shn_tabmenu_open();
	shn_tabmenu_item("status", _t("PFIF Service Status"), "pfif");
	shn_tabmenu_item("import", _t("Import PFIF"),         "pfif");
	shn_tabmenu_item("export", _t("Export PFIF"),         "pfif");
	shn_tabmenu_close();

	if(isset($_GET['status'])) {
		$control = "shn_pfif_status";

	} elseif(isset($_GET['import'])) {
		$control = "shn_pfif_import";

	} elseif(isset($_GET['export'])) {
		$control = "shn_pfif_export";
	}

	if($control == "") {
		$control = "shn_pfif_status";
	}

	$control();
}



/** Manage PFIF Import sessions */
function shn_pfif_import() {

	global $global;
	global $tabid;

	echo "<br>";

	// If there is no post, render the form to upload.
	if(isset( $_POST['upload'])) {
		if( $_FILES['xml']['error'] != 0){
			// Validate
			add_error(_t('Please enter a filename to upload'));
			unset($_FILES); unset($_POST);
			shn_pfif_import();
		} else {
			// If there is a post, upload the file and import the file to the database.
			if (is_uploaded_file($_FILES['xml']['tmp_name'])) {
				$pfif = new Pfif();
				$loaded = $pfif->loadFromXML($_FILES['xml']['tmp_name']);
				if ($loaded > 0) {
					//$xml = $pfif->storeInXML();
					//print "<pre>$xml</pre>";
					$stored = $pfif->storeInDatabase($_POST['pfif_incident_id']);
					// Get incident name.
					$sql = "SELECT name from incident where incident_id=".$_POST['pfif_incident_id'];
					$res = $global['db']->GetRow($sql);
					$name = $res['name'];
					if($stored['person']==0 && $stored['note']==0) {
						add_error("No records were imported into the '$name' event.");
					} else {
						add_confirmation('Successfully imported '.$stored['person'].' persons and '.$stored['note']." notes into the '$name' event.");
					}
				} else {
					add_error('File not loaded. Please confirm that it contains valid XML.');
				}
			}
		}
	}
        // Submitted form calls this function again.
	shn_form_fopen2("pfif?import".$tabid, null, array('enctype'=>'enctype="multipart/form-data"', 'req_message' => false));
        //shn_form_fopen("import",null,array('enctype'=>'enctype="multipart/form-data"','req_message' => false));
		shn_form_fsopen(_t('Import from PFIF File'));
		shn_form_hidden(array('upload'=>'upload'));
		shn_form_upload(_t('PFIF filename'),'xml',array('max_file_size'=>'128M'));
		shn_pfif_incident_select("Import to this event");
		echo "<br><br><span style=\"margin-left: 200pt;\"></span>";
		shn_form_submit(_t("Upload"), "class=\"styleTehButton\"");
		shn_form_fsclose();
        shn_form_fclose();
}



/** Note: This could be made a more generic "shn_incident_select" if others could benefit from it. */
function shn_pfif_incident_select($label) {

        global $global;

        // For now, leave everything unselected. (First event selected by default.)
        $incident_id = 999;
        ?> <label for="pfif_incident"><?php echo $label;?></label><select name="pfif_incident_id"><?php
        $query1 = "SELECT incident_id, name FROM incident WHERE parent_id IS NULL";
        $result1 = $global['db']->Execute($query1);
        while($row1 = $result1->FetchRow()){
                ?><option value="<?php echo $row1['incident_id'];?>"  <?php echo ($incident_id==$row1['incident_id']?'selected="selected"':'');?> >&nbsp;&nbsp;&nbsp;<?php echo $row1['name'];?></option><?php
                $query2 = "SELECT incident_id, name FROM incident WHERE parent_id = '".$row1['incident_id']."';";
                $result2 = $global['db']->Execute($query2);
                while($row2 = $result2->FetchRow() ){
                        ?><option value="<?php echo $row2['incident_id'];?>"  <?php echo ($incident_id==$row2['incident_id']?'selected="selected"':'');?>  >&nbsp;&nbsp;&#8211;&nbsp;<?php echo $row2['name'];?></option><?php
                        $query3 = "SELECT incident_id, name FROM incident WHERE parent_id = '".$row2['incident_id']."'";
                        $result3 = $global['db']->Execute($query3);
                        while($row3 = $result3->FetchRow() ){
                                ?><option value="<?php echo $row3['incident_id'];?>"  <?php echo ($incident_id==$row3['incident_id']?'selected="selected"':'');?>  >&nbsp;&nbsp;&nbsp;&nbsp;&#8211;&nbsp;<?php echo $row3['name'];?></option><?php
                        }
                }
        }
        ?></select><?php
}


/** Manage PFIF Export sessions */
function shn_pfif_export() {

	global $global;

	echo "<br><script type=\"text/javascript\" src=\"res/datetimepicker/datetimepicker_css.js\"></script>";

	// Create a form that when submitted calls shn_xml_pfif_export() below.
	shn_form_fopen("export",null,array('req_message' => false),"xml");

	shn_form_fsopen(_t('Export to PFIF XML'));
	shn_pfif_incident_select("Export from this event");
	echo "<br><div class='brake'></div>";
	$extra_opts['br'] = false;
	shn_form_text(_t('Start date'),'since','',$extra_opts);
	echo "<img src=\"res/datetimepicker/cal.gif\"
		onclick=\"javascript:NewCssCal('since','yyyyMMdd','arrow',true,24,true,'past')\"
		style=\"cursor:pointer\"/>";
	echo "<br><div class='brake'></div>";
	$extra_opts['br'] = false;
	shn_form_text(_t('End date'),'before','',$extra_opts);
	echo "<img src=\"res/datetimepicker/cal.gif\"
		onclick=\"javascript:NewCssCal('before','yyyyMMdd','arrow',true,24,true,'past')\"
		style=\"cursor:pointer\"/>";
	echo "<br><div class='brake'></div>";
	shn_form_checkbox(_t('Records originating in PL only'),'original');
	shn_form_hidden(array('filename'=>'export.xml','download'=>'download'));
	echo "<span style=\"margin-left: 200pt;\"></span>";
	shn_form_submit(_t('Submit'));
	shn_form_fsclose();
	shn_form_fclose();
}



/** Return system cron status. Used for navigation menu status indicator. */
function shn_pfif_status_code() {

   global $global, $deltaOut;

   if(!defined('RED')) {
      define('RED', 0);
   }
   if(!defined('ORANGE')) {
      define('ORANGE', 1);
   }
   if(!defined('GREEN')) {
      define('GREEN', 2);
   }

   $log_dir = $global['approot'].'www/tmp/pfif_logs/';
   $export_out = $log_dir . 'export.out';
   $import_out = $log_dir . 'import.out';
   $import_err = $log_dir . 'import.err';
   $export_err = $log_dir . 'export.err';

   // Check both output files to make sure they are getting updated.
   $lastImportOut = filemtime($import_out);
   $lastExportOut = filemtime($export_out);
   // we are interested in the number of seconds since the oldest timestamp.
   $deltaImportOut = date("U") - $lastImportOut;
   $deltaExportOut = date("U") - $lastExportOut;
   $deltaOut = ($deltaImportOut > $deltaExportOut)? $deltaImportOut:$deltaExportOut;

   // Check for non-zero-size error file.
   $errors = filesize($export_err)!=0 || filesize($import_err)!=0;

   // Check both error files to make sure they aren't recently updated.
   // (If errors only occur intermittantly, we treat it as a warning.)
   $lastImportErr = filemtime($import_err);
   $lastExportErr = filemtime($export_err);
   // we are interested in the number of seconds since the most recent timestamp.
   $deltaImportErr = date("U") - $lastImportErr;
   $deltaExportErr = date("U") - $lastExportErr;
   $deltaErr = ($deltaImportErr < $deltaExportErr)? $deltaImportErr:$deltaExportErr;

   if ($deltaOut < 120 && !$errors) {
      // Recent output and no errors.
      return GREEN;
   } else if ($deltaOut > 120 || $deltaErr < 120) {
      // Missing output or recent errors.
      return RED;
   } else {
      // There are old errors.
      return ORANGE;
   }
}



/** Show status of automated imports and exports. */
function shn_pfif_status() {

   global $global, $deltaOut;

   echo "<br><div id=\"home\">";

   if(shn_pfif_status_code() == GREEN) {
      $statusMsg = "Cron Status: <span style=\"color: green;\"><b>Nominal</b></span>";
   } else if (shn_pfif_status_code() == RED) {
      $statusMsg = "Cron Status: <span style=\"color: red;\"><b>FAILURE</b></span>";
   } else {
      $statusMsg = "Cron Status: <span style=\"color: orange;\"><b>Warning</b></span>";
   }
   echo '
        <div class="form-container">
             <form>
                  <fieldset>
                       <legend>Daemon Status</legend>
                       Cron Job last successfully executed <b>'.$deltaOut.' seconds</b> ago.<br>
                       '.$statusMsg.'
                  </fieldset>
             </form>
        </div>
   ';

   // Show status of imports from Google PF repositories.
   $q = "SELECT pr.base_url, pr.sched_interval_minutes, pr.first_entry, pr.last_entry, pr.total_persons, pr.total_notes, pr.resource_type, i.shortname from pfif_repository pr, incident i WHERE role = 'source' AND pr.name LIKE 'google%' AND pr.incident_id = i.incident_id ORDER BY pr.sched_interval_minutes DESC, pr.base_url";
   $result = $global['db']->Execute($q);
   $count = 0;
   echo "
          <div class=\"form-container\">
               <form>
                    <fieldset>
                         <legend>PFIF Import Progress<br></legend>
                         <table id=\"regLog\">
                             <tr>
                                <td class=\"evener\"><b>PFIF Repository</b></td>
                                <td class=\"evener\"><b>PL Event</b></td>
                                <td class=\"evener\"><b>Record Type</b></td>
                                <td class=\"evener\"><b>Status</b></td>
                                <td class=\"evener\"><b>First Processed Record</b></td>
                                <td class=\"evener\"><b>Last Processed Record</b></td>
                                <td class=\"evener\"><b>Total Imported Records</b></td>
                             </tr>
   ";
   while($row = $result->FetchRow()) {
            if(($count%2)==0) {
                    $odd = "class=\"odder\"";
            } else {
                    $odd = "class=\"evener\"";
            }
            if ($row['resource_type']=='person' || $row['resource_type']=='both') {
               $total = $row['total_persons'];
            } else {
               $total = $row['total_notes'];
            }
            echo "  <tr>
                            <td ".$odd.">".substr_replace($row['base_url'], '', 0, 8)."</td>
                            <td ".$odd.">".$row['shortname']."</td>
                            <td ".$odd.">".$row['resource_type']."</td>
                            <td ".$odd.">".(($row['sched_interval_minutes']==0)? 'disabled':'active')."</td>
                            <td ".$odd.">".(($row['first_entry']=='')? '-':$row['first_entry'])."</td>
                            <td ".$odd.">".(($row['last_entry']=='')? '-':$row['last_entry'])."</td>
                            <td ".$odd.">".$total."</td>
                    </tr>";
            $count++;
   }
   if($count==0) {
            echo "<tr><td colspan=7 class=\"odder\">No repositories!</td></tr>";
   }
   echo "
                                    </table>
                            </fieldset>
                    </form>
            </div>
   ";

   // Show status of exports to Google PF repositories.
   $q = "SELECT pr.base_url, pr.sched_interval_minutes, pr.first_entry, pr.last_entry, pr.total_persons, pr.total_notes, i.shortname from pfif_repository pr, incident i WHERE role = 'sink' AND pr.name LIKE 'google%' AND pr.incident_id = i.incident_id ORDER BY pr.sched_interval_minutes DESC, pr.base_url";
   $result = $global['db']->Execute($q);
   $count = 0;
   echo "
          <div class=\"form-container\">
               <form>
                    <fieldset>
                         <legend>PFIF Export Progress<br></legend>
                         <table id=\"regLog\">
                             <tr>
                                <td class=\"evener\"><b>PFIF Repository</b></td>
                                <td class=\"evener\"><b>PL Event</b></td>
                                <td class=\"evener\"><b>Status</b></td>
                                <td class=\"evener\"><b>First Processed Record</b></td>
                                <td class=\"evener\"><b>Last Processed Record</b></td>
                                <td class=\"evener\"><b>Total Exported Persons</b></td>
                                <td class=\"evener\"><b>Total Exported Notes</b></td>
                             </tr>
   ";
   while($row = $result->FetchRow()) {
            if(($count%2)==0) {
                    $odd = "class=\"odder\"";
            } else {
                    $odd = "class=\"evener\"";
            }
            echo "  <tr>
                            <td ".$odd.">".substr_replace($row['base_url'], '', 0, 8)."</td>
                            <td ".$odd.">".$row['shortname']."</td>
                            <td ".$odd.">".(($row['sched_interval_minutes']==0)? 'disabled':'active')."</td>
                            <td ".$odd.">".(($row['first_entry']=='')? '-':$row['first_entry'])."</td>
                            <td ".$odd.">".(($row['last_entry']=='')? '-':$row['last_entry'])."</td>
                            <td ".$odd.">".$row['total_persons']."</td>
                            <td ".$odd.">".$row['total_notes']."</td>
                    </tr>";
            $count++;
   }
   if($count==0) {
            echo "<tr><td colspan=7 class=\"odder\">No repositories!</td></tr>";
   }
   echo "
                                    </table>
                            </fieldset>
                    </form>
            </div>
   ";
   echo "</div>";
}



/** Stream PFIF in raw xml format.  (Used by above form.) */
function shn_xml_pfif_export() {

    global $global;

    // Get incident name.
    $sql = "SELECT name from incident where incident_id=".$_POST['pfif_incident_id'];
    $res = $global['db']->GetRow($sql);
    $name = $res['name'];
    $pfif = new Pfif();
    $pfif->setIncidentId($_POST['pfif_incident_id']);
    $original = isset($_POST['original']) ? true : false;
    $pfif->loadFromDatabase($_POST['since'], $_POST['before']);
    if ($original) {
       // Export only original records.
       $xml = $pfif->storeInXML(false, $original);
    } else {
       $xml = $pfif->storeInXML();
    }
    if ($xml != null) {
       shn_stream_init(false);
       print $xml;
    } else {
       echo "<pfif>No records to export from '$name' event!</pfif>";
    }
}



/**
 * Stream PFIF in raw xml format.
 * Used for URL-type feeds. Accepts Google-style params min_entry_date, max_results, and skip.
 * Exports all records (not just original ones).
 * @access public
 * @return string
 */
function shn_xml_pfif_feed() {

    global $global;

    // Get shortname from _GET variable.
    $short = mysql_real_escape_string($_GET['shortname']);
    // Get incident id.
    $sql = "SELECT incident_id from incident where shortname='$short'";
    $res = $global['db']->GetRow($sql);
    $incident_id = $res['incident_id'];
    $pfif = new Pfif();
    $pfif->setIncidentId($incident_id);
    if (isset($_GET['min_entry_date'])) {
        // Cap max_results at 200.
        $max_results = isset($_GET['max_results'])? $_GET['max_results'] : 200;
        $skip = isset($_GET['skip'])? $_GET['skip'] : 0;
       // If min_entry_date is set, request a parameterized feed.
       $pfif->loadFromDatabase($_GET['min_entry_date'], null, $max_results, $skip);
    } else {
       // Otherwise, just get the latest 10 records.
       $pfif->loadFromDatabase(-1);
    }
    $xml = $pfif->storeInXML();
    if ($xml != null) {
       shn_stream_init(false);
       print $xml;
    } else {
       echo "<pfif>No records to export!</pfif>";
    }
}
