<?php
/**
 * @name         Person Finder Interchange Format
 * @version      0.1
 * @package      pfif
 * @author       Leif Neve <lneve@mail.nih.gov>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0622
 */


global $global;
global $conf;
include_once $global['approot'] . '/inc/lib_modules.inc';
include_once $global['approot'] . '/inc/lib_menu.inc';
include_once $global['approot'] . '/inc/lib_form.inc';
include_once $global['approot'] . '/inc/lib_validate.inc';
include_once $global['approot'] . '/inc/lib_errors.inc';
include_once $global['approot'] . '/inc/lib_image.inc';
include_once 'lib_pfif.inc';
include_once 'pfif.inc';

function shn_pfif_menu() {
	echo "<ul>";
        $text = "Import from PFIF File";
        if (isset($_GET['act']) && $_GET['act'] == "import") {
	   echo "<li><b>$text</b></li>";
        } else { 
	   echo "<li><a href=\"index.php?mod=pfif&act=import\">$text</a></li>";
        }
        $text = "Export to PFIF File";
        if (isset($_GET['act']) && $_GET['act'] == "export") {
	   echo "<li><b>$text</b></li>";
        } else { 
	   echo "<li><a href=\"index.php?mod=pfif&act=export\">$text</a></li>";
        }
        $text = "View PFIF Service Status";
        if (isset($_GET['act']) && $_GET['act'] == "status") {
	   echo "<li><b>$text</b></li>";
        } else { 
	   echo "<li><a href=\"index.php?mod=pfif&act=status\">$text</a></li>";
        }
	echo "</ul>";
	echo "<hr style=\"height: 1px; background-color: #fff; border: none; border-top: 1px solid #e5eaef; margin-bottom: 15px; \">";
}


/**
 * the default module action...
 * @access public
 * @return void
 */
function shn_pfif_default() {
	global $global;
	shn_pfif_menu();
}


/**
 * Manage PFIF Import sessions
 *
 */
function shn_pfif_import() {
    global $global;

    // If there is no post, render the form to upload.
    if (!isset( $_POST['upload'])) {
        shn_pfif_menu();
        // Submitted form calls this function again.
        shn_form_fopen("import",null,array('enctype'=>'enctype="multipart/form-data"','req_message' => false));
        //add_warning('Please make sure that you are adding a PFIF xml file.');
        shn_form_fsopen(_t('Import from PFIF File'));
        shn_form_hidden(array('upload'=>'upload'));
        shn_form_upload(_t('PFIF filename'),'xml',array('max_file_size'=>'128M'));
        shn_pfif_incident_select("Import to this event");
        echo "<br><div class='brake'></div>";
        shn_form_submit(_t('Upload'));
        shn_form_fsclose();
        shn_form_fclose();
    } else {
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
                 shn_pfif_menu();
             }
        }

    }
}

/**
 * Note: This could be made a more generic "shn_incident_select" if others could benefit from it.
 */
function shn_pfif_incident_select($label){
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


/**
 * Manage PFIF Export sessions
 *
 */
function shn_pfif_export() {
    global $global;

    shn_pfif_menu();

    // Create a form that when submitted calls shn_xml_pfif_export() below.
    shn_form_fopen("export",null,array('req_message' => false),"xml");
    shn_form_fsopen(_t('Export to PFIF XML'));
    shn_pfif_incident_select("Export from this event");
    echo "<br><div class='brake'></div>";
    $extra_opts['br'] = false;
    shn_form_text(_t('Start date'),'since','',$extra_opts);
    echo "&nbsp;&nbsp;(e.g. 2011-08-01)<br><div class='brake'></div>";
    shn_form_text(_t('End date'),'before');
    shn_form_checkbox(_t('Records originating in PL only'),'original');
    shn_form_hidden(array('filename'=>'export.xml','download'=>'download'));
    shn_form_submit(_t('Submit'));
    shn_form_fsclose();
    shn_form_fclose();
}

/**
 * Used for navigation menu status indicator.
 */
function shn_pfif_statusGood() {
   global $global;
   $import_out = "/pl/tmp/pfif_logs/import.out";
   $export_out = "/pl/tmp/pfif_logs/export.out";
   $import_err = "/pl/tmp/pfif_logs/import.err";
   $export_err = "/pl/tmp/pfif_logs/export.err";

   // Check one of the output files to make sure it's getting updated. 
   $lastExecutedU = filemtime($import_out);;
   // Check for non-zero-size error file.
   $errors = filesize($export_err)!=0 || filesize($import_err)!=0;

   $delta = date("U") - $lastExecutedU;

   return ($delta < 120 && !$errors);
}

/**
 * Show status of automated imports and exports.
 *
 */
function shn_pfif_status() {
   global $global;

   shn_pfif_menu();

   $import_out = "/pl/tmp/pfif_logs/import.out";
   $export_out = "/pl/tmp/pfif_logs/export.out";
   $import_err = "/pl/tmp/pfif_logs/import.err";
   $export_err = "/pl/tmp/pfif_logs/export.err";

   echo "<div id=\"home\">";

   // Show system cron status.

   // Check one of the output files to make sure it's getting updated. 
   $lastExecutedU = filemtime($import_out);;
   // Check for non-zero-size error file.
   $errors = filesize($export_err)!=0 || filesize($import_err)!=0;

   $delta = date("U") - $lastExecutedU;

   if($delta < 120 && !$errors) {
      $statusMsg = "Cron Status: <span style=\"color: green;\"><b>Nominal</b></span>";
   } else {
      $statusMsg = "Cron Status: <span style=\"color: red;\"><b>FAILURE</b></span>";
   }
   echo '
        <div class="form-container">
             <form>
                  <fieldset>
                       <legend>Daemon Status</legend>
                       Cron Job last executed <b>'.$delta.' seconds</b> ago.<br>
                       '.$statusMsg.'
                  </fieldset>
             </form>
        </div>
   ';

   // Show status of exports/imports to Google PF repositories.
   $q = "SELECT pr.base_url, pr.sched_interval_minutes, pr.first_entry, pr.last_entry, pr.total_persons, pr.total_notes, pr.resource_type, pr.role, i.shortname from pfif_repository pr, incident i where pr.name LIKE 'google%' AND pr.incident_id = i.incident_id ORDER BY pr.sched_interval_minutes DESC";
   $result = $global['db']->Execute($q);
   $count = 0;
   echo "
          <div class=\"form-container\">
               <form>
                    <fieldset>
                         <legend>PFIF Service Progress<br></legend>
                         <table id=\"regLog\">
                             <tr>
                                <td class=\"evener\"><b>PFIF Repository</b></td>
                                <td class=\"evener\"><b>PL Event</b></td>
                                <td class=\"evener\"><b>Direction</b></td>
                                <td class=\"evener\"><b>Record Type</b></td>
                                <td class=\"evener\"><b>Status</b></td>
                                <td class=\"evener\"><b>First Record</b></td>
                                <td class=\"evener\"><b>Last Record</b></td>
                                <td class=\"evener\"><b>Total Records</b></td>
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
                            <td ".$odd.">".(($row['role']=='source')? 'import':'export')."</td>
                            <td ".$odd.">".$row['resource_type']."</td>
                            <td ".$odd.">".(($row['sched_interval_minutes']==0)? 'disabled':'active')."</td>
                            <td ".$odd.">".(($row['first_entry']=='')? '-':$row['first_entry'])."</td>
                            <td ".$odd.">".(($row['last_entry']=='')? '-':$row['last_entry'])."</td>
                            <td ".$odd.">".$total."</td>
                    </tr>";
            $count++;
   }
   if($count==0) {
            echo "<tr><td colspan=8 class=\"odder\">No repositories!</td></tr>";
   }
   echo "
                                    </table>
                            </fieldset>
                    </form>
            </div>
   ";
   echo "</div>";
}

/**
 * Stream PFIF in raw xml format.  (Used by above form.)
 * @access public
 * @return string
 */
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
