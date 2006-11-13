<?php
/* $Id: lib_st_image.inc,v 1.3 2006-11-13 17:48:32 chamindra Exp $ */

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
 * @subpackage zz_deprecated
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */
 
function shn_stream_init($filename=null)
{
    if($_GET['imagetype'])
        header("Content-type: image/{$_GET['imagetype']}");
    else
        header("Content-type: image/jpeg");

    if(isset($_GET['download']))
        header("Content-Disposition: attachment; filename=$file");
}

function shn_stream_close($function,$output)
{
    echo $output;
}

?>
