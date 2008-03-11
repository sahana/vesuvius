<?php
/**
* The main Sahana configuration meta data file
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravith Botejue <ravithb@yahoo.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

######################################################################
#                 Sahana Main Configuration Settings Meta data                #
######################################################################
#
#
# Welcome to Sahana the disaster management system.
# feel free to edit this config file.
# if you have problem please visit http://sahana.sourceforge.org/
# or join with our irc channel #sahana at freenode.org, 

# Specify the name of this Sahana instance. This should be a unique identifier
# of this instance of Sahana. 
# It has to be a 4 character alphanumeric 
$conf_meta['base_uuid'] = array('type'=>'string','size'=>-1,'allow_null'=>true,'default_value'=>'saha');

# Disable the access control system
$conf_meta['acl_base'] = array('type'=>'boolean','default_value'=>false);

# Root Name :The owner of the machine
$conf_meta['root_name'] = array('type'=>'string','size'=>-1,'allow_null'=>true,'default_value'=>'');

# Root Email :The email address of the admin
$conf_meta['root_email'] = array('type'=>'email','allow_null'=>true,'default_value'=>'root@localhost');

# Root Telephone :The telephone of the admin
$conf_meta['root_tel'] = array('type'=>'string','size'=>-1,'allow_null'=>true,'default_value'=>'');


# specify the host ip address of the database reside.
# if it's the same server that Sahana reside then put 'localhost'
#
$conf_meta['db_host'] = array('type'=>'string','size'=>-1,'allow_null'=>false,'default_value'=>'localhost');

# port that data base talks. leave blank for default.
#
$conf_meta['db_port'] = array('type'=>'integer','min_value'=>1024,'max_value'=>65535,'allow_null'=>false,'default_value'=>'3306');

# theme that sahana will use todo
#
$conf_meta['theme'] = array('type'=>'string','size'=>-1,'allow_null'=>false,'default_value'=>'default');

# specify the database name.
#
$conf_meta['db_name'] = array('type'=>'string','size'=>-1,'allow_null'=>false,'default_value'=>'sahana');

# specify user name that Sahana can use to connect.
#
$conf_meta['db_user'] = array('type'=>'string','size'=>-1,'allow_null'=>false,'default_value'=>'root');

# And password for that user.
#
$conf_meta['db_pass'] = array('type'=>'password','min_size'=>0,'max_size'=>0,'allow_null'=>true,'default_value'=>'');

#debug variable
# true/false
$conf_meta['debug'] = array('type'=>'boolean','default_value'=>false);

##########################
# Database Configuration #
########################## 

# Session writer 
# enter your database name here.
#
$conf_meta['session_writer'] = 'database' ; 

# Sahana uses data base abstraction layer for connecting to data base.
# specify the Database Abstraction Layer Library Name here.
# Database Abstraction Layer Libraries are reside in 
# /inc/lib_database/db_libs/
# The name should be same as the library folder
#
$conf_meta['dbal_lib_name'] = array('type'=>'string','size'=>-1,'allow_null'=>false,'default_value'=>'adodb');

# mention the database engine name
# @todo Find supported engine list
# for the moment, Sahana supported and tested on PostgreSQL and MySql
#
# $conf_meta['db_engine'] = 'postgres'; 
$conf_meta['db_engine'] = array('type'=>'string','size'=>-1,'allow_null'=>false,'default_value'=>'mysql');

#specify the mysql engine to be used
$conf_meta['storage_engine'] = array('type'=>'string','size'=>-1,'allow_null'=>false,'default_value'=>'mysql');

# enable monitor time that takes to process sql queries
# this is an advance feature and recommended only for developers
#
$conf_meta['enable_monitor_sql'] = array('type'=>'boolean','default_value'=>true);

# @todo Look into the database caching directories etc
# This is a testing feature.
#
$conf_meta['enable_cache'] = array('type'=>'boolean','default_value'=>false);
$conf_meta['cache_dir'] = array('type'=>'string','size'=>-1,'allow_null'=>false,'default_value'=>'cache/db_cache');

# Default locale
#
$conf_meta['locale'] = array('type'=>'string','size'=>-1,'allow_null'=>false,'default_value'=>'en_US');

# Logging Configuration
#
#$conf_meta['default_logger'] = 'DatabaseLogger';
$conf_meta['default_logger'] = 'FileLogger';
#File Logger Specific Configuration.
#Prefix to the log file name
$conf_meta['log_file_name_prefix'] = array('type'=>'string','size'=>-1,'allow_null'=>false,'default_value'=>'log');
#Log file location relative to approot.
$conf_meta['log_file_location'] = array('type'=>'string','size'=>-1,'allow_null'=>false,'default_value'=>'logs');


###############################
# GIS and Mapping Configuration
###############################
# @todo Provide Web Interface for cofiguration
# See GIS Module for more configuration information

# GIS Funcitionality
# true: to enable GIS/Mapping Capabilities

$conf_meta['gis'] = array('type'=>'boolean','default_value'=>true);

$conf_meta['proxy_path']= array('type'=>'string','size'=>-1,'allow_null'=>false,'default_value'=>'res/lib_proxy.php?url=');

###############################

###############################
#	Help and Wiki Urls		  #
###############################
# Default values are given below.
$conf_meta['wiki_url'] = 'http://wiki.sahana.lk/doku.php?id=doc:nwhome';

$conf_meta['sahana_url'] = 'http://sahana.lk';

$conf_meta['forum_url'] = 'http://forum.sahana.lk/';

$conf_meta['chat_url'] = 'http://www.sahana.lk/chat';

$conf_meta['shn_user_feedback_enabled'] = array('type'=>'boolean','default_value'=>false);

$conf_meta['user_help_server'] = null;

# end of the config file.

