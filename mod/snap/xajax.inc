<?
/**
 * @name         Snapshot
 * @version      12
 * @package      snap
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0206
 */


global $global;

// create an array as it does not exist previosuly and will make warnings
$global['xajax_functions'] = array();

// publicly register accessible xajax funtions
array_push($global['xajax_functions'],'snap_dim');
array_push($global['xajax_functions'],'snap_append_log');
array_push($global['xajax_functions'],'snap_prepend_log');
array_push($global['xajax_functions'],'snap_show_message');
array_push($global['xajax_functions'],'snap_show_backups');
array_push($global['xajax_functions'],'snap_perform_backup');
array_push($global['xajax_functions'],'snap_perform_restore');
array_push($global['xajax_functions'],'snap_perform_delete');
array_push($global['xajax_functions'],'snap_perform_rename');


// dims the snapshotDiv while an action is being performed
function snap_dim() {
	global $global;
	$global['xajax_res']->addAssign('snapshots','style.opacity','0.2');
	return $global['xajax_res']->getXML();
}


// adds a message to the log div @ tail
function snap_append_log($message = "no message specified?") {
	global $global;
	$global['xajax_res']->addAppend('snapshotLog','innerHTML',$message);
	//---- scroll the log to the bottom
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'snapshotLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}


// adds a message to the log div @ head
function snap_prepend_log($message = "no message specified?") {
	global $global;
	$global['xajax_res']->addPrepend('snapshotLog','innerHTML',$message);
	return $global['xajax_res']->getXML();
}


// shows a status message before another ajax function is executed
function snap_show_message($message = "no message specified?") {
	global $global;
	$global['xajax_res']->addAssign('snapshots','innerHTML','<div class="loadingMessage" id="snapshotLoading"><center><blink>'.$message.'</blink></center></div>');
	return $global['xajax_res']->getXML();
}


// multidimensional array sort
function mSort( $array, $id="id" ) {
	$temp_array = array();
	while ( count( $array ) > 0 ) {
		$lowest_id = 0;
		$index = 0;
		foreach ( $array as $item ) {
			if ( isset( $item[$id] ) && $array[$lowest_id][$id] ) {
				if ( $item[$id] < $array[$lowest_id][$id] ) {
					$lowest_id = $index;
				}
                	}
			$index++;
		}
		$temp_array[] = $array[$lowest_id];
		$array = array_merge(array_slice($array, 0,$lowest_id), array_slice($array, $lowest_id+1));
	}
	return $temp_array;
}


// reloads the snapshotsDiv with information of what backups we already have saved as files
function snap_show_backups($internal = FALSE) {
	global $conf;
	global $global;
	$htmlLog = "";
	$htmlBackups = "";
	$extensionToLookFor = ".sql";
	$totalSize = 0;
        $count = 0;

	$dir = $conf['mod_snap_storage_location'];
	// add a trailing slash to the storage location in case someone forgot to put it there in the conf :D
	if (substr($dir, -1) != "/") {
		$dir .= "/";
	}
	$htmlLog .= "Snapshot Storage Location >>  <b>".$dir."</b><br>";

	//---- check read and write permissions on the backup folder
	$dirHandle = opendir($dir);
	$dirHandle2 = fopen($dir."testFilePermissions","w");

	//---- error on read permissions
	if (!$dirHandle) {
		$htmlLog .= "<b><span style=\"color: red;\">"._t("Snapshot-FolderError-Message|Unable to open storage folder. Please check that the folder exists and has read/write permission for the webserver.")."</span></b> <a href=\"javascript:window.location.reload();\">"._t("Snapshot-FolderError-Link|Check Again")."</a><br>";
		$permsError = TRUE;

	//---- error on write permissions
	} elseif (!$dirHandle2) {
		$htmlLog .= "<b><span style=\"color: red;\">"._t("Snapshot-FolderPermission-Message|Storage folder is not writeable by the webserver. Please correct its permissions.")."</span></b> <a href=\"javascript:window.location.reload();\">"._t("Snapshot-FolderPermission-Link|Check Again")."</a><br>";
		$permsError = TRUE;

	//---- read/write permissions are okay
	} else {
		$htmlLog .= _t("Snapshot-FolderOpen-Message|Storage folder is readable/writeable. Opening...")."<br>";
		$permsError = FALSE;
		fclose($dirHandle2);
	}

	// remove test file
	unlink($dir."testFilePermissions");

	//---- get backup file information
	$data = array();
	while ( $object = readdir($dirHandle) ) {
		$extension = substr( $object, -4, 4);
		$filename = $dir . $object;
		if ( filetype( $filename ) != "dir" && $object != "." && $object != ".." && $extension == $extensionToLookFor ) {
			$data[] = array('filename' => $object, 'size' => filesize($filename), 'type' => filetype($filename), 'time' => filemtime($filename) );
			$count++;
		}
	}

	//---- sort data and build html table
	$sortedData = msort($data, "filename");
	$htmlBackups .= "<table class=\"mainTable\"><tr><td style=\"padding-left: 8px;\" ><b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Filename (databaseName@date_time.sql)</b></td><td style=\"text-align: center;\" ><b>"._t("Snapshot-Operations-TableHeading|Rename")."</b></td><td style=\"text-align: center;\" ><b>"._t("Snapshot-Operations-TableHeading|Size")."</b></td><td style=\"text-align: center;\" ><b>"._t("Snapshot-Operations-TableHeading|Delete")."</b></td><td style=\"text-align: center;\"><b>"
				 ._t("Snapshot-Operations-TableHeading|Restore")."</b></td></tr>";
	if (($count == 0) || ($permsError)) {
		$htmlBackups .= "<tr><td colspan=5 class=\"mainRowEven\" style=\"text-align: center;\">No Backups</td></tr>";
	} else {
		$eo = 0; // even odd count
		foreach ( $sortedData as $row ) {
			if ( $eo == 0 ) {
				$evenOddClass = "mainRowEven";
			} else {
				$evenOddClass = "mainRowOdd";
			}
			$size = $row['size'];
                        $htmlBackups .= "<tr><td style=\"padding-left: 8px;\" class=\"".$evenOddClass."\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;". $row['filename'] ."</td>";

			$htmlBackups .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><a onclick=\"javascript: snap_append_log('"
						 ._t("Snapshot-Rename-Message|Renaming Snapshot ...")."<br>'); e = document.getElementById('newSnapshot'); e.disabled=true; snap_dim(); setTimeout('snap_perform_rename(\'".$row['filename']."\',prompt(\'"
						 ._t("Snapshot-Rename-Prompt|Please enter a new filename:")."\',\'".$row['filename']."\'));', 100);\">"
						 ._t("Snapshot-Rename-Link|Rename")."</a></td>";

			$htmlBackups .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\">". round( $row['size']/1000000, 4) ." MB</td>";

			$htmlBackups .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><a onclick=\"javascript: snap_append_log('"
						 ._t("Snapshot-Delete-Message|Deleting Snapshot ...")."<br>'); e = document.getElementById('newSnapshot'); e.disabled=true; snap_dim(); setTimeout('snap_perform_delete(\'".$row['filename']."\',confirm(\'"
						 ._t("Snapshot-Delete-Confirm|Are you sure you want to delete ").$row['filename']." ?\'));', 100);\">"
						 ._t("Snapshot-Delete-Link|Delete")."</a></td>";

			$htmlBackups .= "<td style=\"text-align: center;\" class=\"".$evenOddClass."\"><a onclick=\"javascript: snap_append_log('"
						 ._t("Snapshot-Restore-Message|Restoring Snapshot ...")."<br>'); e = document.getElementById('newSnapshot'); e.disabled=true;  snap_dim(); setTimeout('snap_perform_restore(\'".$row['filename']."\',confirm(\'"
						 ._t("Snapshot-Restore-Confirm|Are you sure you want to restore from the ").$row['filename']._t("Snapshot-Restore-Confirm|snapshot? Doing this will replace your current database with this snapshot.")."\'));', 100);\">"
						 ._t("Snapshot-Restore-Link|Restore")."</a></td></tr>";

			$eo++;
			$eo %= 2;
			$totalSize += $size;
		}
	}
	$totalSize /= 1000000; // find megabytes, not bytes :)
	$htmlBackups .= "
		<tr>
			<td class=\"justTop\">&nbsp;</td>
			<td class=\"justTop\">&nbsp;</td>
			<td class=\"justTop\" style=\"text-align: center;\"><b>". round($totalSize,2) ." MB total</b></td>
			<td class=\"justTop\">&nbsp;</td>
			<td class=\"justTop\">&nbsp;</td>
		</tr>
	";
	$htmlBackups .= "</table>";

	//---- internally, no ajax, just pass back data
	if ( $internal ) {
		$htmlLog .= "Found <b>".$count."</b> Snapshots.<br>";
		return $htmlBackups;
	} else {
		if ( $permsError ) {
			$global['xajax_res']->addScript("e = document.getElementById('newSnapshot'); e.disabled=true;");
		} else {
			$htmlLog .= _t("Snapshot-Found-Message|Found")." <b>".$count."</b> "._t("Snapshot-Found-Message|Snapshots.")."<br>";
		}
		$global['xajax_res']->addAppend('snapshotLog','innerHTML',$htmlLog);
		$global['xajax_res']->addAssign('snapshots','style.opacity','1.0');
		$global['xajax_res']->addAssign('snapshots','innerHTML',$htmlBackups);
		$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'snapshotLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
		return $global['xajax_res']->getXML();
	}
}


// backup the database to a file
function snap_perform_backup() {
	global $conf;
	global $global;
	include('class.SQLBackup.php');

	$db_host = $conf['db_host'].":".$conf['db_port'];
	$db_name = $conf['db_name'];
	$db_user = $conf['db_user'];
	$db_pass = $conf['db_pass'];

	$dir = $conf['mod_snap_storage_location'];
	// add a trailing slash to the storage location in case someone forgot to put it there in the conf :D
	if (substr($dir, -1) != "/") {
		$dir .= "/";
	}
	$outputFile = $dir . $db_name ."@". date("Ymd") ."_". date("Gis") .".sql";

	//---- TRUE == only tables' structure will be stored.
	//---- FALSE == tables' structure and all their data (everything) will be stored.
	$structure_only = FALSE;

	//---- instantiating object.
	$backup = new SQLBackup($db_user, $db_pass, $db_name, $db_host, $outputFile, $structure_only);

	//---- calling the backup method finally creates a sqldump into a file with the name specified in $outputFile
	$backup->backup();

	//--- update UI
	$global['xajax_res']->addScript("e = document.getElementById('newSnapshot'); e.disabled=false;");
	$global['xajax_res']->addAppend('snapshotLog','innerHTML',"Snapshot created: <b>".$db_name ."@". date("Ymd") ."_". date("Gis") .".sql</b><br>");
	$global['xajax_res']->addAssign('snapshots','style.opacity','1.0');
	$global['xajax_res']->addAssign('snapshots','innerHTML',snap_show_backups(TRUE));
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'snapshotLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}


// restore the database from a file
function snap_perform_restore($filename, $confirm) {
	global $global;
	global $conf;

	if ($confirm == "true") {
		global $conf;
		include('class.SQLBackup.php');

		$db_host = $conf['db_host'].":".$conf['db_port'];
		$db_name = $conf['db_name'];
		$db_user = $conf['db_user'];
		$db_pass = $conf['db_pass'];

		$dir = $conf['mod_snap_storage_location'];
		// add a trailing slash to the storage location in case someone forgot to put it there in the conf :D
		if (substr($dir, -1) != "/") {
			$dir .= "/";
		}
		$restoreFromFile = $dir . $filename;

		//---- this HAS TO BE the same value as what we used for backup
		$structure_only = FALSE;

		//---- instantiating object
		$backup = new SQLBackup($db_user, $db_pass, $db_name, $db_host, $restoreFromFile, $structure_only);

		//---- do the actual database restoration
		$backup->restore();
		$global['xajax_res']->addAppend('snapshotLog','innerHTML',_t("Snapshot-Log-Message|Database restored from Snapshot:")." <b>".$filename."</b><br>");
	} else {
		$global['xajax_res']->addAppend('snapshotLog','innerHTML',_t("Snapshot-Log-Message|Restore operation aborted.")."<br>");
	}

	//---- update UI
	$global['xajax_res']->addScript("e = document.getElementById('newSnapshot'); e.disabled=false;");
	$global['xajax_res']->addAssign('snapshots','style.opacity','1.0');
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'snapshotLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}


// delete a database backup file
function snap_perform_delete($filename, $confirm) {
	global $global;
	global $conf;

	if ($confirm == "true") {
		$dir = $conf['mod_snap_storage_location'];
		// add a trailing slash to the storage location in case someone forgot to put it there in the conf :D
		if (substr($dir, -1) != "/") {
			$dir .= "/";
		}
		//---- delete the snapshot file
		unlink($dir . $filename);
		$global['xajax_res']->addAppend('snapshotLog','innerHTML',"Database Snapshot: <b>".$filename." </b>deleted.<br>");
	} else {
		$global['xajax_res']->addAppend('snapshotLog','innerHTML',"Delete operation aborted.<br>");
	}

	//---- update UI
	$global['xajax_res']->addScript("e = document.getElementById('newSnapshot'); e.disabled=false;");
	$global['xajax_res']->addAssign('snapshots','style.opacity','1.0');
	$global['xajax_res']->addAssign('snapshots','innerHTML',snap_show_backups(TRUE));
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'snapshotLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}


// rename a database backup file
function snap_perform_rename($oldFilename, $newFilename) {
	global $global;
	global $conf;

	if ($newFilename != "" && $newFilename != NULL) {
		$extension = substr( $newFilename, -4, 4);
		if ( $extension != ".sql" ) {
			$newFilename .= ".sql";
		}

		$dir = $conf['mod_snap_storage_location'];
		// add a trailing slash to the storage location in case someone forgot to put it there in the conf :D
		if (substr($dir, -1) != "/") {
			$dir .= "/";
		}

		//---- rename the snapshot file
		rename($dir . $oldFilename, $dir . $newFilename);
		$global['xajax_res']->addAppend('snapshotLog','innerHTML',_t("Snapshot-Log-Message|Renamed Snapshot:")." <b>".$oldFilename." </b> to <b>".$newFilename."</b>.<br>");
	} else {
		$global['xajax_res']->addAppend('snapshotLog','innerHTML',_t("Snapshot-Log-Message|Rename operation aborted.")."<br>");
	}

	//---- update UI
	$global['xajax_res']->addScript("e = document.getElementById('newSnapshot'); e.disabled=false;");
	$global['xajax_res']->addAssign('snapshots','style.opacity','1.0');
	$global['xajax_res']->addAssign('snapshots','innerHTML',snap_show_backups(TRUE));
	$global['xajax_res']->addScript("setTimeout('e = document.getElementById(\'snapshotLog\'); e.scrollTop = e.scrollHeight+1000;', 500);");
	return $global['xajax_res']->getXML();
}
