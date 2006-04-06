<?php
/**
 * Search Category  
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage cs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
include_once('add.inc');

function shn_cs_edit_form()
{

$id = trim($_REQUEST['id']);

global $global;
$db=$global["db"];

$query="select name,parentid,description from ct_catalogue where ct_uuid='$id' ";
$res=$db->Execute($query);

$parentid=$res->fields["parentid"];
$name=$res->fields["name"];
$description=$res->fields["description"];

shn_cs_addmain_form('edit_form_submit',$name,$description);

}


?>