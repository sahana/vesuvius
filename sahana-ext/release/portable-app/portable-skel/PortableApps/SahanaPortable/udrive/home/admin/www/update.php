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
<h2>&#187; <?=$US['update-head']?></h2>
<h3><?=$US['update-check']?></h3>
<p>
<?
//-------------------------------------------------------------------- 

$available = file ('http://www.uniformserver.com/system/.version');
//$available = file ('includes/.version');
$my = file ('includes/.version');

//--------------------------------------------------------------------
if (rtrim($my[0]) == rtrim($available[0])) {
?>
	<?=$US['update-true']?>
<?
}

else{
?>
	<?=$US['update-false']?>
	<br />
	<br />
<?
      echo "". $US['update-new'] .": $available[0]";
	echo "<br />";
      echo "". $US['update-yours'] .": $my[0]";
	echo "<br /><br />";
?>
	<?=$US['update-get']?>
	<br />
	<a href="http://www.uniformserver.com/" target="_blank"><h2><?=$US['nav-web']?></h2></a>
<?
}
?>
</p>
</div>

<?
// Footer
include "includes/footer.php";
?>