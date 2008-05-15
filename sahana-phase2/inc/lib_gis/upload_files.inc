<?php

/**
* Sahana GIS Upload Files
* KML, OSM or GML
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
$extensions=array('kml','kmz','osm','xml');

//check whether a file was uploaded
if(isset($file)){
    //get the extension and the tmp name of the file
    $ext=end(explode('.',$_FILES['load']['name']));
    unset($_SESSION['gis']['file']);
    $_SESSION['gis']['file']="./res/OpenLayers/files/".basename($_FILES['load']['name']);
    //check for  directory write permission
    if(!is_writable('./res/OpenLayers/files')){
        add_error(_t('Make sure the files folder is writable'));
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
        add_error("<b>".strtoupper($ext)."</b> : "._t("Please upload a file with one of these extensions:") . '".kml", ".kmz", ".osm", ".xml"');
    }
    //check for file write permission
    else if(file_exists($_SESSION['gis']['file']) && !is_writable($_SESSION['gis']['file'])){
        add_error(_t('File already exists & is not writable'));
    }
    //move the uploaded file to the files directory, with the correct name
    else {
        move_uploaded_file($_FILES['load']['tmp_name'],$_SESSION['gis']['file']);
        add_confirmation(_t("File was uploaded"));
        if ("kmz"==$ext) {
            $execute = "unzip -u ".$global['approot']."www/".$_SESSION['gis']['file']." -d ".$global['approot']."www/res/OpenLayers/files";
            `$execute`;
            $execute = "rm -f ".$global['approot']."www/".$_SESSION['gis']['file'];
            `$execute`;
            add_confirmation(_t("File was decompressed"));
        }
    }
}    

//Print the error message if an error occurred with the Upload File
display_errors($return=false,$clean_errors=true,$exit=false);
//draw upload form
_shn_gis_upload_files_form();


function _shn_gis_upload_files_form()
{
	print '<center><h2>' . _t("Upload Files") . '</h2></center>';
    print '<p>' . _t("This form allows uploading of files in ") . '<a href="http://en.wikipedia.org/wiki/Keyhole_Markup_Language" target=_blank>KML</a>, <a href="http://wiki.openstreetmap.org/index.php/Protocol" target=_blank>OSM</a>' . _t(" or ") . '<a href="http://en.wikipedia.org/wiki/Geography_Markup_Language" target=_blank>GML</a>' . _t(" format to ") . 'www/res/OpenLayers/files </p>';
    print '<p>' . _t("File should have one of the following extensions:") . '.kml, .kmz, .osm' . _t(" or ") . '.xml </p>';

	global $global;
	include_once $global['approot']."/inc/lib_form.inc";

    $upload_help=_t("KML files should have the extension .kml or .kmz, OSM files should have the extension .osm, GML files should have the extension .xml.");
	shn_form_fopen("gis_files",null,array('enctype'=>'enctype="multipart/form-data"','req_message'=>false));
	shn_form_fsopen(_t("Upload File"));
    shn_form_upload(_t('Upload KML, OSM or GML'),"load",array('req'=>false,"help"=>$upload_help));
	shn_form_fsclose();

	print "<br />";
	shn_form_submit(_t("Upload"));
	shn_form_fclose();
    // List current directory contents
    _shn_gis_list_files();
}

function _shn_gis_list_files()
// ToDo: Separate lists for the 3 different sorts
{
    print '<center><h2>' . _t("Current Files") . '</h2></center>';
    print '<p>' . _t("These are the files currently available on this server") . ':</p>';
    global $global;
    $dir=$global['approot'].'/www/res/OpenLayers/files';
	if ($handle = opendir($dir)) {
        while (false !== ($file = readdir($handle))) {
            if ($file != "." && $file != ".." && !is_dir($dir."/".$file)) {
                //echo "$file\n";
                print("<a href=\"res/OpenLayers/files/".$file."\" target=_blank>".$file."</a><br />\n");
            }
        }
        closedir($handle);
    }
}

?>
