<?php

/**Admin Module for MapServer
*
* PHP version 5
* 
* @author       Hasitha Anjana <hasianjana@gmail.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/    	
* @module      MapServer
* @version     $Id: main_fns.inc,v 1.5 2009-08-22 17:17:25 ravithb Exp $
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

function shn_ms_default()
{
    global $conf;
?>
<div id="home">
<h2><?php echo $conf['mod_ms_name']?></h2>
<p>
<?php echo _t("The {$conf['mod_ms_name']} module provides the ability to configure maps to be displayed by the integrated ");?><a href="http://mapserver.gis.umn.edu" target=_blank>UMN MapServer</a>
<?php echo _t('. Please note that you have to install the UMN/Mapserver GIS Server on your system to use this module')?>
<br><br>
</p>
<hr>
<strong><?php echo _t('Description of Actions:')?></strong><br/>
    <ul>
        <li><a href="index.php?mod=ms&act=create_map"><b><?php echo _t('Create New Map'); ?></b></a><br/><?php echo  _t('Create basic map upon which layers can be added.'); ?></li>
        <li><a href="index.php?mod=ms&act=add_layer"><b><?php echo _t('Add Layer to Map');?></b></a><br/><?php echo  _t('Add a layer to an existing map.'); ?></li>
        <li><a href="index.php?mod=ms&act=edit_layer"><b><?php echo _t('Edit Layer');?></b></a><br/><?php echo  _t('Edit one of the existing layers on one of the maps.'); ?></li>
        <li><a href="index.php?mod=ms&act=list_maps"><b><?php echo _t('Manage Maps');?></b></a><br/><?php echo _t('View/Edit available maps.');?></li>
        <!-- Better moved to bottom of the 'Manage Maps' section
        <li><a href="index.php?mod=ms&act=search_map"><b><?php echo _t('Search Maps');?></b></a><br/><?php echo _t('Search for a map');?></li>
        -->
    </ul>
</div>
<?php
}


