<?php
/**
* Sahana front controller, through which all actions are dispatched
* Sahana - http://sahana.sourceforge.net
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    framework
* @subpackage handler 
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
    <script type="text/javascript" src="res/js/libsahana.js"></script>
    <script type="text/javascript" src="theme/<?=$theme?>/sahana.js"></script>
    <script type="text/javascript" src="res/js/popup.js"></script> 
    <script type="text/javascript" src="res/js/locale.js"></script>    
    <script type="text/javascript" src="index.php?stream=text&amp;mod=home&amp;act=help"></script> 
<?php
    if ($arrPostfix != null) {
        foreach ($arrPostfix as $i) {
            echo '        '.$i."\n";
        }
    }
    echo "    </head>\n";
}

?>
