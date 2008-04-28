<?php
/** 
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author   Mifan Careem <mifan@respere.com>
* @author   Fran Boon <flavour@partyvibe.com>
* @package  Sahana - http://sahana.sourceforge.net
* @module	sm
* @version	$id$
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

function shn_sm_default()
{
        global $conf;
?>
<div id="home">
<h2><?php echo $conf['mod_sm_name'];?></h2>
<p><?php echo  _t("The {$conf['mod_sm_name']} module provides a mechanism to " .
		"collaboratively provide an overview of the developing disaster, using " .
		"online mapping (GIS). You can add markers and pictures to pin point " .
		"incidents on the map.");?> 
</p>
    <div><h3><b><em><?= (_t("Features Include:")) ?></em></b></h3></div>
<br></br>
<ul>
        <li><?php echo _t('Provides a map based view of the disaster situtation'); ?></li>
        <li><?php echo _t('Allow users to collaboratively add markers of the developing disaster situation');?></li>
</ul>
<strong><?php echo _t('Description of Actions:')?></strong><br/>
    <ul>
        <li><a href="index.php?mod=sm&act=swik"><b><?= _t('View Situation Map'); ?></b></a><br/><?= _t('Map of the developing situation with markers of incidents, locations and objects displayed on the map'); ?></li>
        <li><a href="index.php?mod=sm&act=awik"><b><?= _t('Add New Situation'); ?> </b> </a><br/><?= _t('Add markers on the map of incidents and objects with pictures'); ?></li>
        <!--<li><a href="index.php?mod=sm&act=ewik"><b><?= _t('Edit Situation'); ?> </b> </a><br/><?= _t('Edit Situations'); ?></li>-->
        <!--<li><a href="index.php?mod=sm&act=mapc"><b><?= _t('General Map'); ?> </b></a><br/><?= _t('Free form map of the location without markers'); ?></li>-->
    </ul>
<br/>
</div>
<?php
}
?>
