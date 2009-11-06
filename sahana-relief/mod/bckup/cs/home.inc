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
    <h2><?php echo  _t('Aid Catalog and Classification System'); ?></h2>
    <p><?php echo  _t('The Aid Catalog is used by the Inventory and the Request Management System as a reference classification of all aid item types. Item types are classified and grouped by type (e.g. food, medical) and units are associated to aid types for quantifying purposes by the other modules. The quantities of Aid is not kept in this module but for example in the Inventory and Request / Pledge Management Modules'); ?></p>
    <br></br>
    <div><h3><b><em><?php echo  (_t("Features Include:")) ?></em></b></h3></div>
<br></br>
    <ul>
        <li><?php echo _t('Classification or categorization of items to any level of depth')?></li>
        <li><?php echo _t('Association of measurement units for conversion and summation')?></li>
        <li><?php echo _t('Dynamic addition of new items types by authorized individuals')?></li>
    </ul>

    <!-- <div><h3><b><em><?php echo  (_t("Given below are some of the main functions:")) ?></em></b></h3></div> -->

    <strong><?php echo _t("Description of Actions:")?></strong><br/>
    <ul>
        <li><a href="index.php?mod=cs&act=viewedit"><b><?php echo  _t('View and Edit'); ?> </b></a><br/><?php echo  _t('View all the currently registered catalogs, aid items types and their associated measurement units.'); ?></li>
        <li><a href="index.php?mod=cs&act=addmain"><b><?php echo  _t('Add Main Catalog'); ?> </b> </a><br/><?php echo  _t('Do this first to create base groupings by major aid type (e.g. Food and Nutrition)'); ?></li>
        <li><a href="index.php?mod=cs&act=addsub"><b><?php echo  _t('Add (sub)-Category'); ?></b></a><br/><?php echo  _t('Within a Catalog there can be many sub-classifications or sub-categories of items. For example if the Base Catalog is Food and Nutrition a sub category would be Dry Food'); ?></li>
        <li><a href="index.php?mod=cs&act=additem"><b><?php echo  _t('Add Aid Item Type'); ?></b></a><br/><?php echo  _t('Add New Aid Items Types to the Sahana System'); ?>
        <li><a href="index.php?mod=cs&act=addunit"><b><?php echo  _t('Add Measurement Unit'); ?></b></a><br/><?php echo  _t('Associate a measurement scale to an Aid Item Type. For example the Item Type, Rice would be measured in Kilograms'); ?></li>
</ul>

</div>




