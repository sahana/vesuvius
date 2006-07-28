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
<li><b><?= _('Add Main catalogue - '); ?> </b> <?= _('Enables user to add root catalogues.'); ?></li>
<li><b><?= _('Add sub catalogue - '); ?></b><?= _('Enables user to add sub catalogues under root catalogues. Sub catalogues might have several levels. '); ?></li>
<li><b><?= _('Add Item - '); ?></b> <?= _('Enables user to add Items that is used in Inventery Management System.'); ?>
</ul></li>

<em><p><?=_('Eg: Medicine --> Paracetamol --> ... --> Tablets ')?><br> <?=_('<b>Medicine</b> can be considered as an example for a Main Catalogue while <b>Paracetamol</b> is one of the sub catalogues under <b>Medicine</b>. There May be several levels upto the Item level and finally <b>Tablet</b> is an item which is under Paracetamol. ')?></p></em>

<ul>
<li><b><?= _('Add Measurement Unit Type  - '); ?> </b> <?= _('Enables user to add measurement unit type. eg - Volume , Mass , Length etc.'); ?></li>
<li><b><?= _('Add Measurement Unit - '); ?></b><?= _('Enables user to add Measurement Units under Measurement Unit types. eg - kg, g, mg Under Mass Unit Type.'); ?></li>



</div>



