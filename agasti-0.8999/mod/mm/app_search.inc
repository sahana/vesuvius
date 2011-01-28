<?php


function shn_mm_search_box()
{
	shn_form_fopen('search',null, array('req_message'=>false));
	shn_form_fsopen(_('Search in App Store '));
	shn_form_text(_('Search  : '),'search','',array('req'=>true, 'value'=>$_SESSION['search']));
	echo "enter the keywords to search for in App Store .<br>";
	shn_form_submit(_('Submit'));
	shn_form_fsclose();
	shn_form_fclose();
}

function shn_mm_search()
{
global $global;
global $conf;
include_once  $global['approot']."mod/mm/conf.inc";;
include_once $global['approot']."/inc/lib_form.inc";
$db=$global['db'];
	$search_text=$_REQUEST['search'];
	if($search_text=="")
	{
		shn_mm_search_box();
		add_error(_t("Please enter search keywords before submit ."));	
				
	}
	else
	{
		$x=getcontents("search.nodes",array("$search_text","node",array("link","title")));
		//print '<pre>'.htmlspecialchars(print_r($x, true)) .'</pre>';

   $results=array();
   $count=0;
   if(!empty($x) && !preg_match("/xmlrpc/i",$x))
   {
	    $temp="";
		$separator="";
       foreach($x as $arr)
       {
          $temp.=$separator.$arr['node'];
		  $separator=",";
           $count++;
       }
      add_confirmation(_t("Your search returned $count results :"));
   $results=getcontents("echo.getnid_detail",array($temp));
   
 //  print '<pre>'.htmlspecialchars(print_r($results, true)) .'</pre>';
   foreach($results as $result)
       {
                        // this is just dummy form opening 
                        shn_form_fopen('',null, array('req_message'=>false));
                        $title=$result['module_name'];
                        shn_form_fsopen(_("$title"));
			$module_short_name=$result['module_short_name'];
			$module_version=$result['module_version'];
			$module_dependancy=$result['module_dependancy'];
			$node=$result['module_node_id'];
			$url=$conf['app_store_file_url']."?q=node/$node";
			$filepath=$result['module_filepath'];
                        $temp_description=getcontents("node.view",array("$node",array("body"),"",""));
                        $description=$temp_description['body'];
                        echo "Title : $title  <br>";
                        echo "Short name: $module_short_name <br>";
			echo "Module version : $module_version <br>";
			echo "Description : $description <br>";
			echo "Dependancy : $module_dependancy <br>";
			echo "Link to Sahana App store : <a href='$url'> here </a><br>";
			echo "<br>";
                        // 
                        $mod_query = "SELECT module,count(*) as count FROM modules  where module='$module_short_name'";
                        $res = $db->Execute($mod_query);
                        $result_array = $res->GetAssoc();
                        $count=$result_array["$module_short_name"];
                        if($count>0)
                        {
                            include_once $global['approot']."mod/$module_short_name/conf.inc";
                            $current_version= $conf['mod_'.$module_short_name.'_version'];
                            $upgrade_version=$module_version;
                            if(compare_version($upgrade_version, $current_version))
                            {
                                shn_form_fopen('dp',null, array('req_message'=>false));
                                shn_form_hidden(array('version'=>"$module_version","module"=>"$module_short_name","filepath"=>"$filepath"));
                                shn_form_submit(_('Upgrade this module '));
                                shn_form_fclose();
                                }
                                else
                                {
                                    echo "<br>This module is already installed <br>";
                                }
                        }
                        else
                        {
                            shn_form_fopen('search_install',null, array('req_message'=>false));
                            shn_form_hidden(array('nodeid'=>"$node","module_short_name"=>"$module_short_name","module_filepath"=>"$filepath"));
                            shn_form_submit(_('Install '));
                        }
                        shn_form_fsclose();
                        shn_form_fclose();
       }
    }
   
   else
   {
	
	add_warning(_t("Your search returned zero results. Please try again with different keywords. "));	
	shn_mm_search_box();
	
   
   }

}
}

function shn_mm_search_install()
{
    $nodeid=$_REQUEST['nodeid'];
    $module_short_name=$_REQUEST['module_short_name'];
    $module_filepath=$_REQUEST['module_filepath'];
    shn_mm_download($module_short_name, $module_filepath);
    shn_mm_zip_install($module_short_name);
}