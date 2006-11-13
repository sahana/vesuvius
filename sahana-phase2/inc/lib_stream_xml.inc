<?php
/* $Id: lib_stream_xml.inc,v 1.2 2006-11-13 17:46:26 chamindra Exp $ */

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
 
function shn_stream_init($filename)
{
    $file = 'download.xml';
    if(isset($_GET['filename']))
        $file = $_GET['filename'];
    //todo need a way to pass header;

    header("Content-type: text/xml");
    if(isset($_GET['download']))
        header("Content-Disposition: attachment; filename=$file");
        
    
    echo '<?xml version="1.0" ?>';
}

function shn_stream_close($function,$output)
{
    echo $output;
}

?>
