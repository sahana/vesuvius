<?php
/**
 * 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage sync
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

global $global;
ob_start();
/* check if incident differ */

//get the disasters which are not in the incident table
    $imdist=$global['db']->GetAll('SELECT name FROM tmp_incident WHERE parent_id IS NULL AND name NOT IN (SELECT name FROM incident WHERE parent_id IS NULL)');
    foreach($imdist as $dist){
        import_disaster($dist);
    }
//import them one by one

//get the disasters 
function import_disaster($id){
    //go level by level and add the disaster
}
//construct the xajax responce
$console = ob_get_contents();
if(isset($console))
$global['xajax']->addAssign("console","innerHTML", $console);
ob_end_clean();

header("Cache-Control: no-cache, must-revalidate");
header("Pragma: no-cache");
header("Content-type: text/xml");
echo ($global['xajax']->getXML());
$_SESSION['report']=serialize($_SESSION['report']);
exit(0);
?>