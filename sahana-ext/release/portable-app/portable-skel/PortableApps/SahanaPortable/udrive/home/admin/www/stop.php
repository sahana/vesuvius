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
	<h2>&#187; <?=$US['stop-head']?></h2>
	<h3><?=$US['stop-shut']?></h3>
	<p>
	<?=$US['stop-killing']?>
	<br />
	<br />
	<a href="<?=$apanel?>/cgi-bin/includes/lang/<?=file_get_contents("includes/.lang");?>/sserver.cgi"><h2><?=$US['stop-stop']?></h2></a>
	</p>
</div>

<?
// Footer
include "includes/footer.php";
?>

