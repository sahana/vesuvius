<?php
 # mod_displaced.php - Displaced persons module for mambo.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena
 # Created: 18/01/2005
 # Updated: 18/01/2005
defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );
include_once("$mosConfig_absolute_path/acl/inc_acl.php");
if(checkacl($my->username,"People Registry","ADD")){
 include_once("$mosConfig_absolute_path/../peoplereg/displaced/entry.php");
}
?>
