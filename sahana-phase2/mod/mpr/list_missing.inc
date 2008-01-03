<?php


/* $Id: list_missing.inc,v 1.5 2008-01-03 04:43:07 isurunishan Exp $ */

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
<div id="home_recent">
<h1><?= _('Missing People'); ?></h1>
<?php


global $global;
global $conf;
require ($global['approot'] . 'mod/mpr/mpr_lib.inc');
$limit = $conf['mod_mpr_pictures_per_page'];
$type = "missing";
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
	//print $no_of_pages_required.$count.floor($count/$limit);

	for ($i = 0; $i < $no_of_pages_required; $i++) {
?>
<a href="index.php?mod=mpr&act=list_missing&offset=<?=$limit*$i?>" class="hideprint"><?=$i+1?></a>

<?php


	}
	//paging support
	if ($count >= $offset + $limit)
		$next = $limit + $offset;
	else
		$next = 0;
?>

<a href="index.php?mod=mpr&act=list_missing&offset=<?=$next?>" class="hideprint">Next</a>

<?php


	shn_mpr_search_show_verticle($_SESSION['result']);

	for ($i = 0; $i < $no_of_pages_required; $i++) {
?>
<a href="index.php?mod=mpr&act=list_missing&offset=<?=$limit*$i?>" class="hideprint"><?=$i+1?></a>

<?php


	}
?>
<a href="index.php?mod=mpr&act=list_missing&offset=<?=$next?>" class="hideprint">Next</a>
<?php


} else {

	shn_mpr_search_show_verticle($_SESSION['result']);
}
print '<BR/><BR/>';
?>

 <input type="button"  value="Print Current Page" class="hideprint" onClick="self.print()"/>
 </div>

