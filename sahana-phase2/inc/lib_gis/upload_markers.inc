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
    // ToDo: Check for correct image size (or resize on the fly using shn_image_resize?)
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


function _shn_gis_upload_markers_form()
{
	print '<center><h2>' . _t("Upload Marker image") . '</h2></center>';
    print '<p>' . _t("This form allows a Marker image file to be uploaded to $file.") . '</p>';
    print '<p>' . _t("File should be in PNG format & 20 pixels wide, 34 pixels high.") . '</p>';

	global $global;
	include_once $global['approot']."/inc/lib_form.inc";

    $upload_help=_t("Upload a PNG format image which is 20 pixels wide, 34 pixels high");
	shn_form_fopen("gis_markers",null,array('enctype'=>'enctype="multipart/form-data"','req_message'=>false));
	shn_form_fsopen(_t("Upload Marker Image File"));
    shn_form_upload(_t('Upload Marker'),"load",array('req'=>false,"help"=>$upload_help));
	shn_form_fsclose();

	print "<br />";
	shn_form_submit(_t("Upload"));
	shn_form_fclose();
    // List current directory contents
    _shn_gis_list_markers();
}

function _shn_gis_list_markers()
{
    print '<center><h2>' . _t("Current Markers") . '</h2></center>';
    print '<p>' . _t("These are the Markers currently available on this server") . ':</p>';
    global $global;
    global $conf;
    $dir=$conf['gis_marker_folder'];
    $dir2=$global['approot']."/www/$dir";
	if ($handle = opendir($dir2)) {
        print("<table>");
        while (false != ($file = readdir($handle))) {
            if ($file != "." && $file != ".." && !is_dir($dir2."/".$file)) {
                print("<tr><td><img src=\"$dir".$file."\" /></td><td>".$file."</td></tr>");
            }
        }
        closedir($handle);
        print("</table>");
    }
}

?>
