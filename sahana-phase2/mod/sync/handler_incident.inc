<?php
/**
 * This handler will import incidents from the import daya
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

//check weather there is an incident table in import data
if(array_search('incident', $_SESSION['sync']['tables'])===false)return 0;

/* check if incident differ */
//get the disasters which are not in the incident table
echo "<pre>";
    $list=array(array('',''));
    while(count($list)>0){
        $dist=array_pop($list);
        $dist[1]=($dist[1]=='')?'IS NULL':' = '.$dist[1];
        echo $sql="SELECT name, incident_id, parent_id  FROM tmp_incident WHERE parent_id {$dist[1]} AND name NOT IN (SELECT name FROM incident WHERE parent_id {$dist[1]} )\n";
        $imdist=$global['db']->GetAll($sql);
        echo $sql="SELECT a.incident_id , b.incident_id FROM tmp_incident AS a JOIN incident AS b ON a.name = b.name AND a.parent_id {$dist[1]};\n";
        $chdist=$global['db']->GetAll($sql);
        print_r($imdist);
        print_r($chdist);
        import_disaster($imdist);
        change_resource($chdist);
        $list = array_merge($list, $chdist);
    }

//remove the incident table from the table list
$tables= &$_SESSION['sync']['tables'];
$key = array_search('incident', $tables);
unset($tables[$key]);

//import them one by one
function change_resource($list){
    global $global;
    while(count($list)>0){
        $dist=array_pop($list);
        if($dist[1]==$dist[0])continue;
        echo $sql="UPDATE tmp_resource_to_incident SET incident_id = {$dist[1]} WHERE incident_id={$dist[0]}\n";
        $global['db']->Execute($sql);
        //update clild id
        echo $sql="UPDATE tmp_incident SET parent_id = {$dist[1]} WHERE parent_id = {$dist[0]}\n";
        $global['db']->Execute($sql);
    }
}
//get the disasters 
function import_disaster($list){
    global $global;
    while(count($list)>0){
        $dist=array_pop($list);
        //add the disaster to the incident table
        $dist['parent_id']=($dist['parent_id']=='')?'NULL':$dist['parent_id'];
        $sql = "INSERT INTO incident (name,parent_id) VALUES ('{$dist['name']}',{$dist['parent_id']})";
        $global['db']->Execute($sql);
        //get the new id of it
        $newid = $global['db']->insert_id();
        //change the parent_id of child incidents
        $sql="UPDATE tmp_incident SET parent_id = $newid WHERE parent_id = {$dist['incident_id']}";
        $global['db']->Execute($sql);
        //change the import resource_to_incident idvalues
        $sql="UPDATE tmp_resource_to_incident SET incident_id = $newid WHERE incident_id={$dist['incident_id']}";
        $global['db']->Execute($sql);
        //get the child elements and do the same
        $children=$global['db']->GetAll("SELECT name, incident_id, parent_id  FROM tmp_incident WHERE parent_id = $newid");
        $list = array_merge($list, $children);
    }
}
//construct the xajax responce
$console = ob_get_contents();
if(isset($console))
$global['xajax']->addAssign("console","innerHTML", $console);
ob_end_clean();
/*
header("Cache-Control: no-cache, must-revalidate");
header("Pragma: no-cache");
header("Content-type: text/xml");
echo ($global['xajax']->getXML());
$_SESSION['report']=serialize($_SESSION['report']);
exit(0);*/
