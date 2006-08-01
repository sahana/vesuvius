<?php
/**
 * This handler will stream the data file
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

include_once('lib_sync_file.inc');
include_once('lib_dump_data.inc');

//print_r($_POST);
//get a list of avlable module items with sync.xml file
$tables=array();
$modules=shn_get_module_names();
    //loop through all the modules to find sync.xml
foreach($modules as $key=>$module){
    if (!file_exists($syncfile=$global['approot']."mod/".$module."/sync.xml"))
    unset($modules[$key]);
}
//process the selected module files
if(isset($_POST['modules']))
{
    foreach($_POST['modules'] as $key=>$module)
    {
        $tables=_shn_sync_file_tables($module,$tables);
        //remove those items from module array
        $modules=remove_module($modules,$module);
    }
}

//go through the unselected module items
foreach($modules as $module)
{
    //print_r($_POST[$module]);
    if(isset($_POST[$module]))
    {
        $tables=_shn_sync_data_tables($module,$_POST[$module],$tables);
    }
}

//process the sub sections of the modules


//include the sync file

//create the xml object

//switch for file types

switch ($_POST['file_type']){
    case 'xml':
        //creating headers
        header("Content-type: text/xml");
        header("Content-Disposition: attachment; filename=sahana_data_dump_".time().".xml");
        header("Cache-Control: no-cache, must-revalidate");
        //dump the data in the tables
        _shn_sync_dump_xml($tables);
        exit();
    case 'csv':
        echo "csv";
        exit();
    case 'sql':
        echo "sql";
        exit();
    case 'sqlite':
        echo "sqlite";
        exit();
}

function remove_module($modules,$module)
{
    foreach($modules as $key=>$mod)
    {
        if($mod==$module)unset($modules[$key]);
    }
    return $modules;
}
?>