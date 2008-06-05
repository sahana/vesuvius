<?php
/* $Id: show_config_errors.php,v 1.1 2008-06-05 12:28:36 chamindra Exp $ */
// vim: expandtab sw=4 ts=4 sts=4:

/* Simple wrapper just to enable error reporting and include config */

echo "Starting to parse config file...\n";

error_reporting(E_ALL);
require('./config.inc.php');

?>
