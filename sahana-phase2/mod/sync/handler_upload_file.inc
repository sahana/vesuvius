<?php
/**
 * Dump File Upload Handler 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage sync
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

//calculate the file creation date
$time=(int)substr($_FILES['file_dump']['name'], -14, 10);
$ins=substr($_FILES['file_dump']['name'], -18, 4);
?>
<center><strong>The file was uploaded successfully...</strong></center>
<br />
<center>
<table>
<thead><td colspan="2">Uploaded File Info</td></thead>
<tr><td>Name </td><td><?=$_FILES['file_dump']['name']?></td></tr>
<tr><td>Type </td><td><?=$_FILES['file_dump']['type']?></td></tr>
<tr><td>Size </td><td><?=$_FILES['file_dump']['size'].' kb'?></td></tr>
<tr><td colspan="2"></td></tr>
<tr><td>Time Created</td><td><?=date("F j, Y, g:i a",$time)?></td></tr>
<tr><td>Dump Instance</td><td><?=$ins?></td></tr>
</table>
</center>
<br />
<center>
<form action="index.php?mod=sync&act=synchronize" method="POST">
<label>Threshold</label>
<select name="threshold">
    <option value="0">0</option>
    <option value="1">1</option>
    <option value="2">2</option>
</select>
<input type="submit" value="Start Synchronize">
</form>
</center>