<?php

/**
* Sahana GIS Upload Markers
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

function _shn_gis_upload_markers()
{
    global $global;
    global $conf;
    global $file;

    $file=$_FILES['load'];
    $extensions=array('png');
    $dir=$conf['gis_marker_folder'];

    //check whether a file was uploaded
    if(isset($file)){
        //get the extension and the tmp name of the file
        $ext=end(explode('.',$_FILES['load']['name']));
        unset($_SESSION['gis']['file']);
        $_SESSION['gis']['file']="./$dir".basename($_FILES['load']['name']);
        //check for  directory write permission
        if(!is_writable("$dir")){
            add_error(_t("Make sure the $dir folder is writable"));
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
        // ToDo: convert other filetypes automagically (using lib_image.inc?)
        else if(!in_array($ext,$extensions)){
            add_error("<b>".strtoupper($ext)."</b> : "._("Please upload an image file with the extension \".png\""));
        }
        //check for file write permission
        else if(file_exists($_SESSION['gis']['file']) && !is_writable($_SESSION['gis']['file'])){
            add_error(_t('File already exists & is not writable'));
        }
        //move the uploaded file to the Markers directory, with the correct name
        else {
            move_uploaded_file($_FILES['load']['tmp_name'],$_SESSION['gis']['file']);
            add_confirmation(_t("File was uploaded"));
        }
    }    

    //Print the error message if an error occurred with the Upload File
    display_errors($return=false,$clean_errors=true,$exit=false);
    //draw upload form
    _shn_gis_upload_markers_form();
}

function _shn_gis_upload_markers_form()
{
    global $global;
    global $conf;
    include_once $global['approot']."/inc/lib_form.inc";
    $marker_folder=$conf['gis_marker_folder'];

	print '<h2>'._t("Upload Marker image").'</h2>';
    
    $upload_help=_t("Upload a PNG format image to be usable as an Icon for Markers or GeoRSS feeds.");
	shn_form_fopen("gis_markers",null,array('enctype'=>'enctype="multipart/form-data"','req_message'=>false));
	shn_form_fsopen(_t("Upload Marker Image File"));
    print '<p>' . _t("Upload a new image file to ") . "www/$marker_folder" . '</p>';
    print '<p>' . _t("File should be in PNG format.") . '</p>';
	shn_form_upload(_t('Upload Marker: '),"load",array('req'=>false,"help"=>$upload_help));
	shn_form_fsclose();
	shn_form_submit(_t("Upload"));
	shn_form_fclose();
    print '<br />';

    $folder_help=_t("Create a new Folder to store Icons for Markers or GeoRSS feeds.");
	shn_form_fopen("gis_marker_folders_commit",null,array('req_message'=>false));
	shn_form_fsopen(_t("Create Folder"));
    print '<p>' . _t("Create a new sub-folder in ") . "www/$marker_folder" . '</p>';
    shn_form_text(_t('Folder name: '),"gis_markers_folder",'size=40',array('req'=>false,"help"=>$folder_help));
	shn_form_fsclose();
	shn_form_submit(_t("Create"));
	shn_form_fclose();
    print '<br />';
}

function _shn_gis_create_markers_folder()
{
    global $global;
    global $conf;
    
    if(!null==$_POST['gis_markers_folder']){
        $path=$global['approot']."www/".$conf['gis_marker_folder'];
        $new_folder=$path.$_POST['gis_markers_folder'];
        //check for  directory write permission
        if(!is_writable("$path")){
            add_error(_t("Make sure the $path folder is writable"));
        }
        mkdir($new_folder);
    }
}


