<?php

/**
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* Sahana - http://sahana.sourceforge.net
* 
* @author   	Mifan Careem <mifan@respere.com>
* @copyright  	Respere - http://respere.com/
* @version 		$Id: conf.inc,v 1.3 2009-08-22 17:17:27 ravithb Exp $
* @package 		Sahana - http://sahana.lk/
* @subpackage 	messaging   
* @plugin		SMSTools - http://smstools.meinemullemaus.de/
* @license   	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

// provide the nice display name for the GIS Plugin module
$conf['plugin_name'] = _t('SMSTools');

// Path of the Outgoing Queue folder.
$conf['msg_outgoing'] = '/var/spool/sms/outgoing';

# Path of the default Queue directory in case you do not use provider-sorting.
$conf['msg_checked'] = '/var/spool/sms/checked';

# Path of the Failed Folder. Delete this line if you do not want to keep failed files.
$conf['msg_failed'] = '/var/spool/sms/failed';

# Path of the Incoming Folder.
$conf['msg_incoming'] = '/var/spool/sms/incoming';

# Path of the Sent Folder. Delete this line, if you do not want to keep copies of each sent message file.
$conf['msg_sent'] = '/var/spool/sms/sent';

# Specifies the directory where you installed the SMS Server Tools binaries. Default is /usr/local/bin.
$conf['msg_mypath'] = '/usr/bin';

# Name of the log file. Delete this line, if you want to use the syslog for logging. You can use "1" to write to the console (stdout).
$conf['msg_logfile'] = '/var/log/smsd.log';

