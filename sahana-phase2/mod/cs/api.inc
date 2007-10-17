<?php
/**
 * api.inc 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author       Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @author     Ishan Liyanage <ishanul@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage cs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */


/**.
 *This function return all the unit names
 * @access public
 * @return array
 */
function shn_cs_get_all_unit_names()
{
	global $global;
    $db = $global["db"];
    $query = "SELECT name FROM ct_unit";
    $res = $db->Execute($query);
    $unit_name_arr = array();

    while(!$res == NULL && !$res->EOF) {
    	array_push($unit_name_arr,$res->fields['name']);
    	$res->MoveNext();
    }
    
    return $unit_name_arr;
}

/**.
 *This function return all the catalog names
 * @access public
 * @return array
 */
function shn_cs_get_all_catalog_names()
{
    global $global;
    $db = $global["db"];
    $query = "SELECT ct_uuid,parentid,name FROM ct_catalogue";
    $res = $db->Execute($query);
    $catalog_list = array();

    while(!$res == NULL && !$res->EOF) {
    	$catalog_list[] = array('ct_id' => $res->fields["ct_uuid"], 'parent_id' => $res->fields["parentid"], 'name' => $res->fields["name"]);
    	$res->MoveNext();
    }
    
    return $catalog_list;
}

/**.
 *This function return the catalog names without defaults names
 * @access public
 * @return array
 */
function shn_cs_get_catalog_names()
{
    global $global;
    $db = $global["db"];
    $query = "SELECT ct_uuid,parentid,name FROM ct_catalogue WHERE ct_uuid NOT LIKE '%default%'";
    $res = $db->Execute($query);
    $catalog_list = array();

    while(!$res == NULL && !$res->EOF) {
    	$catalog_list[] = array('ct_id' => $res->fields["ct_uuid"], 'parent_id' => $res->fields["parentid"], 'name' => $res->fields["name"]);
    	$res->MoveNext();
    }
    
    return $catalog_list;
}
?>