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

<p><?=_('"Add Main catalogue"  will add root Items of the catalogue while "Add sub catalogue" adding sub Items under those root catalogues. "Add Item" is capturing information about Items that you wish to use in Inventery Management System. Before go to add catalogues and Items add the measurement unit types and units that are used to measure the particular Item.')?></p>
<p><?=_('Eg: Medicine --> Paracetamol --> ... --> Tablets ')?></p>
<p><?=_('"Medicine" can be considered as an example for a Main Catalogue while "Paracetamol" is one of a sub catalogue under "Medicine". There May be several levels upto the Item level and finally "Tablet" is an item which is under Paracetamol. ')?></p>
</div>



