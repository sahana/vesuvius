<?php


/** 
 * Home Page of the Catalogue System. 
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
<h2><?= _('Catalogue System'); ?></h2>
<p><?= _('The Catalogue System helps to capture the Information about catalogues, sub catalogues, Items and measurement Units that are used by the Inventory Management System which manages the Inventories and Pledge/Request Management system which keeps track of requests of aid and supplies.  '); ?></p>
    <br></br>
    <div><h3><b><em><?= (_("Features Include:")) ?></em></b></h3></div>
<ul>

<li><a href="index.php?mod=cs&act=addmain"><b><?= _('Add Main catalogue'); ?> </b> </a><?= _(' - Enables user to add root catalogues.'); ?></li>
<li><a href="index.php?mod=cs&act=addsub"><b><?= _('Add sub catalogue'); ?></b></a><?= _(' - Enables user to add sub catalogues under root catalogues. Sub catalogues might have several levels. '); ?></li>
<li><a href="index.php?mod=cs&act=additem"><b><?= _('Add Item'); ?></b></a><?= _(' - Enables user to add Items that is used in Inventery Management System.'); ?>
</li></ul>

<em><p><?=_('Eg: Medicine --> Paracetamol --> ... --> Tablets ')?><br> <?=_('<b>Medicine</b> can be considered as an example for a Main Catalogue while <b>Paracetamol</b> is one of the sub catalogues under <b>Medicine</b>. There May be several levels upto the Item level and finally <b>Tablet</b> is an item which is under Paracetamol. ')?></p></em>

<ul>
<li><a href="index.php?mod=cs&act=addunittype"><b><?= _('Add Measurement Unit Type'); ?> </b> </a><?= _(' - Enables user to add measurement unit type. eg - Volume , Mass , Length etc.'); ?></li>
<li><a href="index.php?mod=cs&act=addunit"><b><?= _('Add Measurement Unit'); ?></b></a><?= _(' - Enables user to add Measurement Units under Measurement Unit types. eg - kg, g, mg Under Mass Unit Type.'); ?></li>
</ul>

<ul>
<li><a href="index.php?mod=cs&act=viewedit"><b><?= _('View and Edit'); ?> </b></a><?= _(' - Enables user to view, edit and delete item/catalogues, unit types and units that are managed by the catalogue system.'); ?></li>
<li><a href="index.php?mod=cs&act=supplier_report"><b><?= _('Supplier Report'); ?></b></a><?= _(' - Enables user to have a report on registered suppliers for each catalogue.'); ?></li>
</ul>

</div>



