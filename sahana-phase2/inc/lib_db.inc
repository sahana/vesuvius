<?php 
/* $Id: lib_db.inc,v 1.2 2005-09-29 12:22:25 janakawicks Exp $ */

/**
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Janaka Wickramasinghe <janaka@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

//Include the ADOdb Library
require_once($global['approot'].'3rd/adodb/adodb.inc.php');

//Make the connection to $global['db']
$global['db'] = NewADOConnection($conf['db_engine']);
$global['db']->Connect($conf['db_host'].($conf['db_port']?':'.$conf['db_por
t']:''),$conf['db_user'],$conf['db_pass'],$conf['db_name']);
//Error handle baby!!!

//enable logging sql
if($conf['enable_monitor_sql'])
    $global['db']->LogSQL();
?>
