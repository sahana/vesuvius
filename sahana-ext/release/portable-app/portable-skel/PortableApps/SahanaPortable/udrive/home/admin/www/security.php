<?
/*
####################################################
# Name: The Uniform Server Security
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
	$AHandle = fopen($aphtpasswd, 'w');
	fwrite($AHandle, 'root:root');
	fclose($AHandle);
}

if ( !(file_exists($whtpasswd)) ) {
	$WHandle = fopen($whtpasswd, 'w');
	fwrite($WHandle, 'root:root');
	fclose($WHandle);
}

if ( !(file_exists($mysqlpwd)) ) {
	$SHandle = fopen($mysqlpwd, 'w');
	fwrite($SHandle, root);
	fclose($SHandle);
}

// Admin Panel's .htpasswd
	$tfile = fopen($aphtpasswd, "r");
	$fcontents = fgets($tfile);
	$ucontents = explode(":", $fcontents);	

// Private Server's .htpasswd
	$wfile = fopen($whtpasswd, "r");
	$pcontents = fgets($wfile);
	$pscontents = explode(":", $pcontents);

// mysql_password
	$mfile = fopen($mysqlpwd, "r");
	$scontents = fgets($mfile);

	fclose($tfile);
	fclose($wfile);
	fclose($mfile);
?>

	<div id="main">
		<h2>&#187; <?=$US['secure-head']?></h2>

		<h3><?=$US['secure-sub-0']?></h3>
		<p><?=$US['secure-text-0']?></p>
		
		<table width="100%">
			<tr>
				<td width="75%"><b><?=$US['secure-text-1']?></b></td>
				<td><b><?=$US['secure-text-2']?></b></td>
			</tr>
			<tr valign="top">
				<td width="75%"><p>
				<b><?=$US['secure-text-3']?></b>
				<br />
				<?=$US['secure-text-X']?>
				</p></td>
				<td><p>
				<? if (($ucontents[0] == "root") || ($ucontents[1] == "root")) { echo "<font color=\"red\"><a href=\"apsetup.php\">".$US['secure-unsecure']."</a></font>"; }
		   			else { echo "<font color=\"green\">".$US['secure-secure']."</font>"; }?>
				</p></td>
			</tr>
			<tr valign="top">
				<td width="75%"><p>
				<b><?=$US['secure-text-p']?></b> 
				<br />
				<?=$US['secure-text-X']?>
				</p></td>
				<td><p>
				<? if (($pscontents[0] == "root") || ($pscontents[1] == "root")) { echo "<font color=\"red\"><a href=\"psetup.php\">".$US['secure-unsecure']."</a></font>"; }
		   			else { echo "<font color=\"green\">".$US['secure-secure']."</font>"; }?>
				</p></td>
			</tr>
			<tr valign="top">
				<td width="75%"><p>
				<b><?=$US['secure-text-s']?></b> 
				<br />
				<?=$US['secure-text-7']?>
				</p></td>
				<td><p>
				<? if ($scontents == "root") { echo "<font color=\"red\"><a href=\"mqsetup.php\">".$US['secure-unsecure']."</a></font>"; }
		   			else { echo "<font color=\"green\">".$US['secure-secure']."</font>"; }?>
				</p></td>
			</tr>
		</table>

		<h3><?=$US['secure-sub-1']?></h3>
		<p><?=$US['secure-text-8']?></p>
		
		<table width="100%">
			<tr>
				<td width="75%"><b><?=$US['secure-text-1']?></b></td>
				<td><b><?=$US['secure-text-2']?></b></td>
			</tr>
			<tr valign="top">
				<td width="75%"><p>
				<b><?=$US['secure-view']?></b>
				<br />
				<?=$US['secure-look']?>
				</p></td>
				<td><p>
				<? if (getenv("REMOTE_ADDR") !== "127.0.0.1") { echo "<font color=\"red\">".$US['secure-unsecure']."</a>"; }
		   			else { echo "<font color=\"green\">".$US['secure-secure']."</font>"; }?>
				</p></td>
			</tr>
			<tr valign="top">
				<td width="75%"><p>
				<b><?=$US['secure-text-9']?></b>
				<br />
				<?=$US['secure-text-10']?>
				</p></td>
				<td><p>
				<? if (ini_get('safe_mode') == false) { echo "<font color=\"red\"><a href=\"pconfig.php\">".$US['secure-unsecure']."</a></font>"; }
		   			else { echo "<font color=\"green\">".$US['secure-secure']."</font>"; }?>
				</p></td>
			</tr>
<?
	$usfap = strpos(file_get_contents("$apanel_path/.htaccess"), '#Require valid-user');
	$usfps = strpos(file_get_contents("$server_path/.htaccess"), '#Require valid-user');
?>
			<tr valign="top">
				<td width="75%"><p>
				<b><?=$US['secure-text-11']?></b>
				<br />
				<?=$US['secure-text-13']?>
				</p></td>
				<td><p>
				<? if ($usfap === false) { echo "<font color=\"green\">".$US['secure-secure']."</font>"; }
		   			else { echo "<font color=\"red\">".$US['secure-unsecure']."</font>"; }?>
				</p></td>
			</tr>
			<tr valign="top">
				<td width="75%"><p>
				<b><?=$US['secure-text-12']?></b>
				<br />
				<?=$US['secure-text-14']?>
				</p></td>
				<td><p>
				<? if ($usfps === false) { echo "<font color=\"green\">".$US['secure-secure']."</font>"; }
		   			else { echo "<font color=\"red\">".$US['secure-unsecure']."</font>"; }?>
				</p></td>
			</tr>
		</table>
	</div>

<?
// Footer
include "includes/footer.php";
?>