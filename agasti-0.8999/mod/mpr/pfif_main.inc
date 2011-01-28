<?php
/**
* @package     pfif
* @version      1.1
* @author       Nilushan Silva <>
* @author       Carl H. Cornwell <ccornwell@mail.nih.gov>
* LastModified: 2010:0308:1307
* License:      LGPL
* @link         TBD
*/
// TODO: chc 3/8/2010 : may need additional imports when made into a separate module.
include_once $global['approot'] . 'mod/mpr/pfifconf.inc.php';

/**
 * Manage PFIF Import sessions
 *
 */
function shn_mpr_import(){
    // if there is no post, render the form to upload
    // var_dump('$_POST' , $_POST);
    //var_dump('$_FILES' , $_FILES);
    if( ! isset( $_POST['upload'])){
        shn_form_fopen("import",null,array('enctype'=>'enctype="multipart/form-data"','req_message' => true));
        add_warning(_t('Please make sure that you are adding a PFIF xml file.'));
        shn_form_fsopen(_t('Import from PFIF xml'));
        shn_form_hidden(array('upload'=>'upload'));
        // Added 1/23/10 (c.cornwell)  Google daily PFIF snapshot requires increasing max allowed upload size
        // @todo get max size from configuration file
        // @see http://www.php.net/manual/en/features.file-upload.php#74692 regarding alternate solution for large file upload
        shn_form_upload(_t('Upload PFIF xml'),'xml',array('max_file_size'=>'128M'));
        shn_form_submit(_t('Upload'));
        shn_form_fsclose();
        shn_form_fsopen(_t('Download from Google PFIF API'));
        shn_form_text(_t('Enter person_record_id'),'pfif_id');
        shn_form_submit(_t('Download'));
        shn_form_fsclose();
        shn_form_fclose();
    }else{
        //validate
        if (isset($_POST['pfif_id']) && !empty($_POST['pfif_id'])) {
            // TODO: Need to restructure this to maximize reuse
            include_once 'pfif.inc';
             $pfif = new Pfif();
             $loaded = $pfif->loadFromService($_POST['pfif_id']);
             // error_log( $pfif->storeInXML() );
             $result = $loaded ? $pfif->storeInDatabase() : false;
             if($result == true){
                 add_confirmation('Successfully Imported');
             } else {
                 add_error('There was an error in Importing');
             }
             shn_mpr_default();                     
        }
        else if(  $_FILES['xml']['error'] != 0){
            add_warning('Please select a file to upload');
            unset($_FILES); unset($_POST);
            shn_mpr_import();
        }else{
             //if there is a post, upload the file and import the file to the database.
             if(is_uploaded_file($_FILES['xml']['tmp_name'])){
                 include_once 'pfif.inc';
                 $pfif = new Pfif();
                 $loaded = $pfif->loadFromXML($_FILES['xml']['tmp_name']);
                 // $loaded = $pfif->readFromXML($_FILES['xml']['tmp_name']);
                 //$pfif->storeInXML();
                 $result = $loaded ? $pfif->storeInDatabase() : false;
                 if($result == true){
                     add_confirmation('Successfully Imported');
                 } else {
                     add_error('There was an error in Importing');
                 }
                 shn_mpr_default();                     
             
             }
        }
        
    }
   
}

/**
 * Manage PFIF Export sessions
 *
 */
function shn_mpr_export(){

    if( ! isset( $_POST['upload'])){
        echo '<h1 align="center">Get Export XML</h1>';
        echo "<a href='index.php?mod=mpr&act=pfif_export&stream=xml&status=missing' >Get Missing </a>";
        echo '<br />';
        echo "<a href='index.php?mod=mpr&act=pfif_export&stream=xml&status=alive' > Get Alive </a>";
        echo '<br />';
        echo "<a href='index.php?mod=mpr&act=pfif_export&stream=xml&status=injured' > Get Injured </a>";
        echo '<br />';
        echo "<a href='index.php?mod=mpr&act=pfif_export&stream=xml&status=deceased' > Get Deceased </a>";
        echo '<br />';
        echo "<a href='index.php?mod=mpr&act=pfif_export&stream=xml&status=unknown' > Get Unknown </a>";

        echo '<br />';
        shn_form_fopen("export",null,array('enctype'=>'enctype="multipart/form-data"','req_message' => true));
        shn_form_fsopen(_t('Show Selected Record'));
        shn_form_text(_t('Enter person_record_id'),'show_pfif_id');
        shn_form_submit(_t('Show'));        
        shn_form_fsclose();
        shn_form_fclose();
        echo '<h1 align="center">Export To Google PFIF API</h1>';
        shn_form_fopen("export",null,array('enctype'=>'enctype="multipart/form-data"','req_message' => true));
        add_warning(_t('EXPERIMENTAL: Add source, time range selection parameters to replace id in Upload Selected ... section'));
        shn_form_fsopen(_t('Upload PFIF XML file'));
        shn_form_hidden(array('upload'=>'upload'));
        shn_form_upload(_t('Source File'),'xml');
        shn_form_submit(_t('Upload'));
        shn_form_fsclose();
        shn_form_fsopen(_t('Upload Selected Records'));
        shn_form_text(_t('Enter person_record_id'),'pfif_id');
        shn_form_submit(_t('Submit'));
        shn_form_fsclose();
        shn_form_fclose();
    }else{
        //validate
        // error_log(print_r( $_POST, true ));
        if (isset($_POST['show_pfif_id']) && !empty($_POST['show_pfif_id'])) {
            include_once 'pfif.inc';
            $pfif = new Pfif();
            $pfif->loadFromDb('id?'.$_POST['show_pfif_id']);
            print $pfif->storeInXML();
            
        } else if (isset($_POST['pfif_id']) && !empty($_POST['pfif_id'])) {
            // TODO: Need to restructure this to maximize reuse with upload case.
            // TODO: Need to have post parse the return status and return true status for reporting.
            include_once 'pfif.inc';
             $pfif = new Pfif();
             $result = $pfif->postDbToService($_POST['pfif_id']);
             if(!($result == false)){
                 add_confirmation('Successfully Exported<br/>'.$result);
             } else {
                 add_error('There was an error in Exporting');
             }
             shn_mpr_default();                     
        }
        else if(  $_FILES['xml']['error'] != 0){
            add_warning('Please select a file to upload');
            unset($_FILES); unset($_POST);
            shn_mpr_export();
        }else{
             if(is_uploaded_file($_FILES['xml']['tmp_name'])){
                 include_once 'pfif.inc';
                 $pfif = new Pfif();
                 $result = $pfif->postFileToService($_FILES['xml']['tmp_name']);
                 if(!($result == false)){
                     add_confirmation('Successfully Exported<br/>'.$result);
                 } else {
                     add_error('There was an error in Exporting');
                 }
                 shn_mpr_default();                     
             }
        }
        
    }
}
// The next two functions should be moved to API.inc in order for them to be publicly discoverable
/**
 * Export from Sahana to PFIF XLM document.
 *
 */
function shn_xml_mpr_pfif_export(){
	//status could be 'missing' , 'injured' , 'deceased' , 'alive','unknown' (TODO: add 'found = fou')
	$status = $_GET['status'];		
	$version = isset($_GET['ver']) ? $_GET['ver'] : '1.2';
	$since = isset($_GET['since']) ? $_GET['since'] : null;
    
	include_once 'pfif.inc';
    // include_once $global['approot'] . '/inc/lib_stream_xml.inc';

	$pfif = new Pfif();
	//$pfif->storeInXML();
	$pfif->loadFromDatabase($status,$since); // TODO: add max and skip args
    // shn_stream_init(false);
	// $pfif->storeInXML();
    print $pfif->storeInXML($version);
	
}

/**
 * Import from PFIF repository
 *
 */
function shn_xml_mpr_pfif_import(){
	//status could be 'missing' , 'injured' , 'deceased' , 'alive'
	global $global;
	include_once 'pfif.inc';
	$pfif = new Pfif();
	$loaded = $pfif->loadFromXML($global['approot'] . '/mod/mpr/test.xml'); // TODO: how is an arbitrary file imported using this action?
	if ($loaded) {
        $pfif->storeInDatabase();
        // error_log( $pfif->storeInXML() );
    } else {
        error_log( "shn_mod_mpr_pfif_import: Import failed" );
    }
	
}
