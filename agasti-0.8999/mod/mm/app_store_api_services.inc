<?php
//include("xmlrpc.inc");
//include("xmlrpcs.inc");
/*
$v="";
$ar=array();
echo is_array($v)?"a":"b";
echo is_array($ar)?"c":"d";
//test();


//get_node_details("dsm");

//$x=getcontents("echo.getnid",array("cap"));
//print '<pre>'.htmlspecialchars(print_r($x, true)) .'</pre>';
//shn_mm_download("","");
*/


function shn_mm_services()
{
	echo 1;
	$x=getcontents("echo.getnid",array("cap"));
	print '<pre>'.htmlspecialchars(print_r($x, true)) .'</pre>';
	echo 2;


}


function getallviews($views)
{	
	foreach($views as $key_value=>$array_view)
	{
		if(is_array($array_view))
		{
			foreach($array_view as $key=>$view)
				{

				}
		}
		
	}
}



function getview()
{
	$domain = $_SERVER['SERVER_NAME'];
	$endpoint = 'http://localhost/dru/services/xmlrpc';   // end point has to be with servies/xmlrpc
	$method_name = 'views.get';
	$required_args=array("2",array());
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
		print '<h1>Error</h1>';
		trigger_error("xmlrpc: $response[faultString] ($response[faultCode])");
	} else {
		// let's look at what came back
		return $response;
	}
}


function getUniqueCode($length = "") {
  $code = md5(uniqid(rand(), true));
  if ($length != "") return substr($code, 0, $length);
  else return $code;
}

function getversion($module)
{




}

function getcontents($method_name,$required_args)
{
	$domain = $_SERVER['SERVER_NAME'];
	$endpoint = 'http://localhost/d/?q=services/xmlrpcr';   // end point has to be with servies/xmlrpc
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
		print '<h1>Error</h1>';
		trigger_error("xmlrpc: $response[faultString] ($response[faultCode])");
	} else {
		// let's look at what came back
		return $response;
	}
}

function get_node_id($module)
{
	$method_name = 'views.get';
	$required_args=array("2",array());
	$result=array();
	$result=getcontents($method_name,$required_args);
	foreach($result as $key_value=>$array_view)
	{
		$nid="";
		foreach($array_view as $key=>$view)
		{
			if($key=="nid")
			{
				$nid=$view;
			}
			if($view==$module &&  $key=="node_data_field_name_field_name_value")
			{
				return $nid;	
			}
		}
	}

}


function get_node_details($module)
{
	$method_name="node.get";
	$nid=get_node_id($module);
	$required_args=array($nid,array());
	$result=array();
	$result=getcontents($method_name,$required_args);
	//print '<pre>'.htmlspecialchars(print_r($result, true)) .'</pre>';
	$fields=array("nid","type","field_ver","files:filepath",);
	$final=get_node_value($result,$fields);
	print '<pre>'.htmlspecialchars(print_r($final, true)) .'</pre>';
}


function get_node_value($result,$fields)
{
	$values=array();
	foreach($result as $key=>$value)
		{	
			if(in_array($key,$fields))
			{
				$values[$key]=$value;
				if(is_array($value))
					{
						foreach($value as $key2=>$value2)
								{	
									foreach($value2 as $key3=>$value3)
										{
												if($key=="files")
													{
														if($key3=="filepath")
															{
																$values[$key]=$value3;
															}
													}
												else if($key=="field_ver")
													$values[$key]=$value3;
													
											//	echo $value3."<br>";
											
										}
								}
					}
			}
		}
	return $values;
}


function get_taxonomies()
{
	$method_name="node.get";
	$nid=get_node_id($module);
	$required_args=array($nid,array());
	$result=array();
	$result=getcontents($method_name,$required_args);



}



