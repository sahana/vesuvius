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
$ins=substr($_FILES['file_dump']['name'], -19, 4);
?>
<center><strong>The file was uploaded successfully...</strong>
<br />
<table>
<thead><td colspan="2">Uploaded File Info</td></thead>
<tr><td>Name </td><td><?=$_FILES['file_dump']['name']?></td></tr>
<tr><td>Type </td><td><?=$_FILES['file_dump']['type']?></td></tr>
<tr><td>Size </td><td><?=$_FILES['file_dump']['size'].' kb'?></td></tr>
<tr><td colspan="2"></td></tr>
<tr><td>Time Created</td><td><?=date("F j, Y, g:i a",$time)?></td></tr>
<tr><td>Dump Instance</td><td><?=$ins?></td></tr>
</table >
</center>
<br />
<?php
    shn_form_fopen('synchronize',NULL,array('req_message'=>false));
    echo "<center>";
    echo "<a href=\"#\" onclick=\"document.getElementById('adv_opt').style.display='block';\">Advance Options</a>";
    shn_form_submit('Start Synchronizing');
    echo "</center>";
    echo "<div id='adv_opt' style='display:none'>";
    shn_form_fsopen('Advance Options');
    $options=array('0'=>'0','1'=>'1','2'=>'2');
    shn_form_select($options,'Threshold', 'threshold');
    $options=array('yes'=>'Yes','no'=>'No');
    shn_form_select($options,'Overwrite existing data','oed');
    shn_form_fsclose();
    echo "</div>";
    shn_form_fclose();
?>
<br />
