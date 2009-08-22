<?php

/**
* Sahana GIS List Markers
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

function _shn_gis_list_markers()
{
    ?>
    <script type="text/javascript">
        function list_contents(folder,level) {
            var oRequest = new XMLHttpRequest();
            var sURL  = "tmp/gis_list_folders/" + folder + ".txt";
            var text = "Error downloading " + sURL;
            var div = "contents" + level;
            oRequest.open("GET",sURL,false);
            oRequest.setRequestHeader("User-Agent",navigator.userAgent);
            oRequest.send(null);
            if (oRequest.status==200) text = oRequest.responseText;
            
            document.getElementById(div).innerHTML = text;
            //clear all higher levels (up to number of divs we have defined)
            level++;
            text = "";
            for (i=level;i<5;i++) {
                var div = "contents" + i;
                document.getElementById(div).innerHTML = text;
            }
        }
    </script>
    <?php
    print '<h2>'._t("Current Markers").'</h2>';
    print '<p>'._t("These are the Markers currently available on this server").':</p>';
    print '<p>'._t("(Click folder icon to expand)").'</p>';
    global $global;
    global $conf;
    $dir=$conf['gis_marker_folder'];
    $dir2=$global['approot']."/www/$dir";
    print "\n<table><tr><td valign='top' style=\"border: 0px;\"><table>\n";
    _shn_gis_list_markers_path($dir2,$dir);
    print "</table></td><td valign='top' style=\"border: 0px;\"><div id=\"contents1\"></div></td>\n";
    print "<td valign='top' style=\"border: 0px;\"><div id=\"contents2\"></div></td>\n";
    print "<td valign='top' style=\"border: 0px;\"><div id=\"contents3\"></div></td>\n";
    print "<td valign='top' style=\"border: 0px;\"><div id=\"contents4\"></div></td>\n";
    print "<td valign='top' style=\"border: 0px;\"><div id=\"contents5\"></div></td>\n";
    print "</tr></table>\n";
}

/**
 * Print Icons & Folders in table
 */
function _shn_gis_list_markers_path($path,$source_dir,$level = 1)
{
    global $global;
    //Files to ignore and send to /dev/null \:-|
    $ignore = array( 'CVS', '.', '..' );
    //Read into Array ready for sorting
    $files = array();
    $folders = array();
    if($handle = opendir($path)){
    	while( false !== ( $file = readdir( $handle ) ) ){
			//Not to be ignored and tossed aside...    
	        if( !in_array( $file, $ignore ) ){
	            if( is_dir( "$path/$file" ) ){            
	                $folders[$file]="<tr><td style=\"border: 0px;\"><img src='res/img/folder.png' onclick='list_contents(\"$file\",\"$level\");' /></td><td style=\"border: 0px;\">".$file."</td></tr>\n";
                    _shn_gis_list_folders( "$file", "$path/$file", "$source_dir/$file/",($level+1) );
	            } 
	            else {
	                $files[$file]="<tr><td style=\"border: 0px;\"><img src=\"$source_dir".$file."\" /></td><td style=\"border: 0px;\">".$file."</td></tr>\n";
	            }
	        }
    	}
        // Sort arrays
        asort ($folders);
        asort ($files);
        // Print out to screen - folders first
        foreach ($folders as $key => $val) {
            echo "$val\n";
        }
        foreach ($files as $key => $val) {
            echo "$val\n";
        }
        closedir( $handle );
    }
}

/**
 * Recursively write folder contents out to a file
 */
function _shn_gis_list_folders($file,$path,$source_dir,$level = 2)
{
    //Where to store directory listings
    global $global;
    $dir = $global['approot'].'www/tmp/gis_list_folders';
    mkdir($dir);
    $output = $dir."/$file.txt";
    $handle_write = fopen($output, 'w');
    fwrite($handle_write, "<table><tr>\n");
    $ignore = array( 'CVS', '.', '..' );
    //Read into Array ready for sorting
    $files = array();
    $folders = array();
    if($handle = opendir("$path")){
        while( false !== ( $file = readdir( $handle ) ) ){
            if( !in_array( $file, $ignore ) ){
                if( is_dir( "$path/$file" ) ){            
                    $folders[$file]="<tr><td><img src='res/img/folder.png' onclick='list_contents(\"$file\",\"$level\");' /></td><td>".$file."</td></tr>\n";
                    _shn_gis_list_folders( "$file","$path/$file", "$source_dir/$file",($level+1) );
                } else {
                    $files[$file]="<tr><td><img src=\"$source_dir/".$file."\" /></td><td>".$file."</td></tr>\n";
                }
            }
        }
        closedir( $handle );
    }
    // Sort arrays
    asort ($folders);
    asort ($files);
    // Print out to file - folders first
    foreach ($folders as $key => $val) {
        fwrite($handle_write, "$val\n");
    }
    foreach ($files as $key => $val) {
        fwrite($handle_write, "$val\n");
    }
    fwrite($handle_write, "</tr></table>\n");
    fclose($handle_write);
}


