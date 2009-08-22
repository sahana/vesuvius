<?php
/**
* Marker Handling Page of GPS Module
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Sriganeshan <sri@opensource.lk>
* @author     Fran Boon <flavour@partyvibe.com>
* @author     Richard Smith <s0459387@sms.ed.ac.uk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $global;
global $conf;
global $file;

function _shn_sm_form_upload()
{
    global $global;
    global $conf;
    require_once $global['approot']."/inc/lib_form.inc";
    $extension_str = ' .' . implode(', .', $conf['gis_file_extensions']);
    echo '<h2>' . _('Upload Waypoints') . '</h2>';
    shn_form_fopen("upload_seq", null, array('enctype'=>'enctype="multipart/form-data"', 'req_message'=>false));
    shn_form_fsopen(_("Upload File"));
    echo "<p>" . _t('Upload a waypoint file with one of following extensions:') . $extension_str;
    echo "</p>";
    echo "<p><em><strong>"._('important: ')."</strong></em>"._('This system will only accept files which are well-formed and valid.')."</p>";
    shn_form_upload(_('Upload File'),"load"); 
    shn_form_hidden(array('seq' => '2_choose_features'));
    shn_form_fsclose();
    print "<br />";
    shn_form_submit(_("Upload"));
    shn_form_fclose();
}
    
function _shn_sm_check_file_upload()
{
    global $global;
    global $conf;
    global $file;
    $extension_str = ' .' . implode(', .', $conf['gis_file_extensions']);
    // Get the extension and the tmp name of the file
    unset($_SESSION['gps']['filetype']);
    $_SESSION['gps']['filetype'] = end(explode('.',$_FILES['load']['name']));
    unset($_SESSION['gps']['file']);
    $_SESSION['gps']['file'] ="./tmp/".basename($_FILES['load']['name']);
    // Check for tmp file permision
    if(!is_writable('./tmp')) {
        add_error(_('Make sure the tmp folder is writable'));
    // Check whether an error occurred
    } else if($file['error']!= 0) {
        // Give error information
        switch ($file['error']) {
            case 1:
            case 2:
                add_error(_('The uploaded file exceeds the Max upload size'));
                break;
            case 3:
                add_error(_('The uploaded file was only partially uploaded.'));
                break;
            case 4:
                add_error(_('No file was uploaded :  Please press the browse button and select a file to upload before you press the next button'));
                break;
        }
    // Check for correct extension
    } else if(!in_array($_SESSION['gps']['filetype'], $conf['gis_file_extensions'])) {
        add_error("<b>".strtoupper($_SESSION['gps']['filetype'])."</b> : "._t("Please upload a file with one of these extensions: ") . $extension_str );
    // Move the uploaded file to the tmp directory
    } else if (move_uploaded_file($_FILES['load']['tmp_name'], $_SESSION['gps']['file'])) {
        // Check file types
        if(!(FALSE === array_search($_SESSION['gps']['filetype'], $conf['gis_file_extensions'])) && !shn_sm_xml_validator()) {
            return true;
        } else {
            add_error(_('Possible file upload attack!'));
            return false;
        }
    }
}
       
function shn_sm_xml_validator()
{
    $error_flag=false;
    class SchemaDOMDocument extends DOMDocument
    {
        public function validateXMLSchemas() {
            global $ext;
            // Do we want to validate against old schema versions of filetype ???
            $schemaLocation = $conf['schema_location_' . $ext];
            $pairs = preg_split('/\s+/', $schemaLocation);
            $pairCount = count($pairs);
            $valid = true;
            for($x = 1; $x < $pairCount; $x+=2) {
                $valid = $this->schemaValidate($pairs[$x]) && $valid;
            }
            if(!$valid) {
                return false;
            }
            return true;
        }
    } //end of class SchemaDOMDocument
    $file = $_SESSION['gps']['file'];
    if (!($fp = fopen($file, "r"))) {
        add_error(_("Can not open file."));
        unlink($file);
        return $error_flag=true;;
    }
    $xml = fread($fp,filesize($file));
    // close the file
    fclose($fp);
    $parser = xml_parser_create ();
    if (!xml_parse ($parser, $xml, true)) {
        xml_parser_free ($parser);
        unlink($file);
        add_error(_("Your File is not well-formed. Please upload a well-formed file"));
        return $error_flag=true;;
    }
    $library = new SchemaDOMDocument("1.0");
    $library->validateOnParse = true;
    $library->load($file);
    if($library->validateXMLSchemas()) {
        add_confirmation(_('The file was uploaded successfully. Please complete the following steps to add features to database.'));
        return $error_flag=false;;
    } else {
        unlink($file);
        add_error(_("Your File is not valid. Please upload a valid file"));
        return $error_flag=true;
    }
}

/*
 * Deprecated functions (GSoC 2008 rendered these 2007 functions redundant)
 */
//$file=$_FILES['load'];
//$extensions=array('gpx');
////check whether a file was uploaded
//if(isset($file)){
//    //get the extension and the tmp name of the file
//    $ext=end(explode('.',$_FILES['load']['name']));
//    unset($_SESSION['gps']['file']);
//    $_SESSION['gps']['file']="./tmp/".basename($_FILES['load']['name']);
//    //check for tmp file permision
//    if(!is_writable('./tmp')){
//        add_error(_('Make sure the tmp folder is writable'));
//    }
//    //check whether an error occurred
//    else if($file['error']!= 0){
//        //give error information
//        switch ($file['error']){
//            case 1:
//            case 2:
//                add_error(_('The uploaded file exceeds the Max upload size'));
//                break;
//            case 3:
//                add_error(_('The uploaded file was only partially uploaded.'));
//                break;
//            case 4:
//                add_error(_('No file was uploaded :  Please press the browse button and select a file to upload before you press the next button'));
//                break;
//        }
//    }
//    //check for extension
//    else if(!in_array($ext,$extensions)){
//        add_error("<b>".strtoupper($ext)."</b> : "._("Please upload a GPX file with the extension \".gpx\""));
//    }
//    //move the uploaded file to the tmp directory
//    else if (move_uploaded_file($_FILES['load']['tmp_name'],$_SESSION['gps']['file'])) {
//        if(!_shn_gps_file_checker()) {	
//            shn_gps_point_sort_start();	
//            return;
//        }		
//    } else {
//        add_error(_('Possible file upload attack!'));
//    }
//}
////Print the error message if an error occurred with the Upload File
//display_errors($return=false,$clean_errors=true,$exit=false);
////draw upload form
//_shn_gps_upload_form();
////end of main function

//function _shn_gps_upload_form()
//{
//	print '<center><h2>' . _("Upload Waypoints") . '</h2></center>';
//	global $global;
//	global $conf;
//	include_once $global['approot']."/inc/lib_form.inc";
//	shn_form_fopen("upload",null,array('enctype'=>'enctype="multipart/form-data"','req_message'=>false));
//	shn_form_fsopen(_("Upload GPX File"));
//	echo "<p><em><strong>"._('important: ')."</strong></em>"._('This system will only accept GPX files which are well-formed and valid.')."</p>";
//       shn_form_upload(_('Upload File'),"load"); 
//	shn_form_fsclose();
//	print "<br />";
//	shn_form_submit(_("Upload"));
//	shn_form_fclose();
//}

//function _shn_gps_file_checker()
//{
//$error_flag=false;
//
//class SchemaDOMDocument extends DOMDocument
//{
//    public function validateXMLSchemas()
//    {
//        $schemaLocation =$conf['schema_location']; //$this->documentElement->getAttributeNS('http://www.w3.org/2001/XMLSchema-instance', 'schemaLocation');
//        $pairs = preg_split('/\s+/', $schemaLocation);
//        $pairCount = count($pairs);
//        $valid = true;
//        for($x = 1; $x < $pairCount; $x+=2) {
//            $valid = $this->schemaValidate($pairs[$x]) && $valid;
//        }
//        if(!$valid) {
//            return false;
//        }
//        return true;
//    }
//}//end of class SchemaDOMDocument
//
//    $file=$_SESSION['gps']['file'];
//    if (!($fp = fopen($file, "r"))) {
//        add_error(_("Can not open file."));
//        unlink($file);
//        return $error_flag=true;;
//    }
//    $xml = fread($fp,filesize($file));
//    // close the file
//    fclose($fp);
//    $parser = xml_parser_create ();
//    if (!xml_parse ($parser, $xml, true)) {
//        xml_parser_free ($parser);
//        unlink($file);
//        add_error(_("Your File is not well-formed. Please upload a well-formed file"));
//        return $error_flag=true;;
//    }
//    $library = new SchemaDOMDocument("1.0");
//    $library->validateOnParse = true;
//    $library->load($file);
//    if($library->validateXMLSchemas()) {
//        add_confirmation(_('The file was uploaded successfully...'));
//        return $error_flag=false;;
//    } else {
//        unlink($file);
//        add_error(_("Your File is not valid. Please upload a valid file"));
//        return $error_flag=true;
//    }
//}


