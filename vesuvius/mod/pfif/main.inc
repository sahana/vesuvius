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
        if (isset($_GET['act']) && $_GET['act'] == "import") {
	   echo "<li><b>Import Actions</b></li>";
        } else { 
	   echo "<li><a href=\"index.php?mod=pfif&act=import\">Import Actions</a></li>";
        }
        if (isset($_GET['act']) && $_GET['act'] == "export") {
	   echo "<li><b>Export Actions</b></li>";
        } else { 
	   echo "<li><a href=\"index.php?mod=pfif&act=export\">Export Actions</a></li>";
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
	//echo "hello world!";
}


/**
 * the galaxy action!
 * @access public
 * @return void
 */
function shn_pfif_galaxy() {
	global $global;
	shn_pfif_menu();
	echo "hello galaxy!";
}



/**
 * the universe action!
 * @access public
 * @return void
 */
function shn_pfif_universe() {
	global $global;
	shn_pfif_menu();
	echo "hello universe!";
}



/**
 * stream tests...
 * @access public
 * @return void
 */
function shn_pfif_streams() {
	global $global;
	shn_pfif_menu();
	echo '
		<a href="index.php?mod=pfif&stream=xml&act=atomTest">atom feed test</a><br>
		<a href="index.php?mod=pfif&stream=xml&act=rss2Test">rss2 feed test</a><br>
	';
}


/**
 * Manage PFIF Import sessions
 *
 */
function shn_pfif_import() {
    global $global;

    shn_pfif_menu();
    // If there is no post, render the form to upload.
    // var_dump('$_POST' , $_POST);
    // var_dump('$_FILES' , $_FILES);
    // Get shortname from _GET variable.
    $short = mysql_real_escape_string($_GET['shortname']);
    // Get incident id.
    $sql = "SELECT incident_id from incident where shortname='$short'";
    $res = $global['db']->GetRow($sql);
    $incident_id = $res['incident_id'];
    if (!isset( $_POST['upload'])) {
        shn_form_fopen("import",null,null,array('enctype'=>'enctype="multipart/form-data"','req_message' => false));
        //add_warning(_t('Please make sure that you are adding a PFIF xml file.'));
        shn_form_fsopen(_t('Import from PFIF xml to \''.$short.'\' event'));
        shn_form_hidden(array('upload'=>'upload'));
        shn_form_upload(_t('Upload PFIF xml'),'xml',array('max_file_size'=>'128M'));
        shn_form_submit(_t('Upload'));
        shn_form_fsclose();
        shn_form_fclose();
    } else {
        // Validate
        if (isset($_POST['pfif_id']) && !empty($_POST['pfif_id'])) {
            // TODO: Need to restructure this to maximize reuse
            $pfif = new Pfif();
            $loaded = $pfif->loadFromService($_POST['pfif_id']);
            // error_log( $pfif->storeInXML() );
            $result = $loaded ? $pfif->storeInDatabase() : false;
            if($result == true){
                add_confirmation('Successfully Imported');
            } else {
                add_error('There was an error in Importing');
            }
            shn_pfif_default();
        } else if(  $_FILES['xml']['error'] != 0){
            add_warning('Please select a file to upload');
            unset($_FILES); unset($_POST);
            shn_pfif_default();
        } else {
             // If there is a post, upload the file and import the file to the database.
             if(is_uploaded_file($_FILES['xml']['tmp_name'])){
                 $pfif = new Pfif();
                 $loaded = $pfif->loadFromXML($_FILES['xml']['tmp_name']);
                 $shortname = 'test';
                 if ($loaded > 0) {
                    //$xml = $pfif->storeInXML();
                    //print "<pre>$xml</pre>";
                    $stored = $pfif->storeInDatabase($incident_id);
                    if($stored['person']==0 && $stored['note']==0) {
                        add_error('No records were imported.');
                    } else {
                        add_confirmation('Successfully imported '.$stored['person'].' persons and '.$stored['note']." notes into the $short event.");
                    }
                 } else {
                    add_error('File not loaded.');
                 }
                 shn_pfif_menu();
             }
        }

    }
}


/**
 * Manage PFIF Export sessions
 *
 */
function shn_pfif_export() {
    global $global;

    shn_pfif_menu();

    // If there is no post, render the form to upload.
    // var_dump('$_POST' , $_POST);
    // Get shortname from _GET variable.
    $short = mysql_real_escape_string($_GET['shortname']);
    // Get incident id.
    $sql = "SELECT incident_id from incident where shortname='$short'";
    $res = $global['db']->GetRow($sql);
    $incident_id = $res['incident_id'];
    if(!isset( $_POST['since'])){
        shn_form_fopen("export",null,array('req_message' => false),"xml");
        shn_form_fsopen(_t('Export from \''.$short.'\' event to PFIF xml'));
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
}

/**
 * Stream PFIF in raw xml format.
 * @access public
 * @return string
 */
function shn_xml_pfif_export() {
    global $global;

    // Get shortname from _GET variable.
    $short = mysql_real_escape_string($_GET['shortname']);
    // Get incident id.
    $sql = "SELECT incident_id from incident where shortname='$short'";
    $res = $global['db']->GetRow($sql);
    $incident_id = $res['incident_id'];
    $pfif = new Pfif();
    $pfif->setIncidentId($incident_id);
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
       echo "<pfif>No records to export!</pfif>";
    }
}

/**
 * Stream PFIF in raw xml format.
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
    // Fixme: For now, show all records.
    $original = isset($_GET['original']) ? true : false;
    $pfif->loadFromDatabase(-1);
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
       echo "<pfif>No records to export!</pfif>";
    }
}
