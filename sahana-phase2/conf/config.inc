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
# or join with our irc channel #sahana-dev at freenode.org, 

# specify the host ip address of the database reside.
# if it's the same server that Sahana reside then put 'localhost'
$conf['db_host'] = '192.168.101.38';

# port that data base talks. leave blank for default.
$conf['db_port'] = '';

# theme that sahana will use todo
$conf['theme'] = 'default' ; 

# specify the database name.
$conf['db_name'] = 'sahana';

# specify user name that Sahana can use to connect.
$conf['db_user'] = 'sahana';

# And password for that user.
$conf['db_pass'] = '';

# specify a Log Level.
# 0 - no logging at all.
# 1 - basic logging.
# 2 - Security level logging.
# 3 - Debug level logging (not yet implemented).
#
# Default is 1
#
$conf['loglevel'] = 1;




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

# enable monitor time that takes to process sql queries
# this is an advance feature and recommended only for developers
$conf['enable_monitor_sql'] = 'true';

# @todo Look into the database caching directories etc
# This is a testing feature.
#
$conf['enable_cache'] = false;
$conf['cache_dir'] = 'cache/db_cache';

# end of the config file.
?>
