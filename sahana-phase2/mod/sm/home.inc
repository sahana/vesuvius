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
<div id="home" style="postion:relative;">

<div>
<h2><?php echo $conf['mod_sm_name'];?></h2>
<p><?php echo  _t('The Situation Awareness module allows the current situation to be visualized on a map.').' '.
               _t('It allows all users to collaboratively update the map as new information comes to light.');?> 
</p>
    <div><h3><b><em><?php echo  (_t("Features Include:")) ?></em></b></h3></div>
<br></br>
<ul>
        <li><?php echo _t('Provides a map based view of the disaster situtation'); ?></li>
        <li><?php echo _t('Allow users to collaboratively add markers of the developing disaster situation');?></li>
</ul>
<strong><?php echo _t('Description of Actions:')?></strong><br/>
    <ul>
        <li><a href="index.php?mod=sm&act=swik"><b><?php echo  _t('View Situation Map'); ?></b></a><br/><?php echo  _t('Map of the developing situation with markers of incidents, locations and objects displayed on the map'); ?></li>
        <li><a href="index.php?mod=sm&act=awik"><b><?php echo  _t('Add New Situation'); ?> </b> </a><br/><?php echo  _t('Add markers on the map of incidents and objects with pictures'); ?></li>
        <!--<li><a href="index.php?mod=sm&act=ewik"><b><?php echo  _t('Edit Situation'); ?> </b> </a><br/><?php echo  _t('Edit Situations'); ?></li>-->
        <li><a href="index.php?mod=sm&act=analysis_radius"><b><?php echo  _t('Situation Analysis: Radius'); ?> </b> </a><br/><?php echo  _t('Report on which situations are located within a specified radius of a selected location'); ?></li>
        <!--<li><a href="index.php?mod=sm&act=mapc"><b><?php echo  _t('General Map'); ?> </b></a><br/><?php echo  _t('Free form map of the location without markers'); ?></li>-->
    </ul>
</div>

<div id="sm_home_map">
  <h2><?php echo _t('Current Situation'); ?></h2>
  <div style="overflow: hidden;">
    <?php //show a map. function defined in wm_fns.inc
        shn_sm_show_map_home(); ?>
  </div>
</div>

</div>
<?php
}

