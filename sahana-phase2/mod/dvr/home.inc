<?php
/* $Id: home.inc,v 1.1 2005-10-10 03:59:38 janakawicks Exp $ */

/**Main home page of the DVR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author	  Mifan 
* @author	  Janaka Wickramasinghe <janaka@opensource.lk> 
* @author	  Saumya 
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

?>
    <h3> Welcome to the DVR home </h3>
<?php
include($global['approot']."/inc/handler_component.php");
$info = <<<ENDL
    <p>This is some small paragraph explaining about what is DVR. Bla bla bla bla bla bla bla bla bla bla bla bla </p>
    <ul>
        <li>bla bla</li>
        <li>bla bla bla</li>
        <li>bla bla bla bla</li>
    </ul>
    <p>More bla bla bla arrrrgggg!!! that's enough</p>
ENDL;
$missing = <<<ENDL
    <b>Following Information has been updated</b>
    <ul>
        <li><a href="http://localhost/sahana/sahana-phase2/www/index.php?mod=dvr&act=view&id=12">chef's chocolate salted balls were found at...</a></li>
        <li><a href="http://localhost/sahana/sahana-phase2/www/index.php?mod=dvr&act=view&id=12">O my god you killed kenny...</a></li>
        <li><a href="http://localhost/sahana/sahana-phase2/www/index.php?mod=dvr&act=view&id=12">Kyle's mom found in the *ich camp...</a></li>
        <li><a href="http://localhost/sahana/sahana-phase2/www/index.php?mod=dvr&act=view&id=12">Cartman found stuck in the gutter...</a></li>
        <li><a href="http://localhost/sahana/sahana-phase2/www/index.php?mod=dvr&act=view&id=12">New data entered for 10-hitch-hikers group...</a></li>
    </ul>
ENDL;
    $stats = <<<ENDL
    <b>DVR Records</b><br>
    <img src="theme/default/img/stats.png" align="left">
    <a href="http://localhost/sahana/sahana-phase2/www/index.php?mod=dvr&act=stats&id=12">missing ratio in age group</a><br>
    <a href="http://localhost/sahana/sahana-phase2/www/index.php?mod=dvr&act=stats&id=12">found ratio in areas</a><br>
    <a href="http://localhost/sahana/sahana-phase2/www/index.php?mod=dvr&act=stats&id=12">number of affeted in areas</a><br>
ENDL;
?>
<table cellpadding="5" cellspacing="5">
<tr><td width="50%" valign="top">
<?php show_component($info, "DVR Information"); ?>
</td><td width="50%" valign="top">
<?php show_component($missing, "Watch on People"); ?>
</td>
<tr><td colspan="2" valign="top" align="center">
<?php show_component($stats, "Statistics"); ?>
</td>
</tr>
</tr>
</table>
