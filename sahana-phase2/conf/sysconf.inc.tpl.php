<?php
/**
* The main Sahana configuration file
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

######################################################################
#                 Sahana Main Configuration Settings                 #
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
$conf['base_uuid'] = "saha";

# Disable the access control system
$conf['acl_base'] = false;

# Root Name :The owner of the machine
$conf['root_name'] = '';

# Root Email :The email address of the admin
$conf['root_email'] = 'root@localhost';

# Root Telephone :The telephone of the admin
$conf['root_tel'] = '';




# specify the host ip address of the database reside.
# if it's the same server that Sahana reside then put 'localhost'
#
$conf['db_host'] = 'localhost';

# port that data base talks. leave blank for default.
#
$conf['db_port'] = '';

# theme that sahana will use todo
#
$conf['theme'] = 'default';

# specify the database name.
#
$conf['db_name'] = 'sahana';

# specify user name that Sahana can use to connect.
#
$conf['db_user'] = 'root';

# And password for that user.
#
$conf['db_pass'] = '';

#debug variable
# true/false
$conf['debug'] = false;

##########################
# Database Configuration #
########################## 

# Configuration Setting Priority
# Select between configuration file or database to load configuration. 
# Unavailable configuration in the selected method will be loaded from other means.
# Values are,   ( file , database )
$conf['sahana_conf_priority'] = 'database';
# Session writer 
# enter your database name here.
#
$conf['session_writer'] = 'database' ; 

# Sahana uses data base abstraction layer for connecting to data base.
# specify the Database Abstraction Layer Library Name here.
# Database Abstraction Layer Libraries are reside in 
# /inc/lib_database/db_libs/
# The name should be same as the library folder
#
$conf['dbal_lib_name'] = 'adodb' ;

# mention the database engine name
# @todo Find supported engine list
# for the moment, Sahana supported and tested on PostgreSQL and MySql
#
# $conf['db_engine'] = 'postgres'; 
$conf['db_engine'] = 'mysql';

#specify the mysql engine to be used
$conf['storage_engine'] = '';

# enable monitor time that takes to process sql queries
# this is an advance feature and recommended only for developers
#
$conf['enable_monitor_sql'] = true;

# @todo Look into the database caching directories etc
# This is a testing feature.
#
$conf['enable_cache'] = false;
$conf['cache_dir'] = 'cache/db_cache';

# Default locale
#
$conf['locale'] = 'en_US';

# Logging Configuration
#
#$conf['default_logger'] = 'DatabaseLogger';
$conf['default_logger'] = 'FileLogger';
#File Logger Specific Configuration.
#Prefix to the log file name
$conf['log_file_name_prefix'] = 'log';
#Log file location relative to approot.
$conf['log_file_location'] = "logs";


###############################
# GIS and Mapping Configuration
###############################
# See gis_conf.inc for more configuration information

# GIS Functionality
# true: to enable GIS/Mapping Capabilities
$conf['gis'] = true;

$conf['proxy_path']='res/lib_proxy.php?url=';

###############################

###############################
#   Help and Wiki Urls        #
###############################
# Default values are given below.
$conf['wiki_url'] = 'http://wiki.sahana.lk/doku.php?id=doc:nwhome';

$conf['sahana_url'] = 'http://sahana.lk';

$conf['forum_url'] = 'http://forum.sahana.lk/';

$conf['chat_url'] = 'http://www.sahana.lk/chat';

$conf['shn_user_feedback_enabled'] = false;


$conf['user_help_server'] = 'localhost';

$conf['use_local_help'] = false;
#####################################
#   Browser Capabilities Settings   #
#####################################
// whether to auto update the browscaps.ini file
$conf['bcaps_auto_update'] = false;



#####################################
#      Miscellaneous Options        #
#####################################

// which wysiwyg you want to use leave blank for default whcih is EXTjs editor
// available options ( 'fckeditor' , 'tiny_mce' )
$conf['wysiwyg']= '';

// this sets the default module of Sahana. when a user first visits the site or logs in/out
// the user will then land on this module (allows home module to be turned off if not needed
// or the emphasis placed on another module)
$conf['default_module']= 'home';

// this sets the default action we will perform on the default module above
$conf['default_action']= 'default';

// always show the incident select box
// true will always show it, and false will have it disappear after the user logs in
$conf['always_show_language'] = true;

# end of the config file.

