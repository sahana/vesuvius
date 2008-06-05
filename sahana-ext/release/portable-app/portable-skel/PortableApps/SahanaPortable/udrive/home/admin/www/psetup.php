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


if ( !(file_exists($whtpasswd)) ) {
	$FHandle = fopen($whtpasswd, 'w');
	fclose($FHandle);
}


if ($_POST['submit']) {

	$nwuser = $_POST['puser'];
	$nwpass = $_POST['ppass'];

	$urdata = "$nwuser:$nwpass";

	$wfile = fopen($whtpasswd, 'w') ;
	fwrite($wfile, $urdata);
	fclose($wfile);
?>

	<div id="main">
	<h2>&#187; <?=$US['psetup-head']?></h2>
	<h3><?=$US['psetup-sub-0']?></h3>
	<p>
	<?=$US['psetup-success']?>
	<br />
	<br />
	<?=$US['psetup-user']?>: <?=$_POST['puser'];?>
	<br />
	<?=$US['psetup-pass']?>: <?=$_POST['ppass'];?>
	</p>
	</div>

<?
}

else {
	$tfile = fopen($whtpasswd, "r");

	$fcontents = fgets($tfile);
	$ucontents = explode(":", $fcontents);
?>

	<div id="main">
		<h2>&#187; <?=$US['psetup-head']?></h2>
		<h3><?=$US['psetup-sub-0']?></h3>

		<p><?=$US['psetup-text-0']?></p>
		<form action="<?=$PHP_SELF?>" method="post">
		<table width="100%">
		<tr>
		<td width="80">
		<p><?=$US['psetup-user']?></p>
		</td>
		<td>
		<input type="text" name="puser" value="<?=$ucontents[0]?>" />
		</td>
		</tr>
		<tr>
		<td width="80">
		<p><?=$US['psetup-pass']?></p>
		</td>
		<td>
		<input type="text" name="ppass" value="<?=$ucontents[1]?>" />
		</td>
		</tr>
		</table>
		<br />
		<input type="submit" name="submit" value="<?=$US['psetup-change']?>" />
		</form>
	</div>

<?
	fclose($tfile);
}

// Footer
include "includes/footer.php";
?>