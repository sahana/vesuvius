<?php
/**
* The ancillary Sahana configuration file for PFIF related constants
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author ccornwell, contractor, NLM-CEB, ccornwell@mail.nih.gov
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

######################################################################
#                 Sahana MPR PFIF Configuration Settings                 #
# NOTE: This is a temporary file to be replaced by entriesin the MPR module configuration table.
######################################################################
#
$pfif_conf = array(); // declare
$pfif_conf['local_domain'] = 'pl.nlm.nih.gov';
$pfif_conf['services'] = array('google' => 
    array('read_url' => 'http://haiticrisis.appspot.com/api/read',
          'post_url' => 'http://haiticrisis.appspot.com/api/write',
          'auth_key' => 'fn74g09chf6asa2m'));

