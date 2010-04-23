<?php
/* $Id: lib_stream_xml.inc,v 1.9 2009/08/22 17:17:25 ravithb Exp $ */

/**
 *
 * <Description goes here>
 *
 * PHP version 4 and 5
 * * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage stream_xml
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */
 
function shn_stream_init($emit_xml_declaration = false)
{
    $file = 'download.xml';
    if(isset($_GET['filename']))
        $file = $_GET['filename'];
    //todo need a way to pass header;

    header("Content-type: text/xml");
    if(isset($_GET['download']))
        header("Content-Disposition: attachment; filename=$file");

    if ($emit_xml_declaration) {
        echo "<?xml version=\"1.0\" ?>\n";
    }
    
    shn_stream_display_error();
}

function shn_stream_close()
{

}

function shn_xml_check_perms(){
        return ALLOWED;//skip authentication
}

// let the XML stream have it's own error function
function shn_stream_display_error() {

    global $global;

    // return if there are no errors
    if (count($global['submit_errors']) == 0 ) return;
    
    echo '<errorset>';
	foreach ($global['submit_errors'] as $error){
		echo '<error>'._t($error).'</error>';
	}
    echo '</errorset>';

}


function _shn_soap_display_errors(){
    shn_stream_display_error();
    return;
}

