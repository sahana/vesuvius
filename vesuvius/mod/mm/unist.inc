<?php
/**
 * Inclusion of Module Uninstaller
 * @edit: Shree Kant Bohra <skbohra123@gmail.com>
 */

 
include_once 'inc_func.inc';
function shn_mm_uninstall(){
	global $conf, $global;
        $db=$global['db'];
	$module = $_REQUEST['module'];
        echo "<h2>"._t("Module Manager")."</h2>";
	switch ($_REQUEST['ans'])
	{
		case '':
		include_once($global['approot']."/mod/".$module."/conf.inc");
		$nicename=$conf['mod_'.$module.'_name'];
		$version=$conf['mod_'.$module.'_version'];
		$author=$conf['mod_'.$module.'_author'];
		$guid=$conf['mod_'.$module.'_guid'];
		$sahanaver=$conf['mod_'.$module.'_sahanaver'];
		$license=$conf['mod_'.$module.'_license'];
		add_warning("Module once uninstalled can't be restored");
		echo "<h3>"._t("About this Module:")."</h3>";
		echo "Name:".$nicename."<br/>";
		echo "Version:".$version."<br/>";
		echo "Auhtor:".$author."<br/>";
		echo "License:".$license."<br/>";
		echo _t("Are you sure want to uninstall this module?");
		shn_form_fopen("uninstall",null,array('req_message'=>false));
		shn_form_hidden(array('ans'=>'yes','module'=>$module));
		shn_form_submit(_t("Yes"));
		shn_form_fclose();
							
		break;	
		case 'yes':
                {
                    $module=$_REQUEST['module'];
                    $path=$global['approot']."/mod/".$module;
                if($module != null && $module !="")
		{
                    recursiveDelete($path);
                    $q = "DELETE FROM modules WHERE module='$module'";
                    $db->Execute($q) or die ("Error");
                    $mod_query="update mm_cache set status='available' where module_shortname='$module'";
                    $db->Execute($mod_query) or die ("Error");
                    add_confirmation(_t("Module Deleted Successfully"));
                    break;
                }
                }
	}
	
}



