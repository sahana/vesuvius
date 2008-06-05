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

if ($_POST['submit']) {

	function copyr($source, $dest) {
    		// Simple copy for a file
    		if (is_file($source)) {
        		return copy($source, $dest);
    		}

    		// Make destination directory
    		if (!is_dir($dest)) {
        		mkdir($dest);
    		}

    		// Loop through the folder
    		$dir = dir($source);
    		while (false !== $entry = $dir->read()) {
        		// Skip pointers
        		if ($entry == '.' || $entry == '..' || $entry == 'Thumbs.db') {
            		continue;
        		}

        		// Deep copy directories
        		if ($dest !== "$source/$entry") {
            		copyr("$source/$entry", "$dest/$entry");
        		}
    		}

    		// Clean up
    		$dir->close();
    		return true;
	}

	$source1 = $_POST['getlocate'];
	$dest1 = $_POST['destination'];

	//copyr($source1, $dest1);
?>

<div id="main">
<h2>&#187; <?=$US['smig-head']?></h2>
<h3><?=$US['smig-sub']?></h3>
<p><?=$US['smig-success']?><br /><?=$_POST['getlocate'];?></p>
</div>

<?
}

else {
?>

	<div id="main">
	<h2>&#187; <?=$US['smig-head']?></h2>
	<h3><?=$US['smig-sub']?></h3>
	<p><?=$US['smig-text-0']?></p>

	<p><?=$US['smig-text-1']?></p>
	<form action="<?=$PHP_SELF?>" method="post">
	<input type="hidden" value="/www/" name="destination" />
	<p>
	<?=$US['smig-www']?>
	<br />
	<input type="text" name="getlocate" />
	</p>
	<input type="submit" name="submit" value="Migrate" />
	</form>

	<p><?=$US['smig-text-2']?></p>
	<form action="<?=$PHP_SELF?>" method="post">
	<input type="hidden" value="/usr/local/mysql/data/" name="destination" />
	<p>
	<?=$US['smig-mysql']?>
	<br />
	<input type="text" name="getlocate" />
	</p>
	<input type="submit" name="submit" value="Migrate" />
	</form>
	</div>
<?
}

// Footer
include "includes/footer.php";
?> 