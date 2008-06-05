<?
/*
####################################################
# Name: The Uniform Server Admin Panel 2.0
# Developed By: The Uniform Server Development Team
# Modified Last By: Olajide Olaolorun (empirex) 
# Web: http://www.uniformserver.com
####################################################
*/

// Includes
include "includes/config.inc.php";
include "$apanel_path/includes/lang/".file_get_contents("includes/.lang").".php"; 
include "includes/header.php";
?>

<div id="navbar">
	<? include "$apanel_path/includes/basic.inc"; ?>
	<? include "$apanel_path/includes/server.inc"; ?>
	<? include "$apanel_path/includes/config.inc"; ?>
	<? include "$apanel_path/includes/tool.inc"; ?>
	<? include "$apanel_path/includes/plugin.inc"; ?>
	<? include "$apanel_path/includes/python.inc"; ?>
	<? include "$apanel_path/includes/java.inc"; ?>
	<? include "$apanel_path/includes/misc.inc"; ?>
	<? include "$apanel_path/includes/doc.inc"; ?>
	<? include "$apanel_path/includes/lang.inc"; ?>
</div>

</body>
</html>

