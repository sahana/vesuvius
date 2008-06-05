<?
/*
####################################################
# Name: The Uniform Server Programming Code View
# Developed By: The Uniform Server Development Team
# Modified Last By: Olajide Olaolorun (empirex) 
# Web: http://www.uniformserver.com
####################################################
*/

if ($devmode == 1) {
	// Show Source Code Feature
	if ($_REQUEST['showcode']!=1) {
		echo '| <a href="'.$_SERVER['PHP_SELF'].'?showcode=1">'.$US['code-show'].'</a>';
	}

	else {	
		echo '<p>&nbsp;<p>';
		if($file=="")$file=$_SERVER['PHP_SELF'];
		$uscode=htmlentities(file_get_contents(basename($file)));
		echo "<h2>".$US['code-source']." | <a href=\"javascript: history.go(-1)\">".$US['code-back']."</a></h2> ";
		echo "<form><textarea cols=\"80\" rows=\"30\">";
		echo $uscode;
		echo "</textarea></form>";
	}
}
?>
