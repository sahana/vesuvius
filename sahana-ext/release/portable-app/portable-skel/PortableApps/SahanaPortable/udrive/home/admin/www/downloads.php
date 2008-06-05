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
include "includes/secure.php";
?>

<div id="main">
	<h2>&#187; <?=$US['down-head']?></h2>
	<h3><?=$US['down-aval']?></h3>
	<p><?=$US['down-text']?></p>
</div>

<?
// Footer
include "includes/footer.php";
?>
