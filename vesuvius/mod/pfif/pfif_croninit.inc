<?php
/**
* Initialization script for scheduled PFIF import/export services
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author ccornwell, contractor, NLM-CEB, ccornwell@mail.nih.gov
* @author lneve, contractor, NLM-CEB, lneve@mail.nih.gov
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

$pfif_conf['services'] = array();

// TODO: These methods are Google-specific. They should be generalized as needed.
function add_pfif_service($repository) {
   global $pfif_conf;

   $service_name = $repository->name;
   $pfif_conf['map'][$service_name] = $repository->id;
   $pfif_conf['service_to_incident'][$service_name] = $repository->incident_id;

   $pfif_conf['services'][$service_name]['version'] = '1.3';
   $pfif_conf['services'][$service_name]['auth_key'] = $repository->auth_key;
   // The NLM PF uses this parameter to specify the disaster.
   $pfif_conf['services'][$service_name]['subdomain'] = $repository->subdomain;
   if ($repository->role == 'source') {
       $pfif_conf['services'][$service_name]['feed_url'] = $repository->base_url.'/feeds/'.$repository->resource_type;
       $pfif_conf['services'][$service_name]['max_results'] = '200';
   } else if ($repository->role == 'sink') {
       // TODO: Change this to req_url.
       $pfif_conf['services'][$service_name]['post_url'] = $repository->base_url.'api/write';
   } else {
       // ERROR: invalid role
   }
}
