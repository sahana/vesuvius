<?php
/**
 * @name         Main Sahana Configuration File
 * @version      1.0
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0125
 */


# Unique identifier for all resources contained in the system ~ must be unique and 4 or more alphanumberic characters
$conf['base_uuid'] = 'pl.nlm.nih.gov/';

# ACL ~ Access Control List
$conf['acl_base'] = false; // disable ACL?
$conf['acl_enabled'] = true;
$conf['acl_locking'] = true;
$conf['acl_signup_enabled'] = true;



# specify the host ip address of the database reside.
# if it's the same server that Sahana reside then put 'localhost'
#
$conf['db_host'] = 'localhost';

# port that data base talks. leave blank for default.
#
$conf['db_port'] = '3306';

# theme that sahana will use todo
#
$conf['theme'] = 'lpf3';

# specify the database name.
#
$conf['db_name'] = '';

# specify user name that Sahana can use to connect.
#
$conf['db_user'] = '';

# And password for that user.
#
$conf['db_pass'] = '';

#debug variable
# true/false
$conf['debug'] = false;

##########################
# Database Configuration #
##########################

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
$conf['enable_monitor_sql'] = 'false';

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
#$conf['gis'] = true;
#$conf['proxy_path']='res/lib_proxy.php?url=';

#####################################
#   Browser Capabilities Settings   #
#####################################
// whether to auto update the browscaps.ini file
$conf['bcaps_auto_update'] = false;

#####################################
# PASSWORD RULES ####################
#####################################

$conf['pwd_min_chars']       = 6;
$conf['pwd_max_chars']       = 24;
#$conf['pwd_has_uppercase']   = true;
#$conf['pwd_has_numbers']     = true;
#$conf['pwd_has_spchars']     = true;
$conf['pwd_has_username']    = true;
#$conf['pwd_has_reppatterns'] = true;
$conf['pwd_no_change_limit'] = true;



#####################################
#      Miscellaneous Options        #
#####################################

// which wysiwyg you want to use leave blank for default whcih is EXTjs editor
// available options ( 'fckeditor' , 'tiny_mce' )
//$conf['wysiwyg']= 'tiny_mce';

// this sets the default module of Sahana. when a user first visits the site or logs in/out
// the user will then land on this module (allows home module to be turned off if not needed
// or the emphasis placed on another module)
$conf['default_module']= 'rez';

// this sets the default action we will perform on the default module above
$conf['default_action']= 'landing';

// always show the incident select box
// true will always show it, and false will have it disappear after the user logs in
$conf['always_show_language'] = true;

# end of the config file.
