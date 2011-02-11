<?php
/**
 * Inclusion of Module Installer
 * @edit: Shree Kant Bohra <skbohra123@gmail.com>
 */

include_once 'inc_func.inc';
function shn_mm_module_mgr(){
	global $global,$conf;
	$db = $global['db'];
	$destination=  $global['approot'].'mod';
	echo "<h2>"._t("Module Manager")."</h2>";
	if (is_writeable($destination)) {
	 add_information(_t("Mod folder is writable!")); 
} else {
	
	add_error(_t("Cannot write to mod folder. Please check permissions first."));
}
	shn_form_fopen('install',null,array('enctype'=>'enctype="multipart/form-data"'));
	shn_form_upload(_t('Install Module'),"modulezip");
	shn_form_hidden(array('type'=>'zipped'));
	shn_form_submit(_t('Install'));   
	shn_form_fclose();
	echo "<h2>"._t('List of Available Modules')."</h2>";
	echo "<table><tr>";
	echo "<th>"._('Module')."</th>";
	//echo "<th>"._('Status')."</th>";
	echo "<th>"._('Status')."</th>";
        echo "<th>"._('Version')."</th>";
	echo "<th>"._('Actions')."</th>";
	echo "</tr>";
	$mod_dir = $global['approot']."mod";
	$mod_query = "SELECT module,status FROM modules";
	$res = $db->Execute($mod_query);
	$result_array = $res->GetAssoc();

	include_once $global['approot'].'inst/setup_utils.inc';
	$essencial_modules = _shn_setup_get_essencial_modules();

	if($dh = opendir($mod_dir)) {

		while (($file = readdir($dh)) !== false) {
			
			if(is_dir($mod_dir.'/'.$file)){
			
				if($file!='..' && $file!='.' && $file!='CVS' && preg_match('/^\.w+$/i',$file)==false){
					
					if(trim($result_array[$file])=='installed'  ||  trim($result_array[$file])=='disabled' )
					{
                                              echo "<tr>";
                                            echo "<td>".$conf['mod_'.$file.'_name']."</td>";
                                        echo "<td>".(($conf['mod_'.$file.'_enabled']!="False")?_t('Enabled'):_t('Disabled/NA'))."</td>";
                                         echo "<td>".$conf['mod_'.$file.'_version']."</td>";
						echo "<td><form action='index.php?mod=mm&act=uninstall' method='post' ><input type='hidden' name='type' value='unzipped'/><input type='hidden' name='module' value='$file'/><input class='imagebutton' type='image' src='res/img/uninstall.jpg' title='Uninstall This Module' value='Uninstall'/>Uninstall</form></td>";
                                                echo "</tr>";
                                                }
					else
					{
						//echo "<td><form action='index.php?mod=mm&act=install' method='post' ><input type='hidden' name='type' value='unzipped'/><input type='hidden' name='module' value='$file'/><input class='imagebutton' type='image' src='res/img/install.jpg' title='Install This Module' value='Install'/></form></td>";
					}								
				
				}
			}
		
		}
		closedir($dh);

	}
	echo "</table>";
}


function shn_mm_install_old(){
	global $global, $conf, $about;
	$db = $global['db'];
	echo "<h2>"._t("Module Manager")."</h2>";
	if($_REQUEST['type']=='unzipped')
	{
		$module = $_REQUEST['module'];
		$module_dir = $global['approot']."/mod/".$module;
		include_once($module_dir.'/about.inc');
		$nicename=$about['mod_'.$module.'_name'];
		$version=$about['mod_'.$module.'_version'];
		$author=$about['mod_'.$module.'_author'];
		$guid=$about['mod_'.$module.'_guid'];
		$sahanaver=$about['mod_'.$module.'_sahanaver'];
		$license=$about['mod_'.$module.'_license'];
		
		if($nicename && $version && $author && $guid && $guid && $sahanaver && $license)		
		{
			
			$dir_handle = @opendir($module_dir);
			$sqlfiles = array();
			$sqlfiles = list_dir($dir_handle, $module_dir);
		
			foreach($sqlfiles as $file)
			{
			 	if(file_exists($file)){
					if ($fh = fopen($file,'r')) {
						$sql=''; // clear the bucket
						while (! feof($fh) ) { // a fix as Execute gets confused over carriage returns
							$buffer = fgets($fh,1024); // read the script and fill the buffer
							$sql=$sql.$buffer; // fill the buffer until ';' appear
							if(preg_match('/;/',$buffer)) { // look after ';'
								$db->Execute($sql) or die (":(");
								$sql=''; // clear the bucket again
							}
						}
						fclose($fh);
					}
				}	  	 
			}
			
		$q = "INSERT INTO modules VALUES('$module','installed','','$version','$author','$guid','$sahanaver','$license')";			
		if($db->Execute($q))
		{
			add_confirmation(_t("Module Installed Successfully")); 
		}
		else{
			add_error(_t("Error Installing Module"));
		}
		
		}
		else
		{
			add_error(_t("Not a valid Sahana Module Package"));
		}
		
	}
	if($_REQUEST['type']=='web')
	{
		echo "Installation Manager for web based install";
	}
	else if($_REQUEST['type']=='zipped')
	{
		$filename = $_FILES['modulezip']['name'];
		$filename1= explode('.', $filename);
		$filename = $filename1[0];
		$path = $_FILES['modulezip']['tmp_name'];
	if(php_uname('s')=='Linux')
		$destination=  $global['approot'].'/mod/'.$filename.'/';
	else {
		$destination=  $global['approot'].'\\mod\\'.$filename.'\\';
	}
	
	$query = "SELECT * FROM modules WHERE module='$filename'";
	$result = $db->Execute($query);
	if(!$result->EOF){
			add_error(_t("Module already installed"));
	}
	else{
		if(!is_dir($destination))
	{
	

	if (file_exists($path)) {
    $validated=0;
    $files = array();
    $zip = new ZipArchive;
    if ($zip->open($path) === TRUE) {
        for($i = 0; $i < $zip->numFiles; $i++) {
        $entry = $zip->getNameIndex($i);
        $files[] = $entry;
        
       }
			$zip->extractTo($destination, $files);
			include_once($destination.'about.inc');
			$nicename=$about['mod_'.$filename.'_name'];
			$version=$about['mod_'.$filename.'_version'];
			$author=$about['mod_'.$filename.'_author'];
			$guid=$about['mod_'.$filename.'_guid'];
			$sahanaver=$about['mod_'.$filename.'_sahanaver'];
			$license=$about['mod_'.$filename.'_license'];
															
			if($nicename && $version && $author && $guid && $sahanaver && $license)
			{
				$validated=1;	
			}
		}
   }
	
	if($validated){
		chmod($destination, 0777);
		for($i=0;$i<=sizeof($files);$i++)
		{
			if(preg_match("/.sql/",$files[$i]))
			{
				chmod($files[$i], 0777);
				$script = $destination.$files[$i];
			 	if(file_exists($script)){
					if ($fh = fopen($script,'r')) {
						$sql=''; // clear the bucket
						while (! feof($fh) ) { // a fix as Execute gets confused over carriage returns
							$buffer = fgets($fh,1024); // read the script and fill the buffer
							$sql=$sql.$buffer; // fill the buffer until ';' appear
							if(preg_match('/;/',$buffer)) { // look after ';'
								$db->Execute($sql);
								$sql=''; // clear the bucket again
							}
						}
						fclose($fh);
					}
				}	  	 
			}
		}
		$sql = "INSERT INTO modules VALUES('$filename','installed','','$version','$author','$guid','$sahanaver','$license')";			
		$db->Execute($sql) or die("Error updating database");
		add_confirmation(_t("Module Installed Successfully")); 
		
	}
	else{	
			recursiveDelete($destination);
			add_error(_t("Not a valid module package"));
		
		}
	}
	else 
		{
			add_error(_t("Module directory already exist!"));
		}
	}	    	
}
}

function shn_mm_install()
{
    global $global;
    $type=$_REQUEST['type'];
    $filename=$_FILES['modulezip']["name"];
    $module=substr($filename,0,-4);
    move_uploaded_file($_FILES['modulezip']["tmp_name"],
    "tmp/mm_zip/" . $_FILES['modulezip']["name"]);
     shn_mm_zip_install($module) ;
    
}

function shn_mm_zip_install($module)
{
global $conf;
	global $global;
	$db=$global['db'];
	$zip = new ZipArchive();
	$file="tmp/mm_zip/$module.zip";
	$destination="..";
        $path="../mod/$module/sql/install";
        if ($zip->open($file) === TRUE && $module!="") {
		$zip->extractTo("../mod/");
		include_once "../mod/$module/conf.inc";
		$current_version= $conf['mod_'.$module.'_version'];
		if ($handle = opendir($path)) {

		/* This is the correct way to loop over the directory. */
		while (false !== ($file = readdir($handle))) {
		$file_address=$path."/".$file;
					 $lines=file($file_address);
					 foreach($lines as $line)
						$res = $db->Execute($line);
                    	}
               $zip->close();

		}
                $mod_query="insert into modules values('$module','installed','') ";
                $res = $db->Execute($mod_query);
                $mod_query="update mm_cache set status='available' where module_shortname='$module'";
                $db->Execute($mod_query) or die ("Error");
		closedir($handle);
		include_once "../mod/$module/conf.inc";
		$module_name=$conf['mod_'.$module.'_name'];
		add_confirmation(_t("Succesfully installed module ".$module_name));
		}
	 else {
		echo 'failed';
	}
}