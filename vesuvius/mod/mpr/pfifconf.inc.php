<?php
/**
 * @name         Missing Person Registry
 * @version      1.5
 * @package      mpr
 * @author       Carl H. Cornwell <ccornwell at aqulient dor com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0307
 */


######################################################################
#                 Sahana MPR PFIF Configuration Settings                 #
# NOTE: This is a temporary file to be replaced by entries in the MPR module configuration table.
######################################################################
#
$pfif_conf = array(); // declare

//$pfif_conf['source_url_domain'] = '.nlm.nih.gov'; // append to disaster id to yield PFIF source_url
//$pfif_conf['pfif_domain'] = 'pl.nlm.nih.gov'; // TODO: get from sysconf

// TEMPORARY: Maps services to Sahana incidents - should be added to pfif_repository table
$pfif_conf['service_to_incident'] =
        array('googlechristchurch' => array('incident_id'=>8),
        'googlejapan' => array('incident_id'=>9),
        'googleiscram2011' => array('incident_id'=>27),
        'googletest' => array('incident_id'=>27));

$pfif_conf['services'] = array(); // chc 4/7/2010 : Initilialized from pfif_repository table via pfif_croninit.inc
