<?php
 # stats.php - Statistics page.
 # Copyright : Virtusa Corporation
 # License : GPL
 # Author : Buddhika Siddhisena
 # Created: 01/01/2005
 # Updated: 13/01/2005
defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );

include_once("$mosConfig_absolute_path/acl/inc_acl.php");

function get_page($pageurl){
 $page = file($pageurl);
 $page = implode('',$page);
 return $page;
}
 //include_once("$mosConfig_absolute_path/modules/stats/stats.php");
 $cont=get_page ("http://localhost/mambo/sahana/stats.php?attribute=$_REQUEST[attribute]&graph_type=$_REQUEST[graph_type]&disp_unknown=$_REQUEST[disp_unknown]");
 
 if(checkacl($my->username,"People Registry","VIEW")){
  print $cont;
 }
?>
