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
        add_error("<b>".strtoupper($ext)."</b> : "._t("Please upload a file with one of these extensions:").'".kml", ".kmz", ".osm", ".xml"');
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
            // UNIX-specific:
            //$execute = "unzip -u ".$global['approot']."www/".$_SESSION['gis']['file']." -d ".$global['approot']."www/res/OpenLayers/files";
            //`$execute`;
            // PHP 5.2.0+ or PECL:
            if(function_exists("zip_open")) {
                $dir = $global['approot'].'www/res/OpenLayers/files/';
                $zipped = $global['approot']."www/".$_SESSION['gis']['file'];
                $zip = zip_open($zipped);
                while($zip_entry = zip_read($zip)) {
                    $entry = zip_entry_open($zip,$zip_entry);
                    $filename = zip_entry_name($zip_entry);
                    $target_dir = $dir.substr($filename,0,strrpos($filename,'/'));
                    $filesize = zip_entry_filesize($zip_entry);
                    if (is_dir($target_dir) || mkdir($target_dir)) {
                        if ($filesize > 0) {
                            $contents = zip_entry_read($zip_entry, $filesize);
                            file_put_contents($dir.$filename,$contents);
                            $ext_contents=end(explode('.',$filename));
                            if ("kml"==$ext_contents) {
                                $input=$dir.$filename;
                                $output=$dir.$filename.".w";
                                $lines=file($input);
                                $handle = fopen($output, 'w');
                                foreach ($lines as $line_num => $line) {
                                    // Rewrite file to use correct path
                                    $search="<img src='";
                                    $replace="<img src='res/OpenLayers/files/";
                                    $line_out=str_replace($search,$replace,$line);
                                    $search="<href>";
                                    $replace="<href>res/OpenLayers/files/";
                                    $line=str_replace($search,$replace,$line_out);
                                    // If the URL was remote not local, then put it back!
                                    $search="<href>res/OpenLayers/files/http://";
                                    $replace="<href>http://";
                                    $line_out=str_replace($search,$replace,$line);
                                    fwrite($handle, $line_out);
                                }
                                fclose($handle);
                                // All KMZ files seem to have just 'doc.kml' inside so make them more identifable & support multiple simultaneous uploads
                                // (Multiple files in the normal 'files' folder are less likely to collide, but could be fixed by more rewriting)
                                $basename=reset(explode('.',$_FILES['load']['name']));
                                $newname = $dir.$basename.".kml";
                                rename($output, $newname);
                                // remove non-rewritten file:
                                unlink ($input);
                            }
                        }
                    }
                }
            add_confirmation(_t("File was decompressed"));
            // remove zipped file:
            unlink ($zipped);
            add_confirmation(_t("File was deleted"));
            } else {
                if(version_compare(phpversion(), "5.2.0", "<"))
                    $infoVersion="(use PHP 5.2.0+ or <a href=\"http://pecl.php.net/package/zip\" target=_blank>PECL</a>)";
                    
                add_error(_t("You need to install/enable the php_zip extension")." $infoVersion "._t("to decompress KMZ files.")); 
            }
        }
    }
}    

//Print the error message if an error occurred with the Upload File
display_errors($return=false,$clean_errors=true,$exit=false);
//draw upload form
_shn_gis_upload_files_form();


function _shn_gis_upload_files_form()
{
	print '<h2>'._t("Upload Files").'</h2>';
    print '<p>'._t("This form allows uploading of files in").' <a href="http://en.wikipedia.org/wiki/Keyhole_Markup_Language" target=_blank>KML</a>, <a href="http://wiki.openstreetmap.org/index.php/Protocol" target=_blank>OSM</a> '._t("or").' <a href="http://en.wikipedia.org/wiki/Geography_Markup_Language" target=_blank>GML</a> '._t("format to").' www/res/OpenLayers/files</p>';
    print '<p>KMZ '._t("files will be unzipped upon upload").'.</p>';
    print '<p>'._t("NB Be sure that the file contains the actual data you want & isn't simply a 'Network Link'").'.</p>';
    print '<p>'._t("File should have one of the following extensions:").'.kml, .kmz, .osm '._t("or").' .xml</p>';

	global $global;
	include_once $global['approot']."/inc/lib_form.inc";

    $upload_help=_t("KML files should have the extension .kml or .kmz, OSM files should have the extension .osm, GML files should have the extension .xml.");
	shn_form_fopen("gis_files",null,array('enctype'=>'enctype="multipart/form-data"','req_message'=>false));
	shn_form_fsopen(_t("Upload File"));
    shn_form_upload(_t('Upload KML, OSM or GML'),"load",array('req'=>false,"help"=>$upload_help));
	shn_form_fsclose();
	shn_form_submit(_t("Upload"));
	shn_form_fclose();
    print "<br />";
    // List current directory contents
    _shn_gis_list_files();
}

function _shn_gis_list_files()
// ToDo: Separate lists for the 3 different sorts
{
    print '<h2>'._t("Current Files").'</h2>';
    print '<p>'._t("These are the files currently available on this server").':</p>';
    global $global;
    $dir=$global['approot'].'/www/res/OpenLayers/files';
	//Read into Arrays ready for sorting
    $kml = array();
    $osm = array();
    $gml = array();
    if ($handle = opendir($dir)) {
        while (false !== ($file = readdir($handle))) {
            if ($file != "." && $file != ".." && !is_dir($dir."/".$file)) {
                $ext=end(explode('.',$file));
                if ("kml"==$ext){
                    $kml[$file]="<a href=\"res/OpenLayers/files/".$file."\" target=_blank>".$file."</a><br />\n";
                } else if ("osm"==$ext){
                    $osm[$file]="<a href=\"res/OpenLayers/files/".$file."\" target=_blank>".$file."</a><br />\n";
                } else if ("xml"==$ext){
                    $gml[$file]="<a href=\"res/OpenLayers/files/".$file."\" target=_blank>".$file."</a><br />\n";
                }
            }
        }
        // Sort arrays
        asort ($kml);
        asort ($osm);
        asort ($gml);
        // Print out to screen
        echo "<table><thead><td>KML</td><td>OSM</td><td>GML</td></thead>\n";
        echo "<tbody><tr><td valign='top'><table>\n";
        foreach ($kml as $key => $val) {
            echo "<tr><td style=\"border: 0px;\">$val</td></tr>\n";
        }
        echo "</table><td valign='top'><table>\n";
        foreach ($osm as $key => $val) {
            echo "<tr><td style=\"border: 0px;\">$val</td></tr>\n";
        }
        echo "</table><td valign='top'><table>\n";
        foreach ($gml as $key => $val) {
            echo "<tr><td style=\"border: 0px;\">$val</td></tr>\n";
        }
        echo "</table></td></tr></tbody></table>\n";
        closedir($handle);
    }
}


