<?php
/**
* The main Sahana configuration file
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

