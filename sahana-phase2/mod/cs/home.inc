<?php


/** 
 * Home Page of the Catalog System. 
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
?>
<div id="home">
<h2><?= _('Catalog System'); ?></h2>
<p><?= _('The catalog System helps to capture the Information about catalogs, sub catalogs, Items and measurement Units that are used by the Inventory Management System which manages the Inventories and Pledge/Request Management system which keeps track of requests of aid and supplies.  '); ?></p>
    <br></br>
    <div><h3><b><em><?= (_("Features Include:")) ?></em></b></h3></div>
<ul>

<li><a href="index.php?mod=cs&act=addmain"><b><?= _('Add Main catalog'); ?> </b> </a><?= _(' - Enables user to add root catalogs.'); ?></li>
<li><a href="index.php?mod=cs&act=addsub"><b><?= _('Add sub catalog'); ?></b></a><?= _(' - Enables user to add sub catalogs under root catalogs. Sub catalogs might have several levels. '); ?></li>
<li><a href="index.php?mod=cs&act=additem"><b><?= _('Add Item'); ?></b></a><?= _(' - Enables user to add Items that is used in Inventory Management System.'); ?>
</li></ul>

<em><p><?=_('Eg: Medicine --> Paracetamol --> ... --> Tablets ')?><br> <?=_('<b>Medicine</b> can be considered as an example for a Main catalog while <b>Paracetamol</b> is one of the sub catalogs under <b>Medicine</b>. There May be several levels upto the Item level and finally <b>Tablet</b> is an item which is under Paracetamol. ')?></p></em>

<ul>
<li><a href="index.php?mod=cs&act=addunittype"><b><?= _('Add Measurement Unit Type'); ?> </b> </a><?= _(' - Enables user to add measurement unit type. eg - Volume , Mass , Length etc.'); ?></li>
<li><a href="index.php?mod=cs&act=addunit"><b><?= _('Add Measurement Unit'); ?></b></a><?= _(' - Enables user to add Measurement Units under Measurement Unit types. eg - kg, g, mg Under Mass Unit Type.'); ?></li>
</ul>

<ul>
<li><a href="index.php?mod=cs&act=viewedit"><b><?= _('View and Edit'); ?> </b></a><?= _(' - Enables user to view, edit and delete item/catalogs, unit types and units that are managed by the catalog system.'); ?></li>
<li><a href="index.php?mod=cs&act=supplier_report"><b><?= _('Supplier Report'); ?></b></a><?= _(' - Enables user to have a report on registered suppliers for each catalog.'); ?></li>
</ul>

</div>



