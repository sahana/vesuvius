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
# This file specifies how the configuration works
# The default config evaluation order is. This means the latter one gets
# priority as it is evaluated (and overrides) the prior
#   3) /conf/sysconf.inc    = 'system'
#   2) module conf.inc      = 'module' 
#   1) database             = 'database'

# the order in which config values get loaded. 
# The last has the highest priority. You can omit certain config files 
# through this scheme to, but be careful that all values are covered
$conf['sahana_conf_order'] = array ('system','module','database')  ;

