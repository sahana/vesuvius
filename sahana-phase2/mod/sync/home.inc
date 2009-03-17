<?php

/* $Id: home.inc,v 1.10 2009-03-17 06:08:24 ravithb Exp $ */

/** 
 * Home Page of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Janaka Wickramasinghe <janaka@opensource.lk>
 * @author	   J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
?>
<div id="home">
<h2><?php echo  _t('Synchronization Module'); ?></h2>
<!-- <img src="theme/default/img/mpr.png"/> -->
<p><?php echo  _t('This module helps you to synchronize two separate Sahana installations and share information among the independent Sahana instances.'); ?><br /><br />


    <div><h3><b><em><?php echo  (_t("Features Include:")) ?></em></b></h3></div>
<br></br>

</p>
<ul>
    <li><?php echo  _t('Import and export information among Sahana instances'); ?></li>
    <li><?php echo  _t('Allows details of the data sharing history among selected Sahana installations'); ?></li>
</ul>


<strong><?php echo _t('Description of Actions:')?></strong><br/>
    <ul>
        <li><a href="index.php?mod=sync&act=download"><b><?php echo  _t('Export data'); ?> </b></a><br/><?php echo  _t('Save the information of selected modules to XML, CSV, SQL or SQLite in compressed or uncompressed file formats'); ?></li>
        <li><a href="index.php?mod=sync&act=upload"><b><?php echo  _t('Import data'); ?> </b> </a><br/><?php echo  _t('Update Sahana database with information \'exported\' from another Sahana installation.' ); ?></li>
        <li><a href="index.php?mod=sync&act=history"><b><?php echo  _t('History'); ?></b></a><br/><?php echo  _t('Lists all synchronizations done in the past.'); ?></li>
        
	</ul>
<br/>   
        


<!--<center><em class="red">This module is still under heavy development It is not advisable to use it for practical purposes</em></center> -->
</div>
