
<?php
/** 
 * Home Page of the Service Catalog System. 
/**
 * Edit  
 *
 * PHP version 4 and 5
 *
 * @author      thinesh Thusinthaka
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage service
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
?>

<div id="home">
<h2><?= _t('Catalogue System'); ?></h2>
<p><?= _t('The Catalogue System helps to manupulate Feeds data'); ?></p>
    <br></br>
    <div><h3><b><em><?= (_t("Features Include:")) ?></em></b></h3></div>
<ul>

<li><b><?= _t('Delete Feed - '); ?> </b> <?= _t('Enables Admin/root to Delete Feed'); ?></li>
<li><b><?= _t('Modify Feed - '); ?></b><?= _t('Enables Admin/root to Modify Feed Items to his acess levels. '); ?></li>
<li><b><?= _t('Add Feed - '); ?></b> <?= _t('Enables user to add Feeds data to the Catalog and set Feed visibility levels to Normal users.'); ?>
</ul></li>

<ul>
<li><b><?= _t('Add FEEDS '); ?> </b> <?= _t('Enables the admin to Add/Edit/Delete Feeds.'); ?>
</li>

<li><b><?= _t('Admin can set the Feed visibility to normal user by Sahana Admin Interface  '); ?></b><?= _t('Visibilty of Feeds is possible by login session of user ');	?></li>


</div>





