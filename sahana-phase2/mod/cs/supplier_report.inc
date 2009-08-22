<?php
/**
 * Supplier Report
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author       Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage cs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

function shn_cs_show_supplier_report()
{
    global $global;
    $db = $global["db"];
	?>
	<h2><?php echo  _t('Supplier Report'); ?></h2>
	<p><?php echo  _t('Here you can have a report on items with supplier details which are having registered suppliers in catalog system.'); ?></p>

    <br>
    <div id="result">
    <table>
    <thead>
    <td><strong><?php echo _t("Item ID")?></strong></td>
    <td><strong><?php echo _t("Name")?></strong></td>
    <td><strong><?php echo _t("Description")?></strong></td>
    <td><strong><?php echo _t("Supplier ID")?></strong></td>
    <td><strong><?php echo _t("Supplier")?></strong></td>
    </thead>
    <tbody>
    <?php
    $query = "SELECT * FROM ct_suppliers";
    $res = $db->Execute($query);

    while (!$res == NULL && !$res->EOF) {
        $item_id = $res->fields["ct_uuid"];
        $suplier_id = $res->fields["supplier"];

        $suplier_name = shn_or_organization_name(array($suplier_id));

        $item_query = "SELECT * FROM ct_catalogue WHERE ct_uuid ='$item_id' ";
        $item_res = $db->Execute($item_query);

        $description = $item_res->fields["description"];
        $name = $item_res->fields["name"];
    ?>
    <tr>
    <td><?php print $item_id; ?></td>
    <td><?php print $name; ?></td>
    <td><?php print $description; ?></td>
    <td><?php print $suplier_id; ?></td>
    <td><?php print $suplier_name[$suplier_id]; ?></td>
    </tr>
    <?php 
        $res->MoveNext();
    }//end of while loop

    ?>
    </tbody>    
    </table>
    </div>
    <?php
}
