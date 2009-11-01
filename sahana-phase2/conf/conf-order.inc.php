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
* @author     http://www.linux.lk/~chamindra
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

######################################################################
#                 Sahana Configuration Priority Setting              #
######################################################################
# Give database priority for a homogenous clustered deployment
# Give files priority for a hetrogenous setup with a shared database 

# Which will override the database conf values or the conf files 
# To give the database conf priority value = 'database' 
# To give conf files priority value = 'files' 
$conf['sahana_conf_priority'] = 'database';

