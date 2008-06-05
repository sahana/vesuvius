<?
/*
####################################################
# Name: The Uniform Server Setup
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


if ( !(file_exists($aphtpasswd)) ) {
	$FHandle = fopen($aphtpasswd, 'w');
	fclose($FHandle);
}


if ($_POST['submit']) {

	$nwuser = $_POST['apuser'];
	$nwpass = $_POST['appass'];

	$urdata = "$nwuser:$nwpass";

	$wfile = fopen($aphtpasswd, 'w') ;
	fwrite($wfile, $urdata);
	fclose($wfile);
?>

	<div id="main">
	<h2>&#187; <?=$US['apsetup-head']?></h2>
	<h3><?=$US['apsetup-sub-0']?></h3>
	<p>
	<?=$US['apsetup-success']?>
	<br />
	<br />
	<?=$US['apsetup-user']?>: <?=$_POST['apuser'];?>
	<br />
	<?=$US['apsetup-pass']?>: <?=$_POST['appass'];?>
	</p>
	</div>

<?
}

else {
	$tfile = fopen($aphtpasswd, "r");

	$fcontents = fgets($tfile);
	$ucontents = explode(":", $fcontents);
?>

	<div id="main">
		<h2>&#187; <?=$US['apsetup-head']?></h2>
		<h3><?=$US['apsetup-sub-0']?></h3>

		<p><?=$US['apsetup-text-0']?></p>
		<form action="<?=$PHP_SELF?>" method="post">
		<table width="100%">
		<tr>
		<td width="80">
		<p><?=$US['apsetup-user']?></p>
		</td>
		<td>
		<input type="text" name="apuser" value="<?=$ucontents[0]?>" />
		</td>
		</tr>
		<tr>
		<td width="80">
		<p><?=$US['apsetup-pass']?></p>
		</td>
		<td>
		<input type="text" name="appass" value="<?=$ucontents[1]?>" />
		</td>
		</tr>
		</table>
		<br />
		<input type="submit" name="submit" value="<?=$US['apsetup-change']?>" />
		</form>
	</div>

<?
	fclose($tfile);
}

// Footer
include "includes/footer.php";
?>