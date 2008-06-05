<?
/*
####################################################
# Name: The Uniform Server Admin Panel 2.0
# Developed By: The Uniform Server Development Team
# Modified Last By: Olajide Olaolorun (empirex) 
# Web: http://www.uniformserver.com
####################################################
*/

$fp=fopen("includes/.lang","w");
fwrite($fp,$_SERVER['QUERY_STRING']);
fclose($fp);
header("Location: index.php");
?>
