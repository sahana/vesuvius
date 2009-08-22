<?php

/**
* Sahana GIS Upload Projections
*
* PHP version 5
* 
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library      GIS
* @version      $Id
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
global $conf;
global $file;

$file=$_FILES['load'];
$extensions=array('js');

//check whether a file was uploaded
if(isset($file)){
    //get the extension and the tmp name of the file
    $ext=end(explode('.',$_FILES['load']['name']));
    unset($_SESSION['gis']['file']);
    $_SESSION['gis']['file']="./res/OpenLayers/defs/".basename($_FILES['load']['name']);
    //check for  directory write permission
    if(!is_writable('./res/OpenLayers/defs')){
        add_error(_t('Make sure the defs folder is writable'));
    }
    //check whether an error occurred
    else if($file['error']!= 0){
        //give error information
        switch ($file['error']){
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
    }
    //check for correct extension
    else if(!in_array($ext,$extensions)){
        add_error("<b>".strtoupper($ext)."</b> : "._("Please upload a Proj4js definition file with the extension \".js\""));
    }
    //check for file write permission
    else if(file_exists($_SESSION['gis']['file']) && !is_writable($_SESSION['gis']['file'])){
        add_error(_t('File already exists & is not writable'));
    }
    //move the uploaded file to the defs directory, with the correct name
    else {
        move_uploaded_file($_FILES['load']['tmp_name'],$_SESSION['gis']['file']);
        add_confirmation(_t("File was uploaded"));
    }
}    

//Print the error message if an error occurred with the Upload File
display_errors($return=false,$clean_errors=true,$exit=false);
//draw upload form
_shn_gis_upload_projections_form();


function _shn_gis_upload_projections_form()
{
	global $global;
	include_once $global['approot']."/inc/lib_form.inc";

    print '<h2>'._t("Upload Projection Definition").'</h2>';

	shn_form_fopen("gis_projections",null,array('enctype'=>'enctype="multipart/form-data"','req_message'=>false));
	shn_form_fsopen(_t("Upload Projection Definition File"));
    print '<p>'._t("Sahana uses the proj4js definitions format available from").' <a href="http://spatialreference.org" target=_blank>spatialreference.org</a>.</p>';
    print '<p>'._t("Upload a new definition file to").' www/res/OpenLayers/defs.</p>';
    print '<p>'._t("File should be named as 'EPSGxxxx.js'.").'</p>';
    print '<br />';
    $upload_help=_t("Download the proj4js version of the Projection from the ").'<a href="http://spatialreference.org/ref/epsg/" target=_blank>spatialreference.org</a> '._t("website & upload here");
	shn_form_upload(_t('Upload Projection Definition'),"load",array('req'=>false,"help"=>$upload_help));
	shn_form_fsclose();
	shn_form_submit(_t("Upload"));
	shn_form_fclose();
    print "<br />";
	// List current directory contents
    _shn_gis_list_projections();
}

function _shn_gis_list_projections()
{
    print '<h2>'._t("Current Projection Definitions").'</h2>';
    print '<p>'._t("These are the Projection definitions currently available on this server").':</p>';
    global $global;
    $dir=$global['approot'].'/www/res/OpenLayers/defs';
	//Read into Array ready for sorting
    $files = array();
    if ($handle = opendir($dir)) {
        while (false !== ($file = readdir($handle))) {
            if ($file != "." && $file != ".." && !is_dir($dir."/".$file)) {
                //echo "$file\n";
                $files[$file]="<a href=\"res/OpenLayers/defs/".$file."\" target=_blank>".$file."</a><br />\n";
            }
        }
        // Sort array
        asort ($files);
        // Print out to screen
        foreach ($files as $key => $val) {
            echo "$val\n";
        }
        closedir($handle);
    }
}


