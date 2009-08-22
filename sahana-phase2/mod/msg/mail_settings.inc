<?php
/**
* The Sahana Messaging Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Sriganeshan <sri@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	msg
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/


global $global;
require_once $global['approot']."/inc/handler_db.inc";

function shn_update_mail_configuration()
{
       global $sit;
 
        $mod='msg';
        $server='server';
        $usrname='username';
        $password='password';
        $from_id='from_id';
        $from_name='from_name';
                
        $sit['smtp_host']=shn_db_get_config($mod,$server);
	$sit['smtp_username']=shn_db_get_config($mod,$usrname);
	$sit['smtp_password']=shn_db_get_config($mod,$password);
	$sit['from_name']=shn_db_get_config($mod,$from_name);
	$sit['from_email']=shn_db_get_config($mod,$from_id);
	$sit['smtp_port'] = 25;
	$sit['smtp_mode'] = enabled;

}

 //shn_update_mail_configuration();
