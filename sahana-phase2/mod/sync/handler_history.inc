<?php
/**
 * This handeler display the history of synchronization
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

global $global;
echo "<h2>"._t('Synchronization History')."</h2>";
$sql="SELECT * FROM sync_instance";
$rs=$global['db']->GetAll($sql);
echo "<div id ='result'>
        <table><thead><td>"._t('Instance ID')."</td>
        <td>"._t('Owner')."</td>
        <td>"._t('Contacts')."</td>
        <td>"._t('Last Update')."</td>
        <td>"._t('Update Count')."</td>
        </thead>";
foreach($rs as $row){
    echo "<tr>";
        echo "<td>".$row[0]."</td>";
        echo "<td>".$row[1]."</td>";
        echo "<td>".$row[2]."</td>";
        echo "<td>".$row[4]."</td>";
        echo "<td>".$row[5]."</td>";
    echo "</tr>";
}
echo "</table></div>";
