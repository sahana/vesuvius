<?php
 # container.php - The main container for the leftbar,rightbar, bottom links and content area.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena [Bud@babytux.org]
 # Created: 31/12/2004
 # Updated: 31/12/2004
 
// Site configuration
$webroot = '/var/www/mambo/sahana';

$topbar_template="$webroot/templates/topbar.html";
$footer_template="$webroot/templates/footer.html";

// Database support
#require_once ("$webroot/common/db@connect.php");

$db=0;$xdb=0; #local debug options

$container_page=get_page($container_template);

# Split about TAGS and require other includes in between
$container_page=preg_replace("/{TOPIMAGE}/",$topimg,$container_page);

list($top,$bottom)=preg_split("/{TOPBAR}/",$container_page);
print $top; $container_page=$bottom;

list($top,$bottom)=preg_split("/{CONTENT_PAGE}/",$container_page);
print $top; include($content_page);$container_page=$bottom;

list($top,$bottom)=preg_split("/{FOOTER}/",'');
print $top; ;$container_page=$bottom;

# Replace all instances of {DOCROOT} with the actual $docroot
$container_page=preg_replace("/{DOCROOT}/",$docroot,$container_page);

print $container_page;
?>
