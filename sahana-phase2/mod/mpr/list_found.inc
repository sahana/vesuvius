<?php

/* $Id: list_found.inc,v 1.2 2006-12-10 15:08:52 isurunishan Exp $ */

/** 
 * List Missing Persons with paging support
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author Isuru Samaraweera(isuru@opensource.lk)	   
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
?>
<script language="JavaScript" src="mpr_print.js">

function printImages(title,division)
{
	
  var disp_setting="toolbar=yes,location=no,directories=yes,menubar=yes,"; 
      disp_setting+="scrollbars=yes,width=650, height=600, left=100, top=25"; 
  var content_vlue = document.getElementById(division).innerHTML; 
  
  var docprint=window.open("","",disp_setting); 
   docprint.document.open(); 
   docprint.document.write('<html><head><title>'+title+'</title>'); 
   docprint.document.write('</head><body onLoad="self.print()"><center>');          
   docprint.document.write(content_vlue);          
   docprint.document.write('</center></body></html>'); 
   docprint.document.close(); 
   docprint.focus(); 
	
}
</script>

<div id="home_recent">
<h1><?= _('Found People'); ?></h1>
<?php

global $global;
global $conf;
require ($global['approot'] . 'mod/mpr/mpr_lib.inc');

$limit = $conf['mod_mpr_pictures_per_page'];
$type = "found";
$offset = $_GET['offset'];
if ($offset == null)
	$offset = 0;
$count = shn_mpr_home_show_mpr($type, $limit, $offset);
if ($count > $limit) {
	$tmp = $count % $limit;
	if ($tmp > 0)
		$no_of_pages_required = floor($count / $limit) + 1;
	else
		$no_of_pages_required = round($count / $limit);
	//print $no_of_pages_required;

	for ($i = 0; $i < $no_of_pages_required; $i++) {
?>
<a href="index.php?mod=mpr&act=list_missing&offset=<?=$limit*$i?>"><?=$i+1?></a>

<?php

	}
	if ($count >= $offset + $limit)
		$next = $limit + $offset;
	else
		$next = 0;
?>

<a href="index.php?mod=mpr&act=list_missing&offset=<?=$next?>">Next</a>

<?php


	shn_mpr_search_show_verticle($_SESSION['result']);

	for ($i = 0; $i < $no_of_pages_required; $i++) {
?>
<a href="index.php?mod=mpr&act=list_missing&offset=<?=$limit*$i?>"><?=$i+1?></a>

<?php

	}
?>
<a href="index.php?mod=mpr&act=list_missing&offset=<?=$next?>">Next</a>
<?php

} else {

	shn_mpr_search_show_verticle($_SESSION['result']);
}
print '<BR/><BR/>';
?>
<input type="button"  value="Print Current Page" onClick="printImages2('Found People','home_recent')"/>
  
  
  




