<?php

function shn_mm_get_details($module="cap")
{
	$x=getcontents("echo.getnid",array("$module"));
	return  $x;
}
function shn_mm_get_module_details($module)
{
global $global;
global $conf;
$db=$global['db'];
        $mod_query = "SELECT module_name, module_version,module_filepath FROM mm_cache where module_shortname='$module' ";
	$res = $db->Execute($mod_query);
	$result_array = $res->GetAssoc();
        return $result_array;
}
function shn_mm_get_filepath($module="cap")
{
	$filepath_array=getcontents("echo.getnid",array("$module"));
	return  $filepath_array['filepath'];
}

function shn_mm_check_services()
{
	$echo_array=getcontents("echo.echo",array("check"));
	if($echo_array=="check")
		{
		return  "ok";
		}
	else
		{
		return "not";
		}

}

function getcontents($method_name,$required_args)
{
global $conf;
	include_once $global['approot']."mod/mm/conf.inc";
	$domain = $_SERVER['SERVER_NAME'];
 	$endpoint = $conf['app_store_url'];   // end point has to be with servies/xmlrpc
	$request = xmlrpc_encode_request(
	  $method_name, $required_args
	);
	$context = stream_context_create(
	  array(
		'http' => array(
		  'method' => "POST",
		  'header' => "Content-Type: text/xml",
		  'content' => $request,
		)
	  )
	);
	// connect
	$connect = file_get_contents($endpoint, false, $context);
	// retrieve the result
	$response = xmlrpc_decode($connect);
	// display the result on screen
	if (xmlrpc_is_fault($response)) {
		return "xmlrpc: $response[faultString] ($response[faultCode])";
	//	trigger_error("xmlrpc: $response[faultString] ($response[faultCode])");
	} else {
		// let's look at what came back
		return $response;
	}
}


function shn_mm_check_writable($destination="../mod")
{
    if (is_writeable($destination)) {
	 add_information(_t("Mod folder is writable!"));
        } else {

	add_error(_t("Cannot write to mod folder. Please check permissions first."));
}
}
function shn_mm_app_get_description($module)
{
    $temp_description=getcontents("node.view",array("$node",array("body"),"",""));
            print_r($temp_description);
            
}
