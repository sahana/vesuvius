<?
 # reports.php - Daily reports page.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena
 # Created: 17/01/2005
 # Updated: 17/01/2005

# Dont allow directcall. Uses mambo variable
define ('_VALID_MOS',1); # Please comment this line to if you dont want it to be called directly - i.e. embed as a  module
defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );

// Site configuration
require_once("common/site@config.php");


// Database support
require_once ("$webroot/common/db@connect.php");

$db=0;$xdb=0; #local debug options

# The dynamic content page to include (after $webroot)
$container_template="templates/container.html";
$content_template="templates/reports.html";
$content_page="reports/reports.php";

require_once("$webroot/common/container.php");
?>
