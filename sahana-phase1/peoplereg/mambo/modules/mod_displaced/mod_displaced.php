<?php
 # mod_displaced.php - Displaced persons module for mambo.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena
 # Created: 18/01/2005
 # Updated: 21/01/2005
defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );
if($my->username){
 include_once("$mosConfig_absolute_path/../peoplereg/displaced/entry.php");
}else{
 print "Your session has expired! Please login again.";
}
?>
