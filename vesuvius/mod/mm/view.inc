<?php


function shn_mm_app_store_modules()
{
     shn_mm_update_cache('available');
     echo "<h1>Modules on App store </h1>";
    global $global;
    global $conf;
    $db=$global['db'];
    $mod_query="SELECT id, module_shortname, module_name,module_description, module_version,module_filepath,
                module_node_id,module_dependancy, time_stamp FROM mm_cache where (module_shortname not in (select module from modules )) ORDER BY id ASC";
    $res = $db->Execute($mod_query);
    $result_array = $res->GetAssoc();
    $count=sizeof($result_array);
    if($count>0)
    {
    foreach($result_array as $result)
    {
                        shn_form_fopen('search_install',null, array('req_message'=>false));
                        $title=$result['module_name'];
                        shn_form_fsopen(_("$title"));
			$module_short_name=$result['module_shortname'];
			$module_version=$result['module_version'];
			$module_dependancy=$result['module_dependancy'];
			$node=$result['module_node_id'];
			$url=$conf['app_store_file_url']."?q=node/$node";
			$description=$result['module_description'];
                        $time_stamp=$result['time_stamp'];
                        $filepath=$result['module_filepath'];
                        echo "Title : $title  <br>";
                        echo "Short name: $module_short_name <br>";
			echo "Module version : $module_version <br>";
			echo "Description : $description <br>";
			echo "Dependancy : $module_dependancy <br>";
			echo "Link to Sahana App store : <a href='$url'> here </a><br>";
                        echo "Cache last updated on : ".$time_stamp;
			echo "<br>";
                        shn_form_hidden(array('nodeid'=>"$node","module_short_name"=>"$module_short_name","module_filepath"=>"$filepath"));
                        shn_form_submit(_('Install '));
                        shn_form_fsclose();
                        shn_form_fclose();

       }

    }
    else
    {
        echo "Cache has no data .Please go to App store settings on the App Store submenu on the left  and click on refresh cache";
    }
}



function shn_mm_view_cache()
{
    echo "<h1>Modules on App store </h1>";
    global $global;
    global $conf;
    $db=$global['db'];
    $mod_query="SELECT id, module_shortname, module_name,module_description, module_version,
                module_node_id,module_dependancy, time_stamp FROM mm_cache where status='installed' ORDER BY id ASC";
    $res = $db->Execute($mod_query);
    $result_array = $res->GetAssoc();
    $count=sizeof($result_array);
    if($count>0)
    {
    foreach($result_array as $result)
    {
                        shn_form_fopen('',null, array('req_message'=>false));
                        $title=$result['module_name'];
                        shn_form_fsopen(_("$title"));
			$module_short_name=$result['module_shortname'];
			$module_version=$result['module_version'];
			$module_dependancy=$result['module_dependancy'];
			$node=$result['module_node_id'];
			$url=$conf['app_store_file_url']."?q=node/$node";
			$description=$result['module_description'];
                        $time_stamp=$result['time_stamp'];
                        echo "Title : $title  <br>";
                        echo "Short name: $module_short_name <br>";
			echo "Module version : $module_version <br>";
			echo "Description : $description <br>";
			echo "Dependancy : $module_dependancy <br>";
			echo "Link to Sahana App store : <a href='$url'> here </a><br>";
                        echo "Cache last updated on : ".$time_stamp;
			echo "<br>";
                        shn_form_fsclose();
                        shn_form_fclose();
       }

    }
    else
    {
        echo "Cache has no data .Please go to App store settings on the App Store submenu on the left  and click on refresh cache";
    }
}