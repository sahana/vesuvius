<?php
/**
 * @name         Person Finder Interchange Format
 * @version      2
 * @package      pfif
 * @author       Carl H. Cornwell <ccornwell at aqulient dor com>
 * @author       Leif Neve <lneve@mail.nih.gov>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0223
 */


$pfif_conf['services'] = array();

// TODO: These methods are Google-specific. They should be generalized as needed.
function add_pfif_service($repository) {
   global $pfif_conf;

   $service_name = $repository->name;
   // Stash repository here for getting at harvest log, etc.
   $pfif_conf['services'][$service_name]['repository'] = $repository;
   // TODO: Move to repository table.
   $pfif_conf['services'][$service_name]['version'] = '1.3';
   $pfif_conf['services'][$service_name]['auth_key'] = $repository->auth_key;
   $pfif_conf['services'][$service_name]['incident_id'] = $repository->incident_id;
   // The NLM PF uses this parameter to specify the disaster.
   $pfif_conf['services'][$service_name]['subdomain'] = $repository->subdomain;
   if ($repository->role == 'source') {
       $pfif_conf['services'][$service_name]['feed_url'] = $repository->base_url.'/feeds/'.$repository->resource_type;
       $pfif_conf['services'][$service_name]['read_url'] = $repository->base_url.'/api/read';
       $pfif_conf['services'][$service_name]['max_results'] = '200';
   } else if ($repository->role == 'sink') {
       // TODO: Change this to req_url.
       $pfif_conf['services'][$service_name]['post_url'] = $repository->base_url.'/api/write';
   } else {
       // ERROR: invalid role
   }
}
