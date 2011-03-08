#!/opt/php-5.3.1/sapi/cli/php
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

$now = time();
print "Running script at ".strftime('%D %T %n',$now);
$next = $now + 120;
$cmd = 'at -s -f /home/ccornwell/public_html/hepl/mod/mpr/at_job.sh -t ';
$cmd .= strftime('%Y%m%d%H%M',$next);

$return_var = exec($cmd);
print "exec returns: $return_var \n";
