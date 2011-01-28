<?php

function shn_mm_upgrade()
{
    shn_mm_update_cache();
shn_mm_check_writable();
global $global;
global $conf;
$db=$global['db'];
echo "<h2>"._t('List of Available Upgrades for Modules')."</h2>";
	echo "<table><tr>";
	echo "<th>"._('Module')."</th>";
	//echo "<th>"._('Status')."</th>";
	echo "<th>Current version</th>";
	echo "<th>Version available</th>";
	echo "<th>"._('Actions')."</th>";
	echo "</tr>";
	$mod_dir = $global['approot']."mod";
	$mod_query = "SELECT module,status FROM modules  ";
	$res = $db->Execute($mod_query);
	$result_array = $res->GetAssoc();
        include_once $global['approot'].'inst/setup_utils.inc';
	if($dh = opendir($mod_dir)) {
		while (($file = readdir($dh)) !== false) {
			
			if(is_dir($mod_dir.'/'.$file))
			{
				if($file!='..' && $file!='.' && $file!='CVS' && preg_match('/^\.w+$/i',$file)==false)
				{
					$upgrade_info=shn_mm_get_module_details($file);
                                        $upgrade_info=$upgrade_info["$file"];
                                        $upgrade_version=$upgrade_info['module_version'];
                                        $upgrade_version=($upgrade_version=="")?"-1":$upgrade_version;
					include_once $global['approot']."mod/mm/conf.inc";
					$current_version= $conf['mod_'.$file.'_version'];
					$current_version=$current_version=$current_version==""?"0":$current_version;
					$module_name=$conf['mod_'.$file.'_name'];
                                        $filepath=$upgrade_info['module_filepath'];
                                        if( (strcasecmp(trim($result_array[$file]), 'installed') || strcasecmp(trim($result_array[$file]), 'disabled')) && $module_name!="" )  // trim(($result_array[$file])!='disabled'))
					{
                                            if(compare_version($upgrade_version,$current_version))
                                            {
                                                echo "<tr>";
						echo "<td>".$module_name."</td>";
						echo "<td>".($current_version=="0"?"Version not defined":$current_version)."</td>";
						echo "<td>".($upgrade_version=="-1"?"Version not defined":$upgrade_version)."</td>";
						echo "<td>
						<form action='index.php?mod=mm&act=dp' method='post' >
						<input type='hidden' name='type' value='unzipped'/>
						<input type='hidden' name='module' value='$file'/>
						<input type='hidden' name='filepath' value='$filepath'/>
						<input type='hidden' name='version' value='$upgrade_version'/>
						<input class='imagebutton' type='image' src='res/img/upgrade.jpg' title='Deactivate This Module' value='update'/>
						</td></form>";
                                                echo "</tr>";
						
                                               }
                                                else
                                                {
                                                        echo "<tr>";
                                                        echo "<td>".$module_name."</td>";
                                                        echo "<td>".($current_version=="0"?"Version not defined":$current_version)."</td>";
                                                        echo "<td>".($upgrade_version=="-1"?"Version not defined":$upgrade_version)."</td>";
                                                        echo "<td>No need to upgrade</td>";
                                                        echo "</tr>";


                                                }
                                        }
                                        else
                                        {
                                            //
                                        }
				}
			}
		
		}
		closedir($dh);

	}
	echo "</table>";
}
function shn_mm_up($module="None",$filepath,$version)
{
global $global;
global $conf;
if($module=="None")
{
	$module=$_REQUEST['module'];
	$filepath=$_REQUEST['filepath'];
	$version=$_REQUEST['version'];
}
else
{
// module value is the parameter value
}
include_once $global['approot']."mod/$module/conf.inc";
$current_version= $conf['mod_'.$module.'_version'];
$bool=shn_mm_verify_upgrade($module,$version);
if($bool && $module!="" && $module!="None")
{
	shn_mm_download($module,$filepath);
        module_backup($module);
        recursiveDelete("../mod/".$module);
	shn_mm_unzipit($module,$current_version);
}
else
{
	add_confirmation(_t("$module Module already at its latest version"));
}
}


function shn_mm_up2()
{
	$mods = array();
	$filepath=array();
	$version=array();
	$mods=$_REQUEST['mods'];
	$filepath=$_REQUEST['filepath'];
        $version=$_REQUEST['version'];
	$count=0;
	foreach($mods as $mod)
	{
	//echo $mod." ".$filepath[$count]." ".$version[$count];
	shn_mm_up($mod,$filepath[$count],$version[$count]);
		$count++;
	}
}



function shn_mm_download($module,$filepath)
{
	global $global;
	global $conf;
	include_once $global['approot']."mod/mm/conf.inc";
	$app_store_url=$conf['app_store_file_url'];
	$destination= $filepath;                                     // shn_mm_get_filepath($module)  ;  // get filepath
	$target_url = $app_store_url.$destination;
	$userAgent = 'Googlebot/2.1 (http://www.googlebot.com/bot.html)';
	$file_zip = "$module.zip";
	$file_txt = "new.txt";
	//echo "<br>Starting<br>Target_url: $target_url<br><br>";
	// make the cURL request to $target_url
	$ch = curl_init();
	$fp = fopen("tmp/mm_zip/$file_zip", "w");
	curl_setopt($ch, CURLOPT_USERAGENT, $userAgent);
	curl_setopt($ch, CURLOPT_URL,$target_url);
	curl_setopt($ch, CURLOPT_FAILONERROR, true);
	curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
	curl_setopt($ch, CURLOPT_AUTOREFERER, true);
	curl_setopt($ch, CURLOPT_BINARYTRANSFER,true);
	curl_setopt($ch, CURLOPT_TIMEOUT, 100);
	curl_setopt($ch, CURLOPT_FILE, $fp);
	$page = curl_exec($ch);
}


function shn_mm_verify_upgrade($module,$upgrade_version)
{

	global $global;
	global $conf;
	include_once "../mod/$module/conf.inc";
	$current_version= $conf['mod_'.$module.'_version'];
	$current_version=$current_version==""?"0":$current_version;
	if(compare_version($upgrade_version,$current_version) && $current_version!="") 
	{
		
		return true;
	}
	else
	{
		return false;
	}


}


// this function unzips the package and performs the upgrade of the sql 
function shn_mm_unzipit($module,$current_version)
{
	global $conf;
	global $global;
	$db=$global['db'];
	$zip = new ZipArchive();   
	$file="temp/$module.zip";
	$destination="..";
	if ($zip->open($file) === TRUE && $module!="") {
		$zip->extractTo("../mod/");
		if ($handle = opendir($destination."/mod/$module/sql/upgrade")) {
	  
		/* This is the correct way to loop over the directory. */
		while (false !== ($file = readdir($handle))) {
               if(compare_version(ver($file),$current_version))
		{
		 $file_address="../mod/$module/sql/upgrade/$file";
					 $lines=file($file_address);
					 foreach($lines as $line)
						$res = $db->Execute($line);
		
			}
			}
	 
		closedir($handle);
		
		$zip->close();
		
		}
		include_once "../mod/$module/conf.inc";
		$module_name=$conf['mod_'.$module.'_name'];
		add_confirmation(_t("Succesfully upgraded module ".$module_name));
		}
	 else {
		echo 'failed';
	}
}




function ver($file)
{

return substr($file,1,-4); // assuming the file name to be v3.2.5.sql where 3.2.5 is the version of the module
}


function compare_version($upgrade,$current)
{
if($upgrade==$current)
	return false;

$var3=explode(".",$upgrade);
$var4=explode(".",$current);

$count=count($var3)>count($var4)?count($var4):count($var3);
if($count==1)
{
		if($upgrade>$current)
			return true;
		else
		{
			return false;
		}
	

}
$sentinal=0;
while($sentinal<$count)
{
	if($var3[$sentinal]>$var4[$sentinal])
		{
		return true;
		
		}
		else if($var3[$sentinal]<$var4[$sentinal])
		{
		return false;
		}
		else{
			$sentinal++;
			if($sentinal==$count)
				return (count($var3)>count($var4)?true:false);
			continue;
		}
		
	

	}
}


function shn_mm_check_dependancy($module)
{
	/*
	check the array of dependancy from conf file
	compare each with the current version  of dependancy available

	suggest dependancy upgrade if required
	*/
}

function shn_mm_conf_value($module,$value)
{

global $global;
$db=$global['db'];
$mod_query = "SELECT module,$value FROM mm_conf where module='$module' ";
	$res = $db->Execute($mod_query);
	$result_array = $res->GetAssoc();
	$ans=trim($result_array[$module]);
return $ans;


}

function shn_mm_get_dependancy($module)
{
global $global;
$db=$global['db'];
	$mod_query = "SELECT module_shortname,module_dependancy FROM mm_cache where module_shortname='$module' ";
	$res = $db->Execute($mod_query);
        $result_array = $res->GetAssoc();
	$ans=trim($result_array[$module]);
	if($ans=="")
		return "None";
	$arr=split(":",$ans);
	return $arr;


}
