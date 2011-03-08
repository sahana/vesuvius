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
# NOTE: This is a temporary file to be replaced by entriesin the MPR module configuration table.
######################################################################
#
$pfif_conf = array(); // declare

$pfif_conf['source_url_domain'] = '.nlm.nih.gov'; // append to disaster id to yield PFIF source_url
$pfif_conf['pfif_domain'] = 'pl.nlm.nih.gov'; // TODO: get from sysconf

// TEMPORARY: Maps services to Sahana indicents - should be added to pfif_repository table
$pfif_conf['service_to_incident'] =
        array('googlehaiti' => array('incident_id'=>8,
                                     'db_host'=>'localhost', // archivestage.nlm.nih.gov',
                                     'db_name'=>'sahanaCarl',
                                     'disaster_id' => 'hepl'),
              'googlechile' => array('incident_id'=>9,
                                     'db_host'=>'localhost', // 'archivestage.nlm.nih.gov',
                                     'db_name'=>'sahanaCarl',
                                     'disaster_id' => 'cepl'),
              'googlechina' => array('incident_id'=>10,
                                     'db_host'=>'localhost', // 'archivestage.nlm.nih.gov',
                                     'db_name'=>'sahanaCarl',
                                     'disaster_id' => 'chepl'),
              'googlepakistan' => array('incident_id'=>11,
                                     'db_host'=>'localhost', // 'archivestage.nlm.nih.gov',
                                     'db_name'=>'sahanaCarl',
                                     'disaster_id' => 'pfpl'));

$pfif_conf['services'] = array(); // chc 4/7/2010 : Initilialized from pfif_repository table via pfif_init.inc
/*
    'google' =>
    array('read_url' => 'http://haiticrisis.appspot.com/api/read',
          'feed_url' => 'http://haiticrisis.appspot.com/feeds',
          'post_url' => 'http://haiticrisis.appspot.com/api/write',
          'auth_key' => 'fn74g09chf6asa2m'),
    'google_chile' =>
    array('read_url' => 'http://chilepersonfinder.appspot.com/api/read',
          'feed_url' => 'http://chilepersonfinder.appspot.com/feeds',
          'post_url' => 'http://chilepersonfinder.appspot.com/api/write',
          'auth_key' => '0xf28nsvSVho6L3h')
          );
*/
