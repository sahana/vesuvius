<?php

/**
* Main Layer Interface
* 
* To implement layers, implement this interface
* and place the class file within the layers folder:
* /inc/lib_gis/layers/...
* NOTE: The name of the layer include file should match the classname of the relevant file
* e.g: googlemaps.inc contains class googlemaps
* 
*
* PHP version 5
* 
* @author       Mifan Careem <mifan@respere.com>
* @author       Fran Boon <flavour@partyvibe.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package      Sahana - http://sahana.lk/
* @library      GIS
* @version		$Id: layer_class.inc,v 1.5 2009-08-22 17:17:25 ravithb Exp $;
* @license      http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

/**
 * Implement this interface to implement newer OpenLayers Layers...
 */
interface layer {

    /**
     * Print form elements for the admin interface within formsets
     * Each formset is displayed within tabs
     */
    public function print_form();

    /**
     * Commit values to the database
     */
    public function commit_values();

}


