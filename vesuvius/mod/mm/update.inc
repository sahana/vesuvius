<?php

function shn_mm_update()
{
global $global,$conf;
	$db = $global['db'];
	$destination=  $global['approot'].'mod';
	if (is_writeable($destination)) {
	 add_information(_t("Mod folder is writable!")); 
} else {
	
	add_error(_t("Cannot write to mod folder. Please check permissions first."));
}
	echo "<h2>"._t('List of Available Modules')."</h2>";
	echo "<table><tr>";
	echo "<th>"._('Module')."</th>";
	echo "<th>"._('Status')."</th>";
	echo "<th>"._('Actions')."</th>";
	echo "</tr>";
	$mod_dir = $global['approot']."mod";
	$mod_query = "SELECT module,status FROM modules ";
	$res = $db->Execute($mod_query);
	$result_array = $res->GetAssoc();

	include_once $global['approot'].'inst/setup_utils.inc';
	$essencial_modules = _shn_setup_get_essencial_modules();

	if($dh = opendir($mod_dir)) {
echo "<form action='index.php?mod=mm&act=update_step2' method='post' >";
		while (($file = readdir($dh)) !== false) {
			
			echo "<tr>";
			if(is_dir($mod_dir.'/'.$file)){
			
				if($file!='..' && $file!='.' && $file!='CVS' && preg_match('/^\.w+$/i',$file)==false){
				if((trim($result_array[$file])=='installed')||trim(($result_array[$file])=='disabled'))
					{
					echo "<td>".$conf['mod_'.$file.'_name']."</td>";
					echo "<td>".(($conf['mod_'.$file.'_enabled']!="False")?_t('Enabled'):_t('Disabled/NA'))."</td>";
								echo "<td><input name='modules[]' type='checkbox' value='$file'/>".(($conf['mod_'.$file.'_enabled']=='False')?_t('Enable'):_t('Disable'))."</td>";
					}
					else
					{
						//option not available as module is disabled
					}								
				
				}
			}
		echo "</tr>";
		}
		
		echo "</table>";
		echo "<input type='submit' value='Save Configuration'>";
		echo "</form>";
		closedir($dh);

	}
	
}