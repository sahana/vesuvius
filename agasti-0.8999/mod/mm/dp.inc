<?php

function shn_mm_dp()
{
global $conf;
$module=$_REQUEST['module'];
$module_filepath=$_REQUEST['filepath'];
$version=$_REQUEST['version'];

	$arr=shn_mm_get_dependancy($module);
	include_once "../mod/$module/conf.inc";
	if($arr=="None" && $_REQUEST['module']!="")
	{
	add_confirmation(_t("Continue with Upgrade of module : ".$conf['mod_'.$module.'_name']));
	echo "<form action=\"?mod=mm&act=up\" method=post>";
	include_once "../mod/$module/conf.inc";
	echo "<input type='hidden' name='module' value='$module' ><br>";
	echo "<input type='hidden' name='version' value='$version'>";
	echo "<input type='hidden' name='filepath' value='$module_filepath'>";
	echo "<input type=submit value='proceed'></form>";
	}
	else if($_REQUEST['module']!="")
	{
		$mods=array();
		$count=0;
		foreach($arr as $mod)
		{
			$mods[$count]=$mod;
			$count++;
		}
		$i=0;
		while($i<$count)
		{
			
			$temp=shn_mm_get_dependancy($mods[$i]);
			if($temp=="None")
				{
				$i++;
				continue;
				}
				else
				{
					foreach($temp as $t)
					{
						if(!in_array($t,$mods))
						{
							$mods[$count]=$t;
							$count++;
							$i++;
						}
						else
							$i++;
					}
					
				}
				
		}
	
	require_once "../mod/$module/conf.inc";
	echo "<form action=\"?mod=mm&act=up2\" method=post>";
	echo "<h1> Module : ".$conf['mod_$module_name'] ." is dependant on following modules</h1>";
	$count=0;
//	/print_r($mods);
	foreach($mods as $mod)
	{
        $temp_info=get_detail($mod);
		$mod=$temp_info['name'];
                $upgrade_version=$temp_info['version'];
                $filepath=$temp_info['filepath'];
                require_once "../mod/$mod/conf.inc";
		$val=$conf['mod_'.$mod.'_name'];
		$upgrade_version=($upgrade_version=="")?"-1":$upgrade_version;
		$status=shn_mm_verify_upgrade($mod,$upgrade_version)?"yes":"no";  // returns false if upgrade required
		$status_message=($status=="no")?" Compatible with upgrade ":" Need to upgrade ";
		if($status=="yes")
		{
			echo "<input type='hidden' name='filepath[$count]' value='$filepath' >";
			echo "<input type='hidden' name='version[$count]' value='$upgrade_version'/>";
			echo "<input type='hidden' name='mods[$count]' value='$mod' >".$val."\t".$status_message."<br>";

			$count++;
		}	
		else
		{
			echo $val."\t".$status_message."<br>";
		
		}
	
//	shn_mm_module_upgrade_check($mods);
	}
	
	
	require_once "../mod/$module/conf.inc";
	echo "<br><h3>Need to update all above modules for updating module ".$conf['mod_$module_name'] ."</h3> Click proceed to continue with Update";
	echo "<input type='hidden' name='mods[$count]' value='$module' ><br>";
	echo "<input type='hidden' name='version[$count]' value='$version'>";
	echo "<input type='hidden' name='filepath[$count]' value='$module_filepath'>";
	echo "<input type=submit value='proceed'></form>";
	
	
	}
	
	else
	{
	add_error("Illegal access to this funtion");
	
	}
	

}

function get_detail($modules)
{
	$module=array();
$start_index=strpos($modules,"(");
$last_index=strpos($modules,")");
$module['version']=substr($modules,$start_index+1,$last_index-$start_index-1);
$module['name']=substr($modules,"0",$start_index);
$result_array=shn_mm_get_module_details($module['name']);
$module['filepath']=$result_array[$module['name']]['module_filepath'];
return $module;

}
function shn_mm_verify_upgrade_module($module)
{
	$upgrade_info=shn_mm_get_details($module);
	$upgrade_version=$upgrade_info['version'];
	$upgrade_version=($upgrade_version=="")?"-1":$upgrade_version;
	return shn_mm_verify_upgrade($module,$upgrade_version);
}


function shn_mm_module_upgrade_check($modules)
{
	shnp($modules);
}


function shn_mm_get_all_dependancy($module)
{

}

function shnp($arr)
{
	foreach($arr as $elements)
		echo $elements;
}


function shn_mm_update_step2()
{
$modules=$_POST['modules'];
foreach($modules as $module)
	shn_mm_change_conf($module);

}






