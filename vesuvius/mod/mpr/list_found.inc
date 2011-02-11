<?php


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


?><div id="home_recent"><h1><?php echo  _t('Found People'); ?></h1><?php

global $global;
global $conf;
require ($global['approot'] . 'mod/mpr/mpr_lib.inc');

$limit = $conf['mod_mpr_pictures_per_page'];
$type = "found";





/*$offset = $_GET['offset'];
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
<!--<div class="hide">-->
<a href="index.php?mod=mpr&act=list_missing&offset=<?php echo $limit*$i?>" class="hideprint"><?php echo $i+1?></a>

<?php

	}
	if ($count >= $offset + $limit)
		$next = $limit + $offset;
	else
		$next = 0;
?>

<a href="index.php?mod=mpr&act=list_missing&offset=<?php echo $next?>" class="hideprint">Next</a>

<?php


	shn_mpr_search_show_verticle($_SESSION['result']);

	for ($i = 0; $i < $no_of_pages_required; $i++) {
?>
<a href="index.php?mod=mpr&act=list_missing&offset=<?php echo $limit*$i?>" class="hideprint"><?php echo $i+1?></a>

<?php

	}
?>
<a href="index.php?mod=mpr&act=list_missing&offset=<?php echo $next?>" class="hideprint">Next</a>

<?php

} else {

	shn_mpr_search_show_verticle($_SESSION['result']);
}
print '<BR/><BR/>';*/




$offset = 0;
$found = shn_mpr_home_show_mpr($type, $limit, $offset);
_shn_mpr_listing($found);
print '<BR/><BR/>';

?><input type="button"  value="Print Current Page" onClick="self.print()" class="hideprint"/></div><?php 