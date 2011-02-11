<?php

function shn_mm_update()
{
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
			
			echo "<tr>";
			if(is_dir($mod_dir.'/'.$file)){
			
				if($file!='..' && $file!='.' && $file!='CVS' && preg_match('/^\.w+$/i',$file)==false){
					echo "<td>".$conf['mod_'.$file.'_name'].' mod_'.$file.'_enabled'."</td>";
					echo "<td>".(($conf['mod_'.$file.'_enabled']==true)?_t('Enabled'):_t('Disabled'))."</td>";
					if(trim($result_array[$file])=='installed')
					{
						echo "<td><form action='index.php?mod=mm&act=uninstall' method='post' ><input type='hidden' name='type' value='unzipped'/><input type='hidden' name='module' value='$file'/><input class='imagebutton' type='image' src='res/img/uninstall.png' title='Uninstall This Module' value='Uninstall'/></form></td>";
					}
					else
					{
						echo "<td><form action='index.php?mod=mm&act=install' method='post' ><input type='hidden' name='type' value='unzipped'/><input type='hidden' name='module' value='$file'/><input class='imagebutton' type='image' src='res/img/install.png' title='Install This Module' value='Install'/></form></td>";
					}								
				
				}
			}
		echo "</tr>";
		}
		closedir($dh);

	}
	echo "</table>";
}