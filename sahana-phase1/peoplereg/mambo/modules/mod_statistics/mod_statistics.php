<?php
 # stats.php - Statistics page.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena
 # Created: 01/01/2005
 # Updated: 01/01/2005
defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );

function get_page($pageurl){
 $page = file($pageurl);
 $page = implode('',$page);
 return $page;
}

 //include_once("$mosConfig_absolute_path/modules/stats/stats.php");
 $cont=get_page ("http://chalana:moving@localhost/mambo/sahana/stats.php?attribute=$_REQUEST[attribute]");
 print $cont;
?>
