<?
 # stats.php - Main Statistics page.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena
 # Created: 31/12/2004
 # Updated: 05/01/2005

// Site configuration
require_once("common/site@config.php");


// Database support
require_once ("$webroot/common/db@connect.php");

$db=0;$xdb=0; #local debug options

# The dynamic content page to include (after $webroot)
$container_template="templates/container.html";
$content_template="templates/stats.html";
$content_page="stats/stats.php";

require_once("$webroot/common/container.php");
?>
