<?php
/**
* Sahana front controller, through which all actions are dispatched
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     http://www.linux.lk/~chamindra
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/


/**
 * shn_display_xhtml_head
 *
 * @param $arrPostfix array stores the list of lines you want to insert into the header
 * @param $theme string decides on what css theme you are using
 * @param $title string if you want to change it from the default
 */
function shn_display_xhtml_head( $arrPostfix = null, $theme = null, $title = null )
{
    global $conf;

    # set the theme if it is not given as a parameter
    $theme || $theme = $conf['theme'];
    $title || $title = _("Sahana FOSS Disaster Management System");

?>
    <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
    <html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
    <head>
        <title><?=_($title)?></title>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <link rel="stylesheet" media="screen, projection" type="text/css" href="theme/<?=$theme?>/sahana.css" />
	<link rel="stylesheet" media="print" type="text/css" href="theme/<?=$theme?>/print.css" />
	<link rel="stylesheet" media="handheld" type="text/css" href="theme/<?=$theme?>/mobile.css" />
    <script type="text/javascript" src="theme/<?=$theme?>/sahana.js"></script> 
    <script type="text/javascript" src="res/js/popup.js"></script> 
    <script type="text/javascript" src="stream.php?stream_type=help"></script> 
<?php
    if ($arrPostfix != null) {
        foreach ($arrPostfix as $i) {
            echo '        '.$i."\n";
        }
    }

    echo "    </head>\n";
}
?>
<style>

.popupLink { COLOR: red; outline: none }

.popup { POSITION: absolute; VISIBILITY: hidden; BACKGROUND-COLOR: yellow; LAYER-BACKGROUND-COLOR: yellow; width: 200; BORDER-LEFT: 1px solid black; BORDER-TOP: 1px solid black; BORDER-BOTTOM: 3px solid black; BORDER-RIGHT: 3px solid black; PADDING: 3px; z-index: 10; }

</style>
